#ifndef __SL_H__
#define __SL_H__

/******************************************************************************/

#include "sl_types.h"

/******************************************************************************/

#include "stm32f030x8.h"

/******************************************************************************/

#include "stdint.h"
#include <stdarg.h>

/******************************************************************************/

//#include "app_cfg.h"

/******************************************************************************/

#define OK								1
#define NOK								0

#define ON								1
#define OFF								0

#define YES								1
#define NO								0

/******************************************************************************/

#define SL_ENDIANESS      				SL_ENDIANESS_LITTLE

/******************************************************************************/

#define SL_NUMBER_OF_CYCLES_PER_MS 		4250

/******************************************************************************/

#define SL_BIT(n)   					(1 << n)

/******************************************************************************/

#define sl_number_of_elements(array) (sizeof(array)/sizeof(array[0]))

/******************************************************************************/

#define  sl_eint() 						__enable_irq()
#define  sl_dint() 						__disable_irq()

/******************************************************************************/

#define sl_set_pin_dir_in(GPIO, pin_mask)     \
{                                             \
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};  \
                                              \
  GPIO_InitStruct.Pin   = pin_mask;           \
  GPIO_InitStruct.Mode  = LL_GPIO_MODE_INPUT; \
  GPIO_InitStruct.Pull  = LL_GPIO_PULL_NO;    \
                                              \
  LL_GPIO_Init(GPIO, &GPIO_InitStruct);       \
}

/******************************************************************************/

#define sl_set_pin_dir_out(GPIO, pin_mask)              \
{                                                       \
  LL_GPIO_InitTypeDef GPIO_InitStruct;                  \
                                                        \
  GPIO_InitStruct.Pin        = pin_mask;                \
  GPIO_InitStruct.Mode       = LL_GPIO_MODE_OUTPUT;     \
  GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_LOW;  \
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL; \
  GPIO_InitStruct.Pull       = LL_GPIO_PULL_NO;         \
                                                        \
  LL_GPIO_Init(GPIO, &GPIO_InitStruct);                 \
}

/******************************************************************************/

#define sl_write_port(GPIO, value)    LL_GPIO_WriteOutputPort(GPIO, value)
#define sl_read_port(GPIO)            LL_GPIO_ReadInputPort(GPIO)
#define sl_set_pin_hi(GPIO, pin_mask) LL_GPIO_SetOutputPin(GPIO, pin_mask)
#define sl_set_pin_lo(GPIO, pin_mask) LL_GPIO_ResetOutputPin(GPIO, pin_mask)

/******************************************************************************/

void sl_delay_cycles(uint32_t cycles_to_wait);
void sl_delay_ms(uint32_t ms_to_wait);

/******************************************************************************/

void sl_enter_critical(void);
void sl_leave_critical(void);

#define sl_critical_assign(var, val) \
{                                    \
  sl_enter_critical();               \
  var = val;                         \
  sl_leave_critical();               \
}

/******************************************************************************/

void sl_reinit(void);

/******************************************************************************/

void sl_1ms_clock(void);
void sl_init(void);
void sl_update(void);
void sl_deinit(void);

/******************************************************************************/

extern void wlog(const char *format, ...);

#endif/*__SL_H__*/
