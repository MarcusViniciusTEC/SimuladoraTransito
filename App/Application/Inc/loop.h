#ifndef __LOOP_H__
#define __LOOP_H__


#include "loop_types.h"






#define LOOP_EXECUTION_RATE_1MS_TIME            100

void loop_1ms_clock(void);              
void loop_init(void);                   
void loop_update(void);                  
void loop_deinit(void);                  

#endif