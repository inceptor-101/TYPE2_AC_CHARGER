#include <GTSI_1Phase1MPPT.h>                        // Main include file

void Delay_ms(Uint16 val)
{
    Uint16 idelay;
    Uint16 factor;
    factor = val;
    for (idelay = 0; idelay < factor; idelay++)
    {
        DELAY_US(1000);
    }

}
