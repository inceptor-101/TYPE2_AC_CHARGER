/**********************************************************************
* Project Functions for Solar Inverter
* Devices: TMS320F2800137
* Authors: Shikha Singhal and Ramanpreet Kaur
**********************************************************************/
#include "GTSI_1Phase1MPPT.h"
#include "can.h"

uint16_t CANASendMessage(Uint16 objectID, Uint16 dlc, Uint16 *data){
    /*
     * Function to transmit CANA Message
     * Arguments:
     *          1. ObjectId (Refer CAN functions for same)
     *          2. DLC: Data length code
     *          3. Data
     * Return type is void
     */
    Uint32 TXRequestRegisterVal;
    float CANFailureCount = 0;

    TXRequestRegisterVal = CAN_getTxRequests(CANA_BASE);

    while((TXRequestRegisterVal & (1<<(objectID-1))) == (1<<(objectID-1))){
        CANAFailure = 0;
        CANFailureCount++;
        DELAY_US(1);
        if(CANFailureCount > 100000.0){
            CANFailureCount=0.0;
            InitCanaChargerDriverLib();
            CANAFailure = 1;
            break;
        }
    }

    CAN_sendMessage(CANA_BASE,objectID,dlc,data);

    return CANAFailure;
}
