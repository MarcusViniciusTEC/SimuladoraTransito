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

static traffic_update_t traffic_update;
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

    calc_traffic.lane[lane_index].time_between_rising_edge_loops    = ((DISTANCE_BETWEEN_LOOPS_MTS + LENGHT_LOOP_MTS)/(traffic_update.lane[lane_index].velocity_kmh/3.6/*km/h for ms*/))*1000;
    calc_traffic.lane[lane_index].period_turn_on_channel            = traffic_update.lane[lane_index].lenght_max *(77+5);
    calc_traffic.lane[lane_index].time_gap_enter                    = traffic_update.lane[lane_index].gap;
    calc_traffic.lane[lane_index].time_gap_exit                     = traffic_update.lane[lane_index].gap - calc_traffic.lane[lane_index].time_between_rising_edge_loops;
    
    switch (calc_traffic.lane[lane_index].state)
    {
    case LANE_INIT:
        calc_traffic.lane[lane_index].state = LANE_START;  
        break;
    case LANE_START:
        loop_enter[lane_index].loop_delay_init              = calc_traffic.lane[lane_index].time_between_rising_edge_loops - calc_traffic.lane[lane_index].time_between_rising_edge_loops;
        loop_enter[lane_index].loop_period_turn_on          = calc_traffic.lane[lane_index].period_turn_on_channel;
        loop_enter[lane_index].time_restart_between_cycles  = calc_traffic.lane[lane_index].time_gap_enter;

        loop_exit [lane_index].loop_delay_init              = calc_traffic.lane[lane_index].time_between_rising_edge_loops;
        loop_exit [lane_index].loop_period_turn_on          = calc_traffic.lane[lane_index].period_turn_on_channel;
        loop_exit [lane_index].time_restart_between_cycles  = calc_traffic.lane[lane_index].time_gap_exit ;

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
    calc_traffic.lane[0].state = LANE_INIT;
    calc_traffic.lane[1].state = LANE_INIT;           
}

/******************************************************************************/

typedef enum 
{
    traffic_1 = 0,
    traffic_2,
    traffic_3
}traffic_teste_t;

traffic_teste_t traffic_teste  = traffic_1;

void app_update(void)
{
    static uint8_t aux0 = 0;
    static uint8_t aux1 = 0;

    switch (traffic_teste)
    {
    case traffic_1:

        traffic_update.lane[0].gap = 1000;
        traffic_update.lane[0].lenght_max = 6;
        traffic_update.lane[0].qtn_axles = 5;
        traffic_update.lane[0].velocity_kmh =20;

        traffic_update.lane[1].gap = 1000;
        traffic_update.lane[1].lenght_max = 6;
        traffic_update.lane[1].qtn_axles = 5;
        traffic_update.lane[1].velocity_kmh =20;

        aux0 = calculate_traffic_paramters(0, 0);
        aux1 = calculate_traffic_paramters(1, 0);

        if(aux0 == LANE_STATE_SUCESS && aux1 == LANE_STATE_SUCESS)
        {
            traffic_teste = traffic_2;
        }

        break;
    case traffic_2:

        traffic_update.lane[0].gap = 1000;
        traffic_update.lane[0].lenght_max = 6;
        traffic_update.lane[0].qtn_axles = 5;
        traffic_update.lane[0].velocity_kmh =100;

        traffic_update.lane[1].gap = 1000;
        traffic_update.lane[1].lenght_max = 6;
        traffic_update.lane[1].qtn_axles = 5;
        traffic_update.lane[1].velocity_kmh =100;

        aux0 = calculate_traffic_paramters(0, 0);
        aux1 = calculate_traffic_paramters(1, 0);

        if(aux0 == LANE_STATE_SUCESS && aux1 == LANE_STATE_SUCESS)
        {
            traffic_teste = traffic_3;
        }
        break;
    case traffic_3:

        traffic_update.lane[0].gap = 1000;
        traffic_update.lane[0].lenght_max = 6;
        traffic_update.lane[0].qtn_axles = 5;
        traffic_update.lane[0].velocity_kmh =50;

        traffic_update.lane[1].gap = 1000;
        traffic_update.lane[1].lenght_max = 6;
        traffic_update.lane[1].qtn_axles = 5;
        traffic_update.lane[1].velocity_kmh =50;

        aux0 = calculate_traffic_paramters(0, 0);
        aux1 = calculate_traffic_paramters(1, 0);

        if(aux0 == LANE_STATE_SUCESS && aux1 == LANE_STATE_SUCESS)
        {
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
