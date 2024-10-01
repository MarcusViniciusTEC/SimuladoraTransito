#ifndef __APP_CFG_H__
#define __APP_CFG_H__

/******************************************************************************/

#define APP_BOARD_MODEL          83
#define APP_BOARD_FIRMWARE_MAJOR  1
#define APP_BOARD_FIRMWARE_MINOR  1

/******************************************************************************/

#define APP_MB_ID_BASE_ADDRESS    0x30

#define APP_MB_ID_BIT0_GPIO_PORT  nRS485_ID_1_GPIO_Port
#define APP_MB_ID_BIT0_GPIO_PIN   nRS485_ID_1_Pin
#define APP_MB_ID_BIT1_GPIO_PORT  nRS485_ID_2_GPIO_Port
#define APP_MB_ID_BIT1_GPIO_PIN   nRS485_ID_2_Pin
#define APP_MB_ID_BIT2_GPIO_PORT  nRS485_ID_3_GPIO_Port
#define APP_MB_ID_BIT2_GPIO_PIN   nRS485_ID_3_Pin

/******************************************************************************/

#define APP_MB_VALID_MESSAGE_RECEIVED_LED_A_1MS_TIME     250

#define APP_MB_VALID_MESSAGE_RECEIVED_LED_A_INDEX        1

/******************************************************************************/

#define APP_MB_INVALID_MESSAGE_RECEIVED_LED_A_1MS_TIME   1000

#define APP_MB_INVALID_MESSAGE_RECEIVED_LED_A_INDEX      0

/******************************************************************************/

#define APP_TMP_UPDATE_CYCLE_1MS_TIME     				(uint32_t)(15*1000)   	// 15 seg.

/******************************************************************************/

#define APP_HEARTBEAT_LED_A_INDEX                  		 0

/******************************************************************************/

#endif/*__APP_CFG_H__*/
