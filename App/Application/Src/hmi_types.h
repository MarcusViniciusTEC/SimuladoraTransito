#ifndef __HMI_TYPES_H__
#define __HMI_TYPES_H__

/******************************************************************************/

#include "hmi_cfg.h"

/******************************************************************************/

typedef enum
{
  HMI_STATE_INIT = 0,
  HMI_STATE_RUNNING,
  HMI_NUMBER_OF_STATES
} hmi_state_t;

/******************************************************************************/

typedef enum
{
  HMI_SHORT_PULSE_STATE_OFF = 0,
  HMI_SHORT_PULSE_STATE_ON,
  HMI_LONG_PULSE_STATE_OFF,
  HMI_LONG_PULSE_STATE_ON,
  HMI_BLNK_STATE_OFF,
  HMI_BLNK_STATE_ON,
  HMI_BLNK_STATE_DONE,
  HMI_BLNK_NUMBER_OF_STATES
} hmi_blnk_state_t;

/******************************************************************************/

typedef enum
{
  HMI_BLNK_AUTO_RESTART_OFF = 0,
  HMI_BLNK_AUTO_RESTART_ON
} hmi_blnk_auto_restart_t;

/******************************************************************************/

typedef struct
{
  GPIO_TypeDef *GPIO;
      uint32_t  PinMask;
} hmi_pininfo_t;

/******************************************************************************/

typedef struct
{
  hmi_blnk_state_t state;
          uint32_t cycles;
          uint32_t led_1ms_timer;
           uint8_t led_blnk_auto_restart;
} hmi_blnk_data_t;

/******************************************************************************/

typedef struct
{
  uint32_t mask;
  uint32_t next_mask;
} hmi_led_data_t;

/******************************************************************************/

typedef struct
{
      hmi_state_t state;
  hmi_blnk_data_t blnk[HMI_NUMBER_OF_LEDS];
   hmi_led_data_t led;
} hmi_data_t;

/******************************************************************************/

#endif/*__HMI_TYPES_H__*/
