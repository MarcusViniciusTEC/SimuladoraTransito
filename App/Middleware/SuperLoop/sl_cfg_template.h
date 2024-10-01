#ifndef __SL_CFG_H__
#define __SL_CFG_H__

/******************************************************************************/

#define SL_NUMBER_OF_TASKS 1

/******************************************************************************/

#define sl_tasks_data_vector_default_value           \
{                                                    \
  {/*00-app*/                                        \
    app_1ms_clock,                SL_STATUS_ENABLED, \
    app_init,                     SL_STATUS_ENABLED, \
    app_update,                   SL_STATUS_ENABLED, \
    app_deinit,                   SL_STATUS_ENABLED, \
    app_pexecution_rate_1ms_timer,                   \
    APP_EXECUTION_RATE_1MS_TIME,                     \
    SL_STATUS_ENABLED                                \
  }                                                  \
}

/******************************************************************************/

#include "stdlib.h"
//#include "app.h"

/******************************************************************************/

#endif/*__SL_CFG_H__*/
