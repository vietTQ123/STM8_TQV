#include <stm8s.h>
#include <stm8s_adc1.h>
#include <stm8s_gpio.h>
#include <stm8s_uart1.h>
#include <stm8s_clk.h>
#include <stdio.h>
#include <math.h>

float t;
float Vo;
float R1 = 10000;
float logR2, R2, T, temp;
//const double A =  //1.009249522e-03;                    0.001129148;
//const double B =  //2.378405444e-04;                    0.000234125;
//const double C =  //2.019202697e-07;                    0.0000000876741; 

const double A =0.001129148;
const double B =0.000234125;
const double C =0.0000000876741;

#define PUTCHAR_PROTOTYPE int putchar (int c)

PUTCHAR_PROTOTYPE
{
  UART1_SendData8(c);
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);

  return (c);
}

void assert_failed(uint8_t* file, uint32_t line){}

static uint16_t analogRead(const uint8_t channel)
{
  uint16_t val=0;
  ADC1 -> CSR =((0X0F)&channel);
  ADC1 -> CR2 =(1 << 3);
  ADC1 -> CR1 =(1 << 0);
  ADC1 -> CR1 =(1 << 0);
  while(((ADC1 -> CSR) & (1<<7))==0);
  val |= (unsigned int ) ADC1 -> DRL;
  val |= (unsigned int ) ADC1 -> DRH << 8;
  ADC1 -> CR1 &= ~ (1<<10);
  val &= 0x03ff;
  return (val);
}

//uint16_t ADC_Read(uint8_t channel)
//{
//  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,channel,ADC1_PRESSEL_FCPU_D2,ADC1_EXTTRIG_TIM,DISABLE,ADC1_ALIGN_RIGHT,channel,DISABLE);
//     
//  ADC1_Cmd(ENABLE);
//  
//  ADC1_StartConversion();
//	
//  while (RESET == ADC1_GetFlagStatus(ADC1_FLAG_EOC)){}
//  
//  ADC1_ClearFlag(ADC1_FLAG_EOC);
//
//  uint16_t result = ADC1_GetConversionValue();
//  ADC1_DeInit();
//  return result;
//}

void UART_Configuration(uint32_t select)
{
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

void delay(int t)
{
  int i, j;
  for (i = 0; i < t; i++)
  {
    for (j = 0; j < 400; j++){}
  }
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



int main( void )
{
  UART_Configuration(9600);
  
  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_FL_NO_IT);
   
  while (1)
  {
//    ADC1_StartConversion();
//    while(ADC1_GetFlagStatus(ADC1_FLAG_EOC) == SET);
//    Vo = ADC_Read(ADC1_CHANNEL_2);
//    R2 = R1 * (1024 / Vo - 1.0);
//    logR2 = log(R2);
//    T = (1 / (A + (B * log(R2)) + (C * pow((log(R2)),3))));
//    t = T - 273;
//    UART1_Printf_Float (t);
//    UART1_SendData8(0x0a);
//    delay(2000);
    ADC1_StartConversion();
    while(ADC1_GetFlagStatus(ADC1_FLAG_EOC) == SET);
    float V = analogRead(ADC1_CHANNEL_3);
    UART1_Printf_Float (V);
    UART1_SendData8(0x0a);
    delay(2000);
  }
}
