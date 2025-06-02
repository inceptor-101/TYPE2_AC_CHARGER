#include <GTSI_1Phase1MPPT.h>

void InitCpuTimer(Uint16 seconds){
    EALLOW;
//    I want to turn the led on and off after every 3 seconds.
    Uint32 PrdVal                   =       seconds*100000;
    CpuTimer0Regs.TCR.bit.TSS       =       1;                      //Stopping the timer
    CpuTimer0Regs.TCR.bit.TIF       =       1;                      //Clearing any previous flag that might generate the interrupt
    CpuTimer0Regs.TPRH.bit.TDDRH    =       ((1199 & (0xFF00)))>>8;
    CpuTimer0Regs.TPR.bit.TDDR      =       (1199 & (0xFF));        //Setting the prescaler to 1200 for 100kHZ clock of the cpu timer
    CpuTimer0Regs.PRD.all           =       PrdVal;                 //Cpu timer to be set after every 2 sec
    CpuTimer0Regs.TCR.bit.TIE       =       1;                      //Enabling the timer0 interrupt
    CpuTimer0Regs.TCR.bit.TSS       =       0;                      //Starting the timer
    EDIS;
}
