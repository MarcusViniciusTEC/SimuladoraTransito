#ifndef __APP_TYPES_H__
#define __APP_TYPES_H__

/******************************************************************************/

#include "app_cfg.h"

/******************************************************************************/

//#define NUMBER_OF_LANES_MAX 2

#define TIME_ZERO 0


typedef enum
{
  AXLE_1 = 0U,
  AXLE_2,
  AXLE_3,
  AXLE_4,
  AXLE_5,
  AXLE_7,
  AXLE_8,
  AXLE_9,
  NUMBER_OF_AXLES_MAX
}axles_id_t;

typedef enum 
{
  LANE_INIT = 0,
  LANE_CALC,
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
  uint16_t velocity_kmh;
  uint16_t lenght;
  uint16_t gap_vehicle;
}lane_loop_data_t;


typedef struct 
{
  uint8_t     qnt;
  axles_id_t  axles_id_t;
  uint8_t     last_distance_axle[NUMBER_OF_AXLES_MAX]; 
}axles_data_t;

typedef struct
{
  uint16_t        axles[NUMBER_OF_AXLES_MAX];
  uint8_t         weight_ton;
  uint16_t        velocity_kmh;
  uint16_t        lenght_mts;
  uint16_t        gap;
  uint8_t         state;
  dually_weels_state_t duallyweels_state;
}traffic_data_t;

typedef struct 
{
  traffic_data_t lane[NUMBER_OF_LANES];
  uint8_t state;
}traffic_t;

typedef struct 
{
  lane_state_t state;
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
