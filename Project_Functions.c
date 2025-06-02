#include <GTSI_1Phase1MPPT.h>              // Main include file



/********************************************************************
* Function: displayNotChargingReason()
********************************************************************/
void displayNotChargingReason(){
    if(faultDetectConn1 == 15 || faultDetectConn2 == 15)
        HMIWrite("mpt2.txt=\"Emergency Stop\"");
    else if(faultDetectConn1 == 16 || faultDetectConn2 == 16)
        HMIWrite("mpt2.txt=\"Grid Over Voltage\"");
    else if(faultDetectConn1 == 17 || faultDetectConn2 == 17)
        HMIWrite("mpt2.txt=\"Grid Under Voltage\"");
    else if(faultDetectConn1 == 18 || faultDetectConn2 == 18)
        HMIWrite("mpt2.txt=\"Earth Leakage\"");
    else if(faultDetectConn1 == 19 || faultDetectConn2 == 19)
        HMIWrite("mpt2.txt=\"Thermal\"");
    else if(faultDetectConn1 == 20 || faultDetectConn2 == 20)
        HMIWrite("mpt2.txt=\"Residual Current\"");
    else if(faultDetectConn1 == 21 || faultDetectConn2 == 21)
        HMIWrite("mpt2.txt=\"Over Current\"");
    else if(faultDetectConn1 == 22 || faultDetectConn2 == 22)
        HMIWrite("mpt2.txt=\"CP ShortCkt\"");
}

/********************************************************************
* Function: displayStopReason()
********************************************************************/
void displayStopReason(Uint16 chargingStoppedReason){
    if(chargingStoppedReason == 11)
        HMIWrite("stopReason.txt=\"Mobile App\"");
    else if(chargingStoppedReason == 12)
        HMIWrite("stopReason.txt=\"RFID Tapped\"");
    else if(chargingStoppedReason == 13)
        HMIWrite("stopReason.txt=\"Stop Button\"");
    else if(chargingStoppedReason == 14)
        HMIWrite("stopReason.txt=\"System Reset\"");
    else if(chargingStoppedReason == 15)
        HMIWrite("stopReason.txt=\"Emergency Stop\"");
    else if(chargingStoppedReason == 16)
        HMIWrite("stopReason.txt=\"Grid Over Voltage Fault\"");
    else if(chargingStoppedReason == 17)
        HMIWrite("stopReason.txt=\"Grid Under Voltage Fault\"");
    else if(chargingStoppedReason == 18)
        HMIWrite("stopReason.txt=\"Earth Leakage Fault\"");
    else if(chargingStoppedReason == 19)
        HMIWrite("stopReason.txt=\"Thermal Fault\"");
    else if(chargingStoppedReason == 20)
        HMIWrite("stopReason.txt=\"Residual Current Fault\"");
    else if(chargingStoppedReason == 21)
        HMIWrite("stopReason.txt=\"Over Current Fault\"");
    else if(chargingStoppedReason == 22)
        HMIWrite("stopReason.txt=\"CP ShortCkt Fault\"");
    else if(chargingStoppedReason == 23)
        HMIWrite("stopReason.txt=\"Charging Complete\"");
    else if(chargingStoppedReason == 24)
        HMIWrite("stopReason.txt=\"Stopped from EV\"");
    else if(chargingStoppedReason == 25)
        HMIWrite("stopReason.txt=\"Charging Complete\"");
    else if(chargingStoppedReason == 26)
        HMIWrite("stopReason.txt=\"ID Tag Deauthorized\"");
    else
        HMIWrite("stopReason.txt=\"Power Outage\"");
}

/********************************************************************
* Function: resetConnector1Variables()
********************************************************************/
void resetConnector1Variables(void){
    EnergyConn1 = 0.0;
    totalChargeDurationCounterConn1 = 0;
    authorizeMethodConn1 = NULL;
    authenticationStatusConn1 = 0;
    authorizeACKConn1 = NULL;
    chargingStoppedReasonConn1 = 0;
    validPasswordConn1 = 0;
    validRFIDConn1 = 0;
    offlineChargingAmountConn1 = 0.0;
    logSessionDataFlagConn1 = 0;

    RelayOFF_Gun1 = 1;
    if(authenticationForDifferentConnector == 1)
        authenticationForDifferentConnector = 0;

    clearStoredRFIDTagConn1();
}

/********************************************************************
* Function: resetConnector1Variables()
********************************************************************/
void showWiFiAndServerInfo(void){
    Uint16 i=0,j=0;
    char ssidText[]="DefNetwork.txt=\"                         \"";
    char passwordText[]="password.txt=\"                         \"";
    char connURLText[]="EndPtURL.txt=\"                                                                           \"";
    char hostText[]="Host.txt=\"                                                                           \"";
    char portText[]="PortNum.txt=\"          \"";

    if(internetStatusActive != 2){
        HMIWrite("vis warning,0");
        HMIWrite("modifyWiFiInfo.pic=91");
        HMIWrite("modifyServInfo.pic=91");
        HMIWrite("tsw modifyWiFiInfo,1");
        HMIWrite("tsw modifyServInfo,1");
    }
    else{
        if(chargerMode == offlineMode)
            HMIWrite("warning.txt=\"Switch to Online Mode to Modify\"");

        HMIWrite("vis warning,1");
        HMIWrite("modifyWiFiInfo.pic=137");
        HMIWrite("tsw modifyWiFiInfo,0");
        HMIWrite("modifyServInfo.pic=137");
        HMIWrite("tsw modifyServInfo,0");
    }

    // Display existing Default Network and Password
    if(strlen(defaultNetwork) != 0){
        i=0,j=0;
        while(defaultNetwork[j] != ','){
            ssidText[i+16] = defaultNetwork[j];
            i++;
            j++;
        }
        j++;

        i=0;
        while(defaultNetwork[j] != '\0'){
            passwordText[i+14] = defaultNetwork[j];
            i++;
            j++;
        }

        HMIWrite(ssidText);
        HMIWrite(passwordText);
    }
    else if((EEPROM_ReadByte(addressDefaultSSID) != 0xFF) && (EEPROM_ReadByte(addressDefaultPassword) != 0xFF)){
        i=0;
        while((char)EEPROM_ReadByte(addressDefaultSSID+i) != '\0'){
            ssidText[i+16] = (char)EEPROM_ReadByte(addressDefaultSSID+i);
            i++;
        }

        i=0;
        while((char)EEPROM_ReadByte(addressDefaultPassword+i) != '\0'){
            passwordText[i+14] = (char)EEPROM_ReadByte(addressDefaultPassword+i);
            i++;
        }

        HMIWrite(ssidText);
        HMIWrite(passwordText);
    }
    else{
        HMIWrite("DefNetwork.txt=\"Not Configured\"");
        HMIWrite("password.txt=\"Not Configured\"");
    }

    // Display Existing URL parameters
    if(strlen(url) != 0){
        i=0,j=0;
        while(url[j] != ','){
            connURLText[i+14] = url[j];
            i++;
            j++;
        }
        j++;

        i=0;
        while(url[j] != ','){
            hostText[i+10] = url[j];
            i++;
            j++;
        }
        j++;

        i=0;
        while(url[j] != '\0'){
            portText[i+13] = url[j];
            i++;
            j++;
        }

        HMIWrite(connURLText);
        HMIWrite(hostText);
        HMIWrite(portText);
    }
    else if((EEPROM_ReadByte(addressEndPointURL) != 0xFF) && (EEPROM_ReadByte(addressHost) != 0xFF) && (EEPROM_ReadByte(addressPortNumber) != 0xFF)){
        i=0;
        while((char)EEPROM_ReadByte(addressEndPointURL+i) != '\0'){
            connURLText[i+14] = (char)EEPROM_ReadByte(addressEndPointURL+i);
            i++;
        }

        i=0;
        while((char)EEPROM_ReadByte(addressHost+i) != '\0'){
            hostText[i+10] = (char)EEPROM_ReadByte(addressHost+i);
            i++;
        }

        i=0;
        while((char)EEPROM_ReadByte(addressPortNumber+i) != '\0'){
            hostText[i+13] = (char)EEPROM_ReadByte(addressPortNumber+i);
            i++;
        }

        HMIWrite(connURLText);
        HMIWrite(hostText);
        HMIWrite(portText);
    }
    else{
        HMIWrite("EndPtURL.txt=\"Not Configured\"");
        HMIWrite("Host.txt=\"Not Configured\"");
        HMIWrite("PortNum.txt=\"Not Configured\"");
    }

}

/********************************************************************
* Function: validRangeWarningForPowerSetting()
********************************************************************/
void validRangeWarningForPowerSetting(void){

    //Valid Range Suggestion or Warning on Set Power Screen
    if(selectedStandardGunA == Type2AC || selectedStandardGunB == Type2AC){
        if(numberOfPhases == one && selectedNumberofGuns == 1)
            HMIWrite("warning.txt=\"Valid Range : 1.4 kW to 18.4 kW\"");
        else if(numberOfPhases == one && selectedNumberofGuns == 2)
            HMIWrite("warning.txt=\"Valid Range : 2.8 kW to 36.8 kW\"");
        else if(numberOfPhases == three && selectedNumberofGuns == 1)
            HMIWrite("warning.txt=\"Valid Range : 4.2 kW to 55.2 kW\"");
        else if(numberOfPhases == three && selectedNumberofGuns == 2)
            HMIWrite("warning.txt=\"Valid Range : 8.2 kW to 110.4 kW\"");
    }
    else
        HMIWrite("warning.txt=\"Valid Range : 1.0 kW to 110.4 kW\"");
}

/********************************************************************
* Function: showChargerRatedPowerAndSerialNumberInfo()
********************************************************************/
void showChargerRatedPowerAndSerialNumberInfo(void){

         //Display charger rated power configured
        if(EEPROM_ReadByte(addressTotalRatedPowerInt) != 0xFF && EEPROM_ReadByte(addressTotalRatedPowerInt+1) != 0xFF && EEPROM_ReadByte(addressTotalRatedPowerFloat) != 0xFF)
            memoryRatedPower = ((EEPROM_ReadByte(addressTotalRatedPowerInt) * 10) + EEPROM_ReadByte(addressTotalRatedPowerInt+1)) + (EEPROM_ReadByte(addressTotalRatedPowerFloat)/10.0);

        char chargerRatedPowerStr[6];
        char chargerRatedPowerHMIStr[] = "totalPower.txt=\"     \"";

        if(validRatedPowerSinglePhaseSingleGunType2AC || validRatedPowerSinglePhaseDualGunType2AC || validRatedPowerThreePhaseSingleGunType2AC || validRatedPowerThreePhaseDualGunType2AC || validRatedPowerAC001){
            if(dummyChargerRatedPowerValue > 0.0 && dummyChargerRatedPowerValue <= 110.0){
                ftoa(dummyChargerRatedPowerValue, chargerRatedPowerStr, 1);
                replaceStringHMI(chargerRatedPowerHMIStr, chargerRatedPowerStr);
            }
            else if(memoryRatedPower != 0xFF && memoryRatedPower != 0){
                ftoa(memoryRatedPower, chargerRatedPowerStr, 1);
                replaceStringHMI(chargerRatedPowerHMIStr, chargerRatedPowerStr);
            }
        }
        else
            HMIWrite("totalPower.txt=\"Not Configured\"");

        // Display Serial Number setting
        char displaySerialNumber[] = "serialNumber.txt=\"A2300001\"";
        int i=0;

        for(i=0;i<8;i++)
            displaySerialNumber[i+18] = EEPROM_ReadByte(addressSerialNumber+i);

        if(EEPROM_ReadByte(addressSerialNumber) != 0xFF)
            HMIWrite(displaySerialNumber);
        else
            HMIWrite("serialNumber.txt=\"Not Configured\"");
}

/********************************************************************
* Function: resetConnector2Variables()
********************************************************************/
void resetConnector2Variables(void){
    EnergyConn2 = 0.0;
    totalChargeDurationCounterConn2 = 0;
    authorizeMethodConn2 = NULL;
    authenticationStatusConn2 = 0;
    authorizeACKConn2 = NULL;
    chargingStoppedReasonConn2 = 0;
    validPasswordConn2 = 0;
    validRFIDConn2 = 0;
    offlineChargingAmountConn2 = 0.0;
    logSessionDataFlagConn2 = 0;

    RelayOFF_Gun2 = 1;
    if(authenticationForDifferentConnector == 2)
        authenticationForDifferentConnector = 0;

    clearStoredRFIDTagConn2();
}


/********************************************************************
* Function: showSSIDs()
********************************************************************/
void showSSIDs(void){
    clearSSIDs();
    HMIWrite("t0.txt=\"Please Wait, Searching for Networks...\"");

    UARTWrite("NAP","");

    if(NAPReqMsgSent == 0)
        NAPReqMsgSent = 1;

    while(!NAPDataMsgRec && NAPReqMsgSent == 1){  //Wait for NAP Response
        processLCUData();
        Delay_ms(50);
    }

    if(numberOfAccessPoints > 0)    // Request SSID1
        UARTWrite("SSID1","");

    while(numberOfAccessPointsRec != numberOfAccessPoints){ //Wait for all SSID's to be received

        processLCUData();
        Delay_ms(50);

        if(backButtonOnWIFIPagePressed){
            state = restrictedAccess;
            HMIWrite("page RestrictedAcs1");
            backButtonOnWIFIPagePressed = false;
            break;
        }
        else if(refreshButtonOnWIFIPagePressed){
            HMIWrite("vis t0,0");
            Delay_ms(500);
            HMIWrite("vis t0,1");
            refreshButtonOnWIFIPagePressed = false;
        }
    }

    if(NAPReqMsgSent == 2){
        HMIWrite("t0.txt=\"No WiFi Connections Available\"");
        Delay_ms(2000);
        if(softwareCheckComplete){
            state = home;
            if(selectedNumberofGuns == 1)
                HMIWrite("page HomePage1");
            else if(selectedNumberofGuns == 2)
                HMIWrite("page HomePage2");
        }
        else{
            state = softwareCheck;
            HMIWrite("page softwareCheck");
        }

        enteredRestrictedAccessMode = 0;
        NAPReqMsgSent = 0;
    }

    if(numberOfAccessPoints != 0){
        HMIWrite("t0.txt=\"Available Connections\"");

        displaySSID('1', SSID1);
        displaySSID('2', SSID2);
        displaySSID('3', SSID3);
        displaySSID('4', SSID4);
        displaySSID('5', SSID5);
        displaySSID('6', SSID6);
        displaySSID('7', SSID7);
        displaySSID('8', SSID8);

    }
    else{
        HMIWrite("t0.txt=\"No WiFi Connections Available\"");
    }
    numberOfAccessPointsRec = 0, numberOfAccessPoints = 0, NAPDataMsgRec = 0;
} //end of showSSIDs

/********************************************************************
* Function: initialChargerConfigurationSettings()
********************************************************************/
void initialChargerConfigurationSettings(void){

    //Read initial configuration key
    if(EEPROM_ReadByte(addressConfigurationKey) == 0xFF){
        // Write Zero at all memory locations --> first time
        selectedBrand = 0;
        selectedStandardGunA = 0;
        selectedStandardGunB = 0;
        chargerRatedPower = 0.0;
        virtualEnergyMeter = 0;
        numberOfPhases = 0;

        EEPROM_WriteByte(addressConfigurationKey, configurationKey);
        EEPROM_WriteByte(addressBrandSelection, selectedBrand);
        EEPROM_WriteByte(addressStandardGunASelection, selectedStandardGunA);
        EEPROM_WriteByte(addressStandardGunBSelection, selectedStandardGunB);
        EEPROM_WriteByte(addressTotalRatedPowerInt, 0);
        EEPROM_WriteByte(addressTotalRatedPowerInt+1, 0);
        EEPROM_WriteByte(addressTotalRatedPowerFloat, 0);
        EEPROM_WriteByte(addressNumberOfGuns, selectedNumberofGuns);
        EEPROM_WriteByte(addressVirtualEnergyMeterSelection, virtualEnergyMeter);
        EEPROM_WriteByte(addressNumberOfPhasesSelection, numberOfPhases);
    }

    // Read all values from memory
    configurationKey = EEPROM_ReadByte(addressConfigurationKey);
    selectedBrand = EEPROM_ReadByte(addressBrandSelection);
    selectedStandardGunA = EEPROM_ReadByte(addressStandardGunASelection);
    selectedStandardGunB = EEPROM_ReadByte(addressStandardGunBSelection);
    chargerRatedPower = ((EEPROM_ReadByte(addressTotalRatedPowerInt) * 10) + EEPROM_ReadByte(addressTotalRatedPowerInt+1)) + (EEPROM_ReadByte(addressTotalRatedPowerFloat)/10.0);
    selectedNumberofGuns = EEPROM_ReadByte(addressNumberOfGuns);
    virtualEnergyMeter =  EEPROM_ReadByte(addressVirtualEnergyMeterSelection);
    numberOfPhases = EEPROM_ReadByte(addressNumberOfPhasesSelection);

    if(EEPROM_ReadByte(addressOfflineMode) != 0xFF)
        chargerMode = EEPROM_ReadByte(addressOfflineMode);

    if(selectedNumberofGuns == 1)
        changeAvailabilityConn2 = inoperative;

    Delay_ms(3000);

//     Read values if charger already configured
    if(configurationKey == 1){

         /* Configuration according to Brand Name, Standard selection for GunA and GunB:-
         *  Used to set background image in HMI and in Serial Number Displayed
         *
         *  Virtual EM Enabled means: Send virtual EM reading as meterStart in StartTransaction.data whenever LCU sends StartTransaction.req
         *  Virtual EM Disabled means: Send '0' value in meterStart in StartTransaction.data whenever LCU sends StartTransaction.req
         */

        // Send values of brand, standards and no. of connectors to HMI for background images
        char brandText[] = "Brand= ";
        char NOCText[] = "NOC= ";
        char STDAText[] = "STDA= ";
        char STDBText[] = "STDB= ";
        char chargerModeStr[]= "ChargerMode=  ";
        char chargerRatedPowerStr[]= "     ";

        intToStr(chargerRatedPower, chargerRatedPowerStr, 4);

        // Send selected brand
        brandText[6] = selectedBrand+48;
        HMIWrite(brandText);

        // Send no. of connectors
        NOCText[4] = selectedNumberofGuns+48;
        HMIWrite(NOCText);

        //Send GunA and GunB selected standards
        if(selectedNumberofGuns == 2){
            STDAText[5] = selectedStandardGunA+48;
            STDBText[5] = selectedStandardGunB+48;

            HMIWrite(STDAText);
            HMIWrite(STDBText);
        }
        else{
            STDAText[5] = selectedStandardGunA+48;

            HMIWrite(STDAText);
        }

        //Send Charger Mode Selection to HMI : Whether Charger is in Online Mode or Offline Mode
        if(chargerMode == onlineMode){
            chargerModeStr[12] = '4';
            chargerModeStr[13] = '8';
        }
        else if(chargerMode == offlineMode){
            chargerModeStr[12] = '4';
            chargerModeStr[13] = '7';
        }
        HMIWrite(chargerModeStr);

       // Compute model number for BootNotification.ChargePointModel
        if(selectedBrand){
            modelNumber[0] = 'P';
            modelNumber[1] = 'E';
        }

        modelNumber[2] = selectedStandardGunA+48;
        if(selectedNumberofGuns == 2)
            modelNumber[3] = selectedStandardGunB+48;
        else
            modelNumber[3] = '0';

        modelNumber[4] = '0';

        // Input type is AC
        modelNumber[5] = 'A';
        modelNumber[6] = 'C';

        // Output type is AC
        modelNumber[7] = 'A';
        modelNumber[8] = 'C';

        modelNumber[9] = chargerRatedPowerStr[0];
        modelNumber[10] = chargerRatedPowerStr[1];
        modelNumber[11] = chargerRatedPowerStr[2];
        modelNumber[12] = chargerRatedPowerStr[3];
        modelNumber[13] = selectedNumberofGuns+48;
        modelNumber[14] = 'F';
        modelNumber[15] = '0';
        modelNumber[16] = '0';

        // Append terminating char for modeNumber String
        modelNumber[17] = '\0';
        limitPowerMax = chargerRatedPower;
        overCurrentConn1 = 1.2*(limitPowerMax*1000.0/(230*numberOfPhases*selectedNumberofGuns));
        overCurrentConn2 = 1.2*(limitPowerMax*1000.0/(230*numberOfPhases*selectedNumberofGuns));
    }
    else if(configurationKey == 0){

        intToStr(chargerRatedPower, chargerRatedPowerStr, 4);

       // Compute model number for BootNotification.ChargePointModel : Just for the purpose of initial MCU-LCU Communication
        modelNumber[0] = 'P';
        modelNumber[1] = 'E';

        modelNumber[2] = selectedStandardGunA+48;
        if(selectedNumberofGuns == 2)
            modelNumber[3] = selectedStandardGunB+48;
        else
            modelNumber[3] = '0';

        modelNumber[4] = '0';

        // Input type is AC
        modelNumber[5] = 'A';
        modelNumber[6] = 'C';

        // Output type is AC
        modelNumber[7] = 'A';
        modelNumber[8] = 'C';

        modelNumber[9] = chargerRatedPowerStr[0];
        modelNumber[10] = chargerRatedPowerStr[1];
        modelNumber[11] = chargerRatedPowerStr[2];
        modelNumber[12] = chargerRatedPowerStr[3];
        modelNumber[13] = selectedNumberofGuns+48;
        modelNumber[14] = 'F';
        modelNumber[15] = '0';
        modelNumber[16] = '0';

        // Append terminating char for modeNumber String
        modelNumber[17] = '\0';
    }
}   //end of initialChargerConfigurationSettings


/********************************************************************
* Function: avgCurrentConn1()
********************************************************************/
float avgCurrentConn1(void){
    /*
     * To send average of all current values to HMI or LCU.
     * Single Phase: average of all three current r1,y1,b1(because r1 value is copied in y1,b1)
     * Three Phase: average of those which are > 2amps
     */

    if(Ir1Rms>2 && Iy1Rms>2 && Ib1Rms>2)        // r1,y1,b1 > 2amps
        return (Ir1Rms+Iy1Rms+Ib1Rms)/3;

    else if(Ir1Rms>2 && Iy1Rms>2 && Ib1Rms<2)   // r1,y1 > 2amps
        return (Ir1Rms+Iy1Rms)/2;

    else if(Ir1Rms>2 && Iy1Rms<2 && Ib1Rms>2)   // r1,b1 > 2amps
        return (Ir1Rms+Ib1Rms)/2;

    else if(Ir1Rms<2 && Iy1Rms>2 && Ib1Rms>2)   // y1,b1 > 2amps
        return (Iy1Rms+Ib1Rms)/2;

    else if(Ir1Rms>2 && Iy1Rms<2 && Ib1Rms<2)   // r1 > 2amps
        return Ir1Rms;

    else if(Ir1Rms<2 && Iy1Rms>2 && Ib1Rms<2)   // y1 > 2amps
        return Iy1Rms;

    else if(Ir1Rms<2 && Iy1Rms<2 && Ib1Rms>2)   // b1 > 2amps
        return Ib1Rms;

    else
        return 0;
}

/********************************************************************
* Function: avgCurrentConn2()
********************************************************************/
float avgCurrentConn2(void){
    /*
     * To send average of all current values to HMI or LCU.
     * Single Phase: average of all three current r2,y2,b2(because r2 value is copied in y2,b2)
     * Three Phase: average of those which are > 2amps
     */

    if(Ir2Rms>2 && Iy2Rms>2 && Ib2Rms>2)        // r2,y2,b2 > 2amps
        return (Ir2Rms+Iy2Rms+Ib2Rms)/3;

    else if(Ir2Rms>2 && Iy2Rms>2 && Ib2Rms<2)   // r2,y2 > 2amps
        return (Ir2Rms+Iy2Rms)/2;

    else if(Ir2Rms>2 && Iy2Rms<2 && Ib2Rms>2)   // r2,b2 > 2amps
        return (Ir2Rms+Ib2Rms)/2;

    else if(Ir2Rms<2 && Iy2Rms>2 && Ib2Rms>2)   // y2,b2 > 2amps
        return (Iy2Rms+Ib2Rms)/2;

    else if(Ir2Rms>2 && Iy2Rms<2 && Ib2Rms<2)   // r2 > 2amps
        return Ir2Rms;

    else if(Ir2Rms<2 && Iy2Rms>2 && Ib2Rms<2)   // y2 > 2amps
        return Iy2Rms;

    else if(Ir2Rms<2 && Iy2Rms<2 && Ib2Rms>2)   // b2 > 2amps
        return Ib2Rms;

    else
        return 0;
}



