#include <GTSI_1Phase1MPPT.h>                        // Main include file
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

float RTCEEPROMCountSend = 0.0;

void I2CA_Init(void)
{
    I2caRegs.I2CMDR.bit.IRS = 0;    // Reset the I2C module
    // I2C Prescale Register
    I2caRegs.I2CPSC.all = 11;       // Internal I2C module clock = SYSCLK/(PSC +1)
                                    // = 10 MHz

    //I2caRegs.I2CCLKL = 95;          // Tmaster = (PSC +1)[ICCL + 5 + ICCH + 5] / 200MHz
    //I2caRegs.I2CCLKH = 95;          // Tmaster =  20 [ICCL + ICCH + 10] / 200 MHz
                                    // d = 5  for IPSC >1

                                    // for I2C 50 kHz:
                                    // Tmaster = 20 µs * 150 MHz / 15 = 200 = (ICCL + ICCH +10)
                                    // ICCL + ICCH = 190
                                    // ICCL = ICH = 190/2 = 95

   I2caRegs.I2CCLKL = 45;
   I2caRegs.I2CCLKH = 45;          // for I2C 100 kHz:
                                    // Tmaster = 10 µs *200 MHz / 20 = 100 = (ICCL + ICCH + 10)
                                    // ICCL + ICCH = 90
                                    // ICCL = ICH = 90/2 = 45

    I2caRegs.I2CMDR.bit.IRS = 1;    // Take I2C out of reset
}

void RTC_WriteByte(Uint16 address, Uint16 dataWrite)
{
    I2caRegs.I2CSAR.all = 0x68;          // RTC address
    // Send START, Address Byte, Data Byte
    I2caRegs.I2CCNT = 2;
    I2caRegs.I2CDXR.all = address;
    I2caRegs.I2CMDR.all = 0x6E20;
    /*  Bit15 = 0;  no NACK in receiver mode
        Bit14 = 1;  FREE on emulation halt
        Bit13 = 1;  STT  generate START
        Bit12 = 0;  reserved
        Bit11 = 1;  STP  generate STOP
        Bit10 = 1;  MST  master mode
        Bit9  = 1;  TRX  master - transmitter mode
        Bit8  = 0;  XA   7 bit address mode
        Bit7  = 0;  RM   nonrepeat mode, I2CCNT determines # of bytes
        Bit6  = 1;  DLB  no loopback mode
        Bit5  = 1;  IRS  I2C module enabled
        Bit4  = 0;  STB  no start byte mode
        Bit3  = 0;  FDF  no free data format
        Bit2-0: 0;  BC   8 bit per data byte    */
    RTCEEPROMCountSend = 0.0;
    while(I2caRegs.I2CSTR.bit.XRDY == 0)      // wait until first byte is out
    {
        DELAY_US(1);
        RTCEEPROMCountSend = RTCEEPROMCountSend + 1.0;
        if(RTCEEPROMCountSend > 1000000.0)
        {
            break;
        }
    }
    RTCEEPROMCountSend = 0.0;
    I2caRegs.I2CDXR.all = dataWrite;
    while(I2caRegs.I2CSTR.bit.SCD == 0)        // wait for STOP condition
    {
        DELAY_US(1);
        RTCEEPROMCountSend = RTCEEPROMCountSend + 1.0;
        if(RTCEEPROMCountSend > 1000000.0)
        {
            break;
        }
    }
    RTCEEPROMCountSend = 0.0;
    I2caRegs.I2CSTR.bit.SCD = 0;
    I2caRegs.I2CSTR.bit.BB = 0;
    DELAY_US(100);
}

Uint16 RTC_ReadByte(Uint16 address)
{
       Uint16 ByteRead;
       I2caRegs.I2CSAR.all = 0x68;     // RTC address
       //  Send START and set pointer from where read has to be performed
       I2caRegs.I2CCNT     = 1;
       I2caRegs.I2CDXR.all = address;
       // Send start as master transmitter
       I2caRegs.I2CMDR.all = 0x6620;
       /*  Bit15 = 0;  no NACK in receiver mode
           Bit14 = 1;  FREE on emulation halt
           Bit13 = 1;  STT  generate START
           Bit12 = 0;  reserved
           Bit11 = 0;  STP  not generate STOP
           Bit10 = 1;  MST  master mode
           Bit9  = 1;  TRX  master - transmitter mode
           Bit8  = 0;  XA   7 bit address mode
           Bit7  = 0;  RM   nonrepeat mode, I2CCNT determines # of bytes
           Bit6  = 1;  DLB  no loopback mode
           Bit5  = 1;  IRS  I2C module enabled
           Bit4  = 0;  STB  no start byte mode
           Bit3  = 0;  FDF  no free data format
           Bit2-0: 0;  BC   8 bit per data byte    */
       RTCEEPROMCountSend = 0.0;
       while(I2caRegs.I2CSTR.bit.ARDY == 0)           // wait for access ready condition
       {
           DELAY_US(1);
           RTCEEPROMCountSend = RTCEEPROMCountSend + 1.0;
           if(RTCEEPROMCountSend > 1000000.0)
           {
               break;
           }
       }
       RTCEEPROMCountSend = 0.0;
       I2caRegs.I2CCNT     = 1;    // read one byte from address mentioned above
       I2caRegs.I2CMDR.all = 0x6C20;
       /*  Bit15 = 0;  no NACK in receiver mode
           Bit14 = 1;  FREE on emulation halt
           Bit13 = 1;  STT  generate START
           Bit12 = 0;  reserved
           Bit11 = 1;  STP  generate STOP
           Bit10 = 1;  MST  master mode
           Bit9  = 0;  TRX  master - receiver mode
           Bit8  = 0;  XA   7 bit address mode
           Bit7  = 0;  RM   nonrepeat mode, I2CCNT determines # of bytes
           Bit6  = 0;  DLB  no loopback mode
           Bit5  = 1;  IRS  I2C module enabled
           Bit4  = 0;  STB  no start byte mode
           Bit3  = 0;  FDF  no free data format
           Bit2-0: 0;  BC   8 bit per data byte    */
       RTCEEPROMCountSend = 0.0;
       while(I2caRegs.I2CSTR.bit.RRDY == 0)   // wait for 1st byte
       {
           DELAY_US(1);
           RTCEEPROMCountSend = RTCEEPROMCountSend + 1.0;
           if(RTCEEPROMCountSend > 1000000.0)
           {
               break;
           }
       }
       RTCEEPROMCountSend = 0.0;
       ByteRead = I2caRegs.I2CDRR.all ;            // read byte
       DELAY_US(50);
       return ByteRead;
}


Uint16 Binary2BCD(Uint16 a)
{
   Uint16 t1, t2;
   t1 = a%10;
   t1 = t1 & 0x0F;
   a = a/10;
   t2 = a%10;
   t2 = 0x0F & t2;
   t2 = t2 << 4;
   t2 = 0xF0 & t2;
   t1 = t1 | t2;
   return t1;
}  // function end

Uint16 BCD2Binary(Uint16 a)
{
   Uint16 r,t;
   t = a & 0x0F;
   r = t;
   a = 0xF0 & a;
   t = a >> 4;
   t = 0x0F & t;
   r = t*10 + r;
   return r;

} // function end

char BCD2UpperCh( char bcd)
{
  return ((bcd >> 4) + '0');
}   // function end


char BCD2LowerCh( char bcd)
{
  return ((bcd & 0x0F) + '0');
} // function end

void EEPROM_WriteByte(Uint16 address, Uint16 dataWrite)
{
    Uint16 HighByte,LowByte, addressOriginal;
        I2caRegs.I2CSAR.all = 0x50;     // EEPROM address
        addressOriginal = address;
        HighByte = address >> 8;
        LowByte  = addressOriginal & 0x00FF;
    // Send START, Address High Byte, Address Low Byte, Data Byte
        I2caRegs.I2CCNT = 3;
        I2caRegs.I2CDXR.all = HighByte;
        I2caRegs.I2CMDR.all = 0x6E20;
        /*  Bit15 = 0;  no NACK in receiver mode
            Bit14 = 1;  FREE on emulation halt
            Bit13 = 1;  STT  generate START
            Bit12 = 0;  reserved
            Bit11 = 1;  STP  generate STOP
            Bit10 = 1;  MST  master mode
            Bit9  = 1;  TRX  master - transmitter mode
            Bit8  = 0;  XA   7 bit address mode
            Bit7  = 0;  RM   nonrepeat mode, I2CCNT determines # of bytes
            Bit6  = 1;  DLB  no loopback mode
            Bit5  = 1;  IRS  I2C module enabled
            Bit4  = 0;  STB  no start byte mode
            Bit3  = 0;  FDF  no free data format
            Bit2-0: 0;  BC   8 bit per data byte    */
        RTCEEPROMCountSend = 0.0;
        while(I2caRegs.I2CSTR.bit.XRDY == 0)     // wait until first byte is out
        {
            DELAY_US(1);
            RTCEEPROMCountSend = RTCEEPROMCountSend + 1.0;
            if(RTCEEPROMCountSend > 1000000.0)
            {
                break;
            }
        }
        RTCEEPROMCountSend = 0.0;
        I2caRegs.I2CDXR.all = LowByte;
        while(I2caRegs.I2CSTR.bit.XRDY == 0)       // wait until second byte is out
        {
            DELAY_US(1);
            RTCEEPROMCountSend = RTCEEPROMCountSend + 1.0;
            if(RTCEEPROMCountSend > 1000000.0)
            {
                break;
            }
        }
        RTCEEPROMCountSend = 0.0;
        I2caRegs.I2CDXR.all = dataWrite;
        while(I2caRegs.I2CSTR.bit.SCD == 0)       // wait for STOP condition
        {
            DELAY_US(1);
            RTCEEPROMCountSend = RTCEEPROMCountSend + 1.0;
            if(RTCEEPROMCountSend > 1000000.0)
            {
                break;
            }
        }
        RTCEEPROMCountSend = 0.0;
        I2caRegs.I2CSTR.bit.SCD = 0;
        I2caRegs.I2CSTR.bit.BB = 0;
        DELAY_US(3500);
}

Uint16 EEPROM_ReadByte(Uint16 address)
{
       Uint16 ByteRead, HighByte, LowByte, addressOriginal;
       I2caRegs.I2CSAR.all = 0x50;    // EEPROM address
       addressOriginal = address;
       HighByte = address >> 8;
       LowByte  = addressOriginal & 0x00FF;
       //  Send START and set pointer from where read has to be performed
       I2caRegs.I2CCNT     = 2;
       I2caRegs.I2CDXR.all = HighByte;
       // Send start as master transmitter
       I2caRegs.I2CMDR.all = 0x6620;
       /*  Bit15 = 0;  no NACK in receiver mode
           Bit14 = 1;  FREE on emulation halt
           Bit13 = 1;  STT  generate START
           Bit12 = 0;  reserved
           Bit11 = 0;  STP  not generate STOP
           Bit10 = 1;  MST  master mode
           Bit9  = 1;  TRX  master - transmitter mode
           Bit8  = 0;  XA   7 bit address mode
           Bit7  = 0;  RM   nonrepeat mode, I2CCNT determines # of bytes
           Bit6  = 1;  DLB  no loopback mode
           Bit5  = 1;  IRS  I2C module enabled
           Bit4  = 0;  STB  no start byte mode
           Bit3  = 0;  FDF  no free data format
           Bit2-0: 0;  BC   8 bit per data byte    */

       while(I2caRegs.I2CSTR.bit.XRDY == 0)           // wait until first byte is out
       {
           DELAY_US(1);
           RTCEEPROMCountSend = RTCEEPROMCountSend + 1.0;
           if(RTCEEPROMCountSend > 1000000.0)
           {
               break;
           }
       }
       RTCEEPROMCountSend = 0.0;
       I2caRegs.I2CDXR.all = LowByte;
       while(I2caRegs.I2CSTR.bit.ARDY == 0)           // wait for access ready condition
       {
           DELAY_US(1);
           RTCEEPROMCountSend = RTCEEPROMCountSend + 1.0;
           if(RTCEEPROMCountSend > 1000000.0)
           {
               break;
           }
       }
       RTCEEPROMCountSend = 0.0;

       I2caRegs.I2CCNT     = 1;    // read one byte from address mentioned above
       I2caRegs.I2CMDR.all = 0x6C20;
       /*  Bit15 = 0;  no NACK in receiver mode
           Bit14 = 1;  FREE on emulation halt
           Bit13 = 1;  STT  generate START
           Bit12 = 0;  reserved
           Bit11 = 1;  STP  generate STOP
           Bit10 = 1;  MST  master mode
           Bit9  = 0;  TRX  master - receiver mode
           Bit8  = 0;  XA   7 bit address mode
           Bit7  = 0;  RM   nonrepeat mode, I2CCNT determines # of bytes
           Bit6  = 0;  DLB  no loopback mode
           Bit5  = 1;  IRS  I2C module enabled
           Bit4  = 0;  STB  no start byte mode
           Bit3  = 0;  FDF  no free data format
           Bit2-0: 0;  BC   8 bit per data byte    */

       while(I2caRegs.I2CSTR.bit.RRDY == 0)   // wait for 1st byte
       {
           DELAY_US(1);
           RTCEEPROMCountSend = RTCEEPROMCountSend + 1.0;
           if(RTCEEPROMCountSend > 1000000.0)
           {
               break;
           }
       }
       RTCEEPROMCountSend = 0.0;
       ByteRead = I2caRegs.I2CDRR.all ;            // read byte
       DELAY_US(50);
       return ByteRead;
}

 void setDate_RTC(int date, int month, int year)
 {
     dtCounter  = Binary2BCD(date);
     monCounter = Binary2BCD(month);
     yrCounter  = Binary2BCD(year);

     RTC_WriteByte(0x04,dtCounter);
     RTC_WriteByte(0x05,monCounter);
     RTC_WriteByte(0x06,yrCounter);
 }

 void setTime_RTC(int hour, int minute, int second)
 {
     secCounter = Binary2BCD(second);
     minCounter = Binary2BCD(minute);
     hrCounter  = Binary2BCD(hour);

     RTC_WriteByte(0x00,secCounter);
     RTC_WriteByte(0x01,minCounter);
     RTC_WriteByte(0x02,hrCounter);
 }

 void readDateTimeRTC()
 {
     struct tm t;
     Uint16 second = 0, minute = 0, hour = 0, day = 0, month = 0, year = 0;

     int timestampYear, timestampMonth, timestampDay;
     int timestampHour, timestampMinute, timestampSec;

     second = RTC_ReadByte(0x00);
     minute = RTC_ReadByte(0x01);
     hour   = RTC_ReadByte(0x02);
     day    = RTC_ReadByte(0x04);
     month  = RTC_ReadByte(0x05);
     year   = RTC_ReadByte(0x06);

     // Time : HH:MM:SS
     Time[0] = BCD2UpperCh(hour);
     Time[1] = BCD2LowerCh(hour);
     Time[3] = BCD2UpperCh(minute);
     Time[4] = BCD2LowerCh(minute);
     Time[6] = BCD2UpperCh(second);
     Time[7] = BCD2LowerCh(second);
     // Date : DD/MM/YY
     Date[0] = BCD2UpperCh(day);
     Date[1] = BCD2LowerCh(day);
     Date[3] = BCD2UpperCh(month);
     Date[4] = BCD2LowerCh(month);
     Date[6] = BCD2UpperCh(year);
     Date[7] = BCD2LowerCh(year);

     timestampYear = (Uint16)(BCD2UpperCh(year) - '0')*10 + (Uint16)(BCD2LowerCh(year) - '0');
     timestampMonth = (Uint16)(BCD2UpperCh(month) - '0')*10 + (Uint16)(BCD2LowerCh(month) - '0');
     timestampMonth--;
     timestampDay = (Uint16)(BCD2UpperCh(day) - '0')*10 + (Uint16)(BCD2LowerCh(day) - '0');

     timestampHour = (Uint16)(BCD2UpperCh(hour) - '0')*10 + (Uint16)(BCD2LowerCh(hour) - '0');
     timestampMinute = (Uint16)(BCD2UpperCh(minute) - '0')*10 + (Uint16)(BCD2LowerCh(minute) - '0');
     timestampSec = (Uint16)(BCD2UpperCh(second) - '0')*10 + (Uint16)(BCD2LowerCh(second) - '0');

     HMITime[10]  = Time[0];
     HMITime[11]  = Time[1];
     HMITime[13] = Time[3];
     HMITime[14] = Time[4];
     HMITime[16] = Time[6];
     HMITime[17] = Time[7];


     HMIDate[10]  = Date[0];
     HMIDate[11]  = Date[1];
     HMIDate[13] = Date[3];
     HMIDate[14] = Date[4];
     HMIDate[16] = Date[6];
     HMIDate[17] = Date[7];

     t.tm_year = (2000+timestampYear) - 1900;          //Since the year starts from 1900 not from 0
     t.tm_mon =  timestampMonth;
     t.tm_mday = timestampDay;

     t.tm_hour = timestampHour - 5;
     t.tm_min = timestampMinute - 30;
     t.tm_sec = timestampSec;
     t.tm_isdst = 0;

     time_t time =  mktime(&t);

     Uint16 month1 = t.tm_mon+1;
     Uint16 testyear = (t.tm_year + 1900) - 2000;

     // 2022-02-01T20:53:32.486Z
     dateTime[0] = '2';
     dateTime[1] = '0';
     dateTime[2] = ((testyear)/10)+48;
     dateTime[3] = (testyear%10)+48;
     dateTime[4] = '-';
     dateTime[5] = (month1/10)+48;
     dateTime[6] = (month1%10)+48;
     dateTime[7] = '-';
     dateTime[8] = (t.tm_mday/10)+48;
     dateTime[9] = (t.tm_mday%10)+48;
     dateTime[10] = 'T';
     dateTime[11] = (t.tm_hour/10)+48;
     dateTime[12] = (t.tm_hour%10)+48;
     dateTime[13] = ':';
     dateTime[14] = (t.tm_min/10)+48;
     dateTime[15] = (t.tm_min%10)+48;
     dateTime[16] = ':';
     dateTime[17] = (t.tm_sec/10)+48;
     dateTime[18] = (t.tm_sec%10)+48;
     dateTime[19] = '.';
     dateTime[20] = '0';
     dateTime[21] = '0';
     dateTime[22] = '0';
     dateTime[23] = 'Z';
     dateTime[24] = '\0';
 }
