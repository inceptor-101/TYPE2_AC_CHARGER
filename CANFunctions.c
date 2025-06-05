/**********************************************************************
* Code :  CPU2 - CAN Functions
* Devices: TMS320F2800137
* Author: Varun Sharma
**********************************************************************/
#include <GTSI_1Phase1MPPT.h>    // Main include file
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <can.h>

void InitCanaChargerDriverLib(void)
{
    // For communication with EV
    CAN_initModule(CANA_BASE);
    CAN_setBitTiming(CANA_BASE,23,0,6,1,0); // 500kbps
    CAN_enableAutoBusOn(CANA_BASE);
    CAN_setAutoBusOnTime(CANA_BASE,1000000);
    CAN_enableRetry(CANA_BASE);
    CAN_enableInterrupt(CANA_BASE, CAN_INT_IE0);    // enabling the CANINT0 interrupt
    //CAN_enableTestMode(CANA_BASE, CAN_TEST_EXL);    // currently doing in the loopback mode only

//    CONFIGURING THE MESSAGE OBJECTS FOR THE TRANSMISSION
    CAN_setupMessageObject(CANA_BASE, 1, 0x21, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0, CAN_MSG_OBJ_TX_INT_ENABLE, 8);

//    FOR SAMPLE TESTING
    CAN_setupMessageObject(CANA_BASE, 5, 0x31, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0, CAN_MSG_OBJ_RX_INT_ENABLE, 8);

    CAN_startModule(CANA_BASE);

//    For the interrupt mapping
    CAN_setInterruptMux(CANA_BASE, 0x00000000);     //all the mailboxes are muxed to the cana0_isr only
//    CAN_setInterruptMux(CANA_BASE, 0xFFFFFFFF);   //for the mapping to the cana1_isr
    CAN_enableGlobalInterrupt(CANA_BASE, CAN_GLOBAL_INT_CANINT0);
//    CAN_disableGlobalInterrupt(CANA_BASE, CAN_GLOBAL_INT_CANINT1);

}

