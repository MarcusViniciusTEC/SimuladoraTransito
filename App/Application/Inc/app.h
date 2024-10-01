#ifndef __APP_H__
#define __APP_H__

/******************************************************************************/

#include "app_types.h"

/******************************************************************************/

extern volatile uint32_t app_execution_rate_1ms_timer;
#define app_pexecution_rate_1ms_timer (&app_execution_rate_1ms_timer)
#define APP_EXECUTION_RATE_1MS_TIME    100

/******************************************************************************/

void app_on_adc1_eoc(uint32_t channel, uint32_t sample);
void app_on_wdt_timeout_1ms_timer_expired(void);

/******************************************************************************/

    void app_on_mb_invalid_message_received(void);
uint32_t app_on_mb_get_register(uint32_t index, uint16_t *pvalue);
uint32_t app_on_mb_set_register(uint32_t index, uint16_t  value);

/******************************************************************************/

void app_1ms_clock(void);
void app_init(void);
void app_update(void);
void app_deinit(void);

/******************************************************************************/

#endif/*__APP_H__*/
