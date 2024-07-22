#include "lib_uart.h"

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
  uint8_t dataArray[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  uint16_t dataLength = sizeof(dataArray) / sizeof(dataArray[0]);
  
  UART_Configuration(9600);
  
  while(1)
  {
    //slave
    UART_Send_Array(dataArray, dataLength);
    
    //master
    if(flag_arr_receive == 1)
    {
      flag_arr_receive = 0;
      if(strcmp(arr_receive,dataArray) == 0)
      {
        GPIO_WriteLow(GPIOD, GPIO_PIN_1);
        delay(500);
        GPIO_WriteHigh(GPIOD, GPIO_PIN_1);
        delay(500);
      }
    }
  }
}
