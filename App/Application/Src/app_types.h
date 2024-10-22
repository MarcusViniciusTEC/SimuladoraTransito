#ifndef __APP_TYPES_H__
#define __APP_TYPES_H__

/******************************************************************************/

#include "app_cfg.h"

/******************************************************************************/

//#define NUMBER_OF_LANES_MAX 2

#define TIME_ZERO 0

typedef enum 
{
  LANE_INIT = 0,
  LANE_START,
  LANE_SEND_PARAMETERS,
  LANE_STATE_SUCESS,
}lane_state_t;

typedef enum
{
  LANE_1 = 0,
  LANE_2,
  NUMBER_OF_LANES
}number_of_lanes_t;

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
  uint16_t velocity_kmh;
  uint16_t lenght;
  uint16_t gap_vehicle;
}lane_loop_data_t;

typedef struct
{
  uint32_t distance_between_axles;
  uint8_t qtn_axles;
  uint16_t velocity_kmh;
  uint16_t lenght_max;
  uint16_t gap;
  uint8_t state;
  dually_weels_state_t duallyweels_state;
}traffic_data_t;

typedef struct 
{
  traffic_data_t lane[NUMBER_OF_LANES];
  uint8_t state;
}traffic_update_t;


typedef struct 
{
  lane_state_t state;
  uint16_t velocity_khh;
  uint16_t time_between_rising_edge_loops;
  uint16_t period_turn_on_channel;
  uint16_t time_gap_enter;
  uint16_t time_gap_exit;
}traffic_calc_t;

typedef struct 
{
  traffic_calc_t lane[NUMBER_OF_LANES];
}calc_traffic_t;





/******************************************************************************/


/******************************************************************************/


/******************************************************************************/


/******************************************************************************/

#endif/*__APP_TYPES_H__*/
