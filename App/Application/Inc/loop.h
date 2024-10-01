#ifndef __LOOP_H__
#define __LOOP_H__


#include "loop_types.h"

extern volatile uint32_t loop_execution_rate_1ms_timer;
#define loop_pexecution_rate_1ms_timer 	            (&loop_execution_rate_1ms_timer)





#define LOOP_EXECUTION_RATE_1MS_TIME            100

void loop_1ms_clock(void);              
void loop_init(void);                   
void loop_update(void);                  
void loop_deinit(void);                  

#endif