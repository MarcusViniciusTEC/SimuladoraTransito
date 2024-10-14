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
loop_pin_data_t app_send_data_loop;

lane_loop_update_t app_lane_loop_update;

/******************************************************************************/









void app_set_address_and_mode (uint8_t addres, uint8_t mode)
{



}



void traffic_lane_loop_update_state()
{

    uint8_t lane_index = 0;
    switch (app_lane_loop_update.lane_loop[lane_index].state)
    {
    case UPDATE_LOOP_INIT:
        
        break;
    case UPDATE_LOOP_START:
        
        break;
    case UPDATE_LOOP_SEND_PARAMETERS:

        break;
    case UPDATE_LOOP_STATE_SUCESS:
        break;
    default:
        break;
    }
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

}

/******************************************************************************/

void app_update(void)
{
    app_read_address_and_mode();

}

/******************************************************************************/

void app_deinit(void)
{

}

/******************************************************************************/
