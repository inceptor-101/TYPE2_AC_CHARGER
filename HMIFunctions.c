/**********************************************************************
* Code : CPU2 - HMI Functions
* Devices: TMS320F28379D, TMS320F2800137
**********************************************************************/

#include <GTSI_1Phase1MPPT.h>                        // Main include file
#include <string.h>
#include <stdio.h>
#include <math.h>


void clearSSIDs(void){
    Uint16 i=0;
    numberOfAccessPoints = 0;

    for(i=0;i<21;i++){
        SSID1[i] = '\0';
        SSID2[i] = '\0';
        SSID3[i] = '\0';
        SSID4[i] = '\0';
        SSID5[i] = '\0';
        SSID6[i] = '\0';
        SSID7[i] = '\0';
        SSID8[i] = '\0';
    }

    HMIWrite("ssid1.txt=\"\"");
    HMIWrite("ssid2.txt=\"\"");
    HMIWrite("ssid3.txt=\"\"");
    HMIWrite("ssid4.txt=\"\"");
    HMIWrite("ssid5.txt=\"\"");
    HMIWrite("ssid6.txt=\"\"");
    HMIWrite("ssid7.txt=\"\"");
    HMIWrite("ssid8.txt=\"\"");
}

//void displaySSID(char SSID, char *SSIDName){
//    char ssidHMIName[40];
//    Uint16 i=0;
//
//    ssidHMIName[0] = 's';
//    ssidHMIName[1] = 's';
//    ssidHMIName[2] = 'i';
//    ssidHMIName[3] = 'd';
//    ssidHMIName[4] = SSID;
//    ssidHMIName[5] = '.';
//    ssidHMIName[6] = 't';
//    ssidHMIName[7] = 'x';
//    ssidHMIName[8] = 't';
//    ssidHMIName[9] = '=';
//    ssidHMIName[10] = '\"';
//    while(*SSIDName)
//        ssidHMIName[11+(i++)] = *SSIDName++;
//    ssidHMIName[i+11] = '\"';
//
//    HMIWrite(ssidHMIName);
//
//    for(i=0;i<40;i++)
//        ssidHMIName[i] = '\0';
//}

void displaySSID(char SSID, char *SSIDName){
    Uint16 i=0;
    char ssidHMIName[] = "ssid .txt=\"                    \"" ;
    ssidHMIName[4] = SSID;
    for(i=0;i<20;i++){
        if(SSIDName[i])
            ssidHMIName[i+11] = SSIDName[i];
        else
            break;
    }
    HMIWrite(ssidHMIName);
}

//To clear strings
void clearParameters(){
    asm(" NOP");
}

void clearHMIString(char* str){
    int dq=0,i=0;
    while(dq<2){
        if(dq == 1 && str[i]!='\"')
            str[i] = ' ';

        if(str[i]=='\"')
            dq++;

        i++;
    }
}

void HMIWriteDateTime()
{
    readDateTimeRTC();
    HMIWrite(HMIDate);
    HMIWrite(HMITime);
}


void HMIWriteTime()
{
    readDateTimeRTC();
    HMIWrite(HMITime);
}

void HMIWrite(char *string)
{
    while(*string)
    {
        while (SciaRegs.SCICTL2.bit.TXEMPTY == 0);
        SciaRegs.SCITXBUF.bit.TXDT = *string++ ;
        //DelayUs(2);
    }

    while (SciaRegs.SCICTL2.bit.TXEMPTY == 0);
    SciaRegs.SCITXBUF.bit.TXDT = 0xFF;
    while (SciaRegs.SCICTL2.bit.TXEMPTY == 0);
    SciaRegs.SCITXBUF.bit.TXDT = 0xFF;
    while (SciaRegs.SCICTL2.bit.TXEMPTY == 0);
    SciaRegs.SCITXBUF.bit.TXDT = 0xFF;

    Delay_ms(50);
}
void replaceStringHMI(char* str, char* subStr)
{
    if(str[0]=='\0')
        str[0] = 't';
    int i=0,j=0,dq=0;
    for(i=0; str[i] !='\0'; i++)
    {
        if(dq==1)
        {
            for(j=0 ; subStr[j]!='\0'; j++)
            {
                str[i] =subStr[j];
                i++;
            }
            break;
        }
        if(str[i]=='\"')
        {
            dq++;
        }
    }
    HMIWrite(str);
    clearString(subStr);
    clearHMIString(str);
}
