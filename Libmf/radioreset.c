#include "libmfradio.h"

/**
 * \brief delay (busy waiting)
 *
 */
static void delay(uint16_t us)
{
	us;
	__asm
	mov	a,dpl
	jz	00002$
	inc	dph
00002$:	nop
	nop
00000$:	mov	a,#3
00001$:	djnz	acc,00001$
	djnz	dpl,00002$
	djnz	dph,00000$
	ret
	__endasm;
}

static uint8_t radio_wakeup_deepsleep_core(void)
{
	uint8_t i = 3, j = 0;
	PORTR &= (uint8_t)~0x08;
	do {
		do {
			// precharge
			DIRR |= 0x08;
			DIRR &= (uint8_t)~0x08;
			PORTR &= (uint8_t)~1;
			if (PINR & 0x08) {
				i = 0;
				goto dswakeup;
			}
			PORTR |= 1;
		} while (--j);
	} while (--i);
	i = RADIO_ERR_WAKEUPTIMEOUT;
  dswakeup:
	PORTR |= 0x09;
	RADIOMUX = 0x47;
	return i;
}

uint8_t res = 0;
uint8_t radio_reset(void)
{
	// Initialize Interface
	DIRR = 0x15;
	PORTR = 0xEB;
#if DEEPSLEEP
	RADIOMUX = 0x07;
#else
	RADIOMUX = 0x47;
#endif
	RADIOACC = RACC;
	GPIOENABLE = 1;
#if defined SDCC
	RADIOFDATAADDR = FDATA;
	RADIOFSTATADDR = FSTAT;
#else
	RADIOFDATAADDR0 = (FDATA) & 0xFF;
	RADIOFDATAADDR1 = (FDATA) >> 8;
	RADIOFSTATADDR0 = (FSTAT) & 0xFF;
	RADIOFSTATADDR1 = (FSTAT) >> 8;
#endif
#if DEEPSLEEP
	// Ensure Device is not in Deep Sleep
	radio_wakeup_deepsleep_core();
#endif
	// Reset Device
	RADIO_PWRMODE = 0x80;
	RADIO_PWRMODE = PWRMODE_PWRDOWN;
	// Wait some time for regulator startup
#if defined(VREGDELAY) && VREGDELAY > 0
	delay(VREGDELAY);
#endif
	// Check Scratch
	res = RADIO_SILICONREVISION;
	res = RADIO_SILICONREVISION;
#ifdef SILICONREV2
	if (i != SILICONREV1 && i != SILICONREV2)
		return RADIO_ERR_REVISION;
#else
	if (res != SILICONREV1)
		return RADIO_ERR_REVISION;
#endif
	RADIO_SCRATCH = 0x55;
	if (RADIO_SCRATCH != 0x55)
		return RADIO_ERR_COMM;
	RADIO_SCRATCH = 0xAA;
	if (RADIO_SCRATCH != 0xAA)
		return RADIO_ERR_COMM;
	// Initialize Radio Interface Registers
#if RADIO == 5031
#elif RADIO == 5042
	AX5042_IFMODE = 0x00;
	AX5042_AGCTARGET = 0x0E;
	AX5042_PLLRNGMISC = 0x01;
	AX5042_RXMISC = 0x35;
#elif RADIO == 5043
#elif RADIO == 5051
	AX5051_IFMODE = 0x00;
	AX5051_PLLVCOI = 0x01;
	AX5051_RXMISC = 0x35;
#endif
    res = radio_probeirq();
	if (res) return RADIO_ERR_IRQ;
	return RADIO_OK;
}

#if RADIO == 5031

 uint8_t ax5031_probeirq(void)
{
	res = 0x60;
	uint8_t pc1 = AX5031_PINCFG1 & 0x0F;
	uint8_t iesave = IE;
	IE_4 = 0;
	PORTR = 0xEB;
	AX5031_PINCFG1 = pc1;
	AX5031_PINCFG2 = 0x22; /* IRQ Line 1 */
	res &= PINR;
	AX5031_PINCFG2 = 0x20; /* IRQ Line 0 */
	res &= (uint8_t)~PINR;
	AX5031_PINCFG2 = 0x00;
	switch (res) {
	case 0x20: /* IRQ on PR5 */
		RADIOMUX &= (uint8_t)~0x08;
		break;

	case 0x40: /* IRQ on PR6 */
		RADIOMUX |= 0x08;
		break;

	default:
		/* Error */
		AX5031_PINCFG1 = 0x20 | pc1; /* Disable IRQ line */
		IE = iesave;
		return 1;
	}
	PORTR &= (uint8_t)~res; /* disable pullup */
	IE = iesave;
	return 0;
}

#elif RADIO == 5042

 uint8_t ax5042_probeirq(void)
{
	res = 0x60;
	uint8_t pc1 = AX5042_PINCFG1 & 0x0F;
	uint8_t iesave = IE;
	IE_4 = 0;
	PORTR = 0xEB;
	AX5042_PINCFG1 = 0xD0 | pc1;
	AX5042_PINCFG2 = 0xE2; /* IRQ Line 1 */
	res &= PINR;
	AX5042_PINCFG2 = 0xE0; /* IRQ Line 0 */
	res &= (uint8_t)~PINR;
	AX5042_PINCFG2 = 0xC0;
	switch (res) {
	case 0x20: /* IRQ on PR5 */
		RADIOMUX &= (uint8_t)~0x08;
		break;

	case 0x40: /* IRQ on PR6 */
		RADIOMUX |= 0x08;
		break;

	default:
		/* Error */
		AX5042_PINCFG1 = 0xF0 | pc1; /* Disable IRQ line */
		IE = iesave;
		return 1;
	}
	PORTR &= (uint8_t)~res; /* disable pullup */
	IE = iesave;
	return 0;
}

#elif RADIO == 5043

SFRX(RADIODRV,        0x7045)

 uint8_t ax5043_probeirq(void)
{
	uint8_t iesave = IE;
	res = 0x60;
	IE_4 = 0;
	PORTR &= 0xEB;
	PORTR |= 0x2B;
	AX5043_PINFUNCIRQ = 0x01; /* IRQ Line 1 */
	res &= PINR;
	AX5043_PINFUNCIRQ = 0x00; /* IRQ Line 0 */
	res &= (uint8_t)~PINR;
	AX5043_PINFUNCIRQ = 0x03;
	switch (res) {
	case 0x20: /* IRQ on PR5 */
		RADIOMUX &= (uint8_t)~0x08;
		break;

	case 0x40: /* IRQ on PR6 */
		RADIOMUX |= 0x08;
		break;

	default:
		/* Error */
		AX5043_PINFUNCIRQ = 0x02; /* Disable IRQ line */
		IE = iesave;
		return 1;
	}
	PORTR &= (uint8_t)~res; /* disable pullup */
	IE = iesave;
	return 0;
}

#elif RADIO == 5051

 uint8_t ax5051_probeirq(void)
{
	res = 0x60;
	uint8_t pc1 = AX5051_PINCFG1 & 0x0F;
	uint8_t iesave = IE;
	IE_4 = 0;
	PORTR = 0xEB;
	AX5051_PINCFG1 = 0xD0 | pc1;
	AX5051_PINCFG2 = 0xF2; /* IRQ Line 1 */
	res &= PINR;
	AX5051_PINCFG2 = 0xF0; /* IRQ Line 0 */
	res &= (uint8_t)~PINR;
	AX5051_PINCFG2 = 0xD0;
	switch (res) {
	case 0x20: /* IRQ on PR5 */
		RADIOMUX &= (uint8_t)~0x08;
		break;

	case 0x40: /* IRQ on PR6 */
		RADIOMUX |= 0x08;
		break;

	default:
		/* Error */
		AX5051_PINCFG1 = 0xA0 | pc1; /* Disable IRQ line */
		IE = iesave;
		return 1;
	}
	PORTR &= (uint8_t)~res; /* disable pullup */
	/*
	 * Check voltage on test mode pins and drive them
	 * to the correct level. This is somewhat dangerous - we
	 * may momentarily short circuit the output driver (4mA)
	 * no short circuit will happen if the board complies
	 * to AX5051/AX5151/AX8052F151 programming manual
	 */
	EA = 0;
	/* check T2 */
	AX5051_PINCFG1 = 0xC0 | pc1;
	AX5051_PINCFG2 |= AX5051_PINCFG3 & 0x01;
	/* check T1 */
	AX5051_PINCFG1 = 0x80 | pc1;
	AX5051_PINCFG2 |= AX5051_PINCFG3 & 0x04;
	/* check TST3 */
	AX5051_PINCFG1 = pc1;
	AX5051_PINCFG2 |= AX5051_PINCFG3 & 0x08;
	IE |= res;
	/* check whether TST3 is connected to PR5 - if so disable pullup */
	PORTR &= PINR | (uint8_t)~0x20;
	IE = iesave;
	return 0;
}

#endif
