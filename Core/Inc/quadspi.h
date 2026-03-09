/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.h
  * @brief   This file contains all the function prototypes for
  *          the quadspi.c file
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
#ifndef __QUADSPI_H__
#define __QUADSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern QSPI_HandleTypeDef hqspi;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#define QSPI_OK            ((uint8_t)0x00)
#define QSPI_ERROR         ((uint8_t)0x01)
#define QSPI_BUSY          ((uint8_t)0x02)
#define QSPI_NOT_SUPPORTED ((uint8_t)0x04)
#define QSPI_SUSPENDED     ((uint8_t)0x08)

typedef struct {
  uint32_t FlashSize;          /*!< Size of the flash */
  uint32_t EraseSectorSize;    /*!< Size of sectors for the erase operation */
  uint32_t EraseSectorsNumber; /*!< Number of sectors for the erase operation */
  uint32_t ProgPageSize;       /*!< Size of pages for the program operation */
  uint32_t ProgPagesNumber;    /*!< Number of pages for the program operation */
} QSPI_Info;

uint8_t BSP_QSPI_Init();
uint8_t BSP_QSPI_DeInit();
uint8_t BSP_QSPI_Read(uint8_t *pData, uint32_t ReadAddr, uint32_t Size);
uint8_t BSP_QSPI_Write(const uint8_t *pData, uint32_t WriteAddr, uint32_t Size);
uint8_t BSP_QSPI_Erase_Block(uint32_t BlockAddress);
uint8_t BSP_QSPI_Erase_Sector(uint32_t Sector);
uint8_t BSP_QSPI_Erase_Chip();
uint8_t BSP_QSPI_GetStatus();
// uint8_t BSP_QSPI_GetInfo(QSPI_Info *pInfo);
uint8_t BSP_QSPI_EnableMemoryMappedMode();
uint8_t BSP_QSPI_SuspendErase();
uint8_t BSP_QSPI_ResumeErase();
uint8_t BSP_QSPI_EnterDeepPowerDown();
uint8_t BSP_QSPI_LeaveDeepPowerDown();

/* USER CODE BEGIN Prototypes */

/*MX25R3235FM1IL0 memory parameters*/
#define MX25R3235F_FLASH_SIZE                0x400000  /* 32 MBits => 4MBytes */
#define MX25R3235F_BLOCK_SIZE                0x10000   /* 64 blocks of 64KBytes */
#define MX25R3235F_SUBBLOCK_SIZE             0x8000    /* 128 blocks of 32KBytes */
#define MX25R3235F_SECTOR_SIZE               0x1000    /* 1024 sectors of 4kBytes */
#define MX25R3235F_PAGE_SIZE                 0x100     /* 32768 pages of 256 bytes */

#define MX25R3235F_DUMMY_CYCLES_READ         8
#define MX25R3235F_DUMMY_CYCLES_READ_DUAL    4
#define MX25R3235F_DUMMY_CYCLES_READ_QUAD    4
#define MX25R3235F_DUMMY_CYCLES_2READ        2
#define MX25R3235F_DUMMY_CYCLES_4READ        4
#define MX25R3235F_DUMMY_CYCLES_WRITE_1I4O   0

#define MX25R3235F_ALT_BYTES_PE_MODE         0xA5
#define MX25R3235F_ALT_BYTES_NO_PE_MODE      0xAA

#define MX25R3235F_CHIP_ERASE_MAX_TIME       240000
#define MX25R3235F_BLOCK_ERASE_MAX_TIME      3500
#define MX25R3235F_SUBBLOCK_ERASE_MAX_TIME   3000
#define MX25R3235F_SECTOR_ERASE_MAX_TIME     240

/**
  * @brief  MX25R3235F Commands
  */
/* Read Operations */
#define READ_CMD                             0x03
#define FAST_READ_CMD                        0x0B
#define DUAL_OUT_READ_CMD                    0x3B
#define DUAL_INOUT_READ_CMD                  0xBB
#define QUAD_OUT_READ_CMD                    0x6B
#define QUAD_INOUT_READ_CMD                  0xEB

/* Program Operations */
#define PAGE_PROG_CMD                        0x02
#define QUAD_PAGE_PROG_CMD                   0x38

/* Erase Operations */
#define SECTOR_ERASE_CMD                     0x20
#define SUBBLOCK_ERASE_CMD                   0x52
#define BLOCK_ERASE_CMD                      0xD8
#define CHIP_ERASE_CMD                       0x60
#define CHIP_ERASE_CMD_2                     0xC7

#define PROG_ERASE_RESUME_CMD                0x7A
#define PROG_ERASE_RESUME_CMD_2              0x30
#define PROG_ERASE_SUSPEND_CMD               0x75
#define PROG_ERASE_SUSPEND_CMD_2             0xB0

/* Identification Operations */
#define READ_ID_CMD                          0x9F
#define READ_ELECTRONIC_ID_CMD               0xAB
#define READ_ELEC_MANUFACTURER_DEVICE_ID_CMD 0x90
#define READ_SERIAL_FLASH_DISCO_PARAM_CMD    0x5A

/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06
#define WRITE_DISABLE_CMD                    0x04

/* Register Operations */
#define READ_STATUS_REG_CMD                  0x05
#define READ_CFG_REG_CMD                     0x15
#define WRITE_STATUS_CFG_REG_CMD             0x01

#define READ_SEC_REG_CMD                     0x2B
#define WRITE_SEC_REG_CMD                    0x2F

/* Power Down Operations */
#define DEEP_POWER_DOWN_CMD                  0xB9

/* Burst Operations */
#define SET_BURST_LENGTH_CMD                 0xC0

/* One-Time Programmable Operations */
#define ENTER_SECURED_OTP_CMD                0xB1
#define EXIT_SECURED_OTP_CMD                 0xC1

/* No Operation */
#define NO_OPERATION_CMD                     0x00

/* Reset Operations */
#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99
#define RELEASE_READ_ENHANCED_CMD            0xFF

/**
  * @brief  MX25R3235F Registers
  */
/* Status Register */
#define MX25R3235F_SR_WIP                    ((uint8_t)0x01)    /*!< Write in progress */
#define MX25R3235F_SR_WEL                    ((uint8_t)0x02)    /*!< Write enable latch */
#define MX25R3235F_SR_BP                     ((uint8_t)0x3C)    /*!< Block protect */
#define MX25R3235F_SR_QE                     ((uint8_t)0x40)    /*!< Quad enable */
#define MX25R3235F_SR_SRWD                   ((uint8_t)0x80)    /*!< Status register write disable */

/* Configuration Register 1 */
#define MX25R3235F_CR1_TB                    ((uint8_t)0x08)    /*!< Top / bottom */

/* Configuration Register 2 */
#define MX25R3235F_CR2_LH_SWITCH             ((uint8_t)0x02)    /*!< Low power / high performance switch */

/* Security Register */
#define MX25R3235F_SECR_SOI                  ((uint8_t)0x01)    /*!< Secured OTP indicator */
#define MX25R3235F_SECR_LDSO                 ((uint8_t)0x02)    /*!< Lock-down secured OTP */
#define MX25R3235F_SECR_PSB                  ((uint8_t)0x04)    /*!< Program suspend bit */
#define MX25R3235F_SECR_ESB                  ((uint8_t)0x08)    /*!< Erase suspend bit */
#define MX25R3235F_SECR_P_FAIL               ((uint8_t)0x20)    /*!< Program fail flag */
#define MX25R3235F_SECR_E_FAIL               ((uint8_t)0x40)    /*!< Erase fail flag */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __QUADSPI_H__ */
