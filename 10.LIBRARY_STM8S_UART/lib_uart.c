#include "lib_uart.h"

char array_receive[100] = "";
uint8_t count_array_receive = 0;
uint8_t flag_array_receive = 0;

/**
 * @brief Ham cau hinh uart
 * 
 * @param baudrate 
 */

void UART_Configuration(uint32_t baudrate)
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

/**
 * @brief Ham gui mang
 * 
 * @param array,length
 */

void UART_Send_Array (uint8_t* array, uint16_t length) 
{
    for (uint16_t i = 0; i < length; i++) 
    {
        UART1_SendData8(array[i]);
        while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
    }
}

/**
 * @brief Ham gui chuoi ky tu
 * 
 * @param *message
 */

void UART_Printf_String (char *message) 
{
  while (*message)																							
  {
    UART1_SendData8((unsigned char) *message);									
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);	
    message++;                               
  }
}

/**
 * @brief Ham ngat nhan chuoi ky tu
 * 
 */

void UART_Interrupt_Receive_String()
{
  char temp = UART1->DR;
  if(temp != '!')
  {
    array_receive[count_array_receive] = temp;
    count_array_receive++;
  }
  else
  {
    array_receive[count_array_receive] = 0;
    count_array_receive=0;
    flag_array_receive = 1;
  }
}

/**
 * @brief Ham ngat nhan mang
 * 
 */

void UART_Interrupt_Receive_Array(uint16_t length)
{
  char temp = UART1->DR;
  if(count_array_receive < length)
  {
    array_receive[count_array_receive] = temp;
    count_array_receive++;
  }
  else
  {
    count_array_receive=0;
    flag_array_receive = 1;
  }
}