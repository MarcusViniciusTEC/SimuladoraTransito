#include "sl.h"
#include "loop.h"
#include "loop_cfg.h"
#include "hmi.h"

#include <stdbool.h>

/******************************************************************************/

volatile uint32_t loop_execution_rate_1ms_timer;

static const loop_pininfo_t loop_pininfo_vector[LOOP_NUMBER_OF_CHANNELS] = loop_pininfo_vector_default_value;

loop_apply_state_t loop_apply_state;
  
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
  for(uint16_t loop_index = 0; loop_index < LOOP_NUMBER_OF_OUTPUTS; loop_index++ )
  {
    loop_turn_off(loop_index);
  }
}

/******************************************************************************/

void loop_1ms_period_loop(void)
{
  for(uint8_t loop_index = 0; loop_index < LOOP_NUMBER_OF_CHANNELS; loop_index++)
  {
    if(loop_apply_state.loop_pin[loop_index].loop_period_turn_on > 0 && 
    loop_apply_state.loop_pin[loop_index].state == LOOP_UPDATE_PERIOD)
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
    if(loop_apply_state.loop_pin[loop_index].loop_delay_init > 0 && 
    loop_apply_state.loop_pin[loop_index].state == LOOP_UPDATE_DELAY_INIT)
    {
      loop_apply_state.loop_pin[loop_index].loop_delay_init--;
    }
  }
}

/******************************************************************************/

void loop_1ms_delay_restart(void)
{
  for(uint8_t loop_index = 0; loop_index < LOOP_NUMBER_OF_CHANNELS; loop_index++)
  {
    if(loop_apply_state.loop_pin[loop_index].time_restart_between_cycles > 0 && 
    loop_apply_state.loop_pin[loop_index].state == LOOP_UPDATE_DELAY_RESTART_BETWEEN_CYCLES)
    {
      loop_apply_state.loop_pin[loop_index].time_restart_between_cycles--;
    }
  }
}

/******************************************************************************/

uint8_t control_led_loop(uint8_t led_index)
{
  switch (led_index)
  {
    case LOOP_CH0:
      return LOOP_LED_LOOP_0;
      break;
    case LOOP_CH1:
      return LOOP_LED_LOOP_1;
      break;
    case LOOP_CH2:
      return LOOP_LED_LOOP_2;
      break;
    case LOOP_CH3:
      return LOOP_LED_LOOP_3;
      break;
    default:
      break;
  }
}

/******************************************************************************/

void loop_apply_update_state(uint8_t pin_index)
{
  switch (loop_apply_state.loop_pin[pin_index].state)
  { 
    case LOOP_STATE_INIT:
      loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_GET_DELAY; 
      break;
    case  LOOP_UPDATE_GET_DELAY :
      //loop_apply_state.loop_pin[pin_index].last_loop_delay_init               = loop_apply_state.loop_pin[pin_index].loop_delay_init;
      //loop_apply_state.loop_pin[pin_index].last_loop_period_turn_on           =  loop_apply_state.loop_pin[pin_index].loop_period_turn_on;
      //loop_apply_state.loop_pin[pin_index].last_time_restart_between_cycles   = loop_apply_state.loop_pin[pin_index].time_restart_between_cycles;
      loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_STATE_START; 
      break;
    case LOOP_UPDATE_STATE_START:
      if(loop_apply_state.loop_pin[pin_index].state == LOOP_UPDATE_STATE_START) 
      {
        loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_NUMBER_OF_CYCLES; 
      }
      else 
      {
        loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_STATE_INIT; 
      }
      break;
    case LOOP_UPDATE_NUMBER_OF_CYCLES:
      if(loop_apply_state.loop_pin[pin_index].number_of_cycles > 0)
      {
        loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_RUNNING;
      }
      else
      {
        loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_STATE_INIT;
      }
      break;
    case LOOP_UPDATE_RUNNING:
      if(loop_apply_state.loop_pin[pin_index].loop_delay_init > 0)
      {
        loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_DELAY_INIT;
      }
      else
      {
        loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_TURN_ON;
      }
      break;
    case  LOOP_UPDATE_DELAY_INIT:
      if(loop_apply_state.loop_pin[pin_index].loop_delay_init == 0)
      {
        loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_TURN_ON;
      }
      break;
    case LOOP_UPDATE_TURN_ON:
      loop_turn_on(pin_index);
      hmi_led_turn_on(control_led_loop(pin_index));
      loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_PERIOD;
      break;
    case LOOP_UPDATE_PERIOD:
      if(loop_apply_state.loop_pin[pin_index].loop_period_turn_on == 0)
      {        
        loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_TURN_OFF;
      }
      break;  
    case LOOP_UPDATE_TURN_OFF:
      loop_turn_off(pin_index);
      hmi_led_turn_off(control_led_loop(pin_index));
      loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_DELAY_RESTART_BETWEEN_CYCLES;
      break;
    case LOOP_UPDATE_DELAY_RESTART_BETWEEN_CYCLES:

      if(loop_apply_state.loop_pin[pin_index].time_restart_between_cycles == 0)
      {
        loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_TIME;    
      }  
      break;
    case LOOP_UPDATE_TIME:
      loop_apply_state.loop_pin[pin_index].number_of_cycles--;
      if(loop_apply_state.loop_pin[pin_index].number_of_cycles > 0)
      {
        //loop_apply_state.loop_pin[pin_index].loop_delay_init              = loop_apply_state.loop_pin[pin_index].last_loop_delay_init;
        //loop_apply_state.loop_pin[pin_index].loop_period_turn_on          = loop_apply_state.loop_pin[pin_index].last_loop_period_turn_on;
        //loop_apply_state.loop_pin[pin_index].time_restart_between_cycles  = loop_apply_state.loop_pin[pin_index].last_time_restart_between_cycles;  
        loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_STATE_SUCESS;
      } 
      else 
      {
        loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_STATE_SUCESS;
      }
      break;
    case LOOP_UPDATE_STATE_SUCESS:

      loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_STATE_SUCESS;
      //loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_STATE_INIT;
      break;
    default :
      //loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_STATE_INIT;
      break;
  }
}

/******************************************************************************/

void loop_received_parameters(uint8_t pin_index, loop_pin_data_t loop_pin_data_parameters)
{
  loop_apply_state.loop_pin[pin_index] = loop_pin_data_parameters;
  
}

/******************************************************************************/

void loop_group_received_parameters(loop_groups_t loop_group, loop_pin_data_t loop_enter_par, loop_pin_data_t loop_exit_par)
{
  static bool aux = false;
  if(aux == false)
  {
    switch (loop_group)
    {
    case LOOP_GROUP_0:
      loop_apply_state.loop_pin[LOOP_CH0] = loop_enter_par;
      loop_apply_state.loop_pin[LOOP_CH1] = loop_exit_par;
      break;
    case LOOP_GROUP_1:
      loop_apply_state.loop_pin[LOOP_CH2] = loop_enter_par;
      loop_apply_state.loop_pin[LOOP_CH3] = loop_exit_par;
      break;
    default:
      break;
    }
    aux = true;
  }

  // if(loop_apply_state.loop_pin[LOOP_CH1].state == LOOP_UPDATE_STATE_SUCESS)
  // {
  //   aux = false;
  //   return LOOP_GROUP_CYCLE_SUCESS;
  // }
  // else if(loop_apply_state.loop_pin[LOOP_CH1].state != LOOP_UPDATE_STATE_SUCESS)
  // {
  //   return LOOP_GROUP_CYCLE_RUNNING;
  // }
}



/******************************************************************************/

void loop_1ms_clock(void)
{
  loop_1ms_delay_loop();
  loop_1ms_period_loop();
  loop_1ms_delay_restart();
}  

/******************************************************************************/

void loop_init(void)
{
  loop_init_apply();
  loop_apply_state.loop_state = LOOP_STATE_RUNNING;
}              

/******************************************************************************/

void loop_update(void)
{
  switch (loop_apply_state.loop_state)
  {
  case LOOP_STATE_INIT:  
    break;
  case LOOP_STATE_RUNNING:
    for(uint8_t pin_index = 0; pin_index < LOOP_NUMBER_OF_CHANNELS; pin_index++)
    {
      loop_apply_update_state(pin_index);
    }
     break;
  default:
    break;
  }  
}            

/******************************************************************************/

void loop_deinit(void)
{


}

