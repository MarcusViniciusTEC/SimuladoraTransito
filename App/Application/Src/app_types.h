#ifndef __APP_TYPES_H__
#define __APP_TYPES_H__

/******************************************************************************/

#include "app_cfg.h"

/******************************************************************************/

#define NUMBER_OF_LANES_MAX 2

typedef enum 
{
  UPDATE_LOOP_INIT = 0,
  UPDATE_LOOP_START,
  UPDATE_LOOP_SEND_PARAMETERS,
  UPDATE_LOOP_STATE_SUCESS,
}lane_loop_state_t;

typedef struct 
{
  lane_loop_state_t state;
  uint16_t velocity_kmh;
  uint16_t lenght;
  uint16_t gap_vehicle;
}lane_loop_data_t;



typedef enum
{
  KEY_ON = 0,
  KEY_OFF
}key_state_t;

typedef enum
{
  MODE_PE = 0,
  MODE_CONV
}traffic_mode_t;

typedef enum
{
  DUALLYWEELS_ON = 0,
  DUALLYWEELS_OFF
}dually_weels_state_t;

typedef struct
{
  uint32_t distance_between_axles;
  uint32_t qtn_axles;
  uint16_t velocity_kmh;
  uint16_t lenght_max;
  uint16_t gap;
  lane_loop_state_t state;
  dually_weels_state_t duallyweels_state;
}traffic_data_t;

typedef struct 
{
  traffic_data_t lane[NUMBER_OF_LANES_MAX];
  uint8_t state;
}traffic_update_t;


typedef struct 
{
 uint16_t calc_velocity_khh;
 uint16_t time_between_rising_edge_loops;
 uint16_t period_turn_on_channel;
 uint16_t time_gap_enter;
 uint16_t time_gap_exit;

}traffic_calc_t;




/******************************************************************************/


/******************************************************************************/


/******************************************************************************/


/******************************************************************************/

#endif/*__APP_TYPES_H__*/
