#ifndef __PIEZO_TYPES_H__
#define __PIEZO_TYPES_H__


#include "piezo_cfg.h"
/******************************************************************************/

#define LED_PIEZO_AXILE_CONV_CH1      1
#define LED_PIEZO_AXILE_CONV_CH2      4

#define LED_PIEZO_AXILE_PE_CH1        1
#define LED_PIEZO_AXILE_PE_CH2        3

#define LED_PIEZO_DUALLYWEELS_CH1     4
#define LED_PIEZO_DUALLYWEELS_CH2     5

/******************************************************************************/

typedef struct
{
  GPIO_TypeDef *GPIO;
      uint32_t  PinMask;
} piezo_pininfo_t;

/******************************************************************************/

typedef enum
{
  PIEZO_STATE_INIT = 0,
  PIEZO_STATE_RUNNING,
  PIEZO_NUMBER_OF_STATES

}piezo_data_t;

/******************************************************************************/

typedef enum
{
  PIEZO_AXILES_CH1 = 0,
  PIEZO_AXILES_CH2,
  PIEZO_DUALLYWEELS_CH1,
  PIEZO_DUALLYWEELS_CH2,
  PIEZO_NUMBER_OF_CHANNELS,
  PEIZO_DUALLYWEELS_NUMBER_OF_CHANNELS,
  PIEZO_AXILES_NUMBER_OF_CHANNEL
}piezo_channes_t;

/******************************************************************************/

typedef enum 
{
  PIEZO_MODE_PE = 0,
  PIEZO_MODE_CONV
}piezo_mode_t;

/******************************************************************************/

typedef enum
{
  PIEZO_UPDATE_STATE_INIT = 0,
  PIEZO_UPDATE_GET_DELAY,
  PIEZO_UPDATE_STATE_START,
  PIEZO_UPDATE_NUMBER_OF_CYCLES,
  PIEZO_UPDATE_DELAY_INIT,
  PIEZO_UPDATE_RUNNING,
  PIEZO_UPDATE_TURN_ON,
  PIEZO_UPDATE_PERIOD,
  PIEZO_UPDATE_TURN_OFF,
  PIEZO_UPDATE_TIME,
  PIEZO_UPDATE_DELAY_RESTART_BETWEEN_CYCLES,
  PIEZO_UPDATE_STATE_SUCESS
}piezo_state_update_t;

/******************************************************************************/

typedef struct
{
  piezo_mode_t piezo_mode;
  piezo_state_update_t state;
  uint32_t time_restart_between_cycles;
  uint32_t last_time_restart_between_cycles;
  uint32_t delay_init;
  uint32_t last_delay_init;
  uint32_t period_turn_on;
  uint32_t last_period_turn_on;
  uint16_t number_of_cycles;

}piezo_pin_data_t;

/******************************************************************************/

typedef struct
{
  piezo_pin_data_t piezo_pin[PIEZO_NUMBER_OF_CHANNELS]; 
  piezo_data_t loop_state;

}piezo_apply_state_t;

/******************************************************************************/

#endif