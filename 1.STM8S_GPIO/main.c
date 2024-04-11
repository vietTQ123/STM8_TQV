#include <stm8s.h>
#include <stm8s_gpio.h>

void assert_failed(uint8_t* file, uint32_t line){}

void delay(int t)
{
  int i, j;
  for (i = 0; i < t; i++)
  {
    for (j = 0; j < 399; j++){}
  }
}

void GPIO_CONFIGURATION()
{
 GPIO_DeInit(GPIOD);
 GPIO_Init(GPIOD,GPIO_PIN_3,GPIO_MODE_OUT_PP_LOW_FAST);
}

void blinkled()
{
 GPIO_WriteLow(GPIOD,GPIO_PIN_3);
 delay(1000);
 GPIO_WriteHigh(GPIOD,GPIO_PIN_3);
 delay(1000);
}

int main( void )
{
 GPIO_CONFIGURATION();
 while(1)
 {
  blinkled();
 } 
}


