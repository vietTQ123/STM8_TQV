#include <lib_uart.h>

//uint16_t length;
int new=1;
int old=1; 

uint8_t dataArray[] = {0xAA,0x55,0x00,0x01,0x00,0x05,0x01,0x12,0x34};
uint8_t dataArray2[] = {0xAA,0x55,0x00,0x01,0x00,0x09,0x01,0x12,0x34,0x05,0x01,0x12,0x34};
uint8_t test[] = {0x34,0x55,0x00,0x01,0x00,0x09,0x01,0x12,0x34,0x05,0x01,0x12};
uint16_t dataLength = 0;
//uint16_t dataLength = sizeof(dataArray) / sizeof(dataArray[0]);

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
  GPIO_DeInit(GPIOB);

  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);  // LED 1
  
  UART_Configuration(9600);
  
  
  
  while(1)
  {
//master
        
    UART_Time_Out();
        
    if(flag_array_receive == END_RECEIVE)
    {
      flag_array_receive = WAIT_RECEIVE;
      UART_Send_Array(array_receive, ( 4 + Convert_From_Bytes_To_Uint16(array_receive[4], array_receive[5])));
      
    }
    
    delay(1);
  }
}