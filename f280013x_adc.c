//###########################################################################
//
// FILE:    f280013x_adc.c
//
// TITLE:   F28002x ADC Support Functions.
//
//###########################################################################
//
//
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
//
#include <GTSI_1Phase1MPPT.h>                        // Main include file
#include "f280013x_device.h"      // Header File Include File
#include "f280013x_examples.h"    // Examples Include File
#include "f28x_project.h"
//
// SetVREF - Set Vref mode. Function to select reference mode and offset trim.
// Offset trim for Internal VREF 3.3 is unique.  All other modes use the same
// offset trim. Also note that when the mode parameter is ADC_EXTERNAL, the
// ref parameter has no effect.
//
// In this device, the bandgaps are common for all the ADC instances,
// hence common Vref configuration needs to be done for all the ADCs. This
// API configures same Vref configuration for all the supported ADCs in the
// device.
//
void SetVREF(int module, int mode, int ref)
{
    Uint16 *offset, offsetShiftVal;

    if((mode == ADC_INTERNAL) && (ref == ADC_VREF3P3))
    {
        offsetShiftVal = 8U;         // Internal / 1.65v mode offset
    }
    else
    {
        offsetShiftVal = 0U;        // All other modes
    }

    //
    // Set up pointer to offset trim in OTP for ADCA.
    //
    offset = (Uint16 *)((Uint32)0x7016CU);

    EALLOW;

    //
    // Get offset trim from OTP and write it to the register for ADCA.
    //
    AdcaRegs.ADCOFFTRIM.bit.OFFTRIM = (*offset >> offsetShiftVal) & 0xFFU;

    //
    // Set up pointer to offset trim in OTP for ADCC.
    //
    offset = (Uint16 *)((Uint32)0x7016EU);

    //
    // Get offset trim from OTP and write it to the register for ADCC.
    //
    AdccRegs.ADCOFFTRIM.bit.OFFTRIM = (*offset >> offsetShiftVal) & 0xFFU;

    //
    // Configure the reference mode for all ADCs (internal or external).
    //
    AnalogSubsysRegs.ANAREFCTL.bit.ANAREFSEL = mode;

    //
    // Configure the reference voltage for all ADCs (3.3V or 2.5V).
    //
    AnalogSubsysRegs.ANAREFCTL.bit.ANAREF2P5SEL = ref;

    EDIS;
}

//--------------FOR THE BATTERY CHARGER PROJECT--------------------

void MyInitADC(void){

    asm(" EALLOW");                     // Enable EALLOW protected register access

    DevCfgRegs.SOFTPRES13.bit.ADC_A         = 1;    // ADC A is reset
    DevCfgRegs.SOFTPRES13.bit.ADC_A         = 0;    // ADC A is released from reset

    DevCfgRegs.SOFTPRES13.bit.ADC_C         = 1;    // ADC C is reset
    DevCfgRegs.SOFTPRES13.bit.ADC_C         = 0;    // ADC C is released from reset

    // ------ Configuring ADC A, ADC C Control-1 Register: START -------

    AdcaRegs.ADCCTL1.all                    = 0x0004;      // Main ADC A configuration
    AdccRegs.ADCCTL1.all                    = 0x0004;      // Main ADC C configuration

    // ------ Configuring ADC A, ADC C Control-2 Register: START ------

    AdcaRegs.ADCCTL2.all                    = 0x0006;      // ADC A clock configuration (Set to 30MHz)
    AdccRegs.ADCCTL2.all                    = 0x0006;      // ADC C clock configuration (Set to 30MHz)

    // ------ Configuring ADC A, ADC C Burst Control Register (ADCBURSTCTL): START ------
    // ------ Since we are dealing with only one soc we need not care about the burst control or anything like that;

    AdcaRegs.ADCBURSTCTL.all                = 0x0000;
    AdccRegs.ADCBURSTCTL.all                = 0x0000;
    asm(" EDIS");                               // Disable EALLOW protected register access

    // --------  Set Vref as Internal with 0 to 3.3V Range: START ----------

    SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);
    SetVREF(ADC_ADCC, ADC_INTERNAL, ADC_VREF3P3);

    asm(" EALLOW");                     // Enable EALLOW protected register access

    //----- We are trying to configure the trigger and desired start of conversion channel----
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL         = 0x7;    // Trigger by ePWM2 SOC A
    AdcaRegs.ADCSOC0CTL.bit.CHSEL           = 3;    // Convert channel ADC A3: B phase voltage
    AdcaRegs.ADCSOC0CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns

    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL         = 0x7;    // Trigger by ePWM2 SOC A
    AdcaRegs.ADCSOC1CTL.bit.CHSEL           = 6;    // Convert channel ADC A6: Y phase voltage
    AdcaRegs.ADCSOC1CTL.bit.ACQPS           = 0xB;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns

    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL         = 0x7;    // Trigger by ePWM2 SOC A
    AdcaRegs.ADCSOC2CTL.bit.CHSEL           = 15;    // Convert channel ADC A15: Battery voltage sensing
    AdcaRegs.ADCSOC2CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns

    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL         = 0x7;    // Trigger by ePWM2 SOC A
    AdcaRegs.ADCSOC3CTL.bit.CHSEL           = 11;    // Convert channel ADC A11:  Pilot signal sensing
    AdcaRegs.ADCSOC3CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns

    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL         = 0x7;    // Trigger by ePWM2 SOC A
    AdcaRegs.ADCSOC4CTL.bit.CHSEL           = 12;    // Convert channel ADC A12:  B - phase current sensing
    AdcaRegs.ADCSOC4CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns

    AdcaRegs.ADCSOC5CTL.bit.TRIGSEL         = 0x7;    // Trigger by ePWM2 SOC A
    AdcaRegs.ADCSOC5CTL.bit.CHSEL           = 1;    // Convert channel ADC A1:  R - phase current sensing
    AdcaRegs.ADCSOC5CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns

//----- SOC (SOC0, SOC1, SOC2...) Configuration for ADC C: START -----

    AdccRegs.ADCSOC0CTL.bit.TRIGSEL         = 0x7;    // Trigger by ePWM2 SOC A
    AdccRegs.ADCSOC0CTL.bit.CHSEL           = 6;    // Convert channel ADC C6: R phase voltage (GPIO 226)
    AdccRegs.ADCSOC0CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns

    AdccRegs.ADCSOC1CTL.bit.TRIGSEL         = 0x7;    // Trigger by ePWM2 SOC A
    AdccRegs.ADCSOC1CTL.bit.CHSEL           = 9;    // Convert channel ADC C9: It is used for the protective earth sensing
    AdccRegs.ADCSOC1CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns

    AdccRegs.ADCSOC2CTL.bit.TRIGSEL         = 0x7;    // Trigger by ePWM2 SOC A
    AdccRegs.ADCSOC2CTL.bit.CHSEL           = 2;    // Convert channel ADC C2: Temperature sensing
    AdccRegs.ADCSOC2CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns

    AdccRegs.ADCSOC3CTL.bit.TRIGSEL         = 0x7;    // Trigger by ePWM2 SOC A
    AdccRegs.ADCSOC3CTL.bit.CHSEL           = 15;    // Convert channel ADC C15: Residual current sensing
    AdccRegs.ADCSOC3CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns

    AdccRegs.ADCSOC4CTL.bit.TRIGSEL         = 0x7;    // Trigger by ePWM2 SOC A
    AdccRegs.ADCSOC4CTL.bit.CHSEL           = 3;    // Convert channel ADC C3: Y phase current sensing
    AdccRegs.ADCSOC4CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns

    //----- Configuring ADC A Interrupt-1 and disable ADC C interrupts  : START -----

     AdcaRegs.ADCINTSEL1N2.bit.INT1CONT      = 1;     // Interrupt pulses
     AdcaRegs.ADCINTSEL1N2.bit.INT1E         = 1;     // ADC A interrupt enable
     AdcaRegs.ADCINTSEL1N2.bit.INT1SEL       = 5;     // EOC5 triggers the interrupt

     AdccRegs.ADCINTSEL1N2.bit.INT1E         = 0;     // ADC C interrupt disable

      //******** Powering Up ADCs : START *******

      AdcaRegs.ADCCTL1.bit.ADCPWDNZ           = 1;          // Power up the ADC A
      AdccRegs.ADCCTL1.bit.ADCPWDNZ           = 1;          // Power up the ADC C

      //******** Waiting Period after Power-Up the ADCs : START *******

      DELAY_US(1000);                              // Wait 1 ms after power-up before using the ADC

      //******** Waiting Period after Power-Up the ADCs : END *******

        asm(" EDIS");                               // Disable EALLOW protected register access

}

//----------------END OF THE ADC CODE FOR THE PROJECT----------------


