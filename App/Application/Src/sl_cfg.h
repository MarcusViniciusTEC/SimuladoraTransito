#ifndef __SL_CFG_H__
#define __SL_CFG_H__

/******************************************************************************/

#define SL_NUMBER_OF_TASKS                          5


/******************************************************************************/

#define sl_tasks_data_vector_default_value           \
{                                                    \
  {/*06-app*/                                        \
    app_1ms_clock,                SL_STATUS_ENABLED, \
    app_init,                     SL_STATUS_ENABLED, \
    app_update,                   SL_STATUS_ENABLED, \
    app_deinit,                   SL_STATUS_ENABLED, \
    app_pexecution_rate_1ms_timer,                   \
    APP_EXECUTION_RATE_1MS_TIME,                     \
    SL_STATUS_ENABLED                                \
  },                                                 \
  {/*07-hmi*/                                        \
    hmi_1ms_clock,                SL_STATUS_ENABLED, \
    hmi_init,                     SL_STATUS_ENABLED, \
    hmi_update,                   SL_STATUS_ENABLED, \
    hmi_deinit,                   SL_STATUS_ENABLED, \
    hmi_pexecution_rate_1ms_timer,                   \
    HMI_EXECUTION_RATE_1MS_TIME,                     \
    SL_STATUS_ENABLED                                \
  },                                                 \
  {/*08-wlog*/                                       \
    wlog_1ms_clock,               SL_STATUS_ENABLED, \
    wlog_init,                    SL_STATUS_ENABLED, \
    wlog_update,                  SL_STATUS_ENABLED, \
    wlog_deinit,                  SL_STATUS_ENABLED, \
    wlog_pexecution_rate_1ms_timer,                  \
    WLOG_EXECUTION_RATE_1MS_TIME,                    \
    SL_STATUS_ENABLED                                \
  },                                                 \
  {/*06-loop*/                                       \
    loop_1ms_clock,               SL_STATUS_ENABLED, \
    loop_init,                    SL_STATUS_ENABLED, \
    loop_update,                  SL_STATUS_ENABLED, \
    loop_deinit,                  SL_STATUS_ENABLED, \
    loop_pexecution_rate_1ms_timer,                  \
    LOOP_EXECUTION_RATE_1MS_TIME,                    \
    SL_STATUS_ENABLED                                \
  },                                                 \
  {/*07-piezo*/                                      \
    piezo_1ms_clock,               SL_STATUS_ENABLED,\
    piezo_init,                    SL_STATUS_ENABLED,\
    piezo_update,                  SL_STATUS_ENABLED,\
    piezo_deinit,                  SL_STATUS_ENABLED,\
    piezo_pexecution_rate_1ms_timer,                 \
    PIEZO_EXECUTION_RATE_1MS_TIME,                   \
    SL_STATUS_ENABLED                                \
  }                                                  \
}
/******************************************************************************/

#include "stdlib.h"
//#include "adc1.h"
//#include "wdt.h"
//#include "mb.h"
//#include "tmp.h"
//#include "din.h"

#include "app.h"
#include "hmi.h"
#include "wlog.h"
#include "loop.h"
#include "piezo.h"

/******************************************************************************/

#endif/*__SL_CFG_H__*/
