//###########################################################################
//
// FILE:   f280013x_defaultisr.c
//
// TITLE:  f280013x Device Default Interrupt Service Routines
//
//###########################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

//
// Included Files
#include <GTSI_1Phase1MPPT.h>                        // Main include file
#include <stdio.h>
#include "f280013x_device.h"       // f280013x Header File Include File
#include "f280013x_examples.h"     // f280013x Examples Include File
#include "math.h"                        // Main include file
#include "can.h"
//
// CPU Timer 1 Interrupt
//
interrupt void TIMER1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CPU Timer 2 Interrupt
//
interrupt void TIMER2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// Datalogging Interrupt
//
interrupt void DATALOG_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// RTOS Interrupt from ERAD
//
interrupt void RTOS_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// Emulation Interrupt
//
interrupt void EMU_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// Non-Maskable Interrupt
//
interrupt void NMI_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// Illegal Operation Trap
//
interrupt void ILLEGAL_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 1
//
interrupt void USER1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 2
//
interrupt void USER2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 3
//
interrupt void USER3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 4
//
interrupt void USER4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 5
//
interrupt void USER5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 6
//
interrupt void USER6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 7
//
interrupt void USER7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 8
//
interrupt void USER8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 9
//
interrupt void USER9_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 10
//
interrupt void USER10_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 11
//
interrupt void USER11_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 12
//
interrupt void USER12_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}


// 1.1 - ADCA Interrupt 1
//

interrupt void ADCA1_ISR(void){

//    ---------------CODE FOR DETECTING THE SENSED VARIABLES AND GETTING ACTUAL VALUES USING THE OFFSET-----------------
//    -----------------Storing all of the sensed parameters in their corresponding allocated variables------------------
    sensedAnalogADC.grid_voltage = (resultADCA[0])*(3.3/4096.0);
    sensedAnalogADC.prot_earth = (resultADCA[1])*(3.3/4096.0);
    sensedAnalogADC.vbatt = (resultADCA[2])*(3.3/4096.0);
    sensedAnalogADC.residual_curr = (resultADCA[3])*(3.3/4096.0);
    sensedAnalogADC.grid_curr = (resultADCC[0])*(3.3/4096.0);
    sensedAnalogADC.cp_signal = (resultADCC[1])*(3.3/4096.0);
    sensedAnalogADC.temp_sens = (resultADCC[2])*(3.3/4096.0);

//    ----------------CODE FOR FINDIND THE RMS VALUE AND THE AVERAGE VALUE OF THE GRID VOLTAGE WAVEFORM------------------

    static float sinval = 0.0;
    static float rmsvalue = 0.0;
    static float rmsbuffer = 0.0;
    static float avgval = 0.0;
    static float avgvalbuf = 0.0;

//    Writing the code for finding the RMS value
    samples++;
//    compensating for the offset and multiplier
    actualsensedvalues.grid_voltage = (sensedAnalogADC.grid_voltage-offsets.grid_voltage)/(multipliers.grid_voltage);
    rmsbuffer = rmsbuffer + (actualsensedvalues.grid_voltage*actualsensedvalues.grid_voltage);
    avgvalbuf = avgvalbuf + actualsensedvalues.grid_voltage;

////    Since we are assuming that the original sine wave has the frequency of 50Hz thus no of samples = 10000/50 = 200 samples
    if (samples>=2000){
//        GpioDataRegs.GPATOGGLE.bit.GPIO20 = 1;
        samples = 0;
        rmsvalue = sqrtf(rmsbuffer/2000.0);
        avgval = avgvalbuf/2000.0;
        avgvalbuf = 0.0;
        rmsbuffer = 0.0;
    }

//    ----------------CODE FOR SENSING THE AMPLITUDE OF THE CP-SIGNAL WAVEFORM---------------
    static volatile float amplitude;
    static volatile float ampbuf = 0.0;
    static volatile Uint16 samples_cp = 0;

    actualsensedvalues.cp_signal = (sensedAnalogADC.cp_signal - offsets.cp_signal)/(multipliers.cp_signal);
//    ADJUSTING THE OFFSET
    if (actualsensedvalues.cp_signal <= 1 && samples_cp>0){
        amplitude = ampbuf/samples_cp;
        ampbuf = 0.0;
        samples_cp = 0;
    }

    if (actualsensedvalues.cp_signal > 1){
        samples_cp++;
        ampbuf += actualsensedvalues.cp_signal;
    }


//    --------------CODE FOR THE PROTECTIVE EARTH-------------------
    actualsensedvalues.prot_earth = (sensedAnalogADC.prot_earth - offsets.prot_earth)/(multipliers.prot_earth);

//    ---------------CODE FOR THE BATTERY SENSING--------------------
    actualsensedvalues.vbatt = (sensedAnalogADC.vbatt - offsets.vbatt)/(multipliers.vbatt);

//    ---------------CODE FOR THE TEMPERATURE SENSING--------------------
    actualsensedvalues.temp_sens = (sensedAnalogADC.temp_sens - offsets.temp_sens)/(multipliers.temp_sens);

//    ---------------CODE FOR THE RESIDUAL CURRENT SENSING--------------------
    actualsensedvalues.residual_curr = (sensedAnalogADC.residual_curr - offsets.residual_curr)/(multipliers.residual_curr);

//    ---------------CODE FOR THE BATTERY SENSING--------------------
    actualsensedvalues.grid_curr = (sensedAnalogADC.grid_curr - offsets.grid_curr)/(multipliers.grid_curr);

//    -----------TRAMSMITTING THE ACTUAL SENSED VALUES OVER THE CAN BUS TO THE MICROCONTROLLER FOR THE FURTHER PROCESSING--------------
    canCount++;
    if (canCount > 1000000){
        canCount = 0;

        // Configuring transmission for sequence number 1
        can_message_seq1_phvolt.phase_seq.Seq_number        = 0x01;
        can_message_seq1_phvolt.phase_seq.Upper_Byte_PhaseA = 0x10;
        can_message_seq1_phvolt.phase_seq.Lower_Byte_PhaseA = 0x10;
        can_message_seq1_phvolt.phase_seq.Upper_Byte_PhaseB = 0x01;
        can_message_seq1_phvolt.phase_seq.Lower_Byte_PhaseB = 0x01;
        can_message_seq1_phvolt.phase_seq.Upper_Byte_PhaseC = 0x01;
        can_message_seq1_phvolt.phase_seq.Lower_Byte_PhaseC = 0x10;
        can_message_seq1_phvolt.phase_seq.Reserved          = 0xFF;

        CAN_sendMessage(CANA_BASE, 1, 8, can_message_seq1_phvolt.can_seq); // Sending using the mailbox 1 configured for the transmission

//        Configuring for the transmission of the sequence number 2
        // Configuring transmission for sequence number 2 in correct order
        can_message_seq2_phcurr.phase_seq.Seq_number        = 0x02;
        can_message_seq2_phcurr.phase_seq.Upper_Byte_PhaseA = 0x01;
        can_message_seq2_phcurr.phase_seq.Lower_Byte_PhaseA = 0x01;
        can_message_seq2_phcurr.phase_seq.Upper_Byte_PhaseB = 0x01;
        can_message_seq2_phcurr.phase_seq.Lower_Byte_PhaseB = 0x01;
        can_message_seq2_phcurr.phase_seq.Upper_Byte_PhaseC = 0x01;
        can_message_seq2_phcurr.phase_seq.Lower_Byte_PhaseC = 0x01;
        can_message_seq2_phcurr.phase_seq.Reserved          = 0xFF;

        CAN_sendMessage(CANA_BASE, 2, 8, can_message_seq2_phcurr.can_seq);  //Sending using the mailbox 2 configured for the transmission

//        Configuring for the transmission using the sequence number 3
        // Configuring transmission for sequence number 3 in correct order
        can_message_seq3_info.phase_seq.Seq_number           = 0x03;
        can_message_seq3_info.phase_seq.Upper_Byte_RCMU      = 0x01;
        can_message_seq3_info.phase_seq.Lower_Byte_RCMU      = 0x01;
        can_message_seq3_info.phase_seq.Upper_Byte_NEvoltage = 0x01;
        can_message_seq3_info.phase_seq.Lower_Byte_NEvoltage = 0x01;
        can_message_seq3_info.phase_seq.Cp_state             = 0x01;
        can_message_seq3_info.phase_seq.DutyCycle            = 0x01;
        can_message_seq3_info.phase_seq.ConnectorState       = 0x01;

        CAN_sendMessage(CANA_BASE, 3, 8, can_message_seq3_info.can_seq);

    }

//    ---Acknowledgement of the interrupt----
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;         // Must acknowledge the PIE group

    //--- Manage the ADC registers
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;          // Clear ADCINT1 flag
}

//
// 1.2 - ADCC Interrupt 1
//
interrupt void ADCC1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.4 - XINT1 Interrupt
//
interrupt void XINT1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.5 - XINT2 Interrupt
//
interrupt void XINT2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.6 - SYS_ERR Interrupt
//
interrupt void SYS_ERR_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.7 - Timer 0 Interrupt
//
interrupt void TIMER0_ISR(void)
{
    CpuTimer0Regs.TCR.bit.TIF   =   1;      //Cleared the zero crossing flag
    CpuTimer0Regs.TCR.bit.TRB   =   1;      //Reloading the timer
    EALLOW;
    GpioDataRegs.GPATOGGLE.bit.GPIO20 = 1;
    GpioDataRegs.GPATOGGLE.bit.GPIO22 = 1;
    EDIS;
//    Code for the timer interrupt to be addressed in the isr.
    InitCpuTimer(seconds);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// 1.8 - Standby and Halt Wakeup Interrupt
//
interrupt void WAKE_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.1 - ePWM1 Trip Zone Interrupt
//
interrupt void EPWM1_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.2 - ePWM2 Trip Zone Interrupt
//
interrupt void EPWM2_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.3 - ePWM3 Trip Zone Interrupt
//
interrupt void EPWM3_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.4 - ePWM4 Trip Zone Interrupt
//
interrupt void EPWM4_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.5 - ePWM5 Trip Zone Interrupt
//
interrupt void EPWM5_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.6 - ePWM6 Trip Zone Interrupt
//
interrupt void EPWM6_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.7 - ePWM7 Trip Zone Interrupt
//
interrupt void EPWM7_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.1 - ePWM1 Interrupt
//
interrupt void EPWM1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.2 - ePWM2 Interrupt
//
interrupt void EPWM2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.3 - ePWM3 Interrupt
//
interrupt void EPWM3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.4 - ePWM4 Interrupt
//
interrupt void EPWM4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.5 - ePWM5 Interrupt
//
interrupt void EPWM5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.6 - ePWM6 Interrupt
//
interrupt void EPWM6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.7 - ePWM7 Interrupt
//
interrupt void EPWM7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.1 - eCAP1 Interrupt
//
interrupt void ECAP1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.2 - eCAP2 Interrupt
//
interrupt void ECAP2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.1 - eQEP1 Interrupt
//
interrupt void EQEP1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.1 - SPIA Receive Interrupt
//
interrupt void SPIA_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.2 - SPIA Transmit Interrupt
//
interrupt void SPIA_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.7 - DCC0 Interrupt
//
interrupt void DCC0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.1 - I2CA Interrupt 1
//
interrupt void I2CA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.2 - I2CA Interrupt 2
//
interrupt void I2CA_FIFO_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.3 - I2CB Interrupt 1
//
interrupt void I2CB_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.4 - I2CB Interrupt 2
//
interrupt void I2CB_FIFO_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.5 - SCIC Receive Interrupt : MCU-LCU UART Communication
//
interrupt void SCIC_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.6 - SCIC Transmit Interrupt
//
interrupt void SCIC_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.1 - SCIA Receive Interrupt : MCU-HMI Communication
//
interrupt void SCIA_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.2 - SCIA Transmit Interrupt
//
interrupt void SCIA_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.3 - SCIB Receive Interrupt : MCU:RFID Reader EM-18
//
interrupt void SCIB_RX_ISR(void)
{

    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.4 - SCIB Transmit Interrupt
//
interrupt void SCIB_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.5 - CANA Interrupt 0
//
interrupt void CANA0_ISR(void)
{
    static Uint16 objectID = 0;
    objectID = CAN_getInterruptCause(CANA_BASE);

//    ################FOR THE TESTING OF THE THREE SEQUENCES#####################
    while (objectID != 0){
        if (objectID == 4){
                CAN_readMessage(CANA_BASE, 4, getdata.rsgMsgObjSeq1);
            }

        if (objectID == 5){
                CAN_readMessage(CANA_BASE, 5, getdata.rsgMsgObjSeq2);
            }

        if (objectID == 6){
                CAN_readMessage(CANA_BASE, 6, getdata.rsgMsgObjSeq3);
            }
        CAN_clearInterruptStatus(CANA_BASE, objectID);  //for removing only the cause of only that interrupt that is currently under processing
        objectID = CAN_getInterruptCause(CANA_BASE);
    }

//    ##############FOR THE ACTUAL MESSAGE TO BE RECEIVED BY CAN FROM THE MCU####################
    if (objectID == 7){
//        DATA FROM THE RECEIVER IS GETTING STORED IN THE CANRxData
        CAN_readMessage(CANA_BASE, objectID, CANRxData);

//        Fetching the evse status from the MCU
        if (CANRxData[1] == 0){
            EvseState = OFF;
        }

        if (CANRxData[1] == 1){
            EvseState = ON;
        }
    }

    CAN_clearGlobalInterruptStatus(CANA_BASE, CAN_GLOBAL_INT_CANINT0);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

//
// 9.6 - CANA Interrupt 1
//
interrupt void CANA1_ISR(void)
{

    CAN_clearGlobalInterruptStatus(CANA_BASE, CAN_GLOBAL_INT_CANINT1);

    // CAN Interrupt Code : End
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

//
// 10.1 - ADCA Event Interrupt
//
interrupt void ADCA_EVT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.2 - ADCA Interrupt 2
//
interrupt void ADCA2_ISR(void)
{
    static volatile float sinval = 0.0;
    static volatile Uint16 digitalvalue = 0;
    count++;
    sinval = sinf((count * M_PI * 2)/200);
//    CREATING THE SINE WAVE HERE

    if (count >= 200){
        count = 0;
    }

    digitalvalue = (sinval+1)*(4096.0/2.0);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;          // Clear ADCINT1 flag
}

//
// 10.3 - ADCA Interrupt 3
//
interrupt void ADCA3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.4 - ADCA Interrupt 4
//
interrupt void ADCA4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.5 - ADCC Event Interrupt
//
interrupt void ADCC_EVT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.6 - ADCC Interrupt 2
//
interrupt void ADCC2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.7 - ADCC Interrupt 3
//
interrupt void ADCC3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.8 - ADCC Interrupt 4
//
interrupt void ADCC4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.1 - XINT3 Interrupt
//
interrupt void XINT3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.2 - XINT4 Interrupt
//
interrupt void XINT4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.3 - XINT5 Interrupt
//
interrupt void XINT5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.5 - Interrupt from flash sub-system
//
interrupt void FLSS_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// Catch-all Default ISRs:
//

//
// PIE_RESERVED_ISR - Reserved ISR
//
interrupt void PIE_RESERVED_ISR(void)
{
    asm ("      ESTOP0");
    for(;;);
}

//
// EMPTY_ISR - Only does a return
//
interrupt void EMPTY_ISR(void)
{

}

//
// NOTUSED_ISR - Unused ISR
//
interrupt void NOTUSED_ISR(void)
{
    asm ("      ESTOP0");
    for(;;);
}

//
// End of File
//

