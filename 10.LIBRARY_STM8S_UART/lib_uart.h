#ifndef _LIB_UART_H
#define _LIB_UART_H

#ifdef __cplusplus
    extern "C" {
#endif
      
#include <stm8s.h>      
#include <stm8s_uart1.h>
#include <stm8s_gpio.h>
#include <stm8s_clk.h>
#include <stm8s_it.h>
#include <stdio.h>
#include <string.h>
#include <lib_convert.h>
      
#define WAIT_RECEIVE 0
#define RECEIVING 1
#define END_RECEIVE 2
   
extern char array_receive[100];
extern uint16_t count_array_receive;
extern uint8_t flag_array_receive;
      
void UART_Configuration (uint32_t baudrate);

void UART_Send_Array (uint8_t* array, uint16_t length); 

void UART_Printf_String (char *message); 

void UART_Interrupt_Receive_String ();

void UART_Time_Out();

INTERRUPT_HANDLER(UART1_RX_IRQHandler,18);

#ifdef __cplusplus
}
#endif

#endif       
