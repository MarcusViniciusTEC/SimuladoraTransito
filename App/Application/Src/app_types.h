#ifndef __APP_TYPES_H__
#define __APP_TYPES_H__

/******************************************************************************/

#include "app_cfg.h"

/******************************************************************************/

//#define NUMBER_OF_LANES_MAX 2

#define TIME_ZERO 0

#define NUMBER_OF_TYPES_VEHICLE  11
#define NUMBER_OF_MAX_AXLES       9

typedef enum 
{
  LANE_INIT = 0,
  LANE_START,
  LANE_SEND_PARAMETERS,
  LANE_RECEIVED_STATUS,
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
  uint16_t last_distance_axles;
}axles_t;

typedef struct 
{
  uint16_t lengh;
  uint8_t  total_axles;
  axles_t  axles[NUMBER_OF_MAX_AXLES];
}vehicle_t;

typedef struct 
{
  dually_weels_state_t  state;
  uint16_t              velocity;
  vehicle_t             vehicle [NUMBER_OF_TYPES_VEHICLE];
  uint16_t              gap     [NUMBER_OF_TYPES_VEHICLE];
}traffic_update_t;


typedef struct 
{
  lane_state_t state;
  uint16_t velocity_khh;
  uint16_t time_between_rising_edge_loops;
  uint16_t period_turn_on_channel;
  uint16_t time_gap_enter;
  uint16_t time_gap_exit;
}calc_traffic_data_t;

typedef struct 
{
  calc_traffic_data_t lane[NUMBER_OF_LANES];
  lane_state_t state;
}calc_traffic_t;





/******************************************************************************/


/******************************************************************************/


/******************************************************************************/


/******************************************************************************/

#endif/*__APP_TYPES_H__*/
