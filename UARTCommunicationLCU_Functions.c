
#include <GTSI_1Phase1MPPT.h>                        // Main include file
#include <string.h>
#include <stdio.h>
#include <math.h>

#define connector1Fine   changeAvailabilityConn1 == operative && faultDetectConn1 == 0 && (internetStatusActive == 1 && websocketStatusActive == 1) && configurationKey == 1
#define connector2Fine   changeAvailabilityConn2 == operative && faultDetectConn2 == 0 && (internetStatusActive == 1 && websocketStatusActive == 1) && configurationKey == 1

void processLCUData(void){
    if(checkLCUDataFlag == 1 && chargerMode == onlineMode){    //Transmit Messages on Request
        if(!strcmp(MessageName,"Reset") && !strcmp(Data,"Done")){

            if((state != chargingStopped && configurationKey == 1) || state == initialConfigurationPage2)
                UARTWrite("Reset","OK");

            if(internetStatusActive == 2){
                internetStatusActive = 0;
                websocketStatusActive = 0;
            }

            if(bootNotificationStatusFlag == 1 || resetConfMsgRec == 1){
                resetDoneFlag = 1;
                resetConfMsgRec = 0;
            }
        }

        else if(!strcmp(MessageName,"Reset") && !strcmp(Data,"OK")){
            resetConfMsgRec = 1;
            sendResetHardMessage = 0;
        }

        else if(!strcmp(MessageName,"Reset") && !strcmp(Data,"Hard")){
            if(currentConnector1Status == charging)
                chargingStoppedReasonConn1 = hardSoftReset;
            if(currentConnector2Status == charging)
                chargingStoppedReasonConn2 = hardSoftReset;
            UARTWrite("Reset","OK");
        }

        else if(!strcmp(MessageName,"Project") && !strcmp(Data,"")){
            if(selectedStandardGunA == Type2AC)
                UARTWrite("Project","Type2AC");
            else if(selectedStandardGunA == AC001)
                UARTWrite("Project","AC001");
        }

        else if(!strcmp(MessageName,"NOC") && !strcmp(Data,"")){
            if(selectedStandardGunB != 0)
                UARTWrite("NOC","2");
            else
                UARTWrite("NOC","1");
        }

        else if(!strcmp(MessageName,"DefaultNetwork") && !strcmp(Data,"")){
            UARTWrite("DefaultNetwork",defaultNetwork);
        }

        else if(!strcmp(MessageName,"DefaultNetwork") && !strcmp(Data,"OK"));

        else if(!strcmp(MessageName,"DateTime")){
            readDateTimeRTC();
            UARTWrite("DateTime", dateTime);
        }

        else if(!strcmp(MessageName,"InternetStatus")){
            if(!strcmp(Data,"1"))
                internetStatusActive = 1;
            else if(!strcmp(Data,"0"))
                internetStatusActive = 0;

            UARTWrite("InternetStatus","OK");   //Send confirmation message
        }

        else if(!strcmp(MessageName,"WebsocketStatus")){
            if(!strcmp(Data,"1")){
                websocketStatusActive = 1;
                onBootUp = 1;
            }
            else if(!strcmp(Data,"0"))
                websocketStatusActive = 0;

            UARTWrite("WebsocketStatus","OK");  //Send confirmation message
        }

        else if(!strcmp(MessageName,"BootNotification") && !strcmp(Data,"")){
            char bootString[40];

            strcpy(bootString,modelNumber);
            strcat(bootString,",PyramidElectronics");

            UARTWrite("BootNotification",bootString);
        }

        else if(!strcmp(MessageName,"StatusNotification") && !strcmp(Data,"1")){
            if(connector1Fine){
                sendStatusNotificationWithErrorCode(available, noError, 1);
                sendStatusNotificationConn1 = available;
            }
            else{
                sendStatusNotificationWithErrorCode(unavailable, maintenanceMode, 1);
                sendStatusNotificationConn1 = unavailable;
            }
        }
        else if(!strcmp(MessageName,"StatusNotification") && !strcmp(Data,"2")){
            if(connector2Fine){
                sendStatusNotificationWithErrorCode(available, noError, 2);
                currentConnector2Status = available;
            }
            else{
                sendStatusNotificationWithErrorCode(unavailable, maintenanceMode, 2);
                currentConnector2Status = unavailable;
            }
        }

        else if(!strcmp(MessageName,"ChangeAvailability") && !strcmp(Data,"1")){
            if(changeAvailabilityConn1 == operative)
                UARTWrite("ChangeAvailability","Operative,1");

            else if(changeAvailabilityConn1 == inoperative)
                UARTWrite("ChangeAvailability","Inoperative,1");
        }
        else if(!strcmp(MessageName,"ChangeAvailability") && !strcmp(Data,"2")){
            if(changeAvailabilityConn2 == operative)
                UARTWrite("ChangeAvailability","Operative,2");

            else if(changeAvailabilityConn2 == inoperative)
                UARTWrite("ChangeAvailability","Inoperative,2");
        }

        else if(!strcmp(MessageName,"URL") && !strcmp(Data,"")){
            if(url[0] != '\0')
                UARTWrite("URL",url);
        }

        else if(!strcmp(MessageName,"SmartCharge")){
            char limitValue[10];
            char limitType[2];
            char limitonnectorID[2];
            Uint16 i=0;

            extractLCUData(Data,limitType,limitValue,limitonnectorID);
            if(!strcmp(limitonnectorID,"0")){
                for(i=0;i<strlen(limitValue);i++)
                    serverChargerPowerLimitStr[i] = limitValue[i];

                serverChargerPowerLimitStr[i] = '\0';
                // Send confirmation message
                UARTWrite("SmartCharge","OK,0");
                serverChargerPowerLimit = atof(serverChargerPowerLimitStr);
            }
            else if(!strcmp(limitonnectorID,"1") && !strcmp(limitType,"W")){
                for(i=0;i<strlen(limitValue);i++)
                    serverConnectorPowerLimitStrConn1[i] = limitValue[i];

                serverConnectorPowerLimitStrConn1[i] = '\0';
                // Send confirmation message
                UARTWrite("SmartCharge","OK,1");
                serverConnectorPowerLimitConn1 = atof(serverConnectorPowerLimitStrConn1);
            }
            else if(!strcmp(limitonnectorID,"1") && !strcmp(limitType,"A")){
                for(i=0;i<strlen(limitValue);i++)
                    serverConnectorCurrentLimitStrConn1[i] = limitValue[i];

                serverConnectorCurrentLimitStrConn1[i] = '\0';
                // Send confirmation message
                UARTWrite("SmartCharge","OK,1");
                serverConnectorCurrentLimitConn1 = atof(serverConnectorCurrentLimitStrConn1);
            }
            else if(!strcmp(limitonnectorID,"2") && !strcmp(limitType,"W")){
                for(i=0;i<strlen(limitValue);i++)
                    serverConnectorPowerLimitStrConn2[i] = limitValue[i];

                serverConnectorPowerLimitStrConn2[i] = '\0';
                // Send confirmation message
                UARTWrite("SmartCharge","OK,2");
                serverConnectorPowerLimitConn2 = atof(serverConnectorPowerLimitStrConn2);
            }
            else if(!strcmp(limitonnectorID,"2") && !strcmp(limitType,"A")){
                for(i=0;i<strlen(limitValue);i++)
                    serverConnectorCurrentLimitStrConn2[i] = limitValue[i];

                serverConnectorCurrentLimitStrConn2[i] = '\0';
                // Send confirmation message
                UARTWrite("SmartCharge","OK,2");
                serverConnectorCurrentLimitConn2 = atof(serverConnectorCurrentLimitStrConn2);
            }
        }

        else if(!strcmp(MessageName,"LocalListPresent")){
            if(!strcmp(Data,"1"))
                localListPresent = 1;
            else
                localListPresent = 0;
            UARTWrite("LocalListPresent","OK");
        }

        else if(!strcmp(MessageName,"LocalListConflict")){
            char connectorID[1];

            //Data Manipulation
            extractLCUData(Data,connectorID,"","");

            if(connectorID[0] == '1'){
                if(currentConnector1Status == charging)
                    chargingStoppedReasonConn1 = idTagDeauthorized;

                UARTWrite("LocalListConflict","OK,1");  //Send confirmation message
            }
            else if(connectorID[0] == '2'){
                if(currentConnector2Status == charging)
                    chargingStoppedReasonConn2 = idTagDeauthorized;

                UARTWrite("LocalListConflict","OK,2");  //Send confirmation message
            }
        }

        else if(!strcmp(MessageName,"BootNotification")){

            //Data Manipulation
            extractLCUData(Data,currentTime,interval,bootNotificationStatus);

            if(!strcmp(bootNotificationStatus,"Accepted"))
                bootNotificationStatusFlag = 1;
            else
                bootNotificationStatusFlag = 0;
            //Send confirmation message
            UARTWrite("BootNotification","OK");
        }

        else if(!strcmp(MessageName,"CancelReservation")){
            char reservedConnectorID[1];

            // Format of data message --> CancelReservation:Accepted,1
            extractLCUData(Data,"",reservedConnectorID,"");

            if(!strcmp(reservedConnectorID,"1")){
                clearReservationConn1();
                UARTWrite("CancelReservation","OK,1");
            }
            else if(!strcmp(reservedConnectorID,"2")){
                clearReservationConn2();
                UARTWrite("CancelReservation","OK,2");
            }
        }

        else if(!strcmp(MessageName,"ReserveNow")){
            Uint16 i=0;
            char IdTag[21], expiryDateTime[30], reservedConnectorID[1];

            for(i=0;i<21;i++)
                IdTag[i] = '\0';
            for(i=0;i<30;i++)
                expiryDateTime[i] = '\0';
            for(i=0;i<1;i++)
                reservedConnectorID[i] = '\0';

            extractLCUData(Data,expiryDateTime,IdTag,reservedConnectorID);

            if(!strcmp(reservedConnectorID,"1") && (chargingAllowedConn1 || chargingAllowedOnReservationConn1)){
                for(i=0;i<lengthReservedIdTag;i++)
                    reservedIdTagConn1[i] = IdTag[i];
                for(i=0;i<30;i++)
                    reservedExpiryDateTimeConn1[i] = expiryDateTime[i];

                currentConnector1Status = reserved;
                UARTWrite("ReserveNow","OK,1");
            }
            else if(!strcmp(reservedConnectorID,"2") && (chargingAllowedConn2 || chargingAllowedOnReservationConn2)){
                for(i=0;i<lengthReservedIdTag;i++)
                    reservedIdTagConn2[i] = IdTag[i];
                for(i=0;i<30;i++)
                    reservedExpiryDateTimeConn2[i] = expiryDateTime[i];

                currentConnector2Status = reserved;
                UARTWrite("ReserveNow","OK,2");
            }
        }

        else if(!strcmp(MessageName,"Authorize") && !strcmp(Data,"OK,1")){
            if(authorizeMethodConn1 == RFID)
                authorizeACKConn1 = RFID;
            else if(authorizeMethodConn1 == password)
                authorizeACKConn1 = password;

            sendAuthorizeDataMessageConn1 = 0;
        }
        else if(!strcmp(MessageName,"Authorize") && !strcmp(Data,"OK,2")){
            if(authorizeMethodConn2 == RFID)
                authorizeACKConn2 = RFID;
            else if(authorizeMethodConn2 == password)
                authorizeACKConn2 = password;

            sendAuthorizeDataMessageConn2 = 0;
        }

        else if(!strcmp(MessageName,"Authorize") && !strcmp(Data,"Rejected,1")){
            if(authorizeMethodConn1 == RFID){
                // invalid RFID Tag
                clearStoredRFIDTagConn1();
                authorizeACKConn1 = rejectedRFID;
                messagePrompt = rfidUnsuccessfulConn1;
            }
            else if(authorizeMethodConn1 == password)
                authorizeACKConn1 = rejectedPassword;

            authorizeMethodConn1 = NULL;
            UARTWrite("Authorize","OK,1");
        }
        else if(!strcmp(MessageName,"Authorize") && !strcmp(Data,"Rejected,2")){
            if(authorizeMethodConn2 == RFID){
                // invalid RFID Tag
                clearStoredRFIDTagConn2();
                authorizeACKConn2 = rejectedRFID;
                messagePrompt = rfidUnsuccessfulConn2;
            }
            else if(authorizeMethodConn2 == password)
                authorizeACKConn2 = rejectedPassword;

            authorizeMethodConn2 = NULL;
            UARTWrite("Authorize","OK,2");
        }

        else if(!strcmp(MessageName,"Authorize") && !strcmp(Data,"Accepted,1")){
            if(authorizeMethodConn1 == RFID)
                validRFIDConn1 = 1;
            else if(authorizeMethodConn1 == password)
                validPasswordConn1 = 1;

            authenticationStatusConn1 = 1;
            UARTWrite("Authorize","OK,1");
        }
        else if(!strcmp(MessageName,"Authorize") && !strcmp(Data,"Accepted,2")){
            if(authorizeMethodConn2 == RFID)
                validRFIDConn2 = 1;
            else if(authorizeMethodConn2 == password)
                validPasswordConn2 = 1;

            authenticationStatusConn2 = 1;
            UARTWrite("Authorize","OK,2");
        }

        else if(!strcmp(MessageName,"StatusNotification") && !strcmp(Data,"OK,1"))
            sendStatusNotificationConn1 = 0;
        else if(!strcmp(MessageName,"StatusNotification") && !strcmp(Data,"OK,2"))
            sendStatusNotificationConn2 = 0;

        else if(!strcmp(MessageName,"RemoteStartTransaction")){
            char connectorID[1];

            //Data Manipulation
            extractLCUData(Data,idTag,connectorID,"");

            if(connectorID[0] == '1'){
                authenticationStatusConn1 = 1;
                UARTWrite("RemoteStartTransaction","OK,1");
            }
            else if(connectorID[0] == '2'){
                authenticationStatusConn2 = 1;
                UARTWrite("RemoteStartTransaction","OK,2");
            }

        }
        else if(!strcmp(MessageName,"RemoteStopTransaction")){
            char connectorID[1];

            //Data Manipulation
            extractLCUData(Data,transactionId,connectorID,"");

            if(connectorID[0] == '1'){
                if(currentConnector1Status == charging)
                    chargingStoppedReasonConn1 = remoteStop;
                //Send confirmation message
                UARTWrite("RemoteStopTransaction","OK,1");
            }
            else if(connectorID[0] == '2'){
                if(currentConnector2Status == charging)
                    chargingStoppedReasonConn2 = remoteStop;
                //Send confirmation message
                UARTWrite("RemoteStopTransaction","OK,2");
            }
        }

        else if(!strcmp(MessageName,"StartTransaction") && !strcmp(Data,"1")){
            char data[25];
            if(virtualEnergyMeter == enable){
                int64ToStr(virtualEnergyMeterValue, data, 1);
                strcat(data, ",1");
                UARTWrite("StartTransaction",data);
            }
            else if(virtualEnergyMeter == disable)
                UARTWrite("StartTransaction","0,1");
        }
        else if(!strcmp(MessageName,"StartTransaction") && !strcmp(Data,"2")){
            char data[25];
            if(virtualEnergyMeter == enable){
                int64ToStr(virtualEnergyMeterValue, data, 1);
                strcat(data, ",2");
                UARTWrite("StartTransaction",data);
            }
            else if(virtualEnergyMeter == disable)
                UARTWrite("StartTransaction","0,2");
        }

        else if(!strcmp(MessageName,"MeterValues") && !strcmp(Data,"1")){
            int32ToStr((Uint32)(EnergyConn1*1000),energyActiveImportRegisterStr,5);
            int32ToStr((Uint32)(PAvgConn1*1000),powerActiveImportStr,5);
            int32ToStr((Uint32)((VrnRms+VynRms+VbnRms)/3),voltageStr,3);
            int32ToStr((Uint32)(avgCurrentConn1()),currentImportStr,2);

            int i=0;
            int j=0;
            while(energyActiveImportRegisterStr[j])
                meterValuesStr[i++] = energyActiveImportRegisterStr[j++];
            meterValuesStr[i]=',';
            i++;
            j=0;
            while(powerActiveImportStr[j])
                meterValuesStr[i++] = powerActiveImportStr[j++];
            meterValuesStr[i]=',';
            i++;
            j=0;
            while(voltageStr[j])
                meterValuesStr[i++] = voltageStr[j++];
            meterValuesStr[i]=',';
            i++;
            j=0;
            while(currentImportStr[j])
                meterValuesStr[i++] = currentImportStr[j++];
            meterValuesStr[i]=',';
            meterValuesStr[i+1]='1';
            meterValuesStr[i+2]='\0';

            UARTWrite("MeterValues",meterValuesStr);
        }
        else if(!strcmp(MessageName,"MeterValues") && !strcmp(Data,"2")){
            int32ToStr((Uint32)(EnergyConn2*1000),energyActiveImportRegisterStr,5);
            int32ToStr((Uint32)(PAvgConn2*1000),powerActiveImportStr,5);
            int32ToStr((Uint32)((VrnRms+VynRms+VbnRms)/3),voltageStr,3);
            int32ToStr((Uint32)(avgCurrentConn2()),currentImportStr,2);

            int i=0;
            int j=0;
            while(energyActiveImportRegisterStr[j])
                meterValuesStr[i++] = energyActiveImportRegisterStr[j++];
            meterValuesStr[i]=',';
            i++;
            j=0;
            while(powerActiveImportStr[j])
                meterValuesStr[i++] = powerActiveImportStr[j++];
            meterValuesStr[i]=',';
            i++;
            j=0;
            while(voltageStr[j])
                meterValuesStr[i++] = voltageStr[j++];
            meterValuesStr[i]=',';
            i++;
            j=0;
            while(currentImportStr[j])
                meterValuesStr[i++] = currentImportStr[j++];
            meterValuesStr[i]=',';
            meterValuesStr[i+1]='2';
            meterValuesStr[i+2]='\0';

            UARTWrite("MeterValues",meterValuesStr);
        }

        else if(!strcmp(MessageName,"MeterValues") && !strcmp(Data,"OK,1"))
            sendMeterValueConn1 = 0;
        else if(!strcmp(MessageName,"MeterValues") && !strcmp(Data,"OK,2"))
            sendMeterValueConn2 = 0;

        else if(!strcmp(MessageName,"ChangeAvailability") && (!strcmp(Data,"Inoperative") || !strcmp(Data,"Operative"))){
            // Change Availability of Charging Station
            if(!strcmp(Data,"Inoperative")){
                changeAvailabilityConn1 = inoperative;
                changeAvailabilityConn2 = inoperative;
                EEPROM_WriteByte(addressChangeAvailabilityConn1, inoperative);
                EEPROM_WriteByte(addressChangeAvailabilityConn2, inoperative);
            }
            else if(!strcmp(Data,"Operative")){
                changeAvailabilityConn1 = operative;
                changeAvailabilityConn2 = operative;
                EEPROM_WriteByte(addressChangeAvailabilityConn1, operative);
                EEPROM_WriteByte(addressChangeAvailabilityConn2, operative);
            }

            UARTWrite("ChangeAvailability","OK");   // Send confirmation message
        }
        else if(!strcmp(MessageName,"ChangeAvailability") && (!strcmp(Data,"Inoperative,1") || !strcmp(Data,"Operative,1"))){
            if(!strcmp(Data,"Inoperative,1")){
                changeAvailabilityConn1 = inoperative;
                EEPROM_WriteByte(addressChangeAvailabilityConn1, inoperative);
            }
            else if(!strcmp(Data,"Operative,1")){
                changeAvailabilityConn1 = operative;
                EEPROM_WriteByte(addressChangeAvailabilityConn1, operative);
            }

            UARTWrite("ChangeAvailability","OK,1"); // Send confirmation message
        }
        else if(!strcmp(MessageName,"ChangeAvailability") && (!strcmp(Data,"Inoperative,2") || !strcmp(Data,"Operative,2"))){
            if(!strcmp(Data,"Inoperative,2")){
                changeAvailabilityConn2 = inoperative;
                EEPROM_WriteByte(addressChangeAvailabilityConn2, inoperative);
            }
            else if(!strcmp(Data,"Operative,2")){
                changeAvailabilityConn2 = operative;
                EEPROM_WriteByte(addressChangeAvailabilityConn2, operative);
            }

            UARTWrite("ChangeAvailability","OK,2"); // Send confirmation message
        }

        else if(!strcmp(MessageName,"JAP") && !strcmp(Data,"OK")){
            JAPConfMsgRec = 1;
        }

        else if(!strcmp(MessageName,"JAP")){

            if(!strcmp(Data,"NotConnected"))
                connectionStatusJAP = 3;
            else if(!strcmp(Data,"Connected") && defaultNetworkSetting == 1)
                connectionStatusJAP = 1;
            else if(!strcmp(Data,"Connected") && defaultNetworkSetting == 0)
                connectionStatusJAP = 0;

            UARTWrite("JAP","OK");
        }

        else if(!strcmp(MessageName,"NAP")){
            NAPDataMsgRec = 1;
            NAPReqMsgSent = 0;

            //Data Manipulation
            extractLCUData(Data,numberOfAccessPointsStr,"","");
            numberOfAccessPoints = numberOfAccessPointsStr[0] - 48;
        }
        else if(!strcmp(MessageName,"SSID1")){
            numberOfAccessPointsRec++;

            //Data Manipulation
            extractLCUData(Data,&SSID1[ssidIndex],"","");

            if(numberOfAccessPoints > 1)                            // Request SSID2
                UARTWrite("SSID2","");
        }
        else if(!strcmp(MessageName,"SSID2")){
            numberOfAccessPointsRec++;

            //Data Manipulation
            ssidIndex = 0;
            extractLCUData(Data,&SSID2[ssidIndex],"","");

            if(numberOfAccessPoints > 2)                            // Request SSID3
                UARTWrite("SSID3","");
        }
        else if(!strcmp(MessageName,"SSID3")){
            numberOfAccessPointsRec++;

            //Data Manipulation
            ssidIndex = 0;
            extractLCUData(Data,&SSID3[ssidIndex],"","");

            if(numberOfAccessPoints > 3)                            // Request SSID4
                UARTWrite("SSID4","");
        }
        else if(!strcmp(MessageName,"SSID4")){
            numberOfAccessPointsRec++;

            //Data Manipulation
            ssidIndex = 0;
            extractLCUData(Data,&SSID4[ssidIndex],"","");

            if(numberOfAccessPoints > 4)                            // Request SSID5
                UARTWrite("SSID5","");
        }
        else if(!strcmp(MessageName,"SSID5")){
            numberOfAccessPointsRec++;

            //Data Manipulation
            ssidIndex = 0;
            extractLCUData(Data,&SSID5[ssidIndex],"","");

            if(numberOfAccessPoints > 5)                            // Request SSID6
                UARTWrite("SSID6","");
        }
        else if(!strcmp(MessageName,"SSID6")){
            numberOfAccessPointsRec++;

            //Data Manipulation
            ssidIndex = 0;
            extractLCUData(Data,&SSID6[ssidIndex],"","");

            if(numberOfAccessPoints > 6)                            // Request SSID7
                UARTWrite("SSID7","");
        }
        else if(!strcmp(MessageName,"SSID7")){
            numberOfAccessPointsRec++;

            //Data Manipulation
            ssidIndex = 0;
            extractLCUData(Data,&SSID7[ssidIndex],"","");

            if(numberOfAccessPoints > 7)                            // Request SSID8
                UARTWrite("SSID8","");
        }
        else if(!strcmp(MessageName,"SSID8")){
            numberOfAccessPointsRec++;

            //Data Manipulation
            ssidIndex = 0;
            extractLCUData(Data,&SSID8[ssidIndex],"","");
        }

        clearStrings();
        checkLCUDataFlag = 0;
        ScicRegs.SCICTL1.bit.RXENA = 1;     // receiver disabled
        PieCtrlRegs.PIEIER8.bit.INTx5 = 1;  // interrupt disabled
    } //end of checkLCUDataFlag

    //******************************** ADCa Timer 2sec code(Code for Communication with LCU) : START ********************************
    if(transmitDataToLCU == 1 && chargerMode == onlineMode){

        if(sendAuthorizeDataMessageConn1){
            char sendDataLCU[15];
            Uint16 i=0;

            for(i=0;i<15;i++)
                sendDataLCU[i] = '\0';

            if(authorizeMethodConn1 == RFID){
                for(i=0;i<lengthRFID;i++)
                    sendDataLCU[i] = storeRFIDDataConn1[i];
                sendDataLCU[i] = ',';
                sendDataLCU[i+1] = '1';
                sendDataLCU[i+2] = '\0';
                UARTWrite("Authorize",sendDataLCU);
            }
            else if(authorizeMethodConn1 == password){
                for(i=0;i<strlen(sendPasswordStr);i++)
                    sendDataLCU[i] = sendPasswordStr[i];
                sendDataLCU[i] = ',';
                sendDataLCU[i+1] = '1';
                sendDataLCU[i+2] = '\0';
                UARTWrite("Authorize",sendDataLCU);
            }
        }

        if(sendAuthorizeDataMessageConn2 && selectedStandardGunB != 0){
            char sendDataLCU[15];
            Uint16 i=0;

            for(i=0;i<15;i++)
                sendDataLCU[i] = '\0';

            if(authorizeMethodConn2 == RFID){
                for(i=0;i<lengthRFID;i++)
                    sendDataLCU[i] = storeRFIDDataConn2[i];
                sendDataLCU[i] = ',';
                sendDataLCU[i+1] = '2';
                sendDataLCU[i+2] = '\0';
                UARTWrite("Authorize",sendDataLCU);
            }
            else if(authorizeMethodConn2 == password){
                for(i=0;i<strlen(sendPasswordStr);i++)
                    sendDataLCU[i] = sendPasswordStr[i];
                sendDataLCU[i] = ',';
                sendDataLCU[i+1] = '2';
                sendDataLCU[i+2] = '\0';
                UARTWrite("Authorize",sendDataLCU);
            }
        }

        if(sendMeterValueConn1){
            int32ToStr((Uint32)(EnergyConn1*1000),energyActiveImportRegisterStr,5);
            int32ToStr((Uint32)(PAvgConn1*1000),powerActiveImportStr,5);
            int32ToStr((Uint32)((VrnRms+VynRms+VbnRms)/3),voltageStr,3);
            int32ToStr((Uint32)(avgCurrentConn1()),currentImportStr,2);

            int i=0;
            int j=0;
            while(energyActiveImportRegisterStr[j])
                meterValuesStr[i++] = energyActiveImportRegisterStr[j++];
            meterValuesStr[i]=',';
            i++;
            j=0;
            while(powerActiveImportStr[j])
                meterValuesStr[i++] = powerActiveImportStr[j++];
            meterValuesStr[i]=',';
            i++;
            j=0;
            while(voltageStr[j])
                meterValuesStr[i++] = voltageStr[j++];
            meterValuesStr[i]=',';
            i++;
            j=0;
            while(currentImportStr[j])
                meterValuesStr[i++] = currentImportStr[j++];
            meterValuesStr[i]=',';
            meterValuesStr[i+1]='1';
            meterValuesStr[i+2]='\0';

            UARTWrite("MeterValues",meterValuesStr);
        }

        if(sendMeterValueConn2){
            int32ToStr((Uint32)(EnergyConn2*1000),energyActiveImportRegisterStr,5);
            int32ToStr((Uint32)(PAvgConn2*1000),powerActiveImportStr,5);
            int32ToStr((Uint32)((VrnRms+VynRms+VbnRms)/3),voltageStr,3);
            int32ToStr((Uint32)(avgCurrentConn2()),currentImportStr,2);

            int i=0;
            int j=0;
            while(energyActiveImportRegisterStr[j])
                meterValuesStr[i++] = energyActiveImportRegisterStr[j++];
            meterValuesStr[i]=',';
            i++;
            j=0;
            while(powerActiveImportStr[j])
                meterValuesStr[i++] = powerActiveImportStr[j++];
            meterValuesStr[i]=',';
            i++;
            j=0;
            while(voltageStr[j])
                meterValuesStr[i++] = voltageStr[j++];
            meterValuesStr[i]=',';
            i++;
            j=0;
            while(currentImportStr[j])
                meterValuesStr[i++] = currentImportStr[j++];
            meterValuesStr[i]=',';
            meterValuesStr[i+1]='2';
            meterValuesStr[i+2]='\0';

            UARTWrite("MeterValues",meterValuesStr);
        }

        if(sendStatusNotificationConn1){
            sendStatusNotificationWithErrorCode(sendStatusNotificationConn1, statusNotificationErrorCodeConn1, 1);
            if(sendStatusNotificationConn1 == faulted)
                currentConnector1Status = unavailable;
            else
                currentConnector1Status = sendStatusNotificationConn1;
        }

        if(sendStatusNotificationConn2 && selectedStandardGunB != 0){
            sendStatusNotificationWithErrorCode(sendStatusNotificationConn2, statusNotificationErrorCodeConn2, 2);

            if(sendStatusNotificationConn2 == faulted)
                currentConnector2Status = unavailable;
            else
                currentConnector2Status = sendStatusNotificationConn2;
        }

        if(sendResetHardMessage)
            UARTWrite("Reset","Hard");

        if(resetDoneFlag &&
                (CurrentStateConn1 == 'A' || CurrentStateConn1 == 'F' || CurrentStateConn1 == 'E') &&
                (((CurrentStateConn2 == 'A' || CurrentStateConn2 == 'F' || CurrentStateConn2 == 'E') && selectedStandardGunB != 0) || selectedStandardGunB == 0)){
            onBootUp = 0;
            internetStatusActive = 2;
            websocketStatusActive = 2;
            bootNotificationStatusFlag = 0;
            softwareCheckComplete = 0;
            resetConnector1Variables();
            resetConnector2Variables();
            state = hardwareCheck;
            HMIWrite("page HardwareCheck");
            resetDoneFlag = 0;
        }

        transmitDataToLCU = 0;
    } //end of transmitDataToLCU


    // ******************Change connector status in Offline Mode******************
    if(sendStatusNotificationConn1 && chargerMode == offlineMode){
        if(sendStatusNotificationConn1 == faulted)
            currentConnector1Status = unavailable;
        else
            currentConnector1Status = sendStatusNotificationConn1;
        sendStatusNotificationConn1 = 0;
    }
    if(sendStatusNotificationConn2 && chargerMode == offlineMode && selectedStandardGunB != 0){
        if(sendStatusNotificationConn2 == faulted)
            currentConnector2Status = unavailable;
        else
            currentConnector2Status = sendStatusNotificationConn2;
        sendStatusNotificationConn2 = 0;
    }

} //end of processLCUData

void UARTWrite(char *message,char *data)
{
    while(*message)
    {
        while (ScicRegs.SCICTL2.bit.TXEMPTY == 0);
        ScicRegs.SCITXBUF.bit.TXDT = *message++ ;
    }
    while (ScicRegs.SCICTL2.bit.TXEMPTY == 0);
    ScicRegs.SCITXBUF.bit.TXDT = ':';
    while(*data)
    {
        while (ScicRegs.SCICTL2.bit.TXEMPTY == 0);
        ScicRegs.SCITXBUF.bit.TXDT = *data++ ;
    }
    while (ScicRegs.SCICTL2.bit.TXEMPTY == 0);
    ScicRegs.SCITXBUF.bit.TXDT = '\r';
    while (ScicRegs.SCICTL2.bit.TXEMPTY == 0);
    ScicRegs.SCITXBUF.bit.TXDT = '\n';
}

void extractLCUData(char *data,char *parameter1,char *parameter2,char *parameter3){
    int i=0;
    int j=0;
    while(data[i] && data[i]!=','){
        parameter1[j++] = data[i];
        i++;
    }
    parameter1[j] = '\0';
    if(sizeof(parameter2)>1){
        j=0;
        i++;
        while(data[i] && data[i]!=','){
            parameter2[j++] = data[i];
            i++;
        }
        parameter2[j] = '\0';
    }
    if(sizeof(parameter3)>1){
        j=0;
        i++;
        while(data[i] && data[i]!=','){
            parameter3[j++] = data[i];
            i++;
        }
        parameter3[j] = '\0';
    }
}

void clearStrings(void){
    int i=0;
    indexM = 0;
    indexD = 0;
    index = 0;
    for(i=0;i<150;i++)
        UARTDataLCU[i] = '\0';
    for(i=0;i<50;i++)
        MessageName[i] = '\0';
    for(i=0;i<150;i++)
        Data[i] = ' ';
}

void clearStoredRFIDTagConn1(void){
    int i;
    for(i=0; i<lengthRFID+1; i++)
        storeRFIDDataConn1[i] = '\0';
}

void clearStoredRFIDTagConn2(void){
    int i;
    for(i=0; i<lengthRFID+1; i++)
        storeRFIDDataConn2[i] = '\0';
}

void sendStatusNotificationWithErrorCode(Uint16 connectorStatus, Uint16 error, Uint16 connectorId){

    Uint16 i=0,j=0;

    while(status[connectorStatus][i]){
        statusNotificationData[j] = status[connectorStatus][i];
        i++;
        j++;
    }
    statusNotificationData[j] = ',';
    j++;
    i=0;
    while(errorCode[error][i]){
        statusNotificationData[j] = errorCode[error][i];
        i++;
        j++;
    }
    statusNotificationData[j] = ',';
    j++;
    if(connectorId == 1)
        statusNotificationData[j] = '1';
    else if(connectorId == 2)
        statusNotificationData[j] = '2';
    j++;
    statusNotificationData[j] = '\0';

    UARTWrite("StatusNotification",statusNotificationData);
}

void clearReservationConn1(void){
    Uint16 i;

    for(i=0;i<lengthReservedIdTag;i++)
        reservedIdTagConn1[i] = '\0';
    for(i=0;i<30;i++)
        reservedExpiryDateTimeConn1[i] = '\0';

    if(currentConnector1Status == reserved)
        currentConnector1Status = available;
}

void clearReservationConn2(void){
    Uint16 i;

    for(i=0;i<lengthReservedIdTag;i++)
        reservedIdTagConn2[i] = '\0';
    for(i=0;i<30;i++)
        reservedExpiryDateTimeConn2[i] = '\0';

    if(currentConnector2Status == reserved)
        currentConnector2Status = available;
}
