#include "sl.h"
#include "piezo.h"
#include "piezo_cfg.h"
#include "hmi.h"

/******************************************************************************/

volatile uint32_t piezo_execution_rate_1ms_timer;

static const piezo_pininfo_t piezo_pininfo_vector[PIEZO_NUMBER_OF_CHANNELS] = piezo_pininfo_vector_default_value;
piezo_apply_state_t piezo_apply_state;

/******************************************************************************/

void piezo_turn_on(uint8_t index)
{
    piezo_pininfo_t piezo_pininfo;
    piezo_pininfo = piezo_pininfo_vector[index];
    LL_GPIO_SetOutputPin(piezo_pininfo.GPIO, piezo_pininfo.PinMask);
}

/******************************************************************************/

void piezo_turn_off(uint8_t index)
{
    piezo_pininfo_t piezo_pininfo;
    piezo_pininfo = piezo_pininfo_vector[index];
    LL_GPIO_ResetOutputPin(piezo_pininfo.GPIO, piezo_pininfo.PinMask);
}

/******************************************************************************/

static void piezo_init_pin(void)
{
    for(uint8_t piezo_index = 0; piezo_index < PIEZO_NUMBER_OF_CHANNELS; piezo_index ++)
    {
        piezo_turn_off(piezo_index);
    }
}

/******************************************************************************/

static void piezo_1ms_period(void)
{
    for(uint8_t piezo_index = 0; piezo_index < PIEZO_NUMBER_OF_CHANNELS; piezo_index++)
    {
        if(piezo_apply_state.piezo_pin[piezo_index].period_turn_on > 0 && piezo_apply_state.piezo_pin[piezo_index].state == PIEZO_UPDATE_PERIOD)
        {
            piezo_apply_state.piezo_pin[piezo_index].period_turn_on--;
        }
    }
}

/******************************************************************************/

static void piezo_1ms_delay_init(void)
{
    for(uint8_t piezo_index = 0; piezo_index < PIEZO_NUMBER_OF_CHANNELS; piezo_index++)
    {
        if(piezo_apply_state.piezo_pin[piezo_index].delay_init > 0 && piezo_apply_state.piezo_pin[piezo_index].state == PIEZO_UPDATE_DELAY_INIT)
        {
            piezo_apply_state.piezo_pin[piezo_index].delay_init--;
        }
    }
}

/******************************************************************************/

static void piezo_1ms_delay_restart(void)
{
    for(uint8_t piezo_index = 0; piezo_index < PIEZO_NUMBER_OF_CHANNELS; piezo_index++)
    {
        if((piezo_apply_state.piezo_pin[piezo_index].time_restart_between_cycles > 0) 
        && (piezo_apply_state.piezo_pin[piezo_index].state == PIEZO_UPDATE_DELAY_RESTART_BETWEEN_CYCLES))
        {
            piezo_apply_state.piezo_pin[piezo_index].time_restart_between_cycles--;
        }
    }
}

/******************************************************************************/

void piezo_received_parameters(uint8_t pin_index, piezo_pin_data_t piezo_pin_data_par, piezo_mode_t piezo_mode_par)
{
    piezo_apply_state.piezo_pin[pin_index].delay_init = piezo_pin_data_par.delay_init;
    piezo_apply_state.piezo_pin[pin_index].period_turn_on = piezo_pin_data_par.period_turn_on;
    piezo_apply_state.piezo_pin[pin_index].time_restart_between_cycles = piezo_pin_data_par.time_restart_between_cycles;
    piezo_apply_state.piezo_pin[pin_index].number_of_cycles = piezo_pin_data_par.number_of_cycles;
    piezo_apply_state.piezo_pin[pin_index].state = 0;
}

/******************************************************************************/

uint8_t control_led_piezo(uint8_t piezo_index, piezo_mode_t piezo_mode)
{
    switch (piezo_index)
    {
    case PIEZO_AXILES_CH1:
        if(piezo_mode == PIEZO_MODE_PE)
        {
            return LED_PIEZO_AXILE_PE_CH1;
        }
        else if (piezo_mode == PIEZO_MODE_CONV)
        {
            return LED_PIEZO_AXILE_CONV_CH1;
        }
        break;
    case PIEZO_AXILES_CH2:
        if(piezo_mode == PIEZO_MODE_PE)
        {
            return LED_PIEZO_AXILE_PE_CH2;
        }
        else if (piezo_mode == PIEZO_MODE_CONV)
        {
            return LED_PIEZO_AXILE_CONV_CH2;
        }
        break;
    case PIEZO_DUALLYWEELS_CH1:
        if(piezo_mode == PIEZO_MODE_PE || piezo_mode == PIEZO_MODE_CONV)
        {
            return LED_PIEZO_DUALLYWEELS_CH1;
        }
        break;
    case PIEZO_DUALLYWEELS_CH2:    
        if(piezo_mode == PIEZO_MODE_PE || piezo_mode == PIEZO_MODE_CONV)
        {
            return LED_PIEZO_DUALLYWEELS_CH2;
        }
        break;
    default:
        break;
    }
}

/******************************************************************************/

void piezo_update_parameters(uint8_t pin_index, piezo_mode_t piezo_mode)
{
    switch (piezo_apply_state.piezo_pin[pin_index].state)
   { 
    case PIEZO_STATE_INIT:
      piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_GET_DELAY; 
      break;
    case  PIEZO_UPDATE_GET_DELAY :
      piezo_apply_state.piezo_pin[pin_index].last_delay_init = piezo_apply_state.piezo_pin[pin_index].delay_init;
      piezo_apply_state.piezo_pin[pin_index].last_period_turn_on = piezo_apply_state.piezo_pin[pin_index].period_turn_on;
      piezo_apply_state.piezo_pin[pin_index].last_time_restart_between_cycles = piezo_apply_state.piezo_pin[pin_index].time_restart_between_cycles;
      piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_STATE_START; 
      break;
    case PIEZO_UPDATE_STATE_START:
      if(piezo_apply_state.piezo_pin[pin_index].state == PIEZO_UPDATE_STATE_START) 
      {
        piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_NUMBER_OF_CYCLES; 
      }
      else 
      {
        piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_STATE_INIT; 
      }
      break;
    case PIEZO_UPDATE_NUMBER_OF_CYCLES:
      if(piezo_apply_state.piezo_pin[pin_index].number_of_cycles > 0)
      {
        piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_RUNNING;
      }
      else
      {
        piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_STATE_INIT;
      }
      break;
    case PIEZO_UPDATE_RUNNING:
      if(piezo_apply_state.piezo_pin[pin_index].delay_init > 0)
      {
        piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_DELAY_INIT;
      }
      else
      {
        piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_TURN_ON;
      }
      break;
    case  PIEZO_UPDATE_DELAY_INIT:
      if(piezo_apply_state.piezo_pin[pin_index].delay_init == 0)
      {
        piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_TURN_ON;
      }
      break;
    case PIEZO_UPDATE_TURN_ON:
      piezo_turn_on(pin_index);
      hmi_led_turn_on(control_led_piezo(pin_index, piezo_mode));
      piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_PERIOD;
      break;
    case PIEZO_UPDATE_PERIOD:
      if(piezo_apply_state.piezo_pin[pin_index].period_turn_on == 0)
      {        
        piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_TURN_OFF;
      }
      break;  
    case PIEZO_UPDATE_TURN_OFF:
      piezo_turn_off(pin_index);
      hmi_led_turn_off(control_led_piezo(pin_index, piezo_mode));
      piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_DELAY_RESTART_BETWEEN_CYCLES;
      break;
    case PIEZO_UPDATE_DELAY_RESTART_BETWEEN_CYCLES:

      if(piezo_apply_state.piezo_pin[pin_index].time_restart_between_cycles == 0)
      {
        piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_TIME;    
      }  
      break;
    case PIEZO_UPDATE_TIME:
      piezo_apply_state.piezo_pin[pin_index].number_of_cycles--;
      if(piezo_apply_state.piezo_pin[pin_index].number_of_cycles > 0)
      {
        piezo_apply_state.piezo_pin[pin_index].delay_init = piezo_apply_state.piezo_pin[pin_index].last_delay_init;
        piezo_apply_state.piezo_pin[pin_index].period_turn_on = piezo_apply_state.piezo_pin[pin_index].last_period_turn_on;
        piezo_apply_state.piezo_pin[pin_index].time_restart_between_cycles = piezo_apply_state.piezo_pin[pin_index].last_time_restart_between_cycles;  
        piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_STATE_SUCESS;
      } 
      else 
      {
        piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_STATE_SUCESS;
      }
      break;
    case PIEZO_UPDATE_STATE_SUCESS:
      piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_STATE_INIT;
      break;
    default :
      piezo_apply_state.piezo_pin[pin_index].state = PIEZO_UPDATE_STATE_INIT;
      break;
   }
}

/******************************************************************************/

void piezo_1ms_clock(void)
{
    piezo_1ms_delay_init();
    piezo_1ms_delay_restart();
    piezo_1ms_period();
}     

/******************************************************************************/

void piezo_init(void)
{
   // piezo_init_pin();
  piezo_apply_state.piezo_pin[0].delay_init = 0;
  piezo_apply_state.piezo_pin[0].period_turn_on = 3;
  piezo_apply_state.piezo_pin[0].time_restart_between_cycles = 50;
  piezo_apply_state.piezo_pin[0].number_of_cycles = 1000;
  piezo_apply_state.piezo_pin[0].state = 0 ;

  piezo_apply_state.piezo_pin[1].delay_init = 250;
  piezo_apply_state.piezo_pin[1].period_turn_on = 200;
  piezo_apply_state.piezo_pin[1].time_restart_between_cycles = 1250;
  piezo_apply_state.piezo_pin[1].number_of_cycles = 1000;
  piezo_apply_state.piezo_pin[1].state = 0 ;

  piezo_apply_state.piezo_pin[2].delay_init = 0;
  piezo_apply_state.piezo_pin[2].period_turn_on = 400;
  piezo_apply_state.piezo_pin[2].time_restart_between_cycles = 1000;
  piezo_apply_state.piezo_pin[2].number_of_cycles = 1000;
  piezo_apply_state.piezo_pin[2].state = 0 ;

  piezo_apply_state.piezo_pin[3].delay_init = 250;
  piezo_apply_state.piezo_pin[3].period_turn_on = 200;
  piezo_apply_state.piezo_pin[3].time_restart_between_cycles = 1250;
  piezo_apply_state.piezo_pin[3].number_of_cycles = 1000;
  piezo_apply_state.piezo_pin[3].state = 0 ;


}                  

/******************************************************************************/

void piezo_update(void)
{
   // piezo_update_parameters(0, PIEZO_MODE_PE);
    //piezo_update_parameters(1, PIEZO_MODE_PE);
   // piezo_update_parameters(2, PIEZO_MODE_PE);
   // piezo_update_parameters(3, PIEZO_MODE_PE);

    //hmi_led_turn_on(0);
}                

/******************************************************************************/

void piezo_deinit(void)
{

}