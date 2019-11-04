#include "uart.h"  
#include <string.h>
#include "mcc_generated_files/mcc.h"
const uart_functions_t uart[] = {   
    {EUSART_Read, EUSART_Write, EUSART_is_tx_ready, EUSART_is_rx_ready, EUSART_SetTxInterruptHandler, EUSART_Receive_ISR, EUSART_SetRxInterruptHandler, EUSART_is_tx_done, EUSART_Transmit_ISR, EUSART_Initialize }
};
void SendString(const char* command)
{
    while (*command != '\0')
        uart[SML].Write(*command++);
    //uart[SML].Write('\r');
    uart[SML].Write('\n');
}
//*********************************************************
//          Accessible Example Functions
//*********************************************************
void INIT_SMART_LIGHT (void)                           // Call After System Init; Above while(1) Loop in Main.c
{
//    char* exampleRead;
    uart[SML].SetRxISR(ReceivedMessage); 
//    blockingWait(2);
//    blockingWait(400);                          // Wait for Module Information Response             
//    exampleRead = GetResponse();                // Read Response
//    strcpy(ReadStorage, exampleRead);            // Store for use/reference
//    ReadyReceiveBuffer();                       // Prepare for next message
//    SendString("SYS FACTORY RESET");               // Send "sys" Command: "factoryRESET"  
//    SendString("SMART LIGHT INIT");
//    blockingWait(1000);                          // Wait
//    exampleRead = GetResponse();                // Read Version String from Buffer
//    strcpy(ReadStorage, exampleRead);            // Store for use/reference
//    SendString(ReadStorage);
}
void ReceivedMessage(void)       // Call in ISR EUSART RX after EUSART_Receive_ISR() 
{
    uart[SML].RxDefaultISR();
    uint8_t readByte = uart[SML].Read();
    if ( (readByte != '\0') && (ResponseIndex < responseBufferSize) )
        ResponseBuffer[ResponseIndex++] = readByte;
}
//*********************************************************
//          Local Used Example Functions
//*********************************************************
void ReadyReceiveBuffer (void)
{
    ResponseIndex = 0;
    for (uint8_t position = 0; position < responseBufferSize; position++)
        ResponseBuffer[position] = 0;
}
char* GetResponse(void)
{
    return ResponseBuffer;
}
void blockingWait (uint16_t limit)
{
    for (uint16_t counter = 0; counter < limit; counter++)
		__delay_ms(15);
}