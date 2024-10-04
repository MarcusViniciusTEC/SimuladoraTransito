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
    LOOP_PULSE_ON = 0,
    LOOP_PULSE_OFF

}loop_states_pulse_t;

typedef enum
{
  LOOP_CH1 = 0,
  LOOP_CH2,
  LOOP_CH3,
  LOOP_NUMBER_OF_CHANNELS

}loop_channes_t;

typedef struct
{
  loop_states_pulse_t state;
  uint16_t loop_delay_init;
  uint16_t loop_period_turn_on;
  uint16_t number_of_cycles;

}loop_pin_data_t;


typedef struct
{
  loop_states_pulse_t state;
  uint16_t loop_delay_init;
  uint16_t loop_period_turn_on;
  uint16_t number_of_cycles;

}test_loop_t;

test_loop_t  test_loop;


typedef struct
{
  loop_pin_data_t loop_pin[LOOP_NUMBER_OF_OUTPUTS]; 
  loop_states_t loop_state;

}loop_apply_state_t;



static const loop_pininfo_t loop_pininfo_vector[LOOP_NUMBER_OF_CHANNELS] = loop_pininfo_vector_default_value;

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

void loop_received_parameters(uint8_t pin_index, loop_pin_data_t loop_pin_data_parameters)
{
  loop_apply_state.loop_pin[pin_index].loop_delay_init = loop_pin_data_parameters.loop_delay_init;
  loop_apply_state.loop_pin[pin_index].loop_period_turn_on = loop_pin_data_parameters.loop_period_turn_on;
  loop_apply_state.loop_pin[pin_index].number_of_cycles = loop_pin_data_parameters.number_of_cycles;
  loop_apply_state.loop_pin[pin_index].state = loop_pin_data_parameters.state;

  loop_apply_update_state(pin_index);
}

/******************************************************************************/


/******************************************************************************/

void loop_1ms_period_loop(void)
{
  for(uint8_t loop_index = 0; loop_index < LOOP_NUMBER_OF_CHANNELS; loop_index++)
  {
    if(loop_apply_state.loop_pin[loop_index].loop_period_turn_on > 0)
    {
      loop_apply_state.loop_pin[loop_index].loop_period_turn_on--;
    }
  }

}

/******************************************************************************/

void loop_1ms_delay_loop(void)
{

  for(uint8_t loop_index = 0; loop_index < LOOP_NUMBER_OF_CHANNELS; loop_index++)
  {
    if(loop_apply_state.loop_pin[loop_index].loop_delay_init > 0)
    {
      loop_apply_state.loop_pin[loop_index].loop_delay_init--;
    }
  }

}



void loop_apply_update_state(uint8_t pin_index)
{
  switch (loop_apply_state.loop_pin[pin_index].state)
  {
  case LOOP_PULSE_ON:
  if(loop_apply_state.loop_pin[pin_index].number_of_cycles > 0)
  {
    loop_apply_state.loop_pin[pin_index].number_of_cycles --;
    if(loop_apply_state.loop_pin[pin_index].loop_delay_init == 0)
    {
      sl_critical_assign(loop_apply_state.loop_pin[pin_index].loop_delay_init, 1000)
      loop_turn_on(pin_index);
      sl_critical_assign(loop_apply_state.loop_pin[pin_index].loop_delay_init, 500)
      loop_turn_off(pin_index);

      loop_apply_state.loop_pin[pin_index].state = LOOP_PULSE_OFF;

    }
    else
    {
      loop_turn_on(pin_index);
      sl_critical_assign(loop_apply_state.loop_pin[pin_index].loop_delay_init, 500)
      loop_turn_off(pin_index);

      loop_apply_state.loop_pin[pin_index].state = LOOP_PULSE_OFF;
    }

  }else
  {
    loop_apply_state.loop_pin[pin_index].state = LOOP_PULSE_OFF;
  }
  break;

  case LOOP_PULSE_OFF:

  loop_turn_off(pin_index);
  
  break;

  default:
    break;
  }


}



/******************************************************************************/

void loop_1ms_clock(void)
{
  loop_1ms_delay_loop();
  loop_1ms_period_loop();
}     

/******************************************************************************/

void loop_init(void)
{
  loop_init_apply();
}              

/******************************************************************************/

void loop_update(void)
{

}            

/******************************************************************************/

void loop_deinit(void)
{


}

