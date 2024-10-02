
#ifndef __PIEZO_H__
#define __PIEZO_H__

/******************************************************************************/

#include "sl.h"
#include "piezo_types.h"

/******************************************************************************/
extern volatile uint32_t piezo_execution_rate_1ms_timer;

#define piezo_pexecution_rate_1ms_timer 	            (&piezo_execution_rate_1ms_timer)

#define PIEZO_EXECUTION_RATE_1MS_TIME    	        0

/******************************************************************************/

void piezo_1ms_clock(void);    
void piezo_init(void);                 
void piezo_update(void);
void piezo_deinit(void);


#endif