
/*
 * Author: Veer Karan Goyal
 * PWM Modules for Inverter Section : 1-2 (100 kHz/ HERIC Topology)
 * PWM Module for Boost Section: 3 (100 kHz switching frequency)
 */
/**********************************************************************

**********************************************************************/
#include <GTSI_1Phase1MPPT.h>                        // Main include file

/**************************************************************
* Function: InitEPwm()
*
* Description: Initializes the Enhanced PWM modules on the F28x7x
**********************************************************************/
void InitEPwm(void)
{


// ################################################################################################
// ----- Must disable the clock to the ePWM modules if you want all ePWM modules synchronized. ----
// -------------------- Before Configuring the EPwm modules, set TBCLKSYNC = 0  -------------------
// ----------- After Configuring the EPwm modules, set TBCLKSYNC = 1 for synchronization ----------
// ################################################################################################

    asm(" EALLOW");  // Enable EALLOW protected register access

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

    asm(" EDIS");    // Disable EALLOW protected register access


// ################################################################################################
// ------------------------ Configure ePWM1, ePWM2, ePWM3, and ePWM4 modules ----------------------
// ################################################################################################

    //****** Configure ePWM1, ePWM2, ePWM3, ePWM4: START ******

     asm(" EALLOW");   // Enable EALLOW protected register access
//     -------------THIS CODE IS NOTHING BUT RESETTING OF THE VARIOUS EPWMS--------------
     DevCfgRegs.SOFTPRES2.bit.EPWM1          = 1;     // ePWM1 is reset
     DevCfgRegs.SOFTPRES2.bit.EPWM1          = 0;     // ePWM1 is released from reset

     DevCfgRegs.SOFTPRES2.bit.EPWM2          = 1;     // ePWM2 is reset
     DevCfgRegs.SOFTPRES2.bit.EPWM2          = 0;     // ePWM2 is released from reset

     DevCfgRegs.SOFTPRES2.bit.EPWM3          = 1;     // ePWM3 is reset
     DevCfgRegs.SOFTPRES2.bit.EPWM3          = 0;     // ePWM3 is released from reset

     DevCfgRegs.SOFTPRES2.bit.EPWM4          = 1;     // ePWM4 is reset
     DevCfgRegs.SOFTPRES2.bit.EPWM4          = 0;     // ePWM4 is released from reset

     DevCfgRegs.SOFTPRES2.bit.EPWM6          = 1;
     DevCfgRegs.SOFTPRES2.bit.EPWM6          = 0;

     DevCfgRegs.SOFTPRES2.bit.EPWM7          = 1;
     DevCfgRegs.SOFTPRES2.bit.EPWM7          = 0;

     asm(" EDIS");     // Disable EALLOW protected register access

    //****** Configure ePWM1, ePWM2, ePM3, ePWM4, ePWM5, ePWM6 modules: END ******

 // ################################################################################################
 // --------------------- ePWM1 Module Initialization : HERIC TOPOLOGY ------------------
 // ################################################################################################

     //********** EPWM1 Initialization: START ***************

     EPwm1Regs.TBCTL.bit.CTRMODE            = 0x3;              // Disable the timer'
     EPwm1Regs.TBCTL.all                    = 0xC033;           // Configure timer control register

     // bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
     // bit 13        0:      PHSDIR, 0 = count down after sync event
     // bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
     // bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = EPWMCLK/1
     // bit 6         0:      SWFSYNC, 0 = no software sync produced
     // bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
     // bit 3         0:      PRDLD, 0 = reload PRD on counter=0
     // bit 2         0:      PHSEN, 0 = phase control disabled
     // bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled

     EPwm1Regs.TBCTL.bit.HSPCLKDIV          = 0;
     EPwm1Regs.TBCTL.bit.CLKDIV             = 1;                   // Clock to EPWM Module is 60 MHz
     EPwm1Regs.TBCTL.bit.CTRMODE            = 0x2;                   // Count Up-Down Mode
     EPwm1Regs.TBPRD                        = 30000;   // 1 kHz switching frequency set

     EPwm1Regs.AQCTLA.all                   = 0x000F;              // Normal Sine-Triangle PWM
     EPwm1Regs.TBCTR                        = 0x0;

     EPwm1Regs.ETSEL.bit.SOCAEN = 1;
     EPwm1Regs.ETSEL.bit.SOCASEL = 1;
     EPwm1Regs.ETPS.bit.SOCAPRD = 1;


//     asm(" EALLOW");                                      // Enable EALLOW protected register access
//     EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL    = 3;          // select TRIPIN4 as source for DCAH
//     EPwm1Regs.TZDCSEL.bit.DCAEVT1          = 2;          // define event as  : DCAH high
//     EPwm1Regs.DCACTL.bit.EVT1SRCSEL        = 0;          // DCAEVT1 is selected as source
//     EPwm1Regs.DCACTL.bit.EVT1FRCSYNCSEL    = 0;          // passed asynchronously
//     EPwm1Regs.DCACTL.bit.EVT1SOCE          = 0;          // SOC generation Disabled
//     EPwm1Regs.DCACTL.bit.EVT1SYNCE         = 0;          // Synch disabled
//     EPwm1Regs.DCACTL.bit.rsvd1             = 1;          // DCAEVT1 Latch enabled
//     EPwm1Regs.TZCTL2.bit.ETZE              = 1;          // Use data from TZCTL2 and TZCTLDCA
//     EPwm1Regs.TZCTL2.bit.TZAU              = 2;          // Force EPWMA to zero on UP count   if TZ1-TZ6 occurs
//     EPwm1Regs.TZCTL2.bit.TZAD              = 2;          // Force EPWMA to zero on down count if TZ1-TZ6 occurs
//     EPwm1Regs.TZCTL2.bit.TZBU              = 2;          // Force EPWMB to zero on UP count   if TZ1-TZ6 occurs
//     EPwm1Regs.TZCTL2.bit.TZBD              = 2;          // Force EPWMB to zero on down count if TZ1-TZ6 occurs
//     EPwm1Regs.TZCTLDCA.bit.DCAEVT1D        = 2;          // Force EPWMA to zero on down count if DCAEVT1 occurs
//     EPwm1Regs.TZCTLDCA.bit.DCAEVT1U        = 2;          // Force EPWMA to zero on up count   if DCAEVT1 occurs
//     EPwm1Regs.TZCTLDCB.bit.DCBEVT1D        = 2;          // Force EPWMB to zero on down count if DCAEVT1 occurs
//     EPwm1Regs.TZCTLDCB.bit.DCBEVT1U        = 2;          // Force EPWMB to zero on up count   if DCAEVT1 occurs
//     EPwm1Regs.TZSEL.bit.DCAEVT1            = 1;          // DCAEVT1 trip as One Shot
//     EPwm1Regs.TZSEL.bit.OSHT1              = 1;          // TZ1 as one Shot
//     EPwm1Regs.TZEINT.bit.OST               = 1;          // enable One Shot Trip interrupt
//     asm(" EDIS");                                        // Disable EALLOW protected register access

     // ********** EPWM1 Initialization: END ***************


// ################################################################################################
// --------------------- ePWM2 Module Initialization : HERIC TOPOLOGY ------------------
// ################################################################################################

     //********** EPWM2 Initialization: START ***************

//     EPwm2Regs.TBCTL.bit.CTRMODE            = 0x3;              // Disable the timer'
//     EPwm2Regs.TBCTL.all                    = 0xC033;           // Configure timer control register
//
//     // bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
//     // bit 13        0:      PHSDIR, 0 = count down after sync event
//     // bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
//     // bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = EPWMCLK/1
//     // bit 6         0:      SWFSYNC, 0 = no software sync produced
//     // bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
//     // bit 3         0:      PRDLD, 0 = reload PRD on counter=0
//     // bit 2         0:      PHSEN, 0 = phase control disabled
//     // bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)
//
//     EPwm2Regs.TBCTL.bit.HSPCLKDIV          = 0;
//     EPwm2Regs.TBCTL.bit.CLKDIV             = 1;                   // Clock to EPWM Module is 60 MHz
//
//     EPwm2Regs.TBCTL.bit.CTRMODE            = 2;                   // Count Up-Down Mode
//
//     EPwm2Regs.TBPRD                        = PWM_PERIOD_HERIC;   // 100 kHz switching frequency set
//
//     EPwm2Regs.CMPA.bit.CMPA                = 0;                   // Set PWM duty cycle to 0 initially
//
//     EPwm2Regs.CMPCTL.all                   = 0x0000;              // Shadowing of compare registers set to default
//
//     EPwm2Regs.AQCTLA.all                   = 0x000F;              // Normal Sine-Triangle PWM


     asm(" EALLOW");                                      // Enable EALLOW protected register access
//     EPwm2Regs.DCTRIPSEL.bit.DCAHCOMPSEL    = 3;          // select TRIPIN4 as source for DCAH
//     EPwm2Regs.TZDCSEL.bit.DCAEVT1          = 2;          // define event as  : DCAH high
//     EPwm2Regs.DCACTL.bit.EVT1SRCSEL        = 0;          // DCAEVT1 is selected as source
//     EPwm2Regs.DCACTL.bit.EVT1FRCSYNCSEL    = 0;          // passed asynchronously
//     EPwm2Regs.DCACTL.bit.EVT1SOCE          = 0;          // SOC generation Disabled
//     EPwm2Regs.DCACTL.bit.EVT1SYNCE         = 0;          // Synch disabled
//     EPwm2Regs.DCACTL.bit.rsvd1             = 1;          // DCAEVT1 Latch enabled
//     EPwm2Regs.TZCTL2.bit.ETZE              = 1;          // Use data from TZCTL2 and TZCTLDCA
//     EPwm2Regs.TZCTL2.bit.TZAU              = 2;          // Force EPWMA to zero on UP count   if TZ1-TZ6 occurs
//     EPwm2Regs.TZCTL2.bit.TZAD              = 2;          // Force EPWMA to zero on down count if TZ1-TZ6 occurs
//     EPwm2Regs.TZCTL2.bit.TZBU              = 2;          // Force EPWMB to zero on UP count   if TZ1-TZ6 occurs
//     EPwm2Regs.TZCTL2.bit.TZBD              = 2;          // Force EPWMB to zero on down count if TZ1-TZ6 occurs
//     EPwm2Regs.TZCTLDCA.bit.DCAEVT1D        = 2;          // Force EPWMA to zero on down count if DCAEVT1 occurs
//     EPwm2Regs.TZCTLDCA.bit.DCAEVT1U        = 2;          // Force EPWMA to zero on up count   if DCAEVT1 occurs
//     EPwm2Regs.TZCTLDCB.bit.DCBEVT1D        = 2;          // Force EPWMB to zero on down count if DCAEVT1 occurs
//     EPwm2Regs.TZCTLDCB.bit.DCBEVT1U        = 2;          // Force EPWMB to zero on up count   if DCAEVT1 occurs
//     EPwm2Regs.TZSEL.bit.DCAEVT1            = 1;          // DCAEVT1 trip as One Shot
//     EPwm2Regs.TZSEL.bit.OSHT1              = 1;          // TZ1 as one Shot
//     EPwm2Regs.TZEINT.bit.OST               = 1;          // enable One Shot Trip interrupt
//     asm(" EDIS");                                        // Disable EALLOW protected register access
      //********** EPWM2 Initialization: END ***************


     // ################################################################################################
     // --------------------- ePWM3 Module Initialization : BOOST TOPOLOGY ------------------
     // ################################################################################################

          //********** EPWM3 Initialization: START ***************

//          EPwm3Regs.TBCTL.bit.CTRMODE            = 0x3;              // Disable the timer'
//          EPwm3Regs.TBCTL.all                    = 0xC033;           // Configure timer control register
//
//          // bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
//          // bit 13        0:      PHSDIR, 0 = count down after sync event
//          // bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
//          // bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = EPWMCLK/1
//          // bit 6         0:      SWFSYNC, 0 = no software sync produced
//          // bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
//          // bit 3         0:      PRDLD, 0 = reload PRD on counter=0
//          // bit 2         0:      PHSEN, 0 = phase control disabled
//          // bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)
//
//          EPwm3Regs.TBCTL.bit.HSPCLKDIV          = 0;
//          EPwm3Regs.TBCTL.bit.CLKDIV             = 1;                   // Clock to EPWM Module is 60 MHz
//
//          EPwm3Regs.TBCTL.bit.CTRMODE            = 2;                   // Count Up-Down Mode
//
//          EPwm3Regs.TBPRD                        = PWM_PERIOD_BOOST;   // 100 kHz switching frequency set
//
//          EPwm3Regs.CMPA.bit.CMPA                = 0;                   // Set PWM duty cycle to 0 initially
//
//          EPwm3Regs.CMPCTL.all                   = 0x0000;              // Shadowing of compare registers set to default
//
//          EPwm3Regs.AQCTLA.all                   = 0x00FF;              // Normal Sine-Triangle PWM
//
//          asm(" EALLOW");                                      // Enable EALLOW protected register access
//          EPwm3Regs.DCTRIPSEL.bit.DCAHCOMPSEL    = 3;          // select TRIPIN4 as source for DCAH
//          EPwm3Regs.TZDCSEL.bit.DCAEVT1          = 2;          // define event as  : DCAH high
//          EPwm3Regs.DCACTL.bit.EVT1SRCSEL        = 0;          // DCAEVT1 is selected as source
//          EPwm3Regs.DCACTL.bit.EVT1FRCSYNCSEL    = 1;          // passed asynchronously
//          EPwm3Regs.DCACTL.bit.EVT1SOCE          = 0;          // SOC generation Disabled
//          EPwm3Regs.DCACTL.bit.EVT1SYNCE         = 0;          // Synch disabled
//          EPwm3Regs.DCACTL.bit.rsvd1             = 1;          // DCAEVT1 Latch enabled
//          EPwm3Regs.TZCTL2.bit.ETZE              = 1;          // Use data from TZCTL2 and TZCTLDCA
//          EPwm3Regs.TZCTL2.bit.TZAU              = 2;          // Force EPWMA to zero on UP count   if TZ1-TZ6 occurs
//          EPwm3Regs.TZCTL2.bit.TZAD              = 2;          // Force EPWMA to zero on down count if TZ1-TZ6 occurs
////          EPwm3Regs.TZCTL2.bit.TZBU              = 2;          // Force EPWMB to zero on UP count   if TZ1-TZ6 occurs
////          EPwm3Regs.TZCTL2.bit.TZBD              = 2;          // Force EPWMB to zero on down count if TZ1-TZ6 occurs
//          EPwm3Regs.TZCTLDCA.bit.DCAEVT1D        = 2;          // Force EPWMA to zero on down count if DCAEVT1 occurs
//          EPwm3Regs.TZCTLDCA.bit.DCAEVT1U        = 2;          // Force EPWMA to zero on up count   if DCAEVT1 occurs
////          EPwm3Regs.TZCTLDCB.bit.DCBEVT1D        = 2;          // Force EPWMB to zero on down count if DCAEVT1 occurs
////          EPwm3Regs.TZCTLDCB.bit.DCBEVT1U        = 2;          // Force EPWMB to zero on up count   if DCAEVT1 occurs
//          EPwm3Regs.TZSEL.bit.DCAEVT1            = 1;          // DCAEVT1 trip as One Shot
//          EPwm3Regs.TZSEL.bit.OSHT1              = 1;          // TZ1 as one Shot
//          EPwm3Regs.TZEINT.bit.OST               = 1;          // enable One Shot Trip interrupt
//          asm(" EDIS");                                        // Disable EALLOW protected register access
           //********** EPWM3 Initialization: END ***************


          // ################################################################################################
          // --------------------- ePWM4 Module Initialization : BOOST TOPOLOGY ------------------
          // ################################################################################################

               //********** EPWM4 Initialization: START ***************

               EPwm4Regs.TBCTL.bit.CTRMODE            = 0x3;              // Disable the timer'
               EPwm4Regs.TBCTL.all                    = 0xC033;           // Configure timer control register
//
//               // bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
//               // bit 13        0:      PHSDIR, 0 = count down after sync event
//               // bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
//               // bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = EPWMCLK/1
//               // bit 6         0:      SWFSYNC, 0 = no software sync produced
//               // bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
//               // bit 3         0:      PRDLD, 0 = reload PRD on counter=0
//               // bit 2         0:      PHSEN, 0 = phase control disabled
//               // bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)
//
               EPwm4Regs.TBCTL.bit.HSPCLKDIV          = 0;
               EPwm4Regs.TBCTL.bit.CLKDIV             = 1;                   // Clock to EPWM Module is 60 MHz

               EPwm4Regs.TBCTL.bit.CTRMODE            = 2;                   // Count Up-Down Mode

               EPwm4Regs.TBPRD                        = PWM_FOR_ADC_SAMPLING;   // 100 kHz switching frequency set

               EPwm4Regs.CMPA.bit.CMPA                = 0;                   // Set PWM duty cycle to 0 initially

               EPwm4Regs.CMPCTL.all                   = 0x0000;              // Shadowing of compare registers set to default

               EPwm4Regs.AQCTLA.all                   = 0x000F;              // Normal Sine-Triangle PWM

               EPwm4Regs.ETSEL.bit.SOCAEN             = 1;                   // Enable SOCA
               EPwm4Regs.ETSEL.bit.SOCASEL            = 1;                   // SOCA on CTR = 0

               EPwm4Regs.ETPS.bit.SOCAPRD             = 1;                   // sampling frequency = switching frequency: 12.5 kHz
//                //********** EPWM4 Initialization: END ***************
//// ################################################################################################
//// ------------------------------- Phase Synchronization for EPWM Pins ---------------------------
//// ################################################################################################
//
//               EPwm4Regs.EPWMSYNCOUTEN.bit.ZEROEN    = 1;      //  generate a synchout if CTR = 0 for EPWM4
//               EPwm4Regs.TBCTL2.bit.OSHTSYNCMODE     = 0;      //  OneShot sync mode disabled
//
//               This code is used for the purpose of synchronising the epwm4 with epwm1, 2 and 3
//               EPwm1Regs.EPWMSYNCINSEL.bit.SEL       = 4;      // EWPM4SYNCHOUT = EPWM1SYNCHIN
//               EPwm1Regs.TBCTL.bit.PHSEN             = 1;      // enable phase shift for ePWM1
//               EPwm1Regs.TBCTL.bit.PHSDIR            = 1;      // count down/up after synchronization
//               EPwm1Regs.TBPHS.bit.TBPHS             = 0;      //  phase always same as EPWM 4
//
//               EPwm2Regs.EPWMSYNCINSEL.bit.SEL       = 4;      // EWPM4SYNCHOUT = EPWM2SYNCHIN
//               EPwm2Regs.TBCTL.bit.PHSEN             = 1;      // enable phase shift for ePWM2
//               EPwm2Regs.TBCTL.bit.PHSDIR            = 1;      // count down/up after synchronization
//               EPwm2Regs.TBPHS.bit.TBPHS             = 0;      //  phase always same as EPWM 4
//
//               EPwm3Regs.EPWMSYNCINSEL.bit.SEL       = 4;      // EWPM4SYNCHOUT = EPWM3SYNCHIN
//               EPwm3Regs.TBCTL.bit.PHSEN             = 1;      // enable phase shift for ePWM3
//               EPwm3Regs.TBCTL.bit.PHSDIR            = 1;      // count down/up after synchronization
//               EPwm3Regs.TBPHS.bit.TBPHS             = 0;      //  phase always same as EPWM 4

//===================================================================================
//  --------------------------Code for the EPWM6A---------------------------------
//===================================================================================

//               EPwm6Regs.TBCTL.all= 0x0000;
//               EPwm6Regs.TBCTL.bit.CTRMODE = 0x3;
//               EPwm6Regs.TBCTL.bit.CLKDIV = 1;
//               EPwm6Regs.TBCTL.bit.PHSEN = 0;
//
////               GOIND TOWARD MAIN CONFIGURATION
//               EPwm6Regs.TBCTL.bit.CTRMODE = 0x2;
//               EPwm6Regs.TBPRD = 5000;
//               EPwm6Regs.CMPA.bit.CMPA = 2500;
//               EPwm6Regs.AQCTLA.bit.ZRO = 2;
//               EPwm6Regs.AQCTLA.bit.CAU = 1;

//               ENABLING THE SYNC OUT PULSE
//               EPWMSYNCOUTEN.bit.ZEROEN = 1;

//===================================================================================
//  --------------------------Code for the EPWM7A---------------------------------
//===================================================================================
               EPwm7Regs.TBCTL.all = 0x0000;
               EPwm7Regs.TBCTL.bit.CTRMODE = 0x3;  //turning off the ctrmode now it has neither the up-down/up/down
               EPwm7Regs.TBCTL.bit.CLKDIV = 1;
//

//               ------CONFIGURING THE SHAPE AND TIME PERIOD OF THE RESULTING PWM WAVE------
               EPwm7Regs.TBCTL.bit.CTRMODE = 0x2;
               EPwm7Regs.TBPRD = 300;
               EPwm7Regs.CMPA.bit.CMPA = 300;
               EPwm7Regs.AQCTLA.bit.ZRO = 2;
               EPwm7Regs.AQCTLA.bit.CAU = 1;

//               FOR THE ENABLING OF THE SOC TRIGGERING OF THE A7/C3
               EPwm7Regs.ETSEL.bit.SOCAEN = 1;
               EPwm7Regs.ETSEL.bit.SOCASEL = 1;
               EPwm7Regs.ETPS.bit.SOCAPRD = 1;

//===================================================================================
//  --------------------------Code for the EPWM5A---------------------------------
//===================================================================================
              EPwm5Regs.TBCTL.all = 0x0000;
              EPwm5Regs.TBCTL.bit.CTRMODE = 0x3;  //turning off the ctrmode now it has neither the up-down/up/down
              EPwm5Regs.TBCTL.bit.CLKDIV = 1;
              EPwm5Regs.TBCTL.bit.HSPCLKDIV = 5;

//               ------CONFIGURING THE SHAPE AND TIME PERIOD OF THE RESULTING PWM WAVE------
              EPwm5Regs.TBCTL.bit.CTRMODE = 0x2;
              EPwm5Regs.TBPRD = 30000;
              EPwm5Regs.CMPA.bit.CMPA = 3000;
              EPwm5Regs.AQCTLA.all = 0x000F;
//              EPwm5Regs.AQCTLA.bit.CAU = 1;

//               FOR THE ENABLING OF THE SOC TRIGGERING OF THE A7/C3
              EPwm5Regs.ETSEL.bit.SOCAEN = 1;
              EPwm5Regs.ETSEL.bit.SOCASEL = 1;
              EPwm5Regs.ETPS.bit.SOCAPRD = 1;

// ################################################################################################
// -------------------- EPWM XBAR Settings for Over Current Hardware Trip I am going the update the trip settings here ------------------------
// ################################################################################################

//       // ********** EPWM XBAR Settings for Grid AC Current: START ***************
//              asm(" EALLOW");                              // Enable EALLOW protected register access
              EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX0         = 1;  // MUX0 enabled
//              EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX1         = 1;  // MUX1 enabled
//
//              EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX0       = 0; // CMPSS1CTRIPH selected
//              EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX1       = 0; // CMPSS1CTRIPL selected
//
//              // ********** EPWM XBAR Settings for PV Current: START ***************
//
//              EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX4         = 1;  // MUX4 enabled
//              //EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX5         = 1;  // MUX5 enabled
//
//              EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX4       = 0; // CMPSS3CTRIPH selected
//              //EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX5       = 0; // CMPSS3CTRIPL selected
//
//
//              EPwmXbarRegs.TRIPOUTINV.bit.TRIP4       = 0; // drives active high output
//              asm(" EDIS");                                // Disable EALLOW protected register access

// ################################################################################################
// --------------------------------------- Interrupt Settings ------------------------------------
// ################################################################################################

//              asm(" EALLOW");                              // Enable EALLOW protected register access
//              PieCtrlRegs.PIEIER2.bit.INTx1=1;             // Enable Trip interrupt from EPwm1 (Trip ISR)
//              IER |= 0x0002;
//
//              asm(" EDIS");

// ################################################################################################
//---------------- Enable the clocks to the ePWM module.
//---------------- Note: this should be done after all ePWM modules are configured
//---------------- to ensure synchronization between the ePWM modules.
// ################################################################################################

       //********** Enable TBCLK to ePWM Modules : START *************

       asm(" EALLOW");  // Enable EALLOW protected register access

       CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // TBCLK to ePWM modules enabled

       asm(" EDIS");    // Disable EALLOW protected register access

       //********** Enable TBCLK to ePWM Modules : END *************

} // end InitEPwm()

//--- end of file -----------------------------------------------------



