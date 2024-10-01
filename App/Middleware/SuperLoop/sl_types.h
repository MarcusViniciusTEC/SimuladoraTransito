#ifndef __SL_TYPES_H__
#define __SL_TYPES_H__

/******************************************************************************/

typedef enum
{
  SL_STATUS_DISABLED = 0,
  SL_STATUS_ENABLED,
  SL_NUMBER_OF_STATUSES
} sl_status_t;

/******************************************************************************/

#include "stdint.h"

typedef struct
{
               void (*p1ms_clock)(void);
        sl_status_t  clock_enabled;
               void (*pinit)(void);
        sl_status_t  init_enabled;
               void (*pupdate)(void);
        sl_status_t  update_enabled;
               void (*pdeinit)(void);
        sl_status_t  deinit_enabled;
  volatile uint32_t *pexecution_rate_1ms_timer;
           uint32_t  execution_rate_1ms_time;
        sl_status_t  task_enabled;
} sl_task_data_t;

/******************************************************************************/

#include "stdint.h"

typedef struct
{
  uint32_t critical_level;
  uint32_t delay_1ms_timer;
  uint32_t must_reinit;
} sl_data_t;

/******************************************************************************/

#endif/*__SL_TYPES_H__*/
