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

void MyInitADC2(void){

//    IN THE CODE WE ARE CONFIGURING THE ADCA AS THE MASTER AND THE ADCC AS THE SLAVE
//    WHICH MEANS THAT THE INTERRUPT WILL BE GENERATED AT THE END OF THE LOWEST PRIPRITY SOC OF THE ADCA INSTEAD OF THE ADCC
    count++;
    asm(" EALLOW");

//    RESTARTING THE ADC MODULES BOTH THE ADCA AND ADCC
    DevCfgRegs.SOFTPRES13.bit.ADC_A = 1;    // RESETTING THE ADCA MODULE
    DevCfgRegs.SOFTPRES13.bit.ADC_A = 0;    // RELEASED FROM THE RESET

    DevCfgRegs.SOFTPRES13.bit.ADC_C = 1;     // RESETTING THE ADCC MODULE
    DevCfgRegs.SOFTPRES13.bit.ADC_C = 0;    // RELEASING FROM THE RESET

    //    CONFIGURING THE ADCA FOR THE INTERVAL OF THE INTERRUPT GENERATION WHETHER AT THE START OF THE CONVERSION OR THE END OF THE CONVERSION
    AdcaRegs.ADCCTL1.all = 0x0004;   // USING THIS THE INTERRUPT WILL OCCUR AT THE END OF THE CONVERSION AND WE HAVE ALL DATA
    AdccRegs.ADCCTL1.all = 0x0004;   // CONFIGURING FOR THE C ALSO ALTHOUGH WE DONT ACTUALLY NEED IT AS THE INTERRUPT WILL BE GENERATED AT THE END OF THE ADCA INTERRUPT OR THE MASTER ADC MODULE

//    WE WANT TO USE HERE THE 60MHZ ADC CLOCK SO WE CAN CONFIGURE THEM INDIVIDUALLY IN THE A AND C MODULES
    AdcaRegs.ADCCTL2.all = 0x0006;  // AS WE KNOW THAT THE SYSCLK IS 120MHz SO THE RESULTING ADC CLOCK WILL BE 120/4 MHz = 30MHZ
    AdccRegs.ADCCTL2.all = 0x0006;  // REPEATING THE SAME THING FOR THE ADC C MODULE

//    ALTHOUGH WE CAN USE THE BURST MODE BECAUSE WE ARE USING CURRENTLY RELYING ON THE NORMAL SOC FOR OUR MANIPULATIONS
    AdcaRegs.ADCBURSTCTL.all = 0x0000;  // DEACTIVATING THE BURST MODE FOR THE ADCA SUBMODULE
    AdccRegs.ADCBURSTCTL.all = 0x0000;  // DEACTIVATING THE BURST MODE FOR THE ADCD SUBMODULE

    asm(" EDIS");

//    SETTING THE REFERENCE VOLTAGES FOR THE ADC MODULE
    SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);   //SETTING THE INTERNAL REFERENCE OF 3.3V FOR THE ADCA MODULE
    SetVREF(ADC_ADCC, ADC_INTERNAL, ADC_VREF3P3);   //SETTING THE INTERNAL REFERENCE OF 3.3V FOR THE ADCA MODULE

//      THE SOC FOR THE TRIGGERING IS PROVIDED BY THE SOCA OF THE EPM7(GPIO 12) OF THE DSP --- DONE

      asm("EALLOW");

//      WE ARE USING THE ROUND ROBIN THE SOC0 WILL BE CONFIGURED FIRST THEN THE SOC1................THEN SOC3

//      CONFIGURATION OF THE ADCA SOCS
      AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0x11;   //THE SOC0 OF THE ADCA REGISTER WILL BE TRIGGERED BY THE SOCA OF THE EPWM7
      AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0x2;      //WE ARE CONGIGURING THE CHSEL AS A2 WHERE THE CONVERSION WILL START
      AdcaRegs.ADCSOC0CTL.bit.ACQPS = 0x0B;     //KEEPING THE TIME FOR THE CAPACITOR TO CHARGE AS (11+1)*SYSCLK

      AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0x11;   //THE SOC1 OF THE ADCA REGISTER WILL BE TRIGGERED BY THE SOCA OF THE EPWM7
      AdcaRegs.ADCSOC1CTL.bit.CHSEL = 0x3;      //WE ARE CONGIGURING THE CHSEL AS A3 WHERE THE CONVERSION WILL START
      AdcaRegs.ADCSOC1CTL.bit.ACQPS = 0x0B;     //KEEPING THE TIME FOR THE CAPACITOR TO CHARGE AS (11+1)*SYSCLK

      AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 0x11;   //THE SOC2 OF THE ADCA REGISTER WILL BE TRIGGERED BY THE SOCA OF THE EPWM7
      AdcaRegs.ADCSOC2CTL.bit.CHSEL = 0x15;      //WE ARE CONGIGURING THE CHSEL AS A15 WHERE THE CONVERSION WILL START
      AdcaRegs.ADCSOC2CTL.bit.ACQPS = 0x0B;     //KEEPING THE TIME FOR THE CAPACITOR TO CHARGE AS (11+1)*SYSCLK

      AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = 0x11;   //THE SOC3 OF THE ADCA REGISTER WILL BE TRIGGERED BY THE SOCA OF THE EPWM7
      AdcaRegs.ADCSOC3CTL.bit.CHSEL = 0x1;      //WE ARE CONGIGURING THE CHSEL AS A1 WHERE THE CONVERSION WILL START
      AdcaRegs.ADCSOC3CTL.bit.ACQPS = 0x0B;     //KEEPING THE TIME FOR THE CAPACITOR TO CHARGE AS (11+1)*SYSCLK

//      CONFIGURATION OF THE ADCC SOCS
      AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 0x11;   //THE SOC0 OF THE ADCC REGISTER WILL BE TRIGGERED BY THE SOCA OF THE EPWM7
      AdccRegs.ADCSOC0CTL.bit.CHSEL = 0x3;      //WE ARE COFIGURING THE CHSEL AS C3 WHERE THE CONVERSION WILL START
      AdccRegs.ADCSOC0CTL.bit.ACQPS = 0x0B;     //KEEPING THE TIME FOR THE CAPACITOR TO CHARGE AS (11+1)*SYSCLK WHERE SYSCLK = ((1/12) * 1E-7)

      AdccRegs.ADCSOC1CTL.bit.TRIGSEL = 0x11;   //THE SOC1 OF THE ADCC REGISTER WILL BE TRIGGERED BY THE SOCA OF THE EPWM7
      AdccRegs.ADCSOC1CTL.bit.CHSEL = 0x6;      //WE ARE COFIGURING THE CHSEL AS C6 WHERE THE CONVERSION WILL START
      AdccRegs.ADCSOC1CTL.bit.ACQPS = 0x0B;     //KEEPING THE TIME FOR THE CAPACITOR TO CHARGE AS (11+1)*SYSCLK WHERE SYSCLK = ((1/12) * 1E-7)

      AdccRegs.ADCSOC2CTL.bit.TRIGSEL = 0x11;   //THE SOC2 OF THE ADCC REGISTER WILL BE TRIGGERED BY THE SOCA OF THE EPWM7
      AdccRegs.ADCSOC2CTL.bit.CHSEL = 0x0;      //WE ARE COFIGURING THE CHSEL AS C0 WHERE THE CONVERSION WILL START
      AdccRegs.ADCSOC2CTL.bit.ACQPS = 0x0B;     //KEEPING THE TIME FOR THE CAPACITOR TO CHARGE AS (11+1)*SYSCLK WHERE SYSCLK = ((1/12) * 1E-7)

      // ################################################################################################
      // --------------------------------   SOC Priority Selection   ------------------------------------
      // ################################################################################################

      //----- WE WANT TO CALL INTERRUPT AT THE END OF THE CONVERSION OF THE SOC3 WHICH IF OF THE LEAST PRIORITY AND LAST TO CONVERT -----

      AdcaRegs.ADCINTSEL1N2.bit.INT1CONT      = 1;     // WE WANT THE CONTINUOUS PULSES WHETHER THE FLAG IS CLEARED OR NOT
      AdcaRegs.ADCINTSEL1N2.bit.INT1E         = 1;     // WE WANT THE INTERRUPT AT OUT INT1 OF THE ADCA_ISR
      AdcaRegs.ADCINTSEL1N2.bit.INT1SEL       = 3;   // EOC3 WILL TRIGGER THE INTERRUPT AT THE END OF CONVERSION ITS SAMPLING

      AdccRegs.ADCINTSEL1N2.bit.INT1E         = 0;     // ADC C interrupt disable

// ################################################################################################
// ----------------------------------------   Power UP the ADCs --------------------------------
// ################################################################################################

    // POWERING UP THE ADCS FOR THE CONFIGURATION

    AdcaRegs.ADCCTL1.bit.ADCPWDNZ           = 1;          // Power up the ADC A
    AdccRegs.ADCCTL1.bit.ADCPWDNZ           = 1;          // Power up the ADC C

    //******** Waiting Period after Power-Up the ADCs : START *******

    DELAY_US(1000);                              // Wait 1 ms after power-up before using the ADC

    //******** Waiting Period after Power-Up the ADCs : END *******

      asm("EDIS");
}

//----------------END OF THE ADC CODE FOR THE PROJECT----------------



void initADC(void)
{

    asm(" EALLOW");                     // Enable EALLOW protected register access

// ################################################################################################
// --------------------------------   Resetting ADCs - A and C  -----------------------------------
// ################################################################################################

    //******* Resetting the ADCs A, C: START *******

    DevCfgRegs.SOFTPRES13.bit.ADC_A         = 1;    // ADC A is reset
    DevCfgRegs.SOFTPRES13.bit.ADC_A         = 0;    // ADC A is released from reset

    DevCfgRegs.SOFTPRES13.bit.ADC_C         = 1;    // ADC C is reset
    DevCfgRegs.SOFTPRES13.bit.ADC_C         = 0;    // ADC C is released from reset


    //******** Resetting the ADCs A, C: END ********

// ################################################################################################
// ----------------------------    Configure the ADC base register  -------------------------------
// ################################################################################################

    // ------ Configuring ADC A, ADC C Control-1 Register: START -------

    AdcaRegs.ADCCTL1.all                    = 0x0004;      // Main ADC A configuration
    AdccRegs.ADCCTL1.all                    = 0x0004;      // Main ADC C configuration

    // bit 15-14     00:     reserved
    // bit 13        0:      ADCBSY, ADC busy, read-only
    // bit 12        0:      reserved
    // bit 11-8      0's:    ADCBSYCHN, ADC busy channel, read-only
    // bit 7         0:      ADCPWDNZ, ADC power down, 0=powered down, 1=powered up
    // bit 6-3       0000:   reserved
    // bit 2         1:      INTPULSEPOS, INT pulse generation, 0=start of conversion, 1=end of conversion
    // bit 1-0       00:     reserved

    // ------ Configuring ADC A, ADC C Control-1 Register: END -------

    // ------ Configuring ADC A, ADC C Control-2 Register: START ------

    AdcaRegs.ADCCTL2.all                    = 0x0006;      // ADC A clock configuration (Set to 30MHz)
    AdccRegs.ADCCTL2.all                    = 0x0006;      // ADC C clock configuration (Set to 30MHz)

    // bit 15-8      0's:    reserved
    // bit 7         0:      reserved
    // bit 6         0:      reserved
    // bit 5-4       00:     reserved
    // bit 3-0       0110:   PRESCALE, ADC clock prescaler.  0110=CPUCLK/4 = 120MHz/4 = 30MHz

    // ------- Configuring ADC A, ADC C Control-2 Register: END -------

    // ------ Configuring ADC A, ADC C Burst Control Register (ADCBURSTCTL): START ------
    // ------ Since we are dealing with only one soc we need not care about the burst control or anything like that;

    AdcaRegs.ADCBURSTCTL.all                = 0x0000;
    AdccRegs.ADCBURSTCTL.all                = 0x0000;

    // bit 15        0:      BURSTEN, 0=burst mode disabled, 1=burst mode enabled
    // bit 14-12     000:    reserved
    // bit 11-8      0000:   BURSTSIZE, 0=1 SOC converted (don't care)
    // bit 7-6       00:     reserved
    // bit 5-0       000000: BURSTTRIGSEL, 00=software only (don't care)

    // ------- Configuring ADC A, ADC C Burst Control Register (ADCBURSTCTL): END -------


    asm(" EDIS");                               // Disable EALLOW protected register access

    // --------  Set Vref as Internal with 0 to 3.3V Range: START ----------

    SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);
    SetVREF(ADC_ADCC, ADC_INTERNAL, ADC_VREF3P3);

    // --------  Set Vref as Internal with 0 to 3.3V Range: END ----------
    // Pin 4 - ADC A6, CT signal for zero export control - GPIO228 (AGPIO)
    // Pin 5 - ADC A3, DC Link Voltage Sensing - GPIO 242 (AGPIO)
    // Pin 6 - ADC A2, Grid Voltage Sensing - GPIO 224 (AGPIO)
    // Pin 7 - ADC C7, PV Voltage Sensing - AIO 233
    // Pin 8 - ADC A11, PV Side Inductor Core Temperature - AIO 237
    // Pin 9 - ADC C2, PV Side Inductor Copper Temperature - AIO 244
    // Pin 10- ADC A1, Grid Current - AIO 232
    // Pin 11- ADC C15, PV Current - AIO 231
    // Pin 14- ADC C1, Grid Side Inductor Copper Temperature - AIO 238
    // Pin 15- ADC C3, Residual Current Sensing - AIO 245
    // Pin 16- ADC C11, Grid Side Inductor Core Temperature - AIO 241
    // Pin 19- ADC A4, Heat Sink Temperature - AIO 225
// ################################################################################################
// -------------------   SOC Configure for the 4 ADC Groups (A, B, C, D)   ------------------------
// ################################################################################################

    asm(" EALLOW");                     // Enable EALLOW protected register access

    //----- SOC (SOC0, SOC1, SOC2...) Configuration for ADC A: START -----
    //----- We are trying to configure the trigger and desired start of conversion channel----
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL         = 0x11;    // Trigger by ePWM7 SOC A
    AdcaRegs.ADCSOC0CTL.bit.CHSEL           = 0x2;    // Convert channel ADC A1: Grid Current
    AdcaRegs.ADCSOC0CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns

    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL         = 0x11;    // Trigger by ePWM4 SOC A
    AdcaRegs.ADCSOC1CTL.bit.CHSEL           = 0x3;    // Convert channel ADC A2: Grid Voltage
    AdcaRegs.ADCSOC1CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns
//
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL         = 0x11;    // Trigger by ePWM4 SOC A
    AdcaRegs.ADCSOC2CTL.bit.CHSEL           = 0x15;    // Convert channel ADC A3: DC Link Voltage
    AdcaRegs.ADCSOC2CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns
//
    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL         = 0x11;    // Trigger by ePWM4 SOC A
    AdcaRegs.ADCSOC3CTL.bit.CHSEL           = 0x1;    // Convert channel ADC A4: Heat Sink Temperature
    AdcaRegs.ADCSOC3CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns
//
//    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL         = 0x0B;    // Trigger by ePWM4 SOC A
//    AdcaRegs.ADCSOC4CTL.bit.CHSEL           = 0x06;    // Convert channel ADC A6: CT for ZEC
//    AdcaRegs.ADCSOC4CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns
//
//    AdcaRegs.ADCSOC5CTL.bit.TRIGSEL         = 0x0B;    // Trigger by ePWM4 SOC A
//    AdcaRegs.ADCSOC5CTL.bit.CHSEL           = 0x0B;    // Convert channel ADC A11: PV Inductor Core Temperature
//    AdcaRegs.ADCSOC5CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns

//----- SOC (SOC0, SOC1, SOC2...) Configuration for ADC A: END -----

//----- SOC (SOC0, SOC1, SOC2...) Configuration for ADC C: START -----

    AdccRegs.ADCSOC0CTL.bit.TRIGSEL         = 0x11;    // Trigger by ePWM4 SOC A
    AdccRegs.ADCSOC0CTL.bit.CHSEL           = 0x3;    // Convert channel ADC C15: PV Current
    AdccRegs.ADCSOC0CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns
//
    AdccRegs.ADCSOC1CTL.bit.TRIGSEL         = 0x11;    // Trigger by ePWM4 SOC A
    AdccRegs.ADCSOC1CTL.bit.CHSEL           = 0x6;    // Convert channel ADC C7: PV Voltage
    AdccRegs.ADCSOC1CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns
//
    AdccRegs.ADCSOC2CTL.bit.TRIGSEL         = 0x11;    // Trigger by ePWM4 SOC A
    AdccRegs.ADCSOC2CTL.bit.CHSEL           = 0x0;    // Convert channel ADC C1: Grid Inductor Copper Temperature
    AdccRegs.ADCSOC2CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns
//
//    AdccRegs.ADCSOC3CTL.bit.TRIGSEL         = 0x0B;    // Trigger by ePWM4 SOC A
//    AdccRegs.ADCSOC3CTL.bit.CHSEL           = 0x02;    // Convert channel ADC C2: PV Inductor copper temperature
//    AdccRegs.ADCSOC3CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns
//
//    AdccRegs.ADCSOC4CTL.bit.TRIGSEL         = 0x0B;    // Trigger by ePWM4 SOC A
//    AdccRegs.ADCSOC4CTL.bit.CHSEL           = 0x03;    // Convert channel ADC C3: Residual Current Sensing
//    AdccRegs.ADCSOC4CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns
//
//    AdccRegs.ADCSOC5CTL.bit.TRIGSEL         = 0x0B;    // Trigger by ePWM4 SOC A
//    AdccRegs.ADCSOC5CTL.bit.CHSEL           = 0x0B;    // Convert channel ADC C11: Grid Inductor Core Temperature
//    AdccRegs.ADCSOC5CTL.bit.ACQPS           = 0x0B;    // Acquisition window (12 SYSCLK Cycles) i.e., 100ns


//----- SOC (SOC0, SOC1, SOC2...) Configuration for ADC C: END -----


// ################################################################################################
// ----------------------------   Triggring the ADC Interrupts   ---------------------------------
// ################################################################################################

    //----- Triggering ADC Interrupts: START -----

//    AdcaRegs.ADCINTSOCSEL1.bit.SOC0         = 0;                // No ADCINT will trigger SOC0
//    AdcaRegs.ADCINTSOCSEL1.bit.SOC1         = 0;                // No ADCINT will trigger SOC1
//    AdcaRegs.ADCINTSOCSEL1.bit.SOC2         = 0;                // No ADCINT will trigger SOC2
//    AdcaRegs.ADCINTSOCSEL1.bit.SOC3         = 0;                // No ADCINT will trigger SOC3
//    AdcaRegs.ADCINTSOCSEL1.bit.SOC4         = 0;                // No ADCINT will trigger SOC4
//    AdcaRegs.ADCINTSOCSEL1.bit.SOC5         = 0;                // No ADCINT will trigger SOC5
//
//    AdccRegs.ADCINTSOCSEL1.bit.SOC0         = 0;                // No ADCINT will trigger SOC0
//    AdccRegs.ADCINTSOCSEL1.bit.SOC1         = 0;                // No ADCINT will trigger SOC1
//    AdccRegs.ADCINTSOCSEL1.bit.SOC2         = 0;                // No ADCINT will trigger SOC2
//    AdccRegs.ADCINTSOCSEL1.bit.SOC3         = 0;                // No ADCINT will trigger SOC3
//    AdccRegs.ADCINTSOCSEL1.bit.SOC4         = 0;                // No ADCINT will trigger SOC4
//    AdccRegs.ADCINTSOCSEL1.bit.SOC5         = 0;                // No ADCINT will trigger SOC5
//
    //----- Triggering ADC Interrupts: END -----

// ################################################################################################
// --------------------------------   SOC Priority Selection   ------------------------------------
// ################################################################################################

    //----- SOC Priority Selection for ADC SOC Channels: START -----
//
//    AdcaRegs.ADCSOCPRICTL.bit.SOCPRIORITY   = 0;  // SOC priority mode
//    AdccRegs.ADCSOCPRICTL.bit.SOCPRIORITY   = 0;  // SOC priority mode

    //----- SOC Priority Selection for ADC SOC Channels: END -----

// ################################################################################################
// ------------------------------   ADC Interrupt Configuration   ---------------------------------
// ################################################################################################

    //----- Configuring ADC A Interrupt-1 and disable ADC C interrupts  : START -----

     AdcaRegs.ADCINTSEL1N2.bit.INT1CONT      = 1;     // Interrupt pulses
     AdcaRegs.ADCINTSEL1N2.bit.INT1E         = 1;     // ADC A interrupt enable
     AdcaRegs.ADCINTSEL1N2.bit.INT1SEL       = 3;     // EOC5 triggers the interrupt

//
     AdccRegs.ADCINTSEL1N2.bit.INT1E         = 0;     // ADC C interrupt disable
//
//    //----- Configuring ADC A Interrupt-1 and disable ADC C interrupts  : END -----
//
//
//     //--- Allocating Comparator 1 to ADC A1 (grid current) ---
//     AnalogSubsysRegs.CMPHPMXSEL.bit.CMP1HPMXSEL = 4;
//     AnalogSubsysRegs.CMPLPMXSEL.bit.CMP1LPMXSEL = 4;
//
//     //--- Allocating Comparator 3 to ADC C15 (PV current) ---
//     AnalogSubsysRegs.CMPHPMXSEL.bit.CMP3HPMXSEL = 2;
//     AnalogSubsysRegs.CMPLPMXSEL.bit.CMP3LPMXSEL = 2;


     //******* Comparator Subsystem 1: Setting for hardware trip (grid current) : START ********

//     Cmpss1Regs.COMPCTL.bit.COMPHSOURCE      = 0;    // negative pin of high comparator is driven by internal DAC
//     Cmpss1Regs.COMPCTL.bit.COMPLSOURCE      = 0;    // negative pin of low comparator is driven by internal DAC
//
//     Cmpss1Regs.COMPCTL.bit.COMPHINV         = 0;    // output of comparator is not inverted
//     Cmpss1Regs.COMPCTL.bit.COMPLINV         = 1;    // output of low comparator is inverted
//
//     Cmpss1Regs.COMPCTL.bit.CTRIPHSEL        = 2;    // CTRIPH = Output of digital filter
//     Cmpss1Regs.COMPCTL.bit.CTRIPLSEL        = 2;    // CTRIPL = Output of digital filter
//
//     Cmpss1Regs.COMPCTL.bit.ASYNCHEN         = 0;    // don't care
//     Cmpss1Regs.COMPCTL.bit.ASYNCLEN         = 0;    // don't care
//
//     Cmpss1Regs.COMPHYSCTL.bit.COMPHYS       = 1;    // typical hysteresis set for comparator
//
//     Cmpss1Regs.COMPDACHCTL.bit.DACSOURCE    = 0;    // DACVALA = DACVALS
//     Cmpss1Regs.COMPDACHCTL.bit.SWLOADSEL    = 0;    // DACVALA updated every SYSCLK Cycle
//
//     Cmpss1Regs.DACHVALS.bit.DACVAL          = 2155;   // Trip voltage set at 1.7357V
//     Cmpss1Regs.DACLVALS.bit.DACVAL          = 1569;   // Trip voltage set at 1.2643V
//
//     Cmpss1Regs.CTRIPHFILCTL.bit.SAMPWIN     = 8;    // Sampling Window  = 9
//     Cmpss1Regs.CTRIPHFILCTL.bit.THRESH      = 5;    // At least 6 samples required for change in output
//     Cmpss1Regs.CTRIPHFILCTL.bit.FILINIT     = 1;    // initialize the FIFO
//
//     Cmpss1Regs.CTRIPHFILCLKCTL              = 5;    // samples to be taken at xx ns sampling time
//
//     Cmpss1Regs.CTRIPLFILCTL.bit.SAMPWIN     = 8;    // Sampling Window  = 9
//     Cmpss1Regs.CTRIPLFILCTL.bit.THRESH      = 5;    // At least 5 samples required for change in output
//     Cmpss1Regs.CTRIPLFILCTL.bit.FILINIT     = 1;    // initialize the FIFO
//
//     Cmpss1Regs.CTRIPLFILCLKCTL              = 5;    // samples to be taken at xx ns sampling time
//
//     Cmpss1Regs.COMPCTL.bit.COMPDACE         = 1;    // enable comparator 1

     // ******* Comparator Subsystem 1: Setting for hardware trip (Grid Current) : END ********

     // ******* Comparator Subsystem 3: Setting for hardware trip (PV Current) : START ********

//     CmpssLite3Regs.COMPCTL.bit.COMPHSOURCE  = 0;    // negative pin of high comparator is driven by internal DAC
//     CmpssLite3Regs.COMPCTL.bit.COMPLSOURCE  = 0;    // negative pin of low comparator is driven by internal DAC
//
//     CmpssLite3Regs.COMPCTL.bit.COMPHINV     = 0;    // output of comparator is not inverted
//     CmpssLite3Regs.COMPCTL.bit.COMPLINV     = 1;    // output of low comparator is inverted
//
//     CmpssLite3Regs.COMPCTL.bit.CTRIPHSEL        = 2;    // CTRIPH = Output of digital filter
//     CmpssLite3Regs.COMPCTL.bit.CTRIPLSEL        = 2;    // CTRIPL = Output of digital filter
//
//     CmpssLite3Regs.COMPCTL.bit.ASYNCHEN         = 0;    // don't care
//     CmpssLite3Regs.COMPCTL.bit.ASYNCLEN         = 0;    // don't care
//
//     CmpssLite3Regs.COMPHYSCTL.bit.COMPHYS       = 1;    // typical hysteresis set for comparator
//
//     CmpssLite3Regs.COMPDACHCTL.bit.SWLOADSEL     = 0;    // DACVALA updated every SYSCLK Cycle
//
//     CmpssLite3Regs.DACHVALS.bit.DACVAL          = 2155;   // Trip voltage set at 1.7357V
//     CmpssLite3Regs.DACLVALS.bit.DACVAL          = 1569;   // Trip voltage set at 1.2643V
//
//     CmpssLite3Regs.CTRIPHFILCTL.bit.SAMPWIN     = 8;    // Sampling Window  = 32
//     CmpssLite3Regs.CTRIPHFILCTL.bit.THRESH      = 5;    // At least 5 samples required for change in output
//     CmpssLite3Regs.CTRIPHFILCTL.bit.FILINIT     = 1;    // initialize the FIFO
//     CmpssLite3Regs.CTRIPHFILCLKCTL              = 5; // samples to be taken at xx ns sampling time
//
//     CmpssLite3Regs.CTRIPLFILCTL.bit.SAMPWIN     = 8;    // Sampling Window  = 9
//     CmpssLite3Regs.CTRIPLFILCTL.bit.THRESH      = 5;    // At least 5 samples required for change in output
//     CmpssLite3Regs.CTRIPLFILCTL.bit.FILINIT     = 1;    // initialize the FIFO
//
//     CmpssLite3Regs.CTRIPLFILCLKCTL              = 5; // samples to be taken at xx ns sampling time
//
//     CmpssLite3Regs.COMPCTL.bit.COMPDACE         = 1;    // enable comparator 3

     // ******* Comparator Subsystem 3: Setting for hardware trip (PV Current) : END ********

// ################################################################################################
// ----------------------------------------   Power UP the ADCs --------------------------------
// ################################################################################################

      //******** Powering Up ADCs : START *******

      AdcaRegs.ADCCTL1.bit.ADCPWDNZ           = 1;          // Power up the ADC A
      AdccRegs.ADCCTL1.bit.ADCPWDNZ           = 1;          // Power up the ADC C

      //******** Powering Up ADCs : END *******

      //******** Waiting Period after Power-Up the ADCs : START *******

      DELAY_US(1000);                              // Wait 1 ms after power-up before using the ADC

      //******** Waiting Period after Power-Up the ADCs : END *******

        asm(" EDIS");                               // Disable EALLOW protected register access

}

//
// End of File
//
