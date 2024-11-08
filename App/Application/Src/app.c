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

static traffic_t traffic;
//static calc_traffic_t calc_traffic;


/******************************************************************************/

lane_state_t lane_state = LANE_INIT;

void app_set_address_and_mode (uint8_t addres, uint8_t mode)
{



}


uint16_t ms_for_khm(uint16_t khm, uint16_t ms)
{

}

// necessario mudar calc

uint8_t calculate_traffic_paramters(uint8_t lane_index, traffic_mode_t mode)
{   
    static loop_pin_data_t loop_enter;
    static loop_pin_data_t loop_exit ;


    static piezo_pin_data_t piezo_enter;

    switch (traffic.lane[lane_index].state)
    {
    case LANE_INIT:
        traffic.lane[lane_index].state = LANE_CALC;  
        break;
    case LANE_CALC:

        uint16_t calc_velocity_kmh;
        calc_velocity_kmh = (((DISTANCE_BETWEEN_LOOPS_MTS + LENGHT_LOOP_MTS)/(traffic.lane[lane_index].velocity_kmh/3.6/*km/h for ms*/))*1000);

        loop_enter.loop_delay_init              = 0;
        loop_enter.loop_period_turn_on          = traffic.lane[lane_index].lenght_mts *(77+5);
        loop_enter.time_restart_between_cycles  = traffic.lane[lane_index].gap;

        loop_exit.loop_delay_init               = calc_velocity_kmh;
        loop_exit.loop_period_turn_on           = traffic.lane[lane_index].lenght_mts *(77+5);
        loop_exit.time_restart_between_cycles   = traffic.lane[lane_index].gap - (((DISTANCE_BETWEEN_LOOPS_MTS + LENGHT_LOOP_MTS)/(traffic.lane[lane_index].velocity_kmh/3.6/*km/h for ms*/))*1000);


        uint8_t buffer_size = sizeof(traffic.lane[lane_index].axles);

        static uint8_t index_axles = 0;

        piezo_enter.delay_init = ((calc_velocity_kmh *traffic.lane[lane_index].axles[0])/100);
        piezo_enter.period_turn_on = 20;
        piezo_enter.time_restart_between_cycles = 100;
        piezo_enter.number_of_cycles = 1;
        piezo_enter.state = 0;

        if(index_axles > buffer_size)
        {
            index_axles = 0;
        }

        piezo_group_received_parameters(0, piezo_enter, 0);



        traffic.lane[lane_index].state = LANE_SEND_PARAMETERS;
        break;
    case LANE_SEND_PARAMETERS:
        uint8_t aux[NUMBER_OF_LANES] = {0};
        aux[lane_index] = loop_group_received_parameters(lane_index, loop_enter, loop_exit); 
        if(aux[lane_index] == LOOP_GROUP_CYCLE_SUCESS)
        {
            traffic.lane[lane_index].state = LANE_STATE_SUCESS;
        }
        break;
    case LANE_STATE_SUCESS:
        traffic.lane[lane_index].state = LANE_INIT;
        return LANE_STATE_SUCESS;
        break; 
    default:
        break;
    }
}


void calculate_piezo(void)
{

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
    traffic.lane[0].state = LANE_INIT;
    traffic.lane[1].state = LANE_INIT;           
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

    static axles_data_t axles_truck;


    uint16_t vector_2axles [2] = {20, 80};

    switch (traffic_teste)
    {
    case traffic_1:

        traffic.lane[0].gap = 1000;
        traffic.lane[0].lenght_mts = 6;
        traffic.lane[0].axles[NUMBER_OF_AXLES_MAX] = vector_2axles;
        traffic.lane[0].velocity_kmh =50;

        traffic.lane[1].gap = 1000;                                              
        traffic.lane[1].lenght_mts = 6;                                          
        traffic.lane[1].velocity_kmh =50;                                        

        aux0 = calculate_traffic_paramters(0, 0);
        aux1 = calculate_traffic_paramters(1, 0);

        if(aux0 == LANE_STATE_SUCESS && aux1 == LANE_STATE_SUCESS)
        {
            traffic_teste = traffic_2;
        }

        break;
    case traffic_2:

        traffic.lane[0].gap = 1000;
        traffic.lane[0].lenght_mts= 6;
        traffic.lane[0].velocity_kmh =100;

        traffic.lane[1].gap = 1000;
        traffic.lane[1].lenght_mts = 6;
        traffic.lane[1].velocity_kmh =100;

        aux0 = calculate_traffic_paramters(0, 0);
        aux1 = calculate_traffic_paramters(1, 0);

        if(aux0 == LANE_STATE_SUCESS && aux1 == LANE_STATE_SUCESS)
        {
            traffic_teste = traffic_3;
        }
        break;
    case traffic_3:

        traffic.lane[0].gap = 1000;
        traffic.lane[0].lenght_mts = 6;
        traffic.lane[0].velocity_kmh =30;

        traffic.lane[1].gap = 1000;
        traffic.lane[1].lenght_mts = 6;
        traffic.lane[1].velocity_kmh =30;

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

