#include "sl.h"
#include "sl_cfg.h"

/******************************************************************************/

static volatile sl_data_t sl_data;

/******************************************************************************/

const sl_task_data_t sl_tasks_data_vector[] = sl_tasks_data_vector_default_value;

/******************************************************************************/

void sl_enter_critical(void)
{  sl_dint();
  sl_data.critical_level++;
}

/******************************************************************************/

void sl_leave_critical(void)
{
#if 0
  sl_dint();
  if(sl_data.critical_level > 0)
#endif
  {
    sl_data.critical_level--;
  }

  if(sl_data.critical_level == 0)
  {
    sl_eint();
  }
}

/******************************************************************************/

void sl_delay_cycles(uint32_t cycles_to_wait)
{
  uint32_t counter;

  for(counter = cycles_to_wait ;counter > 0; counter--)
  {
    asm("nop");
  }
}

/******************************************************************************/

void sl_delay_ms(uint32_t ms_to_wait)
{
  sl_dint();
  sl_data.delay_1ms_timer = ms_to_wait;
  while(sl_data.delay_1ms_timer != 0)
  {
    sl_eint();
    sl_dint();
  }
  sl_eint();
}

/******************************************************************************/

void sl_reinit(void)
{
  sl_data.must_reinit = 1;
 // wlog("ReInit GPIO Module");
}

/******************************************************************************/

void sl_1ms_clock(void)
{
  const sl_task_data_t *ptask_data;
              uint32_t  index;

  ptask_data = sl_tasks_data_vector;
  for(index = SL_NUMBER_OF_TASKS; index; index--)
  {
    if((ptask_data->task_enabled   == SL_STATUS_ENABLED)
    && (ptask_data->clock_enabled == SL_STATUS_ENABLED)
    && (ptask_data->p1ms_clock        != NULL             ))
    {
      (*(ptask_data->p1ms_clock))();
    }

    if(ptask_data->pexecution_rate_1ms_timer != NULL)
    {
      if(*ptask_data->pexecution_rate_1ms_timer > 0)
      {
        (*ptask_data->pexecution_rate_1ms_timer)--;
      }
    }

    ptask_data++;
  }

  if(sl_data.delay_1ms_timer > 0)
  {
    sl_data.delay_1ms_timer--;
  }
}

/******************************************************************************/

void sl_init(void)
{
  const sl_task_data_t *ptask_data;
              uint32_t  index;

  sl_dint();
  sl_data.critical_level = 0;
  sl_data.delay_1ms_timer = 0;

  ptask_data = sl_tasks_data_vector;
  for(index = SL_NUMBER_OF_TASKS; index; index--)
  {
    if((ptask_data->task_enabled == SL_STATUS_ENABLED)
    && (ptask_data->init_enabled == SL_STATUS_ENABLED)
    && (ptask_data->pinit        != NULL             ))
    {
      (*(ptask_data->pinit))();
    }

    if(ptask_data->pexecution_rate_1ms_timer != NULL)
    {
      *ptask_data->pexecution_rate_1ms_timer = ptask_data->execution_rate_1ms_time;
    }
    ptask_data++;
  }
  sl_eint();

  //wlog("Init GPIO Module [ID 0x%02X]", mb_get_slave_address());

  sl_data.must_reinit = 0;
}

/******************************************************************************/

void sl_update(void)
{
  if(sl_data.must_reinit != 0)
  {
    sl_deinit();
    sl_init();
  }
  else
  {
    const sl_task_data_t *ptask_data;
                uint32_t  index;

    ptask_data = sl_tasks_data_vector;
    for(index = SL_NUMBER_OF_TASKS; index; index--)
    {
      if((ptask_data->task_enabled   == SL_STATUS_ENABLED)
      && (ptask_data->update_enabled == SL_STATUS_ENABLED)
      && (ptask_data->pupdate        != NULL             ))
      {
        if(ptask_data->pexecution_rate_1ms_timer == NULL)
        {
           (*(ptask_data->pupdate))();
        }
        else
        {
          uint32_t timer;

          sl_critical_assign(timer, *ptask_data->pexecution_rate_1ms_timer);
          if(timer == 0)
          {
            sl_critical_assign(*ptask_data->pexecution_rate_1ms_timer, ptask_data->execution_rate_1ms_time);
            (*(ptask_data->pupdate))();
          }
        }
      }
      ptask_data++;
    }
  }
}

/******************************************************************************/

void sl_deinit(void)
{
  const sl_task_data_t *ptask_data;
              uint32_t  index;

  ptask_data = sl_tasks_data_vector;
  for(index = SL_NUMBER_OF_TASKS; index; index--)
  {
    if((ptask_data->task_enabled   == SL_STATUS_ENABLED) &&
       (ptask_data->deinit_enabled == SL_STATUS_ENABLED) &&
       (ptask_data->pdeinit        != NULL             ))
    {
      (*(ptask_data->pdeinit))();
    }
    ptask_data++;
  }
}

/******************************************************************************/
