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

lane_loop_update_t app_lane_loop_update;

/******************************************************************************/


void app_set_address_and_mode (uint8_t addres, uint8_t mode)
{



}


uint16_t ms_for_khm(uint16_t khm, uint16_t ms)
{

}

lane_loop_state_t lane_loop_state = UPDATE_LOOP_INIT;;




void calculate_traffic_paramters(uint8_t lane_index)
{   
    static loop_pin_data_t loop_pin_input;/*enter*/
    static loop_pin_data_t loop_pin_output;/*exit*/

    static uint32_t time_between_rising_edge_loops =0 ;
    static uint32_t period_turn_on_channel =0 ;
    static uint32_t time_gap_loop_in =0 ;
    static uint32_t time_gap_loop_out=0;

    time_between_rising_edge_loops = ((DISTANCE_BETWEEN_LOOPS_MTS + LENGHT_LOOP)/(app_lane_loop_update.lane_loop[lane_index].velocity_kmh/3.6/*km/h for ms*/))*1000;
    period_turn_on_channel = app_lane_loop_update.lane_loop[lane_index].lenght *(77+5);

    time_gap_loop_in = app_lane_loop_update.lane_loop[lane_index].gap_vehicle;
    time_gap_loop_out = app_lane_loop_update.lane_loop[lane_index].gap_vehicle - time_between_rising_edge_loops;

    switch (lane_loop_state)
    {
    case UPDATE_LOOP_INIT:

        loop_pin_input.loop_delay_init = time_between_rising_edge_loops - time_between_rising_edge_loops;
        loop_pin_input.loop_period_turn_on = period_turn_on_channel;
        loop_pin_input.time_restart_between_cycles = time_gap_loop_in;
        loop_pin_input.number_of_cycles = 1000;
        loop_pin_input.state = 0;

        loop_pin_output.loop_delay_init = time_between_rising_edge_loops;
        loop_pin_output.loop_period_turn_on = period_turn_on_channel;
        loop_pin_output.time_restart_between_cycles = time_gap_loop_out;
        loop_pin_output.number_of_cycles = 1000;
        loop_pin_output.state = 0;

        loop_group_received_parameters(0, loop_pin_input, loop_pin_output);

        lane_loop_state = UPDATE_LOOP_START;

        break;
    case UPDATE_LOOP_START:



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
    if(LL_GPIO_IsInputPinSet(APP_ID_BIT3_GPIO_PORT, APP_ID_BIT3_GPIO_PIN) == KEY_ON)
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
    app_lane_loop_update.lane_loop[1].gap_vehicle = 1000;
    app_lane_loop_update.lane_loop[1].lenght = 6;
    app_lane_loop_update.lane_loop[1].velocity_kmh =70;
}

/******************************************************************************/

void app_update(void)
{
    calculate_traffic_paramters(1);
}

/******************************************************************************/

void app_deinit(void)
{

}

/******************************************************************************/
