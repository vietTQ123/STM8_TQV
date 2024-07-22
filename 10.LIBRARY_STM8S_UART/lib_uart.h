#ifndef _LIB_UART_H
#define _LIB_UART_H

#ifdef __cplusplus
    extern "C" {
#endif
      
#include <stm8s.h>      
#include <stm8s_uart1.h>
#include <stm8s_gpio.h>
#include <stm8s_clk.h>
#include <stdio.h>
#include <string.h>
      
extern char arr_receive[100];
extern uint8_t count_arr_receive;
extern uint8_t flag_arr_receive;
      
void UART_Configuration(uint32_t select);
void UART_Send_Array(uint8_t* array, uint16_t length); 
      
#ifdef __cplusplus
}
#endif

#endif       