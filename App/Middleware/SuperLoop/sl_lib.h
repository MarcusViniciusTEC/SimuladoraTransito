#ifndef __SL_LIB_H__
#define __SL_LIB_H__

/******************************************************************************/

#include "sl_lib_types.h"

/******************************************************************************/

void sl_pid_reset(volatile sl_pid_data_type *pid);
void sl_pid_init(volatile sl_pid_data_type *pid, int32_t Kp, int32_t Ki, int32_t Kd, int32_t Kbase, int32_t min_output, int32_t max_output);
int32_t sl_pid_calc(volatile sl_pid_data_type *pid, int32_t error);

/******************************************************************************/

   void sl_avg_init(volatile sl_avg_data_type *pavg, uint32_t length);
   void sl_avg_rst(volatile sl_avg_data_type *pavg);
int32_t sl_avg_calc(volatile sl_avg_data_type *pavg, int32_t sample);

/******************************************************************************/

#define sl_quantize(var, value, quantum)         \
{                                                \
  var = value;                                   \
  var += quantum/2;                              \
  var /= quantum;                                \
  var *= quantum;                                \
}

/******************************************************************************/

#endif/*__SL_LIB_H__*/
