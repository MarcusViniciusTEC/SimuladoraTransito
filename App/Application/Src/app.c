#include "sl.h"
#include "app.h"
#include "app_cfg.h"

/******************************************************************************/

//#include "mb.h"
//#include "adc1.h"
//#include "wdt.h"
//#include "tmp.h"
//#include "din.h"
//#include "dout.h"
#include "hmi.h"
#include "loop.h"
#include "piezo.h"
//#include "wlog.h"

/******************************************************************************/

//#include "gpio.h"

/******************************************************************************/

volatile uint32_t app_execution_rate_1ms_timer;

/******************************************************************************/


static traffic_update_t traffic_update[NUMBER_OF_SIMULATION];
static calc_traffic_t calc_traffic;


/******************************************************************************/

lane_state_t lane_state = LANE_INIT;

void app_set_address_and_mode (uint8_t addres, uint8_t mode)
{



}


uint16_t ms_for_khm(uint16_t khm, uint16_t ms)
{

}



uint8_t calculate_traffic_paramters(uint8_t lane_index, traffic_mode_t mode)
{   
    static loop_pin_data_t loop_enter[NUMBER_OF_LANES];/*enter*/
    static loop_pin_data_t loop_exit [NUMBER_OF_LANES];/*exit*/



    switch (calc_traffic.lane[lane_index].state)
    {
    case LANE_INIT:
        calc_traffic.lane[lane_index].state = LANE_START;  
        break;
    case LANE_START:

        calc_traffic.lane[lane_index].state = LANE_SEND_PARAMETERS;
        break;
    case LANE_SEND_PARAMETERS:
        uint8_t aux[NUMBER_OF_LANES] = {0};

        aux[lane_index] = loop_group_received_parameters(lane_index, loop_enter[lane_index], loop_exit [lane_index]); 
        if(aux[lane_index] == LOOP_GROUP_CYCLE_SUCESS)
        {
            calc_traffic.lane[lane_index].state = LANE_STATE_SUCESS;
        }
        break;
    case LANE_STATE_SUCESS:
        calc_traffic.lane[lane_index].state = LANE_INIT;
        return LANE_STATE_SUCESS;
        break; 
    default:
        break;
    }

 }



void traffic_lane_loop_update_state(uint8_t lane_index, uint8_t loop_pin_index)
{

}


void update_state_loop()
{

}


void app_read_address_and_mode(void)
{
    uint8_t address =0; 
    uint8_t mode = 0;
    if(LL_GPIO_IsInputPinSet(APP_ID_MODE_GPIO_PORT, APP_ID_MODE_GPIO_PIN) == MODE_PE)
    {
       mode = MODE_PE;
    }
    else 
    {
        mode = MODE_CONV;
    }
    if(LL_GPIO_IsInputPinSet(APP_ID_BIT1_GPIO_PORT, APP_ID_BIT1_GPIO_PIN) == KEY_OFF)
    {
        address |= (1 << 0);
    }
    if(LL_GPIO_IsInputPinSet(APP_ID_BIT2_GPIO_PORT, APP_ID_BIT2_GPIO_PIN) == KEY_OFF)
    {
        address |= (1 << 1);
    }
    if(LL_GPIO_IsInputPinSet(APP_ID_BIT3_GPIO_PORT, APP_ID_BIT3_GPIO_PIN) == KEY_OFF)
    {
        address |= (1 << 2);
    }
    app_set_address_and_mode(address, mode);
}


/******************************************************************************/


/******************************************************************************/

void app_1ms_clock(void)
{

}

/******************************************************************************/

void app_init(void)
{
        for (uint16_t index_traffic = 0; index_traffic < NUMBER_OF_SIMULATION; index_traffic++)
    {
        traffic_update[index_traffic].velocity_khm  = 40;

        for(uint8_t index_gap = 0; index_gap < NUMBER_OF_TYPES_VEHICLE; index_gap ++)
        {
            traffic_update[index_traffic].gap[index_gap] = 20;
        }

        for (uint8_t index_vehicle = 0; index_vehicle < NUMBER_OF_TYPES_VEHICLE; index_vehicle++)
        {
            traffic_update[index_traffic].vehicle[index_vehicle].lengh_mts = 20;
            traffic_update[index_traffic].vehicle[index_vehicle].axles_init_distance_mts = 20;
            traffic_update[index_traffic].vehicle[index_vehicle].axles_end_distance_mts = 20;
            traffic_update[index_traffic].vehicle[index_vehicle].total_axles = 6;

            for(uint8_t index_axles = 0; index_axles <= NUMBER_OF_MAX_AXLES; index_axles++)
            {
                traffic_update[index_traffic].vehicle[index_vehicle].axles->last_distance_axles_mts[index_axles] = 2;
            }
        }
        
    }
    

}

/******************************************************************************/

/// traffic_update.lane[0].velocity_kmh =50;

// typedef enum 
// {
//     traffic_1 = 0,
//     traffic_2,
//     traffic_3
// }traffic_teste_t;

// traffic_teste_t traffic_teste  = traffic_1;

void app_update(void)
{


 
}

/******************************************************************************/

void app_deinit(void)
{

}

/******************************************************************************/

