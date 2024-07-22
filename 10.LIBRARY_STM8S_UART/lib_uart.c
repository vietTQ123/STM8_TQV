#include "lib_uart.h"

char arr_receive[100] = "";
uint8_t count_arr_receive = 0;
uint8_t flag_arr_receive = 0;

void UART_Configuration(uint32_t select)
{ 
  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  
  GPIOD->DDR |=  (1 << 5); // TX
  GPIOD->DDR &= ~(1 << 6); // RX
  
  // baudrate 16MHZ / 57600 = 277 = 0x115
  // baudrate 16MHZ / 9600 = 1666 = 0x682
  
  switch (select)
  {
    case 9600:
      UART1->BRR1 = 0x68;
      UART1->BRR2 = 0x02;
      break;
    case 57600:
      UART1->BRR1 = 0x11;
      UART1->BRR2 = 0x05;
      break;
      break;
  }
  
  UART1->CR1  = (0 << 5);
  UART1->CR2  = (1 << 2) | (1 << 3) | (1 << 5);
  
  enableInterrupts(); 
}

void UART_Send_Array(uint8_t* array, uint16_t length) 
{
    for (uint16_t i = 0; i < length; i++) 
    {
        UART1_SendData8(array[i]);
        while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
    }
}

INTERRUPT_HANDLER(UART1_RX_IRQHandler,18)
{
  char temp = UART1->DR;
  if(temp != '!')
  {
    arr_receive[count_arr_receive] = temp;
    count_arr_receive++;
  }
  else
  {
    arr_receive[count_arr_receive] = 0;
    count_arr_receive=0;
    flag_arr_receive = 1;
  }
}