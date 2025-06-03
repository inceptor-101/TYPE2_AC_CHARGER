
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

    //****** Configure ePWM1, ePWM4: START ******

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

     //********** EPWM1 Initialization: START USED FOR THE PILOT CONFIGURATION***************

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
     EPwm1Regs.TBCTL.bit.CTRMODE            = 0x2;                 // Count Up-Down Mode
     EPwm1Regs.TBPRD                        = 30000;               // 1 kHz switching frequency set

     EPwm1Regs.AQCTLA.all                   = 0x0000;              // Normal Sine-Triangle PWM
     EPwm1Regs.AQCTLA.bit.CAU               = 0x1;                 // Set output low on cmpa up
     EPwm1Regs.AQCTLA.bit.CAD               = 0x2;                 // Set output high on cmpa down

     // ********** EPWM1 Initialization: END **************


//===================================================================================
//  --------------------------Code for the EPWM2A---------------------------------
//===================================================================================

     EPwm2Regs.TBCTL.all = 0x0000;
     EPwm2Regs.TBCTL.bit.CTRMODE = 0x3;  //turning off the ctrmode now it has neither the up-down/up/down
     EPwm2Regs.TBCTL.bit.CLKDIV = 1;
//

//   ------CONFIGURING THE SHAPE AND TIME PERIOD OF THE RESULTING PWM WAVE------
     EPwm2Regs.TBCTL.bit.CTRMODE            = 0x2;
     EPwm2Regs.TBPRD                        = 1500;                // Sampling frequency is to be kept as 20kHz
     EPwm2Regs.AQCTLA.all                   = 0x000F;              // Normal Sine-Triangle PWM
//     EPwm2Regs.AQCTLA.bit.CAU               = 0x1;                 // Set output low on cmpa up
//     EPwm2Regs.AQCTLA.bit.CAD               = 0x2;                 // Set output high on cmpa down

//   FOR THE ENABLING OF THE SOC TRIGGERING OF THE A7/C3
     EPwm2Regs.ETSEL.bit.SOCAEN = 1;
     EPwm2Regs.ETSEL.bit.SOCASEL = 1;
     EPwm2Regs.ETPS.bit.SOCAPRD = 1;


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



