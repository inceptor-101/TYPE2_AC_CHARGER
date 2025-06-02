#include <GTSI_1Phase1MPPT.h>                        // Main include file

void SCIAWrite(char *string)
{
    while(*string)
    {
        while (SciaRegs.SCICTL2.bit.TXEMPTY == 0);
        SciaRegs.SCITXBUF.bit.TXDT = *string++ ;
        //DelayUs(2);
    }
}

void SCIA_init()
{
    SciaRegs.SCICCR.all =0x0007;    // 1 stop bit,  No loopback
                                    // No parity,8 char bits,
                                    // async mode, idle-line protocol
    SciaRegs.SCICTL1.all =0x0003;   // enable TX, RX, internal SCICLK,
                                    // Disable RX ERR, SLEEP, TXWAKE

    // SYSCLOCKOUT = 120MHz; LSPCLK = 1/4 = 30.0 MHz
    // BRR = (LSPCLK / (9600 x 8)) -1
    // BRR = 390  gives 9590 Baud
    SciaRegs.SCIHBAUD.bit.BAUD   = 390 >> 8;        // Highbyte
    SciaRegs.SCILBAUD.bit.BAUD   = 390 & 0x00FF;    // Lowbyte

    SciaRegs.SCIFFTX.all = 0xE000;                                  // bit 15 = 1 : relinquish from Reset
                                    // bit 14 = 1 : Enable FIFO
                                    // bit 6 = 0  : TXFFINT-Flag not cleared
                                    // bit 5 = 0  : disable TX FIFO match
                                    // bit 4-0    :  TX-ISR, if TX FIFO is 0(empty)
    SciaRegs.SCIFFCT.all = 0x0000;  // Set FIFO transfer delay to 0

    SciaRegs.SCIFFRX.all = 0xE061;  // Rx interrupt level = 1

    SciaRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset

    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;  // interrupt enable
    IER |= 0x0100;                      // interrupt enable
}


void SCIBWrite(char *string)
{
    while(*string)
    {
        while (ScibRegs.SCICTL2.bit.TXEMPTY == 0);
        ScibRegs.SCITXBUF.bit.TXDT = *string++ ;
        //DelayUs(2);
    }
}
void SCIB_init()
{
    ScibRegs.SCICCR.all =0x0007;    // 1 stop bit,  No loopback
                                    // No parity,8 char bits,
                                    // async mode, idle-line protocol
    ScibRegs.SCICTL1.all =0x0003;   // enable TX, RX, internal SCICLK,
                                    // Disable RX ERR, SLEEP, TXWAKE

    // SYSCLOCKOUT = 120MHz; LSPCLK = 1/4 = 30.0 MHz
    // BRR = (LSPCLK / (9600 x 8)) -1
    // BRR = 390  gives 9590 Baud
    ScibRegs.SCIHBAUD.bit.BAUD   = 390 >> 8;        // Highbyte
    ScibRegs.SCILBAUD.bit.BAUD   = 390 & 0x00FF;    // Lowbyte

    ScibRegs.SCIFFTX.all = 0xE000;                                  // bit 15 = 1 : relinquish from Reset
                                    // bit 14 = 1 : Enable FIFO
                                    // bit 6 = 0  : TXFFINT-Flag not cleared
                                    // bit 5 = 0  : disable TX FIFO match
                                    // bit 4-0    :  TX-ISR, if TX FIFO is 0(empty)
    ScibRegs.SCIFFCT.all = 0x0000;  // Set FIFO transfer delay to 0

    ScibRegs.SCIFFRX.all = 0xE061;  // Rx interrupt level = 1

    ScibRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset

    PieCtrlRegs.PIEIER9.bit.INTx3 = 1;  // interrupt enable
    IER |= 0x0100;                      // interrupt enable
}

void SCICWrite(char *string)
{
    while(*string)
    {
        while (ScicRegs.SCICTL2.bit.TXEMPTY == 0);
        ScicRegs.SCITXBUF.bit.TXDT = *string++ ;
        //DelayUs(2);
    }
}
void SCIC_init()
{
    ScicRegs.SCICCR.all =0x0007;    // 1 stop bit,  No loopback
                                    // No parity,8 char bits,
                                    // async mode, idle-line protocol
    ScicRegs.SCICTL1.all =0x0003;   // enable TX, RX, internal SCICLK,
                                    // Disable RX ERR, SLEEP, TXWAKE

    // SYSCLOCKOUT = 120MHz; LSPCLK = 1/4 = 30.0 MHz
    // BRR = (LSPCLK / (9600 x 8)) -1
    // BRR = 390  gives 9590 Baud
    ScicRegs.SCIHBAUD.bit.BAUD   = 390 >> 8;        // Highbyte
    ScicRegs.SCILBAUD.bit.BAUD   = 390 & 0x00FF;    // Lowbyte

    ScicRegs.SCIFFTX.all = 0xE000;                                  // bit 15 = 1 : relinquish from Reset
                                    // bit 14 = 1 : Enable FIFO
                                    // bit 6 = 0  : TXFFINT-Flag not cleared
                                    // bit 5 = 0  : disable TX FIFO match
                                    // bit 4-0    :  TX-ISR, if TX FIFO is 0(empty)
    ScicRegs.SCIFFCT.all = 0x0000;  // Set FIFO transfer delay to 0

    ScicRegs.SCIFFRX.all = 0xE061;  // Rx interrupt level = 1

    ScicRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset

    PieCtrlRegs.PIEIER8.bit.INTx5 = 1;  // interrupt enable
    IER |= 0x0080;                      // interrupt enable
}
