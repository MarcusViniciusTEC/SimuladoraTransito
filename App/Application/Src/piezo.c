#include "sl.h"
#include "piezo.h"
#include "piezo_cfg.h"

/******************************************************************************/

volatile uint32_t piezo_execution_rate_1ms_timer;

static const piezo_pininfo_t piezo_pininfo_vector[PIEZO_NUMBER_OF_OUTPUTS] = piezo_pininfo_vector_default_value;

/******************************************************************************/

void piezo_turn_on(uint8_t index)
{
    piezo_pininfo_t piezo_pininfo;
    piezo_pininfo = piezo_pininfo_vector[index];
    LL_GPIO_SetOutputPin(piezo_pininfo.GPIO, piezo_pininfo.PinMask);
}

/******************************************************************************/

void piezo_turn_off(uint8_t index)
{
    piezo_pininfo_t piezo_pininfo;
    piezo_pininfo = piezo_pininfo_vector[index];
    LL_GPIO_ResetOutputPin(piezo_pininfo.GPIO, piezo_pininfo.PinMask);
}

/******************************************************************************/

void piezo_1ms_clock(void)
{

}     

/******************************************************************************/

void piezo_init(void)
{

}                  

/******************************************************************************/

void piezo_update(void)
{

}                

/******************************************************************************/

void piezo_deinit(void)
{

}