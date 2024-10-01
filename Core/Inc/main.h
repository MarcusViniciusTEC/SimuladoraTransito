/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_ll_crs.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_dma.h"
#include "stm32f0xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define nMODE_ID_4_Pin LL_GPIO_PIN_5
#define nMODE_ID_4_GPIO_Port GPIOC
#define nMODE_ID_3_Pin LL_GPIO_PIN_0
#define nMODE_ID_3_GPIO_Port GPIOB
#define nMODE_ID_2_Pin LL_GPIO_PIN_1
#define nMODE_ID_2_GPIO_Port GPIOB
#define nMODE_ID_1_Pin LL_GPIO_PIN_2
#define nMODE_ID_1_GPIO_Port GPIOB
#define SENSE_1_LED_Pin LL_GPIO_PIN_10
#define SENSE_1_LED_GPIO_Port GPIOB
#define SENSE_2_LED_Pin LL_GPIO_PIN_11
#define SENSE_2_LED_GPIO_Port GPIOB
#define SENSE_3_LED_Pin LL_GPIO_PIN_12
#define SENSE_3_LED_GPIO_Port GPIOB
#define SENSE_4_LED_Pin LL_GPIO_PIN_13
#define SENSE_4_LED_GPIO_Port GPIOB
#define SENSE_5_LED_Pin LL_GPIO_PIN_14
#define SENSE_5_LED_GPIO_Port GPIOB
#define SENSE_6_LED_Pin LL_GPIO_PIN_15
#define SENSE_6_LED_GPIO_Port GPIOB
#define DWPZ_1_Pin LL_GPIO_PIN_6
#define DWPZ_1_GPIO_Port GPIOC
#define DWPZ_2_Pin LL_GPIO_PIN_7
#define DWPZ_2_GPIO_Port GPIOC
#define DXPZ_1_Pin LL_GPIO_PIN_8
#define DXPZ_1_GPIO_Port GPIOC
#define DXPZ_2_Pin LL_GPIO_PIN_9
#define DXPZ_2_GPIO_Port GPIOC
#define MCU_STATUS_Pin LL_GPIO_PIN_12
#define MCU_STATUS_GPIO_Port GPIOA
#define LP_1_DET_Pin LL_GPIO_PIN_4
#define LP_1_DET_GPIO_Port GPIOB
#define LP_2_DET_Pin LL_GPIO_PIN_5
#define LP_2_DET_GPIO_Port GPIOB
#define LP_3_DET_Pin LL_GPIO_PIN_6
#define LP_3_DET_GPIO_Port GPIOB
#define LP_4_DET_Pin LL_GPIO_PIN_7
#define LP_4_DET_GPIO_Port GPIOB
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
