/*
 * radio.c - definitions for portable functions
 * mini BS board AXSEM radio initialization
 */

#include "nbfi.h"

const uint16_t AX5043_power[26] = {0x00aa, 0x00bf, 0x00d1, 0x00ec, 0x010f, 0x0132, 0x0156, 0x017f, 0x01af, 0x1e0, 0x207, 0x244, 0x290, 0x2eb, 0x35e, 0x3d6, 0x406, 0x4a9, 0x57c, 0x600, 0x700, 0x800, 0x9d4, 0xc00, 0xf00, 0xfff};

struct axradio_address rf_destination;
uint8_t PSK_BAND;
nbfi_phy_channel_t nbfi_phy_channel;

void RF_SetFreq(uint32_t freq)
{
    axradio_phy_chanfreq[0] = axradio_conv_freq_fromhz(freq);//TODO fix freq calc
    // Dirty fix for insufficient arithmetics precision
    if(freq > 800000000)    axradio_phy_chanfreq[0]+=34; //868MHz
    else                    axradio_phy_chanfreq[0]+=18; //446MHz
}

void RF_SetModeAndPower(int8_t dBm, rf_direction_t mode, rf_antenna_t ant)
{

    if(dBm > RF_MAX_POWER) dBm = RF_MAX_POWER;
    if(dBm < RF_MIN_POWER) dBm = RF_MIN_POWER;

    if(mode == TX)
    {
       #if defined(SDR_RASP) || defined(AMPER) || defined (BIGTIFFANY)
        PIN_SET_OUTPUT(PA_EN_DIR,  PA_EN_PIN);
        PA_EN = 1;
        #endif
        #ifdef AMPER_2_1
        PIN_SET_OUTPUT(PA_EN_DIR,  PA_EN_PIN);
        if(dBm <= AX5043_MAX_DBM)
        {
            // set power
            AX5043_TXPWRCOEFFB1 = AX5043_power[dBm + 10] >> 8;
            AX5043_TXPWRCOEFFB0 = AX5043_power[dBm + 10] &0xFF;

            // select differential PA
            AX5043_MODCFGA = 0x1;//5

            // FEM PA bypass
            TX_RX_SEL = RX;
            DIRC |= 1;
            PA_EN = 0;
        }
        else
        {
            // set power, considering FEM gain
            AX5043_TXPWRCOEFFB1 = AX5043_power[dBm - FEM_GAIN + 10] >> 8;
            AX5043_TXPWRCOEFFB0 = AX5043_power[dBm - FEM_GAIN + 10] &0xFF;

            // select single-ended PA
            AX5043_MODCFGA = 0x2;//6

            //enable FEM PA
            TX_RX_SEL = TX;
            DIRC |= 1;
            PA_EN = 1;
        }
        #endif
        #ifdef AMPER_2_2
        PIN_SET_OUTPUT(PA_EN_DIR,  PA_EN_PIN);

        if(dBm <= AX5043_MAX_DBM)
        {
            // set power
            AX5043_TXPWRCOEFFB1 = AX5043_power[dBm + 10] >> 8;
            AX5043_TXPWRCOEFFB0 = AX5043_power[dBm + 10] &0xFF;

            // select differential PA
            AX5043_MODCFGA = 0x1;//5

            // FEM PA bypass
            DIRC &= ~0x0c;
            TX_RX_SEL = RX;
            TX_RX_SEL_2 = RX;
            TX_RX_SEL_3 = RX;
            DIRC |= 0x0c;

            PA_EN = 0;
        }
        else
        {
            // set power, considering FEM gain
            AX5043_TXPWRCOEFFB1 = AX5043_power[dBm - FEM_GAIN + 10] >> 8;
            AX5043_TXPWRCOEFFB0 = AX5043_power[dBm - FEM_GAIN + 10] &0xFF;

            // select single-ended PA
            AX5043_MODCFGA = 0x2;//6

            //enable FEM PA
            DIRC &= ~0x0c;
            TX_RX_SEL = TX;
            TX_RX_SEL_2 = TX;
            TX_RX_SEL_3 = TX;
            DIRC |= 0x0c;
            PA_EN = 1;
        }
        #endif

        #ifdef AMPER_2_3
        if(dBm > AX5043_MAX_DBM) dBm = AX5043_MAX_DBM;
        AX5043_TXPWRCOEFFB1 = AX5043_power[dBm + 10] >> 8;
        AX5043_TXPWRCOEFFB0 = AX5043_power[dBm + 10] &0xFF;
        switch(nbfi.tx_phy_channel)
        {
            case UL_PSK_FASTDL:
            case UL_PSK_200:
            case UL_PSK_500:
            case UL_PSK_5000:
                // select differential PA
                AX5043_MODCFGA = PA_DIFFERENTIAL;
            break;
            default:
                // select single-ended PA
                AX5043_MODCFGA = PA_SINGLE_ENDED;
                break;
        }

        #endif
        #if defined(SDR_RASP) || defined (USPD) || defined(USB_DONGLE)
        PIN_SET_OUTPUT(PA_EN_DIR,  PA_EN_PIN);
        PA_EN = 1;
        // set power
        AX5043_MODCFGA = PA_DIFFERENTIAL;
        AX5043_TXPWRCOEFFB1 = AX5043_power[dBm+10] >> 8;
        AX5043_TXPWRCOEFFB0 = AX5043_power[dBm+10] &0xFF;
        #endif

        #if  BIGTIFFANY
        // set power
        #ifdef SINGLE_ENDED
        AX5043_MODCFGA = PA_SINGLE_ENDED;
        #else
        AX5043_MODCFGA = PA_DIFFERENTIAL;
        #endif
        AX5043_TXPWRCOEFFB1 = AX5043_power[dBm+10] >> 8;
        AX5043_TXPWRCOEFFB0 = AX5043_power[dBm+10] &0xFF;
        #endif

        //#if defined(NEPTUN) || defined (BIGTIFFANY_AX)|| defined (KARAT)
        // set power
        AX5043_MODCFGA = PA_DIFFERENTIAL;
        AX5043_TXPWRCOEFFB1 = AX5043_power[dBm] >> 8;
        AX5043_TXPWRCOEFFB0 = AX5043_power[dBm] &0xFF;
        //#endif

        #ifdef SDR_BS3
        PIN_SET_OUTPUT(PA_SW1_DIR,  PA_SW1_PIN);
        PIN_SET_OUTPUT(PA_SW2_DIR,  PA_SW2_PIN);
        PIN_SET_OUTPUT(PA_450_EN_DIR,  PA_450_EN_PIN);
        PIN_SET_OUTPUT(PA_860_EN_DIR,  PA_860_EN_PIN);

        if(ant == PCB)
        {
            PA_SW1 = 1;
            PA_SW2 = 0;
            PA_450_EN = 1;
            PA_860_EN = 0;
            AX5043_MODCFGA = PA_SINGLE_ENDED;
            AX5043_TXPWRCOEFFB1 = power_table[dBm + 15] >> 8;
            AX5043_TXPWRCOEFFB0 = power_table[dBm + 15] &0xFF;
        }
        else
        {
            PA_SW1 = 0;
            PA_SW2 = 1;
            PA_450_EN = 0;
            if(send_auto_corr == 0)  PA_860_EN = 1;
            else PA_860_EN = 0;
            send_auto_corr = 0;
            AX5043_MODCFGA = PA_DIFFERENTIAL;
            AX5043_TXPWRCOEFFB1 = power_table_864[dBm + 15 - 6] >> 8;
            AX5043_TXPWRCOEFFB0 = power_table_864[dBm + 15 - 6] &0xFF;
        }

        #endif

        #ifdef DEVKIT

        PIN_SET_OUTPUT(PA_EN_DIR,  PA_EN_PIN);

        PIN_SET_OUTPUT(TX_ANT_DIR, TX_ANT_PIN);

        /*if(dBm <= AX5043_MAX_DBM)
        {
            // set power
            AX5043_TXPWRCOEFFB1 = RFM6599_PowerTable[dBm + 10] >> 8;
            AX5043_TXPWRCOEFFB0 = RFM6599_PowerTable[dBm + 10] &0xFF;

            // select PA output
            AX5043_MODCFGA = PA_DIFFERENTIAL;
            // FEM PA bypass
            //TX_RX_SEL = RX;
            PA_EN = HIGH;//LOW;
        }
        else
        {*/
        if(nbfi.tx_phy_channel == UL_PSK_FASTDL)
        {
            if(dBm > 15) dBm = 15;
            AX5043_TXPWRCOEFFB1 = AX5043_power[dBm+10] >> 8;
            AX5043_TXPWRCOEFFB0 = AX5043_power[dBm+10] &0xFF;
            AX5043_MODCFGA = PA_DIFFERENTIAL;
            PIN_SET_OUTPUT(RX_ANT_DIR, RX_ANT_PIN);
            RX_ANT = ant;
        }
        else
        {

            AX5043_TXPWRCOEFFB1 = RFM6599_PowerTable[dBm - FEM_GAIN + 10] >> 8;
            AX5043_TXPWRCOEFFB0 = RFM6599_PowerTable[dBm - FEM_GAIN + 10] &0xFF;

            // select single-ended PA
            AX5043_MODCFGA = PA_SINGLE_ENDED;
            //AX5043_MODCFGA = PA_DIFFERENTIAL;
            // enable FEM PA
            //TX_RX_SEL = TX;
            TX_ANT = ant;
            PA_EN = HIGH;
        }
            // set power, considering FEM gain

        //}
        #endif // DEVICE
    }
}


void RF_SetDstAddress(uint8_t * addr)
{
    uint8_t i;

    for(i = 0; i != 3; i++) rf_destination.addr[i] = addr[i];
}


void RF_SetLocalAddress(uint8_t * addr)
{
    struct axradio_address_mask localaddress = {{0,0,0,0},{0xff, 0, 0, 0}};

    localaddress.addr[0] = addr[0];
    //localaddress.addr[1] = addr[1];
    //localaddress.addr[2] = addr[2];

    axradio_set_local_address(&localaddress);
}

nbfi_status_t RF_Init(  nbfi_phy_channel_t  phy_channel,
                        rf_antenna_t        antenna,
                        int8_t              power,
                        uint32_t            freq)
{

    if(freq > 600000000) PSK_BAND = 1;
    else PSK_BAND = 0;

    nbfi_phy_channel = UL_DBPSK_50_PROT_D;
    ax5043_set_constants();
    RF_SetFreq(freq);
    if (axradio_init() != AXRADIO_ERR_NOERROR) return ERR;

    RF_SetModeAndPower(power, TX, antenna);

    switch(phy_channel)
    {
        case UL_CARRIER:
            axradio_set_mode(AXRADIO_MODE_CW_TRANSMIT);
            break;
        case UL_DBPSK_50_PROT_D:
            axradio_set_mode(AXRADIO_MODE_ASYNC_TRANSMIT);
            break;
        default:
            break;
    }

    return OK;
}

nbfi_status_t RF_Deinit()
{
    RF_SetModeAndPower(0, TX, 0);
    if (axradio_set_mode(AXRADIO_MODE_OFF) != AXRADIO_ERR_NOERROR) return ERR;

    return OK;
}

nbfi_status_t RF_Transmit(uint8_t * pkt, uint8_t len,  rf_padding_t padding, rf_blocking_t blocking)
{
    axradio_transmit(&rf_destination, pkt, len, padding);

    if(blocking == BLOCKING)
    {
        while(axradio_trxstate != trxstate_tx_done);// Wait for TX complete
    }

    return OK;
}
