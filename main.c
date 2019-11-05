#include "mcc_generated_files/mcc.h"
#include "uart.h"
#include "string.h"
char* rxData;
void main(void)
{
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    INIT_SMART_LIGHT ();
    while (1)
    {
        if(ResponseIndex != 0)
        {
            blockingWait(2);
            rxData = GetResponse();
            SendString(rxData);
            ReadyReceiveBuffer(); 
        }
    }
}