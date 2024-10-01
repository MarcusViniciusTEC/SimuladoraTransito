#ifndef __SL_LIB_TYPES_H__
#define __SL_LIB_TYPES_H__

/******************************************************************************/

#include "stdint.h"

/******************************************************************************/

typedef struct
{
  int32_t mod;
  int32_t Kp;
  int32_t Ki;
  int32_t Kd;
  int32_t Kbase;
  int32_t error1;
  int32_t error2;
  int32_t min_output;
  int32_t max_output;
  int32_t output;
} sl_pid_data_type;

/******************************************************************************/

typedef struct
{
   int32_t val;
   int32_t val_mod;
  uint32_t length;
} sl_avg_data_type;

/******************************************************************************/

#endif/*__SL_LIB_TYPES_H__*/
