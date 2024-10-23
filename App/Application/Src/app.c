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

/******************************************************************************/


void app_set_address_and_mode (uint8_t addres, uint8_t mode)
{



}


uint16_t ms_for_khm(uint16_t khm, uint16_t ms)
{
    //teste
}

lane_loop_state_t lane_loop_state = UPDATE_LOOP_INIT;

static uint8_t get_state = 0;
void calculate_traffic_paramters(uint8_t lane_index, traffic_mode_t mode)
{   
    

    loop_pin_data_t loop_enter[NUMBER_OF_LANES];/*enter*/
    loop_pin_data_t loop_exit [NUMBER_OF_LANES];/*exit*/
    static calc_traffic_t calc_traffic;

    calc_traffic.lane[lane_index].time_between_rising_edge_loops    = ((DISTANCE_BETWEEN_LOOPS_MTS + LENGHT_LOOP)/(traffic_update.lane[lane_index].velocity_kmh/3.6/*km/h for ms*/))*1000;
    calc_traffic.lane[lane_index].period_turn_on_channel            = traffic_update.lane[lane_index].lenght_max *(77+5);
    calc_traffic.lane[lane_index].time_gap_enter                    = traffic_update.lane[lane_index].gap;
    calc_traffic.lane[lane_index].time_gap_exit                     = traffic_update.lane[lane_index].gap - calc_traffic.lane[lane_index].time_between_rising_edge_loops;

    switch (lane_loop_state)
    {
    case UPDATE_LOOP_INIT:

    //sl_critical_assign(lane_index, lane_index);
    
    loop_enter[lane_index].loop_delay_init              = TIME_ZERO;
    loop_enter[lane_index].loop_period_turn_on          = calc_traffic.lane[lane_index].period_turn_on_channel;
    loop_enter[lane_index].time_restart_between_cycles  = calc_traffic.lane[lane_index].time_gap_enter;
    loop_enter[lane_index].number_of_cycles             = 1;
    loop_enter[lane_index].state                        = 0;

    loop_exit [lane_index].loop_delay_init              = calc_traffic.lane[lane_index].time_between_rising_edge_loops;
    loop_exit [lane_index].loop_period_turn_on          = calc_traffic.lane[lane_index].period_turn_on_channel;
    loop_exit [lane_index].time_restart_between_cycles  = calc_traffic.lane[lane_index].time_gap_exit ;
    loop_exit [lane_index].number_of_cycles             = 1;
    loop_exit [lane_index].state                        = 0;  
 
    

    
    get_state = loop_group_received_parameters(lane_index, loop_enter[lane_index], loop_exit[lane_index]);

    lane_loop_state = UPDATE_LOOP_START;

        break;
    case UPDATE_LOOP_START:
    
   

    if(get_state == LOOP_CYCLE_SUCESS) 
    {
        hmi_led_turn_on(5);
    }

        
         
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
    // traffic_update.lane[0].gap = 1000;
    // traffic_update.lane[0].lenght_max = 6;
    // traffic_update.lane[0].qtn_axles = 5;
    // traffic_update.lane[0].velocity_kmh =100;

    // traffic_update.lane[1].gap = 1000;
    // traffic_update.lane[1].lenght_max = 2;
    // traffic_update.lane[1].qtn_axles = 5;
    // traffic_update.lane[1].velocity_kmh =59;
}

/******************************************************************************/

void app_update(void)
{
static uint8_t teste= 0;

    traffic_update.lane[0].gap = 1000;
    traffic_update.lane[0].lenght_max = 6;
    traffic_update.lane[0].qtn_axles = 5;
    traffic_update.lane[0].velocity_kmh =100;

    calculate_traffic_paramters(0, 0);

   if (get_state == LOOP_CYCLE_SUCESS) 
   {
        lane_loop_state = UPDATE_LOOP_INIT;
   }
    // static uint8_t update = 0; 

    // switch (teste)
    // {
    // case 0:
    // traffic_update.lane[0].gap = 1000;
    // traffic_update.lane[0].lenght_max = 6;
    // traffic_update.lane[0].qtn_axles = 5;
    // traffic_update.lane[0].velocity_kmh =100;

    // teste = 1;
    //     break;
    // case 1:

    // traffic_update.lane[0].gap = 1000;
    // traffic_update.lane[0].lenght_max = 2;
    // traffic_update.lane[0].qtn_axles = 5;
    // traffic_update.lane[0].velocity_kmh =59;

    // calculate_traffic_paramters(0, 0);
    // lane_loop_state = UPDATE_LOOP_INIT;

    // teste = 2;

    // break;

    // case 2:

    // break;

    // default:
    //     break;
    // }


    
}

/******************************************************************************/

void app_deinit(void)
{

}

/******************************************************************************/
