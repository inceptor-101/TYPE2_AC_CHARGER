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

static inline void UtilsRMS(void){
//    For the RMS values calculations
    rmsvalues.grid_curr_B = sqrtf(sum_values.grid_curr_B/(float)rmsSamples);
    rmsvalues.grid_curr_R = sqrtf(sum_values.grid_curr_R/(float)rmsSamples);
    rmsvalues.grid_curr_Y = sqrtf(sum_values.grid_curr_Y/(float)rmsSamples);
    rmsvalues.grid_voltage_B = sqrtf(sum_values.grid_voltage_B/(float)rmsSamples);
    rmsvalues.grid_voltage_R = sqrtf(sum_values.grid_voltage_R/(float)rmsSamples);
    rmsvalues.grid_voltage_Y = sqrtf(sum_values.grid_voltage_Y/(float)rmsSamples);
    rmsvalues.prot_earth = sqrtf(sum_values.prot_earth/(float)rmsSamples);
    rmsvalues.residual_curr = sqrtf(sum_values.residual_curr/(float)rmsSamples);

//    For the average values calculations
    rmsvalues.actualTemp = sum_values.actualTemp/(float)rmsSamples;
    rmsvalues.vbatt = sum_values.vbatt/(float)rmsSamples;

//    Resetting the sum structure
    memset(&sum_values, 0, sizeof(sum_values));
}

static inline void current2DutyCycle(void){
    if (inputCurrent >= 6.0f && inputCurrent <= 51.0f){
        dutyCycle = inputCurrent/(60.0f);
    }
    else if (inputCurrent > 51 && inputCurrent <= 80){
        dutyCycle = ((inputCurrent/(2.5f)) + 64.0f)/(100.0f);
    }
    else {
        dutyCycle = 0.0f;
    }
}

static inline void getCurrentState(){

//    epwmState = ((1/dutyCycle)*(((EvStateAvgVolt - 1.451612903f)/(0.1202346f)) + (11.96f * (1 - dutyCycle))));

    if (epwmState >= 10.0f){
        EVSEstate = CP_STATE_A;
        return;
    }
    else if (epwmState >= 7.0f){
        EVSEstate = CP_STATE_B;
        return;
    }
    else if (epwmState >= 4.0f){
        EVSEstate = CP_STATE_C;
        return;
    }
    else if (epwmState >= 1.0f){
        EVSEstate = CP_STATE_D;
        return;
    }
    else if (epwmState >= -2.0f){
        EVSEstate = CP_STATE_E;
        return;
    }
    else{
        EVSEstate = CP_STATE_F;
        return;
    }
}

static inline void UtilsEVstate(){
    EvStateAvgVolt = cpSignalBuffer/(20.0f);
    cpSignalBuffer = 0.0f;
}

// 1.1 - ADCA Interrupt 1
//

interrupt void ADCA1_ISR(void){

//    Setting the epwm duty cycle
    Uint16 cmpaval = dutyCycle*(float)TBPRDEPWM1;
    EPwm1Regs.CMPA.bit.CMPA = cmpaval;

//    ---------------CODE FOR DETECTING THE SENSED VARIABLES AND GETTING ACTUAL VALUES USING THE OFFSET-----------------
//    -----------------Storing all of the sensed parameters in their corresponding allocated variables------------------
    sensedAnalogADC.grid_voltage_R = (AdccResultRegs.ADCRESULT0)*(3.3/4096.0);
    sensedAnalogADC.grid_voltage_B = (AdcaResultRegs.ADCRESULT0)*(3.3/4096.0);
    sensedAnalogADC.grid_voltage_Y = (AdcaResultRegs.ADCRESULT1)*(3.3/4096.0);
    sensedAnalogADC.prot_earth = (AdccResultRegs.ADCRESULT1)*(3.3/4096.0);
    sensedAnalogADC.vbatt = (AdcaResultRegs.ADCRESULT2)*(3.3/4096.0);
    sensedAnalogADC.temp_sens = (AdccResultRegs.ADCRESULT2)*(3.3/4096.0);
    sensedAnalogADC.cp_signal = (AdcaResultRegs.ADCRESULT3)*(3.3/4096.0);
    sensedAnalogADC.residual_curr = (AdccResultRegs.ADCRESULT3)*(3.3/4096.0);
    sensedAnalogADC.grid_curr_B = (AdcaResultRegs.ADCRESULT4)*(3.3/4096.0);
    sensedAnalogADC.grid_curr_Y = (AdccResultRegs.ADCRESULT4)*(3.3/4096.0);
    sensedAnalogADC.grid_curr_R = (AdcaResultRegs.ADCRESULT5)*(3.3/4096.0);

//    Getting the new temperature resistance
    tempSensRes = (25500.0f/(sensedAnalogADC.temp_sens)) - 10200.0f;

//    For finding the temperature at every sample of the resistance found or calculated
    sensedAnalogADC.actualTemp = (1.0f/((1/298.0f) + ((1/beta) * logf(tempSensRes/10000.0)))) - 273.0f; // in degree celsius

    // Developing the statemachine
    switch (currstate){
        case oneseconddelaymode: {
            turnMainRelayOff;
            transition_counter++;
            if (transition_counter >= oneSecDelayCounter){
                currstate = offsetcalcmode;
                transition_counter = 0;
            }
            break;
        }

        case offsetcalcmode: {
            turnMainRelayOff;
            transition_counter++;
            sum_values.grid_curr_B += sensedAnalogADC.grid_curr_B;
            sum_values.grid_curr_R += sensedAnalogADC.grid_curr_R;
            sum_values.grid_curr_Y += sensedAnalogADC.grid_curr_Y;
            sum_values.residual_curr += sensedAnalogADC.residual_curr;
            sum_values.grid_voltage_B += sensedAnalogADC.grid_voltage_B;
            sum_values.grid_voltage_R += sensedAnalogADC.grid_voltage_R;
            sum_values.grid_voltage_Y += sensedAnalogADC.grid_voltage_Y;
            sum_values.prot_earth += sensedAnalogADC.prot_earth;

            if (transition_counter >= oneSecDelayCounter){
                AvgOffsets.grid_curr_B = sum_values.grid_curr_B/(float)transition_counter;
                AvgOffsets.grid_curr_R = sum_values.grid_curr_R/(float)transition_counter;
                AvgOffsets.grid_curr_Y = sum_values.grid_curr_Y/(float)transition_counter;
                AvgOffsets.residual_curr = sum_values.residual_curr/(float)transition_counter;
                AvgOffsets.grid_voltage_B = sum_values.grid_voltage_B/(float)transition_counter;
                AvgOffsets.grid_voltage_R = sum_values.grid_voltage_R/(float)transition_counter;
                AvgOffsets.grid_voltage_Y = sum_values.grid_voltage_Y/(float)transition_counter;
                AvgOffsets.prot_earth = sum_values.prot_earth/(float)transition_counter;

//                Reinitialising the sum structure values
                transition_counter = 0;
                memset(&sum_values, 0, sizeof(sum_values));

//                Switching to the new active state
                currstate = activemode;
            }
            break;
        }

        case activemode: {
            transition_counter++;
//            Found out the actual value of the various parameters
            actualsensedvalues.grid_curr_B = (sensedAnalogADC.grid_curr_B-AvgOffsets.grid_curr_B)*multipliers.grid_curr_B;
            actualsensedvalues.grid_curr_R = (sensedAnalogADC.grid_curr_R-AvgOffsets.grid_curr_R)*multipliers.grid_curr_R;
            actualsensedvalues.grid_curr_Y = (sensedAnalogADC.grid_curr_Y-AvgOffsets.grid_curr_Y)*multipliers.grid_curr_Y;
            actualsensedvalues.grid_voltage_B = (sensedAnalogADC.grid_voltage_B-AvgOffsets.grid_voltage_B)*multipliers.grid_voltage_B;
            actualsensedvalues.grid_voltage_R = (sensedAnalogADC.grid_voltage_R-AvgOffsets.grid_voltage_R)*multipliers.grid_voltage_R;
            actualsensedvalues.grid_voltage_Y = (sensedAnalogADC.grid_voltage_Y-AvgOffsets.grid_voltage_Y)*multipliers.grid_voltage_Y;
            actualsensedvalues.prot_earth = (sensedAnalogADC.prot_earth-AvgOffsets.prot_earth)*multipliers.prot_earth;
            actualsensedvalues.residual_curr = (sensedAnalogADC.residual_curr-AvgOffsets.residual_curr)*multipliers.residual_curr;
            actualsensedvalues.cp_signal = (sensedAnalogADC.cp_signal-AvgOffsets.cp_signal)/multipliers.cp_signal;

//            For few we need to find the RMS values
            sum_values.grid_curr_B += (actualsensedvalues.grid_curr_B*actualsensedvalues.grid_curr_B);
            sum_values.grid_curr_R += (actualsensedvalues.grid_curr_R*actualsensedvalues.grid_curr_R);
            sum_values.grid_curr_Y += (actualsensedvalues.grid_curr_Y*actualsensedvalues.grid_curr_Y);
            sum_values.grid_voltage_B += (actualsensedvalues.grid_voltage_B*actualsensedvalues.grid_voltage_B);
            sum_values.grid_voltage_R += (actualsensedvalues.grid_voltage_R*actualsensedvalues.grid_voltage_R);
            sum_values.grid_voltage_Y += (actualsensedvalues.grid_voltage_Y*actualsensedvalues.grid_voltage_Y);
            sum_values.prot_earth += (actualsensedvalues.prot_earth*actualsensedvalues.prot_earth);
            sum_values.residual_curr += (actualsensedvalues.residual_curr*actualsensedvalues.residual_curr);

//            For the average values
            sum_values.actualTemp += (sensedAnalogADC.actualTemp);
            sum_values.vbatt += (actualsensedvalues.vbatt);

//            cpSignalBuffer += (sensedAnalogADC.cp_signal);
//
////            For processing the cp signal buffer
//            if (transition_counter%20 == 0){
//                UtilsEVstate();                 // Using this function the value of the EvStateAvgVoltage will be updated
//                getCurrentState();              // Finding the state of the EV
//            }

//            Finding the RMS after fetching 400 samples
            if (transition_counter >= 400){
                transition_counter = 0;
                UtilsRMS();
            }

            break;
        }
    }

    canCount++;
    if (canCount > canMessageSendCounter){
//        Sending the CAN message after every 1 seconds
        sendMessageNow = 1;
        canCount = 0;
        Uint16 buffer = 0;

        // Configuring transmission for sequence number 1
        can_message_seq1_phvolt.phase_seq.Seq_number        = 0x01;
        buffer = (Uint16) (rmsvalues.grid_voltage_R*10.0f);
        can_message_seq1_phvolt.phase_seq.Upper_Byte_PhaseA = buffer>>8;
        can_message_seq1_phvolt.phase_seq.Lower_Byte_PhaseA = buffer&(0x00ff);
        buffer = (Uint16) (rmsvalues.grid_voltage_B*10.0f);
        can_message_seq1_phvolt.phase_seq.Upper_Byte_PhaseB = buffer>>8;
        can_message_seq1_phvolt.phase_seq.Lower_Byte_PhaseB = buffer&(0x00ff);
        buffer = (Uint16) (rmsvalues.grid_voltage_Y*10.0f);
        can_message_seq1_phvolt.phase_seq.Upper_Byte_PhaseC = buffer>>8;
        can_message_seq1_phvolt.phase_seq.Lower_Byte_PhaseC = buffer&(0x00ff);
        can_message_seq1_phvolt.phase_seq.Reserved          = 0xFF;

//        CAN_sendMessage(CANA_BASE, 1, 8, can_message_seq1_phvolt.can_seq); // Sending using the mailbox 1 configured for the transmission

//        Configuring for the transmission of the sequence number 2

        can_message_seq2_phcurr.phase_seq.Seq_number        = 0x02;
        buffer = (Uint16) (rmsvalues.grid_curr_R*10.0f);
        can_message_seq2_phcurr.phase_seq.Upper_Byte_PhaseA = buffer>>8;
        can_message_seq2_phcurr.phase_seq.Lower_Byte_PhaseA = buffer&(0x00ff);
        buffer = (Uint16) (rmsvalues.grid_curr_B*10.0f);
        can_message_seq2_phcurr.phase_seq.Upper_Byte_PhaseB = buffer>>8;
        can_message_seq2_phcurr.phase_seq.Lower_Byte_PhaseB = buffer&(0x00ff);
        buffer = (Uint16) (rmsvalues.grid_curr_Y*10.0f);
        can_message_seq2_phcurr.phase_seq.Upper_Byte_PhaseC = buffer>>8;
        can_message_seq2_phcurr.phase_seq.Lower_Byte_PhaseC = buffer&(0x00ff);
        can_message_seq2_phcurr.phase_seq.Reserved          = 0xFF;

//        CAN_sendMessage(CANA_BASE, 2, 8, can_message_seq2_phcurr.can_seq);  //Sending using the mailbox 2 configured for the transmission

//        Configuring for the transmission using the sequence number 3

        can_message_seq3_info.phase_seq.Seq_number           = 0x03;
        buffer = (Uint16) (rmsvalues.residual_curr*10000.0f);           //Ten multiplier by default and multiplying by 1000 to convert to milliamperes
        can_message_seq3_info.phase_seq.Byte_RCMU            = buffer&(0x00ff);
        buffer = (Uint16) (rmsvalues.prot_earth*10.0f);
        can_message_seq3_info.phase_seq.Byte_NEvoltage       = buffer&(0x00ff);
        can_message_seq3_info.phase_seq.Cp_state             = EVSEstate&(0x00ff);
        buffer = (Uint16) (dutyCycle*100.0f);
        can_message_seq3_info.phase_seq.DutyCycle            = buffer&(0x00ff);
        can_message_seq3_info.phase_seq.ConnectorState       = 0x01;
        can_message_seq3_info.phase_seq.Reserved             = 0xffffffff;

//        CAN_sendMessage(CANA_BASE, 3, 8, can_message_seq3_info.can_seq);

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
//    CpuTimer0Regs.TCR.bit.TIF   =   1;      //Cleared the zero crossing flag
//    CpuTimer0Regs.TCR.bit.TRB   =   1;      //Reloading the timer
//    EALLOW;
//    GpioDataRegs.GPATOGGLE.bit.GPIO20 = 1;
//    GpioDataRegs.GPATOGGLE.bit.GPIO22 = 1;
//    EDIS;
//    Code for the timer interrupt to be addressed in the isr.
//    InitCpuTimer(seconds);
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
//    All these thing we are doing to make sure that the ADCA ISR dont get interrupted in between
    Uint16 tempPIEIER = PieCtrlRegs.PIEIER9.all;            // Storing the interrupt configuration inside a temporary variable
    IER |= 0x0001;                                          // Enabling the group 1 interrupts
    IER &= 0x0001;                                          // Disabling all other interrupts 4
    PieCtrlRegs.PIEACK.all = 0xffff;                        // All the interrupts are acknowledged
    asm("       NOP");                                      // Waiting for a sysclock cycle
    EINT;

//    When entering the ADC ISR we have all the interrupts automatically disabled

    static Uint16 objectID = 0;
    objectID = CAN_getInterruptCause(CANA_BASE);
    CAN_readMessage(CANA_BASE, 5, getdata.rsgMsgObjSeq2);
    CAN_clearInterruptStatus(CANA_BASE, objectID);

//    ################FOR THE TESTING OF THE THREE SEQUENCES#####################
//    while (objectID != 0){
//        if (objectID == 4){
//                CAN_readMessage(CANA_BASE, 4, getdata.rsgMsgObjSeq1);
//            }
//
//        if (objectID == 5){
//                CAN_readMessage(CANA_BASE, 5, getdata.rsgMsgObjSeq2);
//            }
//
//        if (objectID == 6){
//                CAN_readMessage(CANA_BASE, 6, getdata.rsgMsgObjSeq3);
//            }
//        CAN_clearInterruptStatus(CANA_BASE, objectID);  //for removing only the cause of only that interrupt that is currently under processing
//        objectID = CAN_getInterruptCause(CANA_BASE);
//    }

//    Now the actual data has got stored in the getdata.rsgMsgObjSeq2
    SeqNumberReceived = getdata.rsgMsgObjSeq2[0];
    EVSE_Ready_To_Charge = getdata.rsgMsgObjSeq2[1];
    inputCurrent = (float)getdata.rsgMsgObjSeq2[2];

//    Restoring to previous configuration of the interrupts
    DINT;
    PieCtrlRegs.PIEIER9.all = tempPIEIER;
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
