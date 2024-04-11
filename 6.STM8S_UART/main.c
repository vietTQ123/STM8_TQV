#include <stm8s.h>
#include <string.h>
#include <stm8s_uart1.h>
#include <stm8s_gpio.h>
#include <stdio.h>
#include <stm8s_clk.h>

#define PUTCHAR_PROTOTYPE int putchar (int c)

PUTCHAR_PROTOTYPE
{
  UART1_SendData8(c);
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
  return (c);
}

static char arr[100] = "";
static char count_arr_receive = 0;
static uint8_t flag_arr_receive = 0;

void assert_failed(uint8_t* file, uint32_t line){}

void delay(int t)
{
  int i, j;
  for (i = 0; i < t; i++)
  {
    for (j = 0; j < 400; j++){}
  }
}

void UART_Configuration(uint32_t select)
{
//  CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, ENABLE);
//  UART1_DeInit();
//  UART1_Init((u32)9600, UART1_WORDLENGTH_8D,UART1_STOPBITS_1,UART1_PARITY_NO,UART1_SYNCMODE_CLOCK_DISABLE,UART1_MODE_TXRX_ENABLE);
//  UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE);
//  UART1_Cmd(ENABLE);
  
  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  GPIOD->DDR |=  (1 << 5);
  GPIOD->DDR &= ~(1 << 6);
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

void UART1_Printf_Char (char value) 
{
  UART1_SendData8(value);
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET); //wait for sending
}

void UART1_Printf_String (char *message) 
{
  while (*message)																							
  {
    UART1_SendData8((unsigned char) *message);									
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);	
    message++;                               
  }
}

void UART1_Printf_Int (int number) 
{
 char count = 0;
 char digit[7] = "";
 if(number==0)
 {
   UART1_SendData8('0');
   while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
 }
 if(number>0)
 {
  while (number != 0) 
  {
    digit[count] = number%10;
    count++;
    number = number/10;
  }
	 
  while (count !=0)  
  {
    UART1_SendData8(digit[count-1] + 0x30);
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);  
    count--; 
  }
 }
 if(number<0)
 {
   number=-number;
   while (number != 0) //split the int to char array 
  {
    digit[count] = number%10;
    count++;
    number = number/10;
  }
  UART1_SendData8('-');
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
  while (count !=0) //print char array in correct direction 
  {
    UART1_SendData8(digit[count-1] + 0x30);
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET); //wait for sending 
    count--;
  }
 }
}

void UART1_Printf_Long (long number) 
{
 char count = 0;
 char digit[12] = "";
 if(number==0)
 {
   UART1_SendData8('0');
   while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
 }
 if(number>0)
 {
  while (number != 0) 
  {
    digit[count] = number%10;
    count++;
    number = number/10;
  }
	 
  while (count !=0)  
  {
    UART1_SendData8(digit[count-1] + 0x30);
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);  
    count--; 
  }
 }
 if(number<0)
 {
   number=-number;
   while (number != 0) 
  {
    digit[count] = number%10;
    count++;
    number = number/10;
  }
  UART1_SendData8('-');
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
  while (count !=0) 
  {
    UART1_SendData8(digit[count-1] + 0x30);
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET); 
    count--;
  }
 }
}

void UART1_Printf_Float1 (float number)
{
 printf("%0.4f",number); 
}

void UART1_Printf_Double1 (double number)
{
 printf("%0.4f",number); 
}

char UART1_Read_Char()
{
	while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
	return (UART1_ReceiveData8());
}

void UART1_Printf_Float (float number)
{
  int count1 =0;
  int count2 =0;
  char arr1[10]="";
  char arr2[10]="";
  
  if(number==0.0)
 {
   UART1_SendData8('0');
   while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
 }
 
 if(number>0)
 {
    int x = (int)number;     // so trc dau phay
    float y = (float)number - x;     // so sau dau phay
    int z=100*y;
    
    while (x != 0) 
    {
      arr1[count1] = x%10;
      count1++;
      x = x/10;
    }
           
    while (count1 !=0)  
    {
      UART1_SendData8(arr1[count1-1] + 0x30);
      while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);  
      count1--; 
    }
    
    UART1_SendData8('.');
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
    
    while (z != 0) 
    {
      arr2[count2] = z%10;
      count2++;
      z = z/10;
    }
    
    while (count2 !=0)  
    {
      UART1_SendData8(arr2[count2-1] + 0x30);
      while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);  
      count2--; 
    }
 }
 
 if(number<0)
 {
    number=-number;
    int x = (int)number;     // so trc dau phay
    float y = (float)number - x;     // so sau dau phay
    int z=100*y;
    
    while (x != 0) 
    {
      arr1[count1] = x%10;
      count1++;
      x = x/10;
    }
       
    UART1_SendData8('-');
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
    
    while (count1 !=0)  
    {
      UART1_SendData8(arr1[count1-1] + 0x30);
      while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);  
      count1--; 
    }
    
    UART1_SendData8('.');
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
    
    while (z != 0) 
    {
      arr2[count2] = z%10;
      count2++;
      z = z/10;
    }
    
    while (count2 !=0)  
    {
      UART1_SendData8(arr2[count2-1] + 0x30);
      while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);  
      count2--; 
    }
 }
}



int main()
{
  GPIO_DeInit(GPIOD);
  GPIO_DeInit(GPIOB);
  GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST); // TX
  GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_IN_FL_NO_IT);      // RX
  GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_IN_FL_NO_IT);      // button  
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
  
  UART_Configuration(9600);
  
  
  while(1)
  {
    
//   UART1_SendData8('V');
//   delay(100);
    
   UART1_Printf_String("HELLO WORLD");
   UART1_SendData8('\n');
   delay(1000);
    
//    for( char i=65; i<=90;i++)
//    {
//      UART1_SendData8(i);
//      while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
//      UART1_SendData8(0x0a);
//      delay(100);
//    }
    
//   UART1_Printf_Int(a);
//   UART1_SendData8(0x0a);
//   delay(100);
    
//   UART1_Printf_Int(GPIO_ReadInputPin(GPIOA, GPIO_PIN_1));
//   UART1_SendData8(0x0a);
//   delay(100);
    
//  UART1_Printf_Long(a);
//  UART1_SendData8(0x0a);
//  delay(100);
    
//    if(UART1_Read_Char() == '0')
//    {
//      GPIO_WriteLow(GPIOB, GPIO_PIN_5);
//    }
//     if(UART1_Read_Char() == '1')
//    {
//      GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
//    }
    
    
//    if(flag_arr_receive == 1)
//    {
//      flag_arr_receive = 0;
//      if(strcmp(arr,"on") == 0)
//      {
//        GPIO_WriteLow(GPIOB, GPIO_PIN_5);
//      }
//      else if(strcmp(arr,"off") == 0)
//      {
//        GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
//      }
//    }
    
//    UART1_Printf_Float (10.56);
//    UART1_SendData8('\n');
//    delay(1000);
    
//    UART1_Printf_Double (2023.1235);
//    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
//    UART1_SendData8('\n');
//    delay(1000);
  }
}


INTERRUPT_HANDLER(UART1_RX_IRQHandler,18)
{
  char temp = UART1->DR;
  if(temp != '!')
  {
    arr[count_arr_receive] = temp;
    count_arr_receive++;
  }
  else
  {
    arr[count_arr_receive] = 0;
    count_arr_receive=0;
    flag_arr_receive = 1;
  }
}

//INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
// {
//  if (UART1_GetFlagStatus (UART1_FLAG_RXNE)!= RESET)
//  {
//    char data_re = UART1_ReceiveData8 ();
//    UART1_SendData8 (data_re);
//    while (UART1_GetFlagStatus (UART1_FLAG_TXE) ==RESET) ;
//  }
//  UART1_ClearFlag (UART1_FLAG_RXNE) ;
// }

