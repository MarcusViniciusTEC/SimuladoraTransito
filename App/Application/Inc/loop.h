#ifndef __LOOP_H__
#define __LOOP_H__

/******************************************************************************/

#include "loop_types.h"
#include <stdbool.h>

extern volatile uint32_t loop_execution_rate_1ms_timer;

#define loop_pexecution_rate_1ms_timer 	            (&loop_execution_rate_1ms_timer)

/******************************************************************************/

#define LOOP_EXECUTION_RATE_1MS_TIME    	        0

/******************************************************************************/

void piezo_turn_on(uint8_t index);
void piezo_turn_off(uint8_t index);

/******************************************************************************/

void loop_init_apply(void);
void loop_1ms_period_loop(void);
void loop_1ms_delay_loop(void);
void loop_1ms_delay_restart(void);
void loop_received_parameters(uint8_t pin_index, loop_pin_data_t loop_pin_data_parameters);
uint8_t loop_group_received_parameters(loop_groups_t loop_group, loop_pin_data_t loop_enter_par, loop_pin_data_t loop_exit_par);

/******************************************************************************/

void loop_1ms_clock(void);              
void loop_init(void);                   
void loop_update(void);                  
void loop_deinit(void);                  

/******************************************************************************/

#endif