#include "sl.h"
#include "loop.h"
#include "loop_cfg.h"
#include "hmi.h"


/******************************************************************************/

/*****************************************************************************

 ====================== NÃO PAGAR, EXEMPLO DE TRANSITO FUNCIONAL =============

  loop_apply_state.loop_pin[1].loop_delay_init = 0;
  loop_apply_state.loop_pin[1].loop_period_turn_on = 500;
  loop_apply_state.loop_pin[1].time_restart_between_cycles = 1500;
  loop_apply_state.loop_pin[1].number_of_cycles = 1000;
  loop_apply_state.loop_pin[1].state = init ;

  loop_apply_state.loop_pin[2].loop_delay_init = 250;
  loop_apply_state.loop_pin[2].loop_period_turn_on = 500;
  loop_apply_state.loop_pin[2].time_restart_between_cycles = 1250;
  loop_apply_state.loop_pin[2].number_of_cycles = 1000;
  loop_apply_state.loop_pin[2].state = init ;
 
 ******************************************************************************/

volatile uint32_t loop_execution_rate_1ms_timer;

#define LOOP_LED_LOOP_0         0
#define LOOP_LED_LOOP_1         2
#define LOOP_LED_LOOP_2         3
#define LOOP_LED_LOOP_3         5
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

}loop_data_t;

typedef enum
{
  LOOP_CH0 = 0,
  LOOP_CH1,
  LOOP_CH2,
  LOOP_CH3,
  LOOP_NUMBER_OF_CHANNELS

}loop_channes_t;

typedef enum
{
  LOOP_UPDATE_STATE_INIT = 0,
  LOOP_UPDATE_GET_DELAY,
  LOOP_UPDATE_STATE_START,
  LOOP_UPDATE_NUMBER_OF_CYCLES,
  LOOP_UPDATE_DELAY_INIT,
  LOOP_UPDATE_RUNNING,
  LOOP_UPDATE_TURN_ON,
  LOOP_UPDATE_PERIOD,
  LOOP_UPDATE_TURN_OFF,
  LOOP_UPDATE_TIME,
  LOOP_UPDATE_DELAY_RESTART_BETWEEN_CYCLES,
  LOOP_UPDATE_STATE_SUCESS
}loop_state_update_t;

typedef struct
{
  loop_state_update_t state;
  uint32_t time_restart_between_cycles;
  uint32_t last_time_restart_between_cycles;
  uint32_t loop_delay_init;
  uint32_t last_loop_delay_init;
  uint32_t loop_period_turn_on;
  uint32_t last_loop_period_turn_on;
  uint16_t number_of_cycles;

}loop_pin_data_t;

typedef struct
{
  loop_pin_data_t loop_pin[LOOP_NUMBER_OF_OUTPUTS]; 
  loop_data_t loop_state;

}loop_apply_state_t;


static const loop_pininfo_t loop_pininfo_vector[LOOP_NUMBER_OF_CHANNELS] = loop_pininfo_vector_default_value;

loop_apply_state_t loop_apply_state;
  
//loop_states_t loop_states = LOOP_STATE_INIT;

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
  loop_apply_state.loop_pin[pin_index].time_restart_between_cycles = loop_pin_data_parameters.time_restart_between_cycles;
  loop_apply_state.loop_pin[pin_index].number_of_cycles = loop_pin_data_parameters.number_of_cycles;
  loop_apply_state.loop_pin[pin_index].state = loop_pin_data_parameters.state;
}

/******************************************************************************/


/******************************************************************************/

void loop_1ms_period_loop(void)
{
  for(uint8_t loop_index = 0; loop_index < LOOP_NUMBER_OF_CHANNELS; loop_index++)
  {
    if(loop_apply_state.loop_pin[loop_index].loop_period_turn_on > 0 && loop_apply_state.loop_pin[loop_index].state == LOOP_UPDATE_PERIOD)
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
    if(loop_apply_state.loop_pin[loop_index].loop_delay_init > 0 && loop_apply_state.loop_pin[loop_index].state == LOOP_UPDATE_DELAY_INIT)
    {
      loop_apply_state.loop_pin[loop_index].loop_delay_init--;
    }
  }
}

void loop_1ms_delay_restart(void)
{
  for(uint8_t loop_index = 0; loop_index < LOOP_NUMBER_OF_CHANNELS; loop_index++)
  {
    if(loop_apply_state.loop_pin[loop_index].time_restart_between_cycles > 0 && loop_apply_state.loop_pin[loop_index].state == LOOP_UPDATE_DELAY_RESTART_BETWEEN_CYCLES)
    {
      loop_apply_state.loop_pin[loop_index].time_restart_between_cycles--;
    }
  }
}

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


/******************************************************************
 * 
 * _______________________
 * |                     |
 * |                     |
 * |                     |____________________________
 *
 *             _________________________
 *             |                       |
 *             |                       |
 * ____________|                       |_______________
 * 
 * |-----------|-----------------------|----------------
 *  period/2             PERIOD            DELAY RESTART 
 * 
 * 
 * ****************************************************************/

void loop_apply_update_state(uint8_t pin_index)
{
  switch (loop_apply_state.loop_pin[pin_index].state)
  { 
    case LOOP_STATE_INIT:
      loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_GET_DELAY; 
      break;
    case  LOOP_UPDATE_GET_DELAY :
      loop_apply_state.loop_pin[pin_index].last_loop_delay_init = loop_apply_state.loop_pin[pin_index].loop_delay_init;
      loop_apply_state.loop_pin[pin_index].last_loop_period_turn_on =  loop_apply_state.loop_pin[pin_index].loop_period_turn_on;
      loop_apply_state.loop_pin[pin_index].last_time_restart_between_cycles = loop_apply_state.loop_pin[pin_index].time_restart_between_cycles;
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
        loop_apply_state.loop_pin[pin_index].loop_delay_init = loop_apply_state.loop_pin[pin_index].last_loop_delay_init;
        loop_apply_state.loop_pin[pin_index].loop_period_turn_on = loop_apply_state.loop_pin[pin_index].last_loop_period_turn_on;
        loop_apply_state.loop_pin[pin_index].time_restart_between_cycles = loop_apply_state.loop_pin[pin_index].last_time_restart_between_cycles;  
        loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_STATE_SUCESS;
      } 
      else 
      {
        loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_STATE_SUCESS;
      }
      break;
    case LOOP_UPDATE_STATE_SUCESS:
      loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_STATE_INIT;
      break;
    default :
      loop_apply_state.loop_pin[pin_index].state = LOOP_UPDATE_STATE_INIT;
      break;
  }
}

/******************************************************************************/
uint8_t index_test;


void loop_1ms_clock(void)
{
  loop_1ms_delay_loop();
  loop_1ms_period_loop();
  loop_1ms_delay_restart();
}  

/******************************************************************************/

void loop_init(void)
{
  loop_apply_state.loop_pin[0].loop_delay_init = 0;
  loop_apply_state.loop_pin[0].loop_period_turn_on = 500;
  loop_apply_state.loop_pin[0].time_restart_between_cycles = 1500;
  loop_apply_state.loop_pin[0].number_of_cycles = 1000;
  loop_apply_state.loop_pin[0].state = 0 ;

  loop_apply_state.loop_pin[1].loop_delay_init = 250;
  loop_apply_state.loop_pin[1].loop_period_turn_on = 500;
  loop_apply_state.loop_pin[1].time_restart_between_cycles = 1250;
  loop_apply_state.loop_pin[1].number_of_cycles = 1000;
  loop_apply_state.loop_pin[1].state = 0 ;

  loop_apply_state.loop_pin[2].loop_delay_init = 0;
  loop_apply_state.loop_pin[2].loop_period_turn_on = 500;
  loop_apply_state.loop_pin[2].time_restart_between_cycles = 1500;
  loop_apply_state.loop_pin[2].number_of_cycles = 1000;
  loop_apply_state.loop_pin[2].state = 0 ;

  loop_apply_state.loop_pin[3].loop_delay_init = 250;
  loop_apply_state.loop_pin[3].loop_period_turn_on = 500;
  loop_apply_state.loop_pin[3].time_restart_between_cycles = 1250;
  loop_apply_state.loop_pin[3].number_of_cycles = 1000;
  loop_apply_state.loop_pin[3].state = 0 ;
  

 loop_apply_state.loop_state = LOOP_STATE_RUNNING;
}              

/******************************************************************************/

void loop_update(void)
{

  //hmi_led_turn_on(1);
  switch (loop_apply_state.loop_state)
  {
    case LOOP_STATE_INIT:
    
      break;

    case LOOP_STATE_RUNNING:


    loop_apply_update_state(0);
    loop_apply_update_state(1);
    loop_apply_update_state(2);
    loop_apply_update_state(3);

      break;
  
  default:
    break;
  }  
}            

/******************************************************************************/

void loop_deinit(void)
{


}

