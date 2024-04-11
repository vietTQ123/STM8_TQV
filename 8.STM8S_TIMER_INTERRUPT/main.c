#include <stm8s.h>
#include <stm8s_clk.h>
#include <stm8s_tim1.h>
#include <stm8s_tim4.h>

void assert_failed(uint8_t* file, uint32_t line){}
void Delayms_timer4(uint16_t time_delay);
void CLK_Cofiguration(void);
void GPIO_Configuration(void);
void Timer1_int_Configuration(void);

int count=0;

void main(void)
{
  CLK_Cofiguration();
  GPIO_Configuration();
  Timer1_int_Configuration();
  
  while (1)
  {
    if(count % 2 == 0)
    {
      GPIO_WriteLow(GPIOD,GPIO_PIN_2);
    }
    else
    {
      GPIO_WriteHigh(GPIOD,GPIO_PIN_2);
    }
  }
}

void CLK_Cofiguration(void)
{
 CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
}

void GPIO_Configuration(void)
{
  GPIO_DeInit(GPIOD);                                     
  GPIO_Init(GPIOD,GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST); 
}

void Delayms_timer4(uint16_t time_delay)
{
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE); // enable clock timer 4
  TIM4_TimeBaseInit(TIM4_PRESCALER_64, 250);		    // set frequence timer 4 la 16*10^6/64/250 = 1000Hz
  TIM4_SetCounter(0);					    // set counter value = 0    															//set counter ve gia tri ban dau =0	
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);                         // clear flag update timer4(when over timer = 1) clear 0
  TIM4_Cmd(ENABLE);					    // enable timer													// enable timer hoat dong
  while(time_delay--)																				// tan so la 1000Hz -> khi lap lai 1000 lan la 1Hz = 1s
  {
    while(TIM4_GetFlagStatus(TIM4_FLAG_UPDATE)== 0) ;	   // watting over timer exit whiles
    TIM4_ClearFlag(TIM4_FLAG_UPDATE);			   // clear timer for next counter    									
  }

  TIM4_Cmd(DISABLE);																				// sau khi delay xong, disable timer.
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, DISABLE);// Disable clock for timer when finish delay
}

void Timer1_int_Configuration(void)
{
    TIM1_DeInit();						// reset all resgister timer1
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, ENABLE);	// provide clock for timer1
    TIM1_TimeBaseInit(15999,TIM1_COUNTERMODE_UP, 1000,0);       // config frequency interrupt PSC= 15999+1 =16000, ARR = 1000 -> F_interrupt = 16*10^6 / 16000/1000 = 1Hz = 1s
    TIM1_ARRPreloadConfig(ENABLE);				// enable register auto reload active -  over counter -> reset counter
    TIM1_ITConfig(TIM1_IT_UPDATE,ENABLE);		        // ennable over inerrupt 
    TIM1_ClearFlag(TIM1_FLAG_UPDATE);	                        // clear flag over counter for firttime run
    TIM1_Cmd(ENABLE);						// enable timer active
    enableInterrupts();						// enable global interrupt
}

INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11)
{
 count++;
 TIM1_ClearITPendingBit(TIM1_FLAG_UPDATE);
}