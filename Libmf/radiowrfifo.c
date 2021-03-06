#include "libmfradio.h"

#if RADIO == 5031
#define RADIO 5031
#elif RADIO == 5042
#define RADIO 5042
#elif RADIO == 5043
#define RADIO 5043
#elif RADIO == 5051
#define RADIO 5051
#endif

#if defined(SDCC)

void radio_writefifo(const uint8_t *ptr, uint8_t len)
{
	ptr;
	len;
        __asm;
	mov	a,sp
	add	a,#-2
	mov	r0,a
	mov	a,@r0
	jz	nodata$
	mov	r7,a
	jb	_B_7,codeptr$		; >0x80 code
	jnb	_B_6,xdataptr$		; <0x40 far
	mov	r0,dpl
	mov	dptr,#(AX8052_RADIOBASE | FDATA)
	jb	_B_5,pdataptr$		; >0x60 pdata
idataloop$:
	mov	a,@r0
	movx	@dptr,a
	inc	r0
	djnz	r7,idataloop$
nodata$:
	ret
pdataptr$:
pdataloop$:
	movx	a,@r0
	movx	@dptr,a
	inc	r0
	djnz	r7,pdataloop$
	ret
xdataptr$:
	mov	a,#0x80
	anl	a,_IE
	mov	r5,a
	clr	_EA
	mov	r6,_XPAGE
	mov	_XPAGE,#((AX8052_RADIOBASE | FDATA) >> 8)
	mov	r0,#(AX8052_RADIOBASE | FDATA)
xdataloop$:
	movx	a,@dptr
	movx	@r0,a
	inc	dptr
	djnz	r7,xdataloop$
	mov	_XPAGE,r6
	mov	a,r5
	orl	_IE,a
	ret
codeptr$:
	mov	a,#0x80
	anl	a,_IE
	mov	r5,a
	clr	_EA
	mov	r6,_XPAGE
	mov	_XPAGE,#((AX8052_RADIOBASE | FDATA) >> 8)
	mov	r0,#(AX8052_RADIOBASE | FDATA)
codeloop$:
	clr	a
	movc	a,@a+dptr
	movx	@r0,a
	inc	dptr
	djnz	r7,codeloop$
	mov	_XPAGE,r6
	mov	a,r5
	orl	_IE,a
	ret
        __endasm;
}

#else

__reentrantb void radio_writefifo(const uint8_t __generic *ptr, uint8_t len) __reentrant
{
	if (!len)
		return;
	do {
		*(uint8_t __xdata *)(AX8052_RADIOBASE | FDATA) = *ptr++;
	} while (--len);
}

#endif
