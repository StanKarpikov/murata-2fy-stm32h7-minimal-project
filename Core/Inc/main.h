/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define USER_LED_Pin GPIO_PIN_3
#define USER_LED_GPIO_Port GPIOE
#define SPI4_NSS_Pin GPIO_PIN_4
#define SPI4_NSS_GPIO_Port GPIOE
#define USER_BUTTON_Pin GPIO_PIN_13
#define USER_BUTTON_GPIO_Port GPIOC
#define RECEIVER_TRANSMITTER_SELECT_Pin GPIO_PIN_3
#define RECEIVER_TRANSMITTER_SELECT_GPIO_Port GPIOA
#define DVP_PWDN_Pin GPIO_PIN_7
#define DVP_PWDN_GPIO_Port GPIOA
#define NRF_nCS_Pin GPIO_PIN_8
#define NRF_nCS_GPIO_Port GPIOE
#define NRF_CE_Pin GPIO_PIN_9
#define NRF_CE_GPIO_Port GPIOE
#define LED_LED_Pin GPIO_PIN_10
#define LED_LED_GPIO_Port GPIOE
#define LCD_CS_Pin GPIO_PIN_11
#define LCD_CS_GPIO_Port GPIOE
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
#define SPI_CS_Pin GPIO_PIN_6
#define SPI_CS_GPIO_Port GPIOD
#define TEST_3_Pin GPIO_PIN_5
#define TEST_3_GPIO_Port GPIOB
#define TEST_2_Pin GPIO_PIN_7
#define TEST_2_GPIO_Port GPIOB
#define I2C_SCL_Pin GPIO_PIN_8
#define I2C_SCL_GPIO_Port GPIOB
#define I2C_SDA_Pin GPIO_PIN_9
#define I2C_SDA_GPIO_Port GPIOB
#define TEST_1_Pin GPIO_PIN_0
#define TEST_1_GPIO_Port GPIOE
#define TEST_0_Pin GPIO_PIN_1
#define TEST_0_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
