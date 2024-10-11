#ifndef __HMI_CFG_H__
#define __HMI_CFG_H__

/******************************************************************************/

#define HMI_INIT_BLNK_NUMBER_OF_CYCLES		10

#define HMI_PULSE_NUMBER_OF_CYCLES			1

#define HMI_SHORT_PULSE_ON_1MS_TIME      	10
#define HMI_SHORT_PULSE_OFF_1MS_TIME     	200

#define HMI_LONG_PULSE_ON_1MS_TIME      	1000
#define HMI_LONG_PULSE_OFF_1MS_TIME     	200

#define HMI_BLNK_ON_1MS_TIME				100
#define HMI_BLNK_OFF_1MS_TIME				1900

/******************************************************************************/

#include "main.h"

/******************************************************************************/

#define HMI_NUMBER_OF_LEDS 					6
#define HMI_NUMBER_LOOP_LEDS        4
#define HMI_NUMBER_PIEZO_PE_LEDS    2
#define HMI_NUMBER_PIEZO_CONV_LEDS  2

#define hmi_led_pininfo_vector_default_value \
{                                            \
  {/*00_LCE*/                                \
    .GPIO = SENSE_1_LED_GPIO_Port,           \
    .PinMask = SENSE_1_LED_Pin,              \
  }                                          \
  ,                                          \
  {/*01_PZ/PPE*/                             \
    .GPIO = SENSE_2_LED_GPIO_Port,           \
    .PinMask = SENSE_2_LED_Pin,              \
  }                                          \
  ,                                          \
  {/*LCS*/                                   \
    .GPIO = SENSE_3_LED_GPIO_Port,           \
    .PinMask = SENSE_3_LED_Pin,              \
  }                                          \
  ,                                          \
  {/*LCE/PPS*/                               \
    .GPIO = SENSE_4_LED_GPIO_Port,           \
    .PinMask = SENSE_4_LED_Pin,              \
  }                                          \
  ,                                          \
  {/*PZ/PRE*/                                \
    .GPIO = SENSE_5_LED_GPIO_Port,           \
    .PinMask = SENSE_5_LED_Pin,              \
  }                                          \
  ,                                          \
  {/*LCS/PRS*/                               \
    .GPIO = SENSE_6_LED_GPIO_Port,           \
    .PinMask = SENSE_6_LED_Pin,              \
  }                                          \
}

/******************************************************************************/

#define SET_BIT_BUFFER(buffer,index)                ( buffer |= ( 1 << index ) )
#define RESET_BIT_BUFFER(buffer,index)              ( buffer &= ~( 1 << index ) )
#define TOGGLE_BIT_BUFFER(buffer,index)             ( buffer ^= ( 1 << index ) )

#define LED_ON(led_mask,led_index)                  SET_BIT_BUFFER(led_mask,led_index)
#define LED_OFF(led_mask,led_index)                 RESET_BIT_BUFFER(led_mask,led_index)
#define LED_TOGGLE(led_mask,led_index)              TOGGLE_BIT_BUFFER(led_mask,led_index)

/******************************************************************************/

#endif/*__HMI_CFG_H__*/
