#include <stm8s.h>
#include <stm8s_gpio.h>

#define ledA GPIOC,GPIO_PIN_7
#define ledB GPIOC,GPIO_PIN_6
#define ledC GPIOC,GPIO_PIN_5
#define ledD GPIOC,GPIO_PIN_4
#define ledE GPIOC,GPIO_PIN_3
#define ledF GPIOB,GPIO_PIN_4
#define ledG GPIOB,GPIO_PIN_5


void assert_failed(uint8_t* file, uint32_t line){}

void delay(int t)
{
  int i, j;
  for (i = 0; i < t; i++)
  {
    for (j = 0; j < 400; j++){}
  }
}

void GPIO_CONFIGURATION()
{

 GPIO_DeInit(GPIOB);
 GPIO_DeInit(GPIOC);
 
 GPIO_Init(ledA,GPIO_MODE_OUT_PP_LOW_FAST);
 GPIO_Init(ledB,GPIO_MODE_OUT_PP_LOW_FAST);
 GPIO_Init(ledC,GPIO_MODE_OUT_PP_LOW_FAST);
 GPIO_Init(ledD,GPIO_MODE_OUT_PP_LOW_FAST);
 GPIO_Init(ledE,GPIO_MODE_OUT_PP_LOW_FAST);
 GPIO_Init(ledF,GPIO_MODE_OUT_PP_LOW_FAST);
 GPIO_Init(ledG,GPIO_MODE_OUT_PP_LOW_FAST);
 
}

unsigned char led7Hex[]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
void LED7_writeByte (unsigned char b)
{
  if(((b>>0)& 0x01)==0)
  {
    GPIO_WriteLow(ledA);
  }
  else
  {
    GPIO_WriteHigh(ledA);
  }
  if(((b>>1)& 0x01)==0)
  {
    GPIO_WriteLow(ledB);
  }
  else
  {
    GPIO_WriteHigh(ledB);
  }
  if(((b>>2)& 0x01)==0)
  {
    GPIO_WriteLow(ledC);
  }
  else
  {
    GPIO_WriteHigh(ledC);
  }
  if(((b>>3)& 0x01)==0)
  {
    GPIO_WriteLow(ledD);
  }
  else
  {
    GPIO_WriteHigh(ledD);
  }
  if(((b>>4)& 0x01)==0)
  {
    GPIO_WriteLow(ledE);
  }
  else
  {
    GPIO_WriteHigh(ledE);
  }
  if(((b>>5)& 0x01)==0)
  {
    GPIO_WriteLow(ledF);
  }
  else
  {
    GPIO_WriteHigh(ledF);
  }
  if(((b>>6)& 0x01)==0)
  {
    GPIO_WriteLow(ledG);
  }
  else
  {
    GPIO_WriteHigh(ledG);
  }
}

int main( void )
{
 int i;
 GPIO_CONFIGURATION();
 while(1)
 {
   for(i=0;i<=9;i++)
   {
    LED7_writeByte(led7Hex[1]);
    delay(100);
   }  
 } 
}

