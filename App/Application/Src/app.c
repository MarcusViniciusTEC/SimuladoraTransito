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

piezo_pin_data_t app_send_data_piezo;
//loop_pin_data_t app_send_data_loop;

//lane_loop_update_t app_lane_loop_update;

traffic_update_t traffic_update;
calc_traffic_t calc_traffic;


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
    calc_traffic_t calc_traffic;

    calc_traffic.lane[lane_index].time_between_rising_edge_loops    = ((DISTANCE_BETWEEN_LOOPS_MTS + LENGHT_LOOP)/(traffic_update.lane[lane_index].velocity_kmh/3.6/*km/h for ms*/))*1000;
    calc_traffic.lane[lane_index].period_turn_on_channel            = traffic_update.lane[lane_index].lenght_max *(77+5);
    calc_traffic.lane[lane_index].time_gap_enter                    = traffic_update.lane[lane_index].gap;
    calc_traffic.lane[lane_index].time_gap_exit                     = traffic_update.lane[lane_index].gap - calc_traffic.lane[lane_index].time_between_rising_edge_loops;
    
    switch (lane_state)
    {
    case LANE_INIT:
        lane_state = LANE_START;  
        break;
    case LANE_START:
        loop_enter[lane_index].loop_delay_init              = calc_traffic.lane[lane_index].time_between_rising_edge_loops - calc_traffic.lane[lane_index].time_between_rising_edge_loops;
        loop_enter[lane_index].loop_period_turn_on          = calc_traffic.lane[lane_index].period_turn_on_channel;
        loop_enter[lane_index].time_restart_between_cycles  = calc_traffic.lane[lane_index].time_gap_enter;
        loop_enter[lane_index].number_of_cycles             = 1;
        loop_enter[lane_index].state                        = 0;

        loop_exit [lane_index].loop_delay_init              = calc_traffic.lane[lane_index].time_between_rising_edge_loops;
        loop_exit [lane_index].loop_period_turn_on          = calc_traffic.lane[lane_index].period_turn_on_channel;
        loop_exit [lane_index].time_restart_between_cycles  = calc_traffic.lane[lane_index].time_gap_exit ;
        loop_exit [lane_index].number_of_cycles             = 1;
        loop_exit [lane_index].state                        = 0;  

        lane_state = LANE_SEND_PARAMETERS;
        break;
    case LANE_SEND_PARAMETERS:

        loop_group_received_parameters(lane_index, loop_enter[lane_index], loop_exit [lane_index]); 
        lane_state = LANE_RECEIVED_STATUS;

        break;
        case LANE_RECEIVED_STATUS:

        lane_state = LANE_INIT;
        return LANE_STATE_SUCESS;
        break;
    case LANE_STATE_SUCESS:
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
    // traffic_update.lane[0].gap = 1000;
    // traffic_update.lane[0].lenght_max = 6;
    // traffic_update.lane[0].qtn_axles = 5;
    // traffic_update.lane[0].velocity_kmh =100;

    // traffic_update.lane[1].gap = 1000;
    // traffic_update.lane[1].lenght_max = 2;
    // traffic_update.lane[1].qtn_axles = 5;
    // traffic_update.lane[1].velocity_kmh =59;

    calc_traffic.state = LANE_INIT;
}

/******************************************************************************/


typedef enum 
{
    traffic_1 = 0,
    traffic_2,
}traffic_teste_t;

traffic_teste_t traffic_teste  = traffic_1;

void app_update(void)
{
    static uint8_t aux = 0;
    switch (traffic_teste)
    {
    case traffic_1:
        traffic_update.lane[0].gap = 1000;
        traffic_update.lane[0].lenght_max = 6;
        traffic_update.lane[0].qtn_axles = 5;
        traffic_update.lane[0].velocity_kmh =20;
        aux = calculate_traffic_paramters(0, 0);

        if(aux == LANE_STATE_SUCESS)
        {
            aux = 0;
            traffic_teste = traffic_2;
        }
        break;
    case traffic_2:
        traffic_update.lane[0].gap = 1000;
        traffic_update.lane[0].lenght_max = 6;
        traffic_update.lane[0].qtn_axles = 5;
        traffic_update.lane[0].velocity_kmh =100;

        aux = calculate_traffic_paramters(0, 0);
        if(aux == LANE_STATE_SUCESS)
        {
            aux = 0;
            traffic_teste = traffic_1;
        }
        break;
    default:
        break;
    }


    
}

/******************************************************************************/

void app_deinit(void)
{

}

/******************************************************************************/
