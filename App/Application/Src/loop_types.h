#ifndef __LOOP_TYPES_H__
#define __LOOP_TYPES_H__


#include "loop_cfg.h"

#define LOOP_LED_LOOP_0                         0
#define LOOP_LED_LOOP_1                         2
#define LOOP_LED_LOOP_2                         3
#define LOOP_LED_LOOP_3                         5

#define DISTANCE_BETWEEN_LOOPS_MTS              1
#define LENGHT_LOOP_MTS                         2

typedef enum
{
  LOOP_AUTO_RESTART_OFF = 0,
  LOOP_AUTO_RESTART_ON
} loop_auto_restart_t;

typedef enum
{
  LOOP_GROUP_CYCLE_RUNNING = 0,
  LOOP_GROUP_CYCLE_SUCESS
}loop_state_cycles_t;

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
  LOOP_GROUP_0 = 0,
  LOOP_GROUP_1,
  NUMBER_OF_GROUPS
}loop_groups_t;

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
  LOOP_UPDATE_STATE_SUCESS,
  LOOP_UPTATE_STATE_STANDBY
}loop_state_update_t;

typedef struct
{
  uint16_t loop_delay_init;
  uint16_t loop_period_turn_on;
  uint16_t time_restart_between_cycles;
  uint8_t number_of_cycles;
  loop_state_update_t state;
}loop_pin_data_t;

typedef struct
{
  loop_pin_data_t loop_pin[LOOP_NUMBER_OF_OUTPUTS]; 
  loop_data_t loop_state;
}loop_apply_state_t;


#endif