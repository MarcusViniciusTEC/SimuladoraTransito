#include "sl.h"
#include "loop.h"
#include "loop_cfg.h"
#include "hmi.h"


/******************************************************************************/

volatile uint32_t loop_execution_rate_1ms_timer;

typedef enum
{
  LOOP_AUTO_RESTART_OFF = 0,
  LOOP_AUTO_RESTART_ON
} loop_auto_restart_t;

typedef struct
{
  GPIO_TypeDef *GPIO;
      uint32_t  PinMask;
} loop_pininfo_t;


typedef enum
{
  LOOP_STATE_INIT = 0,
  LOOP_STATE_RUNNING,
  LOOP_NUMBER_OF_STATES

}loop_states_t;

typedef enum
{
  LOOP_ON = 1,
  LOOP_OFF

}loop_data_t;

typedef struct
{
  uint8_t loop_pin[LOOP_NUMBER_OF_OUTPUTS];
  uint32_t loop_delay_init;
  uint32_t loop_period;
  uint32_t cycles;
  loop_data_t loop_state;

}loop_apply_state_t;



static const loop_pininfo_t loop_pininfo_vector[LOOP_NUMBER_OF_OUTPUTS] = loop_pininfo_vector_default_value;

loop_apply_state_t loop_apply_state;
  
loop_states_t loop_states = LOOP_STATE_INIT;

/******************************************************************************/

void loop_turn_on(uint8_t index)
{
    loop_pininfo_t loop_pininfo;
    loop_pininfo = loop_pininfo_vector[index];
    LL_GPIO_SetOutputPin(loop_pininfo.GPIO, loop_pininfo.PinMask);
}

/******************************************************************************/

void loop_turn_off(uint8_t index)
{
    loop_pininfo_t loop_pininfo;
    loop_pininfo = loop_pininfo_vector[index];
    LL_GPIO_ResetOutputPin(loop_pininfo.GPIO, loop_pininfo.PinMask);
}

/******************************************************************************/

void loop_init_apply(void)
{
  for(uint16_t loop_index = 0; loop_index <= LOOP_NUMBER_OF_OUTPUTS; loop_index++ )
  {
    piezo_turn_off(loop_index);
  }
}

/******************************************************************************/

void loop_pulse(void)
{
  //loop_apply_state.loop_pin[2];
  loop_apply_state.loop_delay_init = 10;
  loop_apply_state.loop_period = 10;
  loop_apply_state.cycles = 2;

}


void loop_apply_update_state(void)
{
  if(loop_apply_state.loop_state)
  {
    if(loop_apply_state.cycles > 0)
    {
      if(loop_apply_state.cycles < 2)
      {
       // loop_turn_on(loop_apply_state.loop_pin);
        //sl_critical_assign(, led_1ms_timer)

      }
      else
      {

      }

      loop_apply_state.cycles--;



    } 
  }

}

/******************************************************************************/

void loop_1ms_period_loop(void)
{
  

}

/******************************************************************************/

void loop_1ms_delay_loop(void)
{



}

/******************************************************************************/

void loop_1ms_clock(void)
{
  if(loop_states = LOOP_STATE_RUNNING)
  {
    loop_1ms_delay_loop();
    loop_1ms_period_loop();
  }
}     

/******************************************************************************/

void loop_init(void)
{
  loop_init_apply();
  hmi_led_turn_on(1);
}              

/******************************************************************************/

void loop_update(void)
{
  loop_apply_update_state();
  loop_pulse();
  loop_states = LOOP_STATE_RUNNING;
}            

/******************************************************************************/

void loop_deinit(void)
{


}

