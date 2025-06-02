#include <GTSI_1Phase1MPPT.h>                        // Main include file
#include <string.h>
#include <stdio.h>
#include <math.h>

void retrieveValuesFromEEPROM(void)
{
    int i,j;
    Uint32 limitInt;

// ###########################################################################
// -------------------------------- Fault Values -----------------------------
// ###########################################################################

    //Grid Voltage Fault Enable/Disable
    if(EEPROM_ReadByte(addressGridVoltageFaultEnabled) == 1)
        gridVoltageFaultEnabled = 1;
    else if (EEPROM_ReadByte(addressGridVoltageFaultEnabled) == 0)
        gridVoltageFaultEnabled = 0;

    //NE Voltage Fault Enable/Disable
    if(EEPROM_ReadByte(addressNEVoltageFaultEnabled) == 1)
        neVoltageFaultEnabled = 1;
    else if (EEPROM_ReadByte(addressNEVoltageFaultEnabled) == 0)
        neVoltageFaultEnabled = 0;

    //Residual Current Fault Enable/Disable
    if(EEPROM_ReadByte(addressResidualCurrentFaultEnabled) == 1)
        residualCurrentFaultEnabled = 1;
    else if (EEPROM_ReadByte(addressResidualCurrentFaultEnabled) == 0)
        residualCurrentFaultEnabled = 0;

    //Over Current Connector 1 Fault Enable/Disable
    if(EEPROM_ReadByte(addressOverCurrentFaultEnabledConn1) == 1)
        overCurrentFaultEnabledConn1 = 1;
    else if (EEPROM_ReadByte(addressOverCurrentFaultEnabledConn1) == 0)
        overCurrentFaultEnabledConn1 = 0;

    //Over Current Connector 2 Fault Enable/Disable
    if(EEPROM_ReadByte(addressOverCurrentFaultEnabledConn2) == 1)
        overCurrentFaultEnabledConn2 = 1;
    else if (EEPROM_ReadByte(addressOverCurrentFaultEnabledConn2) == 0)
        overCurrentFaultEnabledConn2 = 0;


// ###########################################################################
// ------------------------------ Limit Settings Value ------------------------------
// ###########################################################################

    // Gun A limits
    if(EEPROM_ReadByte(addressGunACurrentLimit) != 0xFF)
        gunAMaxCurrentHMI = EEPROM_ReadByte(addressGunACurrentLimit);
    else
        gunAMaxCurrentHMI = FLT_MAX;    // Initialize to float max otherwise


    if(EEPROM_ReadByte(addressGunAPowerLimit) != 0xFF){
        limitInt = 0, i = 0;
        char limitchar;
        while((char)EEPROM_ReadByte(addressGunAPowerLimit+i) != '\0'){
            limitchar = (char)EEPROM_ReadByte(addressGunAPowerLimit+i);
            limitInt = limitInt*10 + ((Uint16)limitchar - 48);
            i++;
        }
        gunAMaxPowerHMI = (float)limitInt;
    }
    else
        gunAMaxPowerHMI = FLT_MAX;      // Initialize to float max otherwise

    // Gun B limits
    if(EEPROM_ReadByte(addressGunBCurrentLimit) != 0xFF)
        gunBMaxCurrentHMI = EEPROM_ReadByte(addressGunBCurrentLimit);
    else
        gunBMaxCurrentHMI = FLT_MAX;    // Initialize to float max otherwise

    if(EEPROM_ReadByte(addressGunBPowerLimit) != 0xFF){
        limitInt = 0, i = 0;
        char limitchar;
        while((char)EEPROM_ReadByte(addressGunBPowerLimit+i) != '\0'){
            limitchar = (char)EEPROM_ReadByte(addressGunBPowerLimit+i);
            limitInt = limitInt*10 + ((Uint16)limitchar - 48);
            i++;
        }
        gunBMaxPowerHMI = (float)limitInt;
    }
    else
        gunBMaxPowerHMI = FLT_MAX;     // Initialize to float max otherwise

    // Charger Power Limit
    if(EEPROM_ReadByte(addressChargerPowerLimit) != 0xFF){
        limitInt = 0, i = 0;
        while((char)EEPROM_ReadByte(addressChargerPowerLimit+i) != '\0'){
            chargerPowerLimitStr[i] = (char)EEPROM_ReadByte(addressChargerPowerLimit+i);
            limitInt = limitInt*10 + ((Uint16)chargerPowerLimitStr[i] - 48);
            i++;
        }
        chargerPowerLimitHMI = (float)limitInt;
    }
    else
        chargerPowerLimitHMI = FLT_MAX;     // Initialize to float max otherwise


// ###########################################################################
// ------------------------ Change Availability Value ------------------------
// ###########################################################################
    if(EEPROM_ReadByte(addressChangeAvailabilityConn1) != 0xFF)
        changeAvailabilityConn1 = EEPROM_ReadByte(addressChangeAvailabilityConn1);
    if(EEPROM_ReadByte(addressChangeAvailabilityConn2) != 0xFF && selectedNumberofGuns == 2)
        changeAvailabilityConn2 = EEPROM_ReadByte(addressChangeAvailabilityConn2);


// ###########################################################################
// ------------------------- Local List Present Value ------------------------
// ###########################################################################
    if(EEPROM_ReadByte(addressLocalListPresent) != 0xFF)
        localListPresent = EEPROM_ReadByte(addressLocalListPresent);


// ###########################################################################
// --------------------------- Offline Mode Value ----------------------------
// ###########################################################################
    if(EEPROM_ReadByte(addressOfflineMode) != 0xFF)
        chargerMode = EEPROM_ReadByte(addressOfflineMode);

    if(EEPROM_ReadByte(addressOfflineModePrevious) != 0xFF)
        chargerModePrevious = EEPROM_ReadByte(addressOfflineModePrevious);

    //Test Mode
    chargerMode = offlineMode;
    chargerModePrevious = offlineMode;

    //BootUp In Offline Mode
    if(chargerMode == offlineMode){
        ScicRegs.SCICTL1.bit.RXENA = 0;     // Disable Receiver
        PieCtrlRegs.PIEIER8.bit.INTx5 = 0;  // Disable Interrupt
        currentConnector1Status = available;
        currentConnector2Status = available;

        if(EEPROM_ReadByte(addressOfflinePassword+i) != 0xFF){
            i=0;
            while(EEPROM_ReadByte(addressOfflinePassword+i) != '\0')
                storeOfflinePassword[i++] = EEPROM_ReadByte(addressOfflinePassword+i);
            storeOfflinePassword[i] = '\0';
        }
    }


// ###########################################################################
// --------------------------- Per Unit Cost Value ---------------------------
// ###########################################################################
    if(EEPROM_ReadByte(addressCostPerUnitInt) != 0xFF && EEPROM_ReadByte(addressCostPerUnitInt+1) != 0xFF && EEPROM_ReadByte(addressCostPerUnitFloat) != 0xFF)
        perUnitCost = ((EEPROM_ReadByte(addressCostPerUnitInt) * 10) + EEPROM_ReadByte(addressCostPerUnitInt+1)) + (EEPROM_ReadByte(addressCostPerUnitFloat)/100.00);


// ----------------------- Virtual Energy Meter Value ------------------------
// ###########################################################################
    if(EEPROM_ReadByte(addressVirtualEnergyMeterValue) != 0xFF && EEPROM_ReadByte(addressVirtualEnergyMeterValue+1) != 0xFF){
        i=0;
        while(EEPROM_ReadByte(addressVirtualEnergyMeterValue+i) != '\0'){
            virtualEnergyMeterValue = virtualEnergyMeterValue*10 + (EEPROM_ReadByte(addressVirtualEnergyMeterValue+i) - '0');
            i++;
        }
    }

// ###########################################################################
// -------------------------- Default Network Value --------------------------
// ###########################################################################
    if(EEPROM_ReadByte(addressDefaultSSID) != 0xFF && EEPROM_ReadByte(addressDefaultPassword) != 0xFF){
        i=0,j=0;
        while((char)EEPROM_ReadByte(addressDefaultSSID+i) != '\0'){
            defaultNetwork[j] = (char)EEPROM_ReadByte(addressDefaultSSID+i);
            i++;
            j++;
        }

        defaultNetwork[j] = ',';
        j++;

        i=0;
        while((char)EEPROM_ReadByte(addressDefaultPassword+i) != '\0'){
            defaultNetwork[j] = (char)EEPROM_ReadByte(addressDefaultPassword+i);
            i++;
            j++;
        }

        defaultNetwork[j] = '\0';
    }
    else if(EEPROM_ReadByte(addressDefaultSSID) == 0xFF && EEPROM_ReadByte(addressDefaultPassword) == 0xFF){
        char SSID[] = "ssid";
        char Password[] = "password";

        for(i=0;i<strlen(SSID);i++)
            EEPROM_WriteByte(addressDefaultSSID+i, (Uint16)SSID[i]);

        EEPROM_WriteByte(addressDefaultSSID+i, (Uint16)'\0');       // To determine end of string in memory

        for(i=0;i<strlen(Password);i++)
            EEPROM_WriteByte(addressDefaultPassword+i, (Uint16)Password[i]);

        EEPROM_WriteByte(addressDefaultPassword+i, (Uint16)'\0');       // To determine end of string in memory

        i=0,j=0;
        while((char)EEPROM_ReadByte(addressDefaultSSID+i) != '\0'){
            defaultNetwork[j] = (char)EEPROM_ReadByte(addressDefaultSSID+i);
            i++;
            j++;
        }

        defaultNetwork[j] = ',';
        j++;

        i=0;
        while((char)EEPROM_ReadByte(addressDefaultPassword+i) != '\0'){
            defaultNetwork[j] = (char)EEPROM_ReadByte(addressDefaultPassword+i);
            i++;
            j++;
        }

        defaultNetwork[j] = '\0';
    }

// ###########################################################################
// -------------------------------- URL Value --------------------------------
// ###########################################################################
    if(EEPROM_ReadByte(addressEndPointURL) == 0xFF && EEPROM_ReadByte(addressHost) == 0xFF && EEPROM_ReadByte(addressPortNumber) == 0xFF){
        char OCPP_URL[] = "ws://ocpp.chargehq.net/ocpp16/ewe777";
        char OCPP_Host[] = "ocpp.chargehq.net";
        char OCPP_PORT[] = "80";

        for(i=0;i<strlen(OCPP_URL);i++)
            EEPROM_WriteByte(addressEndPointURL+i, (Uint16)OCPP_URL[i]);

        EEPROM_WriteByte(addressEndPointURL+i, (Uint16)'\0');       // To determine end of string in memory

        for(i=0;i<strlen(OCPP_Host);i++)
            EEPROM_WriteByte(addressHost+i, (Uint16)OCPP_Host[i]);

        EEPROM_WriteByte(addressHost+i, (Uint16)'\0');       // To determine end of string in memory

        for(i=0;i<strlen(OCPP_PORT);i++)
            EEPROM_WriteByte(addressPortNumber+i, (Uint16)OCPP_PORT[i]);

        EEPROM_WriteByte(addressPortNumber+i, (Uint16)'\0');       // To determine end of string in memory
    }

    i=0;
    j=0;
    while((char)EEPROM_ReadByte(addressEndPointURL+i) != '\0'){
        url[j] = (char)EEPROM_ReadByte(addressEndPointURL+i);
        i++;
        j++;
    }

    url[j] = ',';
    j++;

    i=0;
    while((char)EEPROM_ReadByte(addressHost+i) != '\0'){
        url[j] = (char)EEPROM_ReadByte(addressHost+i);
        i++;
        j++;
    }

    url[j] = ',';
    j++;

    i=0;
    while((char)EEPROM_ReadByte(addressPortNumber+i) != '\0'){
        url[j] = (char)EEPROM_ReadByte(addressPortNumber+i);
        i++;
        j++;
    }

    url[j] = '\0';
}

void sessionDataLogging(void){
    /*
     * logSessionDataFlagConn(x) = 0    Initial Value
     *   Value changed in ADC ISR
     * logSessionDataFlagConn(x) = 1    Log Start Session Data
     *      Value changed here
     * logSessionDataFlagConn(x) = 2    Charging Ongoing(DO NOTHING)
     *  Value changed in ADC ISR
     * logSessionDataFlagConn(x) = 3    Log End Session Data
     *      Value changed here
     * logSessionDataFlagConn(x) = 4    Resetting all variables(DO NOTHING)
     *          x = 1,2
     */

    char virtualEnergyMeterValueStr[20];
    int i;

    // -------- Connector 1 --------
    if(logSessionDataFlagConn1 == 1){
        readDateTimeRTC();
        for(i=0;i<8;i++)
            startTimeStrConn1[i] = Time[i];
        logStartSessionDataConn1(Date, Time);
        logSessionDataFlagConn1 = 2;
    }

    if(logSessionDataFlagConn1 == 3){
        logEndSessionDataConn1(Date, Time, EnergyConn1, totalChargeDurationCounterConn1/60, chargingStoppedReasonConn1);
        logEnergyData(EnergyConn1);

        // ----- Log Virtual Energy Meter Value -----
        int64ToStr(virtualEnergyMeterValue, virtualEnergyMeterValueStr, 1);
        for(i=0;i<strlen(virtualEnergyMeterValueStr);i++)
            EEPROM_WriteByte(addressVirtualEnergyMeterValue+i, virtualEnergyMeterValueStr[i]);
        EEPROM_WriteByte(addressVirtualEnergyMeterValue+i, '\0');

        if(selectedStandardGunA == AC001){
            while(sendStatusNotificationConn1 != 0){
                processLCUData();
            }
            authenticationStatusConn1 = 0;
        }

        logSessionDataFlagConn1 = 4;
    }

    // -------- Connector 2 --------
    if(logSessionDataFlagConn2 == 1){
        readDateTimeRTC();
        for(i=0;i<8;i++)
            startTimeStrConn2[i] = Time[i];
        logStartSessionDataConn2(Date, Time);
        logSessionDataFlagConn2 = 2;
    }

    if(logSessionDataFlagConn2 == 3){
        logEndSessionDataConn2(Date, Time, EnergyConn2, totalChargeDurationCounterConn2/60, chargingStoppedReasonConn2);
        logEnergyData(EnergyConn2);

        // ----- Log Virtual Energy Meter Value -----
        int64ToStr(virtualEnergyMeterValue, virtualEnergyMeterValueStr, 1);
        for(i=0;i<strlen(virtualEnergyMeterValueStr);i++)
            EEPROM_WriteByte(addressVirtualEnergyMeterValue+i, virtualEnergyMeterValueStr[i]);
        EEPROM_WriteByte(addressVirtualEnergyMeterValue+i, '\0');

        if(selectedStandardGunB == AC001){
            while(sendStatusNotificationConn2 != 0){
                processLCUData();
            }
            authenticationStatusConn2 = 0;
        }

        logSessionDataFlagConn2 = 4;
    }
}

const int monthDays[12]
    = { 31, 28, 31, 30, 31, 30,
       31, 31, 30, 31, 30, 31 };

// Return if year is leap year or not.
bool isLeap(int y){
    if (y%100 != 0 && y%4 == 0 || y %400 == 0)
        return true;

    return false;
}


// Given a date, returns number of days elapsed
// from the  beginning of the current year (1st jan).
int offsetDays(int d, int m, int y){
    int offset = d;

    switch (m - 1){
        case 11:
            offset += 30;
        case 10:
            offset += 31;
        case 9:
            offset += 30;
        case 8:
            offset += 31;
        case 7:
            offset += 31;
        case 6:
            offset += 30;
        case 5:
            offset += 31;
        case 4:
            offset += 30;
        case 3:
            offset += 31;
        case 2:
            offset += 28;
        case 1:
            offset += 31;
    }
    if (isLeap(y) && m > 2)
        offset += 1;
    return offset;
}

// Given a year and days elapsed in it, finds
// date by storing results in d and m.
void revoffsetDays(int offset, int y, int *d, int *m){
    int month[13] = { 0, 31, 28, 31, 30, 31, 30,
                      31, 31, 30, 31, 30, 31 };

    if(isLeap(y))
        month[2] = 29;

    int i;
    for (i = 1; i <= 12; i++){
        if (offset <= month[i])
            break;
        offset = offset - month[i];
    }

    *d = offset;
    *m = i;
}

void addDays(char *date, int x){

    int d1, m1, y1;

    d1 = (date[0] - 48)*10 + (date[1] - 48);
    m1 = (date[3] - 48)*10 + (date[4] - 48);
    y1 = 2000 + (date[6] - 48)*10 + (date[7] - 48);

    int offset1 = offsetDays(d1, m1, y1);
    int remDays = isLeap(y1)?(366-offset1):(365-offset1);


    // y2 is going to store result year and
    // offset2 is going to store offset days
    // in result year.
    int y2, offset2;
    if (x <= remDays){
        y2 = y1;
        offset2 = offset1 + x;
    }
    else
    {
        // x may store thousands of days.
        // We find correct year and offset
        // in the year.
        x -= remDays;
        y2 = y1 + 1;
        int y2days = isLeap(y2)?366:365;
        while (x >= y2days){
            x -= y2days;
            y2++;
            y2days = isLeap(y2)?366:365;
        }
        offset2 = x;
    }

    // Find values of day and month from
    // offset of result year.
    int m2, d2;
    revoffsetDays(offset2, y2, &d2, &m2);

    y2 -= 2000;

    calculatedDate[0] = d2/10 + 48;
    calculatedDate[1] = d2%10 + 48;
    calculatedDate[2] = '/';
    calculatedDate[3] = m2/10 + 48;
    calculatedDate[4] = m2%10 + 48;
    calculatedDate[5] = '/';
    calculatedDate[6] = y2/10 + 48;
    calculatedDate[7] = y2%10 + 48;
    calculatedDate[8] = '\0';
}

void resetEEPROMData(void){
    // Reset Tariff
    EEPROM_WriteByte(addressCostPerUnitInt, 0xFF);       // Lower Byte
    EEPROM_WriteByte(addressCostPerUnitInt+1, 0xFF);     // Upper Byte
    EEPROM_WriteByte(addressCostPerUnitFloat, 0xFF);

    // For Charging Session Logs
    EEPROM_WriteByte(nextLogPointerLocationConn1, 0xFF);       // Lower Byte
    EEPROM_WriteByte(nextLogPointerLocationConn1+1, 0xFF);     // Upper Byte
    EEPROM_WriteByte(sessionStopLocationConn1, 0xFF);
    EEPROM_WriteByte(sessionsLoggedLocationConn1, 0xFF);

    // For Connector 2 Charging Session Logs
    EEPROM_WriteByte(nextLogPointerLocationConn2, 0xFF);       // Lower Byte
    EEPROM_WriteByte(nextLogPointerLocationConn2+1, 0xFF);     // Upper Byte
    EEPROM_WriteByte(sessionStopLocationConn2, 0xFF);
    EEPROM_WriteByte(sessionsLoggedLocationConn2, 0xFF);

    // For Energy Data
    EEPROM_WriteByte(addressFirstDate, 0xFF);
    EEPROM_WriteByte(addressFirstDate+1, 0xFF);
    EEPROM_WriteByte(addressFirstMonth, 0xFF);
    EEPROM_WriteByte(addressFirstMonth+1, 0xFF);
    EEPROM_WriteByte(addressFirstYear, 0xFF);
    EEPROM_WriteByte(addressFirstYear+1, 0xFF);

    //For Virtual Energy Meter Value
    EEPROM_WriteByte(addressVirtualEnergyMeterValue, 0xFF);
    EEPROM_WriteByte(addressVirtualEnergyMeterValue+1, 0xFF);
    virtualEnergyMeterValue = 0;


    dataLoggingInit();
}

void dataLoggingInit(void){

//     Energy Data Logging Initialization: Start
//     Read RTC Date
    Date[0] = BCD2UpperCh(RTC_ReadByte(0x04));    // Date
    Date[1] = BCD2LowerCh(RTC_ReadByte(0x04));
    Date[3] = BCD2UpperCh(RTC_ReadByte(0x05));    // Month
    Date[4] = BCD2LowerCh(RTC_ReadByte(0x05));
    Date[6] = BCD2UpperCh(RTC_ReadByte(0x06));    // Year
    Date[7] = BCD2LowerCh(RTC_ReadByte(0x06));

    // Write First date of data logging in EEPROM and keep a track of current date
    firstDateEEPROM = (EEPROM_ReadByte(addressFirstDate + 1) << 8) | EEPROM_ReadByte(addressFirstDate);
    firstMonthEEPROM = (EEPROM_ReadByte(addressFirstMonth + 1) << 8) | EEPROM_ReadByte(addressFirstMonth);
    firstYearEEPROM = (EEPROM_ReadByte(addressFirstYear + 1) << 8) | EEPROM_ReadByte(addressFirstYear);

    if(firstDateEEPROM == 0xFFFF && firstMonthEEPROM == 0xFFFF && firstYearEEPROM == 0xFFFF){
        Uint16 i=0;

        EEPROM_WriteByte(addressFirstDate, (Uint16)Date[0]);
        EEPROM_WriteByte(addressFirstDate+1, (Uint16)Date[1]);
        EEPROM_WriteByte(addressFirstMonth, (Uint16)Date[3]);
        EEPROM_WriteByte(addressFirstMonth+1, (Uint16)Date[4]);
        EEPROM_WriteByte(addressFirstYear, (Uint16)Date[6]);
        EEPROM_WriteByte(addressFirstYear+1, (Uint16)Date[7]);

        for(i=addressStartDailyDataLogging;i<=addressEndYearlyDataLogging;i++)
            EEPROM_WriteByte(i,0);
    }

    EEPROMFirstDate[0] =  (char)EEPROM_ReadByte(addressFirstDate);
    EEPROMFirstDate[1] =  (char)EEPROM_ReadByte(addressFirstDate+1);
    EEPROMFirstDate[2] = '/';
    EEPROMFirstDate[3] =  (char)EEPROM_ReadByte(addressFirstMonth);
    EEPROMFirstDate[4] =  (char)EEPROM_ReadByte(addressFirstMonth+1);
    EEPROMFirstDate[5] = '/';
    EEPROMFirstDate[6] =  (char)EEPROM_ReadByte(addressFirstYear);
    EEPROMFirstDate[7] =  (char)EEPROM_ReadByte(addressFirstYear+1);
    EEPROMFirstDate[8] = '\0';
    // Energy Data Logging Initialization: End

    // Data Logging Initialization Connector 1: Start
    nextLogPointerEEPROMConn1 = (EEPROM_ReadByte(nextLogPointerLocationConn1 + 1) << 8) | EEPROM_ReadByte(nextLogPointerLocationConn1);
    if(nextLogPointerEEPROMConn1 == 0xFFFF || nextLogPointerEEPROMConn1 == endLogLocationConn1){
        nextLogPointerEEPROMConn1 = startLogLocationConn1;
        EEPROM_WriteByte(nextLogPointerLocationConn1, (startLogLocationConn1 & 0xFF));      // Lower Byte
        EEPROM_WriteByte(nextLogPointerLocationConn1+1, ((startLogLocationConn1 >> 8) & 0xFF));  // Upper Byte
    }

    // Check if session terminated properly OR abruptly
    sessionStopEEPROMConn1 = EEPROM_ReadByte(sessionStopLocationConn1);
    if(sessionStopEEPROMConn1 == 0xFF){
        sessionStopEEPROMConn1 = sessionIdle;
        EEPROM_WriteByte(sessionStopLocationConn1, sessionStopEEPROMConn1);
    }
    else if(sessionStopEEPROMConn1 == sessionStarted){
        Uint16 i=0;
//         Session terminated due to DSP supply cut abruptly
        for(i=0;i<19;i++)
            EEPROM_WriteByte(nextLogPointerLocationConn1+12+i,0);

        // Update next log pointer
        nextLogPointerEEPROMConn1 = nextLogPointerEEPROMConn1 + 31;
        EEPROM_WriteByte(nextLogPointerLocationConn1, (nextLogPointerEEPROMConn1 & 0xFF));            // Lower Byte
        EEPROM_WriteByte(nextLogPointerLocationConn1+1, ((nextLogPointerEEPROMConn1 >> 8) & 0xFF));   // Upper Byte
        sessionStopEEPROMConn1 = sessionIdle;
        EEPROM_WriteByte(sessionStopLocationConn1, sessionStopEEPROMConn1);
    }

    // Check total sessions logged
    sessionsLoggedEEPROMConn1 = EEPROM_ReadByte(sessionsLoggedLocationConn1);
    if(sessionsLoggedEEPROMConn1 == 0xFF){
        sessionsLoggedEEPROMConn1 = 0;
        EEPROM_WriteByte(sessionsLoggedLocationConn1, sessionsLoggedEEPROMConn1);
    }
    // Data Logging Initialization Connector 1: End

    // Data Logging Initialization Connector 2: Start
    nextLogPointerEEPROMConn2 = (EEPROM_ReadByte(nextLogPointerLocationConn2 + 1) << 8) | EEPROM_ReadByte(nextLogPointerLocationConn2);
    if(nextLogPointerEEPROMConn2 == 0xFFFF || nextLogPointerEEPROMConn2 == endLogLocationConn2){
        nextLogPointerEEPROMConn2 = startLogLocationConn2;
        EEPROM_WriteByte(nextLogPointerLocationConn2, (startLogLocationConn2 & 0xFF));      // Lower Byte
        EEPROM_WriteByte(nextLogPointerLocationConn2+1, ((startLogLocationConn2 >> 8) & 0xFF));  // Upper Byte
    }

    // Check if session terminated properly OR abruptly
    sessionStopEEPROMConn2 = EEPROM_ReadByte(sessionStopLocationConn2);
    if(sessionStopEEPROMConn2 == 0xFF){
        sessionStopEEPROMConn2 = sessionIdle;
        EEPROM_WriteByte(sessionStopLocationConn2, sessionStopEEPROMConn2);
    }
    else if(sessionStopEEPROMConn2 == sessionStarted){
        Uint16 i=0;
        // Session terminated due to DSP supply cut abruptly
        for(i=0;i<20;i++)
            EEPROM_WriteByte(nextLogPointerLocationConn2+12+i,0);

        // Update next log pointer
        nextLogPointerEEPROMConn2 = nextLogPointerEEPROMConn2 + 31;
        EEPROM_WriteByte(nextLogPointerLocationConn2, (nextLogPointerEEPROMConn2 & 0xFF));            // Lower Byte
        EEPROM_WriteByte(nextLogPointerLocationConn2+1, ((nextLogPointerEEPROMConn2 >> 8) & 0xFF));   // Upper Byte
        sessionStopEEPROMConn2 = sessionIdle;
        EEPROM_WriteByte(sessionStopLocationConn2, sessionStopEEPROMConn2);
    }
    // Check total sessions logged
    sessionsLoggedEEPROMConn2 = EEPROM_ReadByte(sessionsLoggedLocationConn2);
    if(sessionsLoggedEEPROMConn2 == 0xFF){
        sessionsLoggedEEPROMConn2 = 0;
        EEPROM_WriteByte(sessionsLoggedLocationConn2, sessionsLoggedEEPROMConn2);
    }
    // Data Logging Initialization Connector 2: End
}

void readDailyEnergyData(int difference){
    float previousValue = 0.0;
    Uint16 previousValueInt, previousValueFloat;
    char HMIDisplayEnergyData[] = "totalUnits.txt=\"         \"";
    char unitsConsumedStr[] = "       ";

    if(difference >= 0){
        Uint16 address = addressStartDailyDataLogging + difference*3;

        previousValueInt = (EEPROM_ReadByte(address+1) << 8) | EEPROM_ReadByte(address);
        previousValueFloat = EEPROM_ReadByte(address+2);
        previousValue     = (float) previousValueInt  + ((float) previousValueFloat)/100.0;

        ftoa(previousValue,unitsConsumedStr,1);
        replaceStringHMI(HMIDisplayEnergyData, unitsConsumedStr);
    }
}

void readMonthlyEnergyData(int difference){
    float previousValue = 0.0;
    Uint16 previousValueInt, previousValueFloat;
    char HMIDisplayEnergyData[] = "totalUnits.txt=\"         \"";
    char unitsConsumedStr[] = "          ";

    if(difference >= 0){
        Uint16 address = addressStartMonthlyDataLogging + difference*3;

        previousValueInt = (EEPROM_ReadByte(address+1) << 8) | EEPROM_ReadByte(address);
        previousValueFloat = EEPROM_ReadByte(address+2);

        previousValue     = (float) previousValueInt  + ((float) previousValueFloat)/100.0;

        f64toa(previousValue,unitsConsumedStr,1);
        replaceStringHMI(HMIDisplayEnergyData, unitsConsumedStr);
    }
}

void readYearlyEnergyData(int difference){
    float previousValue = 0.0;
    Uint32 previousValueInt, previousValueFloat;
    char HMIDisplayEnergyData[] = "totalUnits.txt=\"         \"";
    char unitsConsumedStr[] = "          ";

    if(difference >= 0){
        Uint16 address = addressStartYearlyDataLogging + difference*4;

        Uint32 previousValueLowByte = EEPROM_ReadByte(address) & 0xFF;
        Uint32 previousValueMidByte = EEPROM_ReadByte(address+1) & 0xFF;
        Uint32 previousValueHighByte = EEPROM_ReadByte(address+2) & 0xFF;

        previousValueFloat = EEPROM_ReadByte(address+3);

        previousValueInt = (previousValueHighByte << 16)  | (previousValueMidByte << 8) | previousValueLowByte;
        previousValue     = (float) previousValueInt  + ((float) previousValueFloat)/100.0;

        f64toa(previousValue,unitsConsumedStr,1);
        replaceStringHMI(HMIDisplayEnergyData, unitsConsumedStr);
    }
}

void logEnergyData(float unitsConsumed){
    int difference = 0;
    float previousValue = 0.0;
    Uint16 unitsConsumedInt, unitConsumedFloatPart, previousValueFloat, address;
    Uint32 previousValueInt;

    readDateTimeRTC();

    // Update Daily Energy data
    difference = getDateDifference(EEPROMFirstDate, Date);
    address = addressStartDailyDataLogging + difference*3;
    if(difference >= 0 && address < addressEndDailyDataLogging){
        previousValueInt = (EEPROM_ReadByte(address+1) << 8) | EEPROM_ReadByte(address);
        previousValueFloat = EEPROM_ReadByte(address+2);
        previousValue     = (float) previousValueInt  + ((float) previousValueFloat)/100.0;

        // Read previous energy value and add current session energy
        previousValue += unitsConsumed;
        unitsConsumedInt = (Uint16)previousValue;
        unitConsumedFloatPart = (Uint16)(100*(previousValue - unitsConsumedInt));

        EEPROM_WriteByte(address,unitsConsumedInt & 0xFF);
        EEPROM_WriteByte(address+1,(unitsConsumedInt >> 8) & 0xFF);
        EEPROM_WriteByte(address+2,unitConsumedFloatPart & 0xFF);
    }

    // Update Monthly Energy Data
    difference = getMonthDifference(&EEPROMFirstDate[3], &Date[3]);
    address = addressStartMonthlyDataLogging + difference*3;
    if(difference >= 0 && address < addressEndMonthlyDataLogging){
        previousValueInt = (EEPROM_ReadByte(address+1) << 8) | EEPROM_ReadByte(address);
        previousValueFloat = EEPROM_ReadByte(address+2);
        previousValue     = (float) previousValueInt  + ((float) previousValueFloat)/100.0;

        // Read previous energy value and add current session energy
        previousValue += unitsConsumed;
        unitsConsumedInt = (Uint16)previousValue;
        unitConsumedFloatPart = (Uint16)(100*(previousValue - unitsConsumedInt));

        EEPROM_WriteByte(address,unitsConsumedInt & 0xFF);
        EEPROM_WriteByte(address+1,(unitsConsumedInt >> 8) & 0xFF);
        EEPROM_WriteByte(address+2,unitConsumedFloatPart & 0xFF);
    }

    // Update Yearly Energy Data
    difference = getYearDifference(&EEPROMFirstDate[7], &Date[7]);
    address = addressStartYearlyDataLogging + difference*4;
    if(difference >= 0 && address < addressEndYearlyDataLogging){
        Uint32 unitsConsumedInt = 0;
        Uint32 previousValueLowByte = EEPROM_ReadByte(address) & 0xFF;
        Uint32 previousValueMidByte = EEPROM_ReadByte(address+1) & 0xFF;
        Uint32 previousValueHighByte = EEPROM_ReadByte(address+2) & 0xFF;
        previousValueFloat = EEPROM_ReadByte(address+3);

        previousValueInt = (previousValueHighByte << 16)  | (previousValueMidByte << 8) | previousValueLowByte;

        previousValue     = (float) previousValueInt  + ((float) previousValueFloat)/100.0;

        // Read previous energy value and add current session energy
        previousValue += unitsConsumed;
        unitsConsumedInt = (Uint32)previousValue;
        unitConsumedFloatPart = (Uint16)(100*(previousValue - unitsConsumedInt));

        EEPROM_WriteByte(address, unitsConsumedInt & 0xFF);
        EEPROM_WriteByte(address+1,(unitsConsumedInt >> 8) & 0xFF);
        EEPROM_WriteByte(address+2,(unitsConsumedInt >> 16) & 0xFF);
        EEPROM_WriteByte(address+3,unitConsumedFloatPart & 0xFF);
    }
}

Uint16 countLeapYears(Uint16 date,Uint16 month, Uint16 year){
    Uint16 years = year;

    // Check if the current year needs to be
    //  considered for the count of leap years
    // or not
    if (month <= 2)
        years--;

    // An year is a leap year if it
    // is a multiple of 4,
    // multiple of 400 and not a
     // multiple of 100.
    return years / 4
           - years / 100
           + years / 400;
}
int getYearDifference(char *date1, char *date2){
    Uint16 year1, year2;
    int answer;

    year1 = (date1[0] - 48)*10 + (date1[1] - 48);
    year2 = (date2[0] - 48)*10 + (date2[1] - 48);

    answer = year2 - year1;

    if(answer < 0)
        return -1;
    return answer;

}
int getMonthDifference(char *date1, char *date2){
    Uint16  month1, year1, month2, year2;
    int answer;

    month1 = (date1[0] - 48)*10 + (date1[1] - 48);
    year1 = (date1[3] - 48)*10 + (date1[4] - 48);

    month2 = (date2[0] - 48)*10 + (date2[1] - 48);
    year2 = (date2[3] - 48)*10 + (date2[4] - 48);

    if(year1 == year2)
        answer =  month2 - month1;
    else
        answer = ((year2 - year1)*12) - month1 + month2;

    if(answer < 0)
        return -1;
    return answer;
}

int getDateDifference(char *date1, char *date2){
    Uint16 day1, month1, year1, day2, month2, year2,i;
    int answer;

    day1 = (date1[0] - 48)*10 + (date1[1] - 48);
    month1 = (date1[3] - 48)*10 + (date1[4] - 48);
    year1 = 2000 + (date1[6] - 48)*10 + (date1[7] - 48);

    day2 = (date2[0] - 48)*10 + (date2[1] - 48);
    month2 = (date2[3] - 48)*10 + (date2[4] - 48);
    year2 = 2000 + (date2[6] - 48)*10 + (date2[7] - 48);

    // COUNT TOTAL NUMBER OF DAYS
    // BEFORE FIRST DATE 'dt1'

    // initialize count using years and day
    long int n1 = (year1*365) + day1;

    // Add days for months in given date
    for (i = 0; i < month1 - 1; i++)
        n1 += monthDays[i];

    // Since every leap year is of 366 days,
    // Add a day for every leap year
    n1 += countLeapYears(day1, month1, year1);

    // SIMILARLY, COUNT TOTAL NUMBER OF
    // DAYS BEFORE 'dt2'

    long int n2 = (year2*365) + day2;
    for (i = 0; i < month2 - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(day2, month2, year2);

    // return difference between two counts
    answer = (n2-n1);
    if(answer < 0)
        return -1;
    return answer;
}



void logStartSessionDataConn1(char *date, char *time){
//void logStartSessionData(char *date){

    // Log session started
    sessionStopEEPROMConn1 = sessionStarted;
    EEPROM_WriteByte(sessionStopLocationConn1, sessionStopEEPROMConn1);

    //Increment Sessions Logged
    if(sessionsLoggedEEPROMConn1 < totalSessionsToBeLogged){
        sessionsLoggedEEPROMConn1 += 1;
        EEPROM_WriteByte(sessionsLoggedLocationConn1, sessionsLoggedEEPROMConn1);
    }
    // Date example: 21/12/23
    EEPROM_WriteByte(nextLogPointerEEPROMConn1, (Uint16)date[0]);    //day
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+1, (Uint16)date[1]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+2, (Uint16)date[3]);  //month
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+3, (Uint16)date[4]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+4, (Uint16)date[6]);  //year
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+5, (Uint16)date[7]);
    // Time example: 11:12:59
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+6, (Uint16)time[0]);    //day
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+7, (Uint16)time[1]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+8, (Uint16)time[3]);  //month
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+9, (Uint16)time[4]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+10, (Uint16)time[6]);  //year
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+11, (Uint16)time[7]);

    nextLogPointerEEPROMConn1 = nextLogPointerEEPROMConn1 + 12;

    // Charging Stopped Reason
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+18, 0);
} //end of logStartSessionData

void logStartSessionDataConn2(char *date, char *time){

    // Log session started
    sessionStopEEPROMConn2 = sessionStarted;
    EEPROM_WriteByte(sessionStopLocationConn2, sessionStopEEPROMConn2);

    //Increment Sessions Logged
    if(sessionsLoggedEEPROMConn2 < totalSessionsToBeLogged){
        sessionsLoggedEEPROMConn2 += 1;
        EEPROM_WriteByte(sessionsLoggedLocationConn2, sessionsLoggedEEPROMConn2);
    }
    // Date example: 21/12/23
    EEPROM_WriteByte(nextLogPointerEEPROMConn2, (Uint16)date[0]);    //day
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+1, (Uint16)date[1]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+2, (Uint16)date[3]);  //month
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+3, (Uint16)date[4]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+4, (Uint16)date[6]);  //year
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+5, (Uint16)date[7]);
    // Time example: 11:12:59
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+6, (Uint16)time[0]);    //day
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+7, (Uint16)time[1]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+8, (Uint16)time[3]);  //month
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+9, (Uint16)time[4]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+10, (Uint16)time[6]);  //year
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+11, (Uint16)time[7]);

    nextLogPointerEEPROMConn2 = nextLogPointerEEPROMConn2 + 12;

    EEPROM_WriteByte(nextLogPointerEEPROMConn2+18, 0);
}

void logEndSessionDataConn1(char *date, char *time, float unitsConsumed, Uint16 chargingTime, Uint16 stopReason){

    Uint16 unitsConsumedInt = (Uint16)unitsConsumed;
    Uint16 unitConsumedFloatPart = (Uint16)(1000*(unitsConsumed - unitsConsumedInt));

    // Date example: 21/12/23
    EEPROM_WriteByte(nextLogPointerEEPROMConn1, (Uint16)date[0]);                                    //day
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+1, (Uint16)date[1]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+2, (Uint16)date[3]);                                  //month
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+3, (Uint16)date[4]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+4, (Uint16)date[6]);                                  //year
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+5, (Uint16)date[7]);

    // Time example: 11:12:59
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+6, (Uint16)time[0]);                                  //date
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+7, (Uint16)time[1]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+8, (Uint16)time[3]);                                  //month
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+9, (Uint16)time[4]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+10, (Uint16)time[6]);                                 //year
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+11, (Uint16)time[7]);

    // Energy Consumed Int part and float part
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+12, (unitsConsumedInt & 0xFF));              // Lower Byte
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+13, ((unitsConsumedInt >> 8) & 0xFF));       // Upper Byte

    EEPROM_WriteByte(nextLogPointerEEPROMConn1+14, (unitConsumedFloatPart & 0xFF));         // Lower Byte
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+15, ((unitConsumedFloatPart >> 8) & 0xFF));  // Upper Byte

    // Charging Time
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+16, (chargingTime & 0xFF));                  // Lower Byte
    EEPROM_WriteByte(nextLogPointerEEPROMConn1+17, ((chargingTime >> 8) & 0xFF));           // Upper Byte

    EEPROM_WriteByte(nextLogPointerEEPROMConn1+18, stopReason);

    nextLogPointerEEPROMConn1 = nextLogPointerEEPROMConn1 + 19;

    //Update Pointer for next location
    if(nextLogPointerEEPROMConn1 == endLogLocationConn1)
        nextLogPointerEEPROMConn1 = startLogLocationConn1;

    EEPROM_WriteByte(nextLogPointerLocationConn1, (nextLogPointerEEPROMConn1 & 0xFF));            // Lower Byte
    EEPROM_WriteByte(nextLogPointerLocationConn1+1, ((nextLogPointerEEPROMConn1 >> 8) & 0xFF));   // Upper Byte

    sessionStopEEPROMConn1 = sessionIdle;
    EEPROM_WriteByte(sessionStopLocationConn1, sessionStopEEPROMConn1);
}

void logEndSessionDataConn2(char *date, char *time, float unitsConsumed, Uint16 chargingTime, Uint16 stopReason){

    Uint16 unitsConsumedInt = (Uint16)unitsConsumed;
    Uint16 unitConsumedFloatPart = (Uint16)(1000*(unitsConsumed - unitsConsumedInt));

    // Date example: 21/12/23
    EEPROM_WriteByte(nextLogPointerEEPROMConn2, (Uint16)date[0]);                                    //day
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+1, (Uint16)date[1]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+2, (Uint16)date[3]);                                  //month
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+3, (Uint16)date[4]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+4, (Uint16)date[6]);                                  //year
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+5, (Uint16)date[7]);

    // Time example: 11:12:59
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+6, (Uint16)time[0]);                                  //date
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+7, (Uint16)time[1]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+8, (Uint16)time[3]);                                  //month
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+9, (Uint16)time[4]);
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+10, (Uint16)time[6]);                                 //year
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+11, (Uint16)time[7]);

    // Energy Consumed Int part and float part
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+12, (unitsConsumedInt & 0xFF));              // Lower Byte
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+13, ((unitsConsumedInt >> 8) & 0xFF));       // Upper Byte

    EEPROM_WriteByte(nextLogPointerEEPROMConn2+14, (unitConsumedFloatPart & 0xFF));         // Lower Byte
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+15, ((unitConsumedFloatPart >> 8) & 0xFF));  // Upper Byte

    // Charging Time
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+16, (chargingTime & 0xFF));                  // Lower Byte
    EEPROM_WriteByte(nextLogPointerEEPROMConn2+17, ((chargingTime >> 8) & 0xFF));           // Upper Byte

    EEPROM_WriteByte(nextLogPointerEEPROMConn2+18, stopReason);

    nextLogPointerEEPROMConn2 = nextLogPointerEEPROMConn2 + 19;

    //Update Pointer for next location
    if(nextLogPointerEEPROMConn2 == endLogLocationConn2)
        nextLogPointerEEPROMConn2 = startLogLocationConn2;

    EEPROM_WriteByte(nextLogPointerLocationConn2, (nextLogPointerEEPROMConn2 & 0xFF));            // Lower Byte
    EEPROM_WriteByte(nextLogPointerLocationConn2+1, ((nextLogPointerEEPROMConn2 >> 8) & 0xFF));   // Upper Byte

    sessionStopEEPROMConn2 = sessionIdle;
    EEPROM_WriteByte(sessionStopLocationConn2, sessionStopEEPROMConn2);
}

void retrieveSessionData(Uint16 pointer){
    // Session Logs variables
    char logStartDateHMIStr[] = "startDate.txt=\"        \"";
    char logStartTimeHMIStr[] = "startTime.txt=\"        \"";
    char logEndDateHMIStr[] = "endDate.txt=\"        \"";
    char logEndTimeHMIStr[] = "endTime.txt=\"        \"";
    char logTotalEnergyConsumedHMIStr[] = "unitsValue.txt=\"       \"";
    char logTotalChargeDurationHMIStr[] = "chargeDuration.txt=\"   \"";
    char currentLogCountHMIStr[] = "logNumber.txt=\"  \"";

    char chargingTimeStr[] = "   ";
    char unitsConsumedStr[] = "       ";

    float unitsConsumed;
    Uint16  chargingTime, unitsConsumedInt, unitsConsumedFloat;
    Uint16 stopReason;
    char startDate[9];
    char startTime[9];
    char endDate[9];
    char endTime[9];
    char currentLogCountStr[2];

    stopReason = (Uint16)EEPROM_ReadByte(pointer-1);

    startTime[8] = '\0';
    startTime[7] = (char)EEPROM_ReadByte(pointer-20);
    startTime[6] = (char)EEPROM_ReadByte(pointer-21);
    startTime[5] = ':';
    startTime[4] = (char)EEPROM_ReadByte(pointer-22);
    startTime[3] = (char)EEPROM_ReadByte(pointer-23);
    startTime[2] = ':';
    startTime[1] = (char)EEPROM_ReadByte(pointer-24);
    startTime[0] = (char)EEPROM_ReadByte(pointer-25);

    startDate[8] = '\0';
    startDate[7] = (char)EEPROM_ReadByte(pointer-26);
    startDate[6] = (char)EEPROM_ReadByte(pointer-27);
    startDate[5] = '/';
    startDate[4] = (char)EEPROM_ReadByte(pointer-28);
    startDate[3] = (char)EEPROM_ReadByte(pointer-29);
    startDate[2] = '/';
    startDate[1] = (char)EEPROM_ReadByte(pointer-30);
    startDate[0] = (char)EEPROM_ReadByte(pointer-31);


    replaceStringHMI(logStartDateHMIStr, startDate);
    replaceStringHMI(logStartTimeHMIStr, startTime);

    displayStopReason(stopReason);

    if(stopReason != 0){

        chargingTime =  (EEPROM_ReadByte(pointer-2) << 8) | EEPROM_ReadByte(pointer-3);

        unitsConsumedFloat = (EEPROM_ReadByte(pointer-4) << 8) | EEPROM_ReadByte(pointer-5);
        unitsConsumedInt = (EEPROM_ReadByte(pointer-6) << 8) | EEPROM_ReadByte(pointer-7);
        unitsConsumed     = (float) unitsConsumedInt  + ((float) unitsConsumedFloat)/1000.0;

        endTime[8] = '\0';
        endTime[7] = (char)EEPROM_ReadByte(pointer-8);
        endTime[6] = (char)EEPROM_ReadByte(pointer-9);
        endTime[5] = ':';
        endTime[4] = (char)EEPROM_ReadByte(pointer-10);
        endTime[3] = (char)EEPROM_ReadByte(pointer-11);
        endTime[2] = ':';
        endTime[1] = (char)EEPROM_ReadByte(pointer-12);
        endTime[0] = (char)EEPROM_ReadByte(pointer-13);

        endDate[8] = '\0';
        endDate[7] = (char)EEPROM_ReadByte(pointer-14);
        endDate[6] = (char)EEPROM_ReadByte(pointer-15);
        endDate[5] = '/';
        endDate[4] = (char)EEPROM_ReadByte(pointer-16);
        endDate[3] = (char)EEPROM_ReadByte(pointer-17);
        endDate[2] = '/';
        endDate[1] = (char)EEPROM_ReadByte(pointer-18);
        endDate[0] = (char)EEPROM_ReadByte(pointer-19);


        replaceStringHMI(logEndDateHMIStr, endDate);
        replaceStringHMI(logEndTimeHMIStr, endTime);

        intToStr(chargingTime, chargingTimeStr, 3);
        replaceStringHMI(logTotalChargeDurationHMIStr, chargingTimeStr);

        ftoa(unitsConsumed, unitsConsumedStr, 3);
        replaceStringHMI(logTotalEnergyConsumedHMIStr, unitsConsumedStr);

    }
    else if(stopReason == 0){
        HMIWrite(logEndDateHMIStr);
        HMIWrite(logEndTimeHMIStr);
        HMIWrite(logTotalChargeDurationHMIStr);
        HMIWrite(logTotalEnergyConsumedHMIStr);
    }
    if(connectorSelected == connector1)
        intToStr(currentLogCountConn1, currentLogCountStr, 0);
    else if(connectorSelected == connector2)
        intToStr(currentLogCountConn2, currentLogCountStr, 0);
    replaceStringHMI(currentLogCountHMIStr, currentLogCountStr);
} //End of retrieveSessionData

