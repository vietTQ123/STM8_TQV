#include "lib_uart.h"

int new=1;
int old=1; 

uint8_t dataArray[] = {0x01, 0x02, 0x03, 0x04, 0x05};
uint16_t dataLength = sizeof(dataArray) / sizeof(dataArray[0]);

void assert_failed(uint8_t* file, uint32_t line){}

void delay(int t)
{
  int i, j;
  for (i = 0; i < t; i++)
  {
    for (j = 0; j < 400; j++){}
  }
}


int main( void )
{
  GPIO_DeInit(GPIOD);

  GPIO_Init(GPIOD, GPIO_PIN_1, GPIO_MODE_OUT_PP_LOW_SLOW);  // LED 1
  
  UART_Configuration(9600);
  
  while(1)
  {
//slave
    UART_Send_Array(dataArray, dataLength);

//master
//    if(flag_array_receive == 1)
//    {
//      flag_array_receive = 0;
//      if(strcmp(array_receive,dataArray) == 0)
//      {
//        GPIO_WriteLow(GPIOD, GPIO_PIN_1);
//        delay(1000);
//        GPIO_WriteHigh(GPIOD, GPIO_PIN_1);
//        delay(1000);
//      }
//    }
  }
}


INTERRUPT_HANDLER(UART1_RX_IRQHandler,18)
{
  UART_Interrupt_Receive_Array(dataLength);
}
