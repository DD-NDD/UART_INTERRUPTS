#include "mcc_generated_files/mcc.h"
#include "uart.h"
#include "string.h"
#include "stdlib.h"
// reset hardware FE 01 41 00 00 40    
// reset software FE 01 41 00 00 40                                      
// key 5 = true FE 02 27 07 10 01 33
// key 3 = true FE 02 27 07 04 01 27                                   
// SUC FE 01 67 07 00 61      
// Debug String LEVEL 100
char RESET[6] = {0xFE,0x01,0x41,0x00,0x00,0x40};
char KEY5[7] = {0xFE,0x02,0x27,0x07,0x10,0x01,0x33};
char KEY3[7] = {0xFE,0x02,0x27,0x07,0x04,0x01,0x27};
char LVL[5] = {0x4C, 0x45,0x56,0x45,0x4C};
char* rxData;
char Storage [responseBufferSize] = {0};
char Storage2 [9] = {0};
char Num_Char[3];
void main(void)
{
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    INIT_SMART_LIGHT ();
    ReadyReceiveBuffer();
    int test = 0;
    while (1)
    {
        if(ResponseIndex != 0)
        {
            blockingWait(2);
            rxData = GetResponse();
            //SendString(rxData);
            //ReadyReceiveBuffer();
            strcpy(Storage, rxData);
            //SML_SendString(Storage,64);
            char *s;
            s = strstr(Storage,"LEVEL");
            strcpy(Storage2, s);
            //SML_SendString(Storage2,9);
            Num_Char[0] = Storage2[6];
            Num_Char[1] = Storage2[7];
            Num_Char[2] = Storage2[8];
            int num = 0;
            //triac_level.level = atoi(Num_Char);
//            if(num == 100)
//            {
//                SML_SendString(Storage2,9);
//            }
            memset(Storage2,NULL,9);
            memset(Num_Char,NULL,3);
            ReadyReceiveBuffer(); 
        }
    }
}