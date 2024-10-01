#include "sl_lib.h"

/******************************************************************************/

//#include "wlog.h"

/******************************************************************************/

void sl_pid_reset(volatile sl_pid_data_type *pid)
{
  pid->mod    = 0;
  pid->error1 = 0;
  pid->error2 = 0;
  pid->output = 0;
}

/******************************************************************************/

void sl_pid_init(volatile sl_pid_data_type *pid, int32_t Kp, int32_t Ki, int32_t Kd, int32_t Kbase, int32_t min_output, int32_t max_output)
{
  pid->Kp    = Kp;
  pid->Ki    = Ki;
  pid->Kd    = Kd;
  pid->Kbase = Kbase;
  pid->min_output = min_output;
  pid->max_output = max_output;

  sl_pid_reset(pid);
}

/******************************************************************************/

int32_t sl_pid_calc(volatile sl_pid_data_type *pid, int32_t error)
{
  int32_t delta,
          P_parcel,
          I_parcel,
          D_parcel;

  P_parcel = pid->Kp * (error -   pid->error1              );
  I_parcel = pid->Ki * (error                              );
  D_parcel = pid->Kd * (error - 2*pid->error1 + pid->error2);

  delta = P_parcel
        + I_parcel
        + D_parcel
        + pid->mod;

  pid->mod = delta % pid->Kbase;
  delta   /= pid->Kbase;

  pid->output += delta;

  if(pid->output < pid->min_output)
  {
    pid->output = pid->min_output;
    pid->mod = 0;
  }
  else if(pid->output > pid->max_output)
  {
    pid->output = pid->max_output;
    pid->mod = 0;
  }

  pid->error2 = pid->error1;
  pid->error1 = error;

  return pid->output;
}

/******************************************************************************/

void sl_avg_init(volatile sl_avg_data_type *pavg, uint32_t length)
{
  pavg->length = length;
  sl_avg_rst(pavg);
}

/******************************************************************************/

void sl_avg_rst(volatile sl_avg_data_type *pavg)
{
  pavg->val = 0;
  pavg->val_mod = 0;
}

/******************************************************************************/

int32_t sl_avg_calc(volatile sl_avg_data_type *pavg, int32_t sample)
{
  pavg->val     *= (pavg->length - 1);
  pavg->val     += sample;
  pavg->val     += pavg->val_mod;
  pavg->val_mod  = pavg->val % pavg->length;
  pavg->val     /= pavg->length;

  return pavg->val;
}

/******************************************************************************/
