#include <stm8s.h>
#include <stm8s_gpio.h>

int new=1;
int old; 
int onoff=0;

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
 GPIO_DeInit(GPIOA);
 GPIO_Init(GPIOB,GPIO_PIN_5,GPIO_MODE_OUT_PP_LOW_FAST);
 GPIO_Init(GPIOA,GPIO_PIN_1,GPIO_MODE_IN_PU_NO_IT);
}

void blinkled()
{
 GPIO_WriteLow(GPIOB,GPIO_PIN_5);
 delay(1000);
 GPIO_WriteHigh(GPIOB,GPIO_PIN_5);
 delay(1000);
}

int main( void )
{
 GPIO_CONFIGURATION();
 
 while(1)
 {
  old=new;
  new=GPIO_ReadInputPin(GPIOA,GPIO_PIN_1);
  if( new == 0 && old == 1)
  {
    if(onoff==0)
    {
      onoff=1;
      GPIO_WriteLow(GPIOB,GPIO_PIN_5);
    }
    else
    {
      onoff=0;
      GPIO_WriteHigh(GPIOB,GPIO_PIN_5);
    }
  }
 } 
}