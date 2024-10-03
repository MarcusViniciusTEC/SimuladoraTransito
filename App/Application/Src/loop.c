#include "sl.h"
#include "loop.h"
#include "loop_cfg.h"

/******************************************************************************/

volatile uint32_t loop_execution_rate_1ms_timer;

typedef struct
{
  GPIO_TypeDef *GPIO;
      uint32_t  PinMask;
} loop_pininfo_t;

static const loop_pininfo_t loop_pininfo_vector[LOOP_NUMBER_OF_OUTPUTS] = loop_pininfo_vector_default_value;

/******************************************************************************/

void loop_1ms_clock(void)
{

}     

/******************************************************************************/

void loop_init(void)
{

}              

/******************************************************************************/

void loop_update(void)
{

}            

/******************************************************************************/

void loop_deinit(void)
{


}

