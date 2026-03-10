/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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
#define DVP_PWDN_Pin GPIO_PIN_7
#define DVP_PWDN_GPIO_Port GPIOA
#define WIFI_WLREG_ON_Pin GPIO_PIN_14
#define WIFI_WLREG_ON_GPIO_Port GPIOE
#define BT_REG_ON_Pin GPIO_PIN_15
#define BT_REG_ON_GPIO_Port GPIOE
#define BT_HOST_WAKE_Pin GPIO_PIN_13
#define BT_HOST_WAKE_GPIO_Port GPIOB
#define BT_DEVICE_WAKE_Pin GPIO_PIN_15
#define BT_DEVICE_WAKE_GPIO_Port GPIOB
#define WIFI_HOST_WAKE_Pin GPIO_PIN_9
#define WIFI_HOST_WAKE_GPIO_Port GPIOD
#define WIFI_DEVICE_WAKE_Pin GPIO_PIN_10
#define WIFI_DEVICE_WAKE_GPIO_Port GPIOD
#define RCC_32K_OUT_Pin GPIO_PIN_8
#define RCC_32K_OUT_GPIO_Port GPIOA
#define USB_DN_Pin GPIO_PIN_11
#define USB_DN_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TEST_3_Pin GPIO_PIN_5
#define TEST_3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
