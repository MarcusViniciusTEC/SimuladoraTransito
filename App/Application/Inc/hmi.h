#ifndef __HMI_H__
#define __HMI_H__

/******************************************************************************/

#include "hmi_types.h"

/******************************************************************************/

extern volatile uint32_t hmi_execution_rate_1ms_timer;

#define hmi_pexecution_rate_1ms_timer (&hmi_execution_rate_1ms_timer)

#define HMI_EXECUTION_RATE_1MS_TIME    		100

/******************************************************************************/
void hmi_turn_on_led_loop(uint8_t led_index);
void hmi_turn_off_led_loop(uint8_t led_index);
void hmi_led_turn_on(uint8_t led_index);
void hmi_led_turn_off(uint8_t led_index);
void hmi_led_toggle(uint8_t led_index);

/******************************************************************************/

void hmi_led_blink(uint8_t led_index, hmi_blnk_auto_restart_t blnk_auto_restart);
void hmi_led_short_pulse(uint8_t led_index, hmi_blnk_auto_restart_t blnk_auto_restart);
void hmi_led_long_pulse(uint8_t led_index, hmi_blnk_auto_restart_t blnk_auto_restart);

/******************************************************************************/

void hmi_1ms_clock(void);
void hmi_init(void);
void hmi_update(void);
void hmi_deinit(void);


#endif