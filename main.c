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
        rxData = GetResponse();               
        if(*rxData != NULL)
        {
            blockingWait(1);
            strcpy(ReadStorage, rxData);
            SendString(ReadStorage);
            ReadyReceiveBuffer(); 
        }
    }
}