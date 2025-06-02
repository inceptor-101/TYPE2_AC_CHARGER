
/**********************************************************************
Code   : Main C file for Single Phase Single MPPT GTSI
Author : Varun Sharma, EE Intern
**********************************************************************/
#include <GTSI_1Phase1MPPT.h>    // Main include file
#include "F28x_Project.h"
#include "math.h"
#include "can.h"

// Sampling Time for the controller -> 80 us


//**********************************************************************
//--- Global Variables---
//**********************************************************************

//########################################################################################################
//########################Defining the variables for the Type2 AC Charger#################################
//########################################################################################################

volatile Uint16* resultADCA = &AdcaResultRegs.ADCRESULT0;
volatile Uint16* resultADCC = &AdccResultRegs.ADCRESULT0;
SENSEDVALUES sensedAnalogADC;
SENSEDVALUES actualsensedvalues;
CANSEQUNION can_message_seq1_phvolt;
CANSEQUNION can_message_seq2_phcurr;
CANSEQUNION3 can_message_seq3_info;
//#######Declaring the multipliers##########
SENSEDVALUES multipliers = {
     .grid_voltage = 0.003367f,
     .cp_signal = 0.12023f,
     .grid_curr = 0.0f,
     .prot_earth = 1.0f/245.0f,
     .residual_curr = 0.0f,
     .temp_sens = 0.0f,
     .vbatt = 25.0f
};

//#########Declaring the offsets#########
SENSEDVALUES offsets = {
     .grid_voltage = 1.65f,
     .cp_signal = 1.65f,
     .grid_curr = 0.0f,
     .prot_earth = 0.0f,
     .residual_curr = 0.0f,
     .temp_sens = 0.0f,
     .vbatt = 0.0f
};

Uint32 count = 0;
Uint32 canCount = 0;
Uint16 samples = 0;
Uint16 Pwmstatus = OFF;
unsigned char transmit[8];
uint16_t CANTxData[8];
uint16_t CANRxData[8];
RXDATA getdata;
Uint16 EvseState = OFF;
Uint16 special = 0;
Uint16 seconds = 5;
void main(void)
{



    CANTxData[0] = 1;
    CANTxData[1] = 4;
    CANTxData[2] = 9;
    CANTxData[3] = 16;
    CANTxData[4] = 25;
    CANTxData[5] = 36;
    CANTxData[6] = 49;
    CANTxData[7] = 64;

//--- CPU Initialization
//    SysCtl_setClock(DEVICE_SETCLOCK_CFG);
//    Make sure the LSPCLK divider is set to the default (divide by 4)
//    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_4);
    InitSysCtrl();                      // Initialize the CPU (FILE: f28002x_sysCtrl.c)
    InitGpio();                         // Initialize the shared GPIO pins (FILE: f28002x_gpio.c)
    InitPieCtrl();
    // Initialize and enable the PIE (FILE: PieCtrl.c)
//    InitWatchdog();                   // Initialize the Watchdog Timer (FILE: WatchDog.c)

    //Initialize the Flash
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
    InitFlash();

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // Service Routines (ISR).
    InitPieVectTable();

    // Map ISR functions
    EALLOW;
    PieVectTable.ADCA1_INT = &ADCA1_ISR;        // Function for ADCA interrupt 1
    PieVectTable.EPWM1_TZ_INT = &EPWM1_TZ_ISR;  // Function for EPWM1_TZ interrupt
    PieVectTable.CANA1_INT = &CANA1_ISR;        // Function for CANA1 interrupt (CAN Receive Interrupt)
    PieVectTable.CANA0_INT = &CANA0_ISR;
    PieVectTable.TIMER0_INT = &TIMER0_ISR;
    EDIS;

    Delay_ms(100);
//    initCmpss();
    InitEPwm();
//    initADC();                                      // Initialize the ADC-A (FILE: Adc.c)                                    // Initialize the EPwm (FILE: EPwm.c)
    MyInitADC();
    InitCanaChargerDriverLib();                     // Initialize the CAN
    // Interrupt Enable for ADC A1
    IER |= M_INT1;                                  // Enable INT1 in IER to enable PIE group 1
    IER |= M_INT9;                                  // Enable CAN_INT1 INTRRUPT AT THE CPU LEVEL

    // Enable PIE interrupt
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;              // ADC A1 Interrupt
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;              // ADC A1 Interrupt
    PieCtrlRegs.PIEIER9.bit.INTx6 = 1;              // Enable for the PIE canint1 interrupt
    PieCtrlRegs.PIEIER9.bit.INTx5 = 1;

    // Acknowledge the groups
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;         // Must acknowledge the PIE group
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    EALLOW;
    ClkCfgRegs.CLKSRCCTL3.bit.XCLKOUTSEL = 5;
    EDIS;

    //--- Enable global interrupts
    EINT;           // Enable Global interrupt INTM
    ERTM;           // Enable Global realtime interrupt DBGM

//    ------------------------------------------------------------------
//    ---------------CAN CODE WAS AFTER  THAT---------------------------
//    -------------------------------------------------------------------
    InitCpuTimer(seconds);
    EALLOW;
    GpioDataRegs.GPADAT.bit.GPIO20 = 1; // Uncomment to turn LED OFF
    GpioDataRegs.GPADAT.bit.GPIO22 = 0;
    EDIS;

    while (true){

    }

}  //end of main
