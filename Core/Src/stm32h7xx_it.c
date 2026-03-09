/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32h7xx_it.c
 * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32h7xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
/**
 * @brief   Prints the registers and gives detailed information about the error(s).
 * @param   *stack_frame: Stack frame registers (R0-R3, R12, LR, LC, PSR).
 * @param   exc: EXC_RETURN register.
 * @return  void
 */
__attribute__((no_instrument_function)) void ReportHardFault(uint32_t *stack_frame, uint32_t exc)
{
    bsp_breakpoint();
    // Check if FPU context was saved (bit 4 of EXC_RETURN indicates FPU was active)
    uint32_t fpu_was_active        = (exc & 0x10) != 0;
    uint32_t *adjusted_stack_frame = stack_frame;

    // If FPU was active, FPU registers (S0-S31, FPSCR) are pushed before the basic frame
    if(fpu_was_active)
    {
        // FPU context adds 34 words to the stack (32 S-registers + FPSCR + reserved)
        adjusted_stack_frame += 34;
    }

    uint32_t r0   = adjusted_stack_frame[0];
    uint32_t r1   = adjusted_stack_frame[1];
    uint32_t r2   = adjusted_stack_frame[2];
    uint32_t r3   = adjusted_stack_frame[3];
    uint32_t r12  = adjusted_stack_frame[4];
    uint32_t lr   = adjusted_stack_frame[5];
    uint32_t pc   = adjusted_stack_frame[6];
    uint32_t psr  = adjusted_stack_frame[7];
    uint32_t hfsr = SCB->HFSR;
    uint32_t cfsr = SCB->CFSR;
    uint32_t mmar = SCB->MMFAR;
    uint32_t bfar = SCB->BFAR;
    uint32_t afsr = SCB->AFSR;

    char fault_report[2048];
    int offset = 0;

    offset += sprintf(fault_report + offset, "\n!!!Hard Fault detected!!!\n");

    offset += sprintf(fault_report + offset, "\nStack frame:\n");
    offset += sprintf(fault_report + offset, "R0 :        0x%08lX\n", r0);
    offset += sprintf(fault_report + offset, "R1 :        0x%08lX\n", r1);
    offset += sprintf(fault_report + offset, "R2 :        0x%08lX\n", r2);
    offset += sprintf(fault_report + offset, "R3 :        0x%08lX\n", r3);
    offset += sprintf(fault_report + offset, "R12:        0x%08lX\n", r12);
    offset += sprintf(fault_report + offset, "LR :        0x%08lX\n", lr);
    offset += sprintf(fault_report + offset, "PC :        0x%08lX\n", pc);
    offset += sprintf(fault_report + offset, "PSR:        0x%08lX\n", psr);

    offset += sprintf(fault_report + offset, "\nFault status:\n");
    offset += sprintf(fault_report + offset, "HFSR:       0x%08lX\n", hfsr);
    offset += sprintf(fault_report + offset, "CFSR:       0x%08lX\n", cfsr);
    offset += sprintf(fault_report + offset, "MMAR:       0x%08lX\n", mmar);
    offset += sprintf(fault_report + offset, "BFAR:       0x%08lX\n", bfar);
    offset += sprintf(fault_report + offset, "AFSR:       0x%08lX\n", afsr);

    offset += sprintf(fault_report + offset, "\nOther:\n");
    offset += sprintf(fault_report + offset, "EXC_RETURN: 0x%08lX\n", exc);

    offset += sprintf(fault_report + offset, "\nDetails of the fault status:\n");
    offset += sprintf(fault_report + offset, "Hard fault status:\n");
    if(hfsr & SCB_HFSR_FORCED_Msk)
    {
        offset += sprintf(fault_report + offset, " - Forced Hard fault.\n");
    }
    if(hfsr & SCB_HFSR_VECTTBL_Msk)
    {
        offset += sprintf(fault_report + offset, " - Bus fault on vector table read.\n");
    }
    offset += sprintf(fault_report + offset, "MemManage fault status:\n");
    if(cfsr & SCB_CFSR_MMARVALID_Msk)
    {
        offset += sprintf(fault_report + offset, " - MMAR holds a valid address.\n");
    }
    else
    {
        offset += sprintf(fault_report + offset, " - MMAR holds an invalid address.\n");
    }
    if(cfsr & SCB_CFSR_MLSPERR_Msk)
    {
        offset += sprintf(fault_report + offset, " - Fault occurred during floating-point lazy state preservation.\n");
    }
    if(cfsr & SCB_CFSR_MSTKERR_Msk)
    {
        offset += sprintf(fault_report + offset, " - Stacking has caused an access violation.\n");
    }
    if(cfsr & SCB_CFSR_MUNSTKERR_Msk)
    {
        offset += sprintf(fault_report + offset, " - Unstacking has caused an access violation.\n");
    }
    if(cfsr & SCB_CFSR_DACCVIOL_Msk)
    {
        offset += sprintf(fault_report + offset, " - Load or store at a location that does not permit the operation.\n");
    }
    if(cfsr & SCB_CFSR_IACCVIOL_Msk)
    {
        offset += sprintf(fault_report + offset, " - Instruction fetch from a location that does not permit execution.\n");
    }
    offset += sprintf(fault_report + offset, "Bus fault status:\n");
    if(cfsr & SCB_CFSR_BFARVALID_Msk)
    {
        offset += sprintf(fault_report + offset, " - BFAR holds a valid address.\n");
    }
    else
    {
        offset += sprintf(fault_report + offset, " - BFAR holds an invalid address.\n");
    }
    if(cfsr & SCB_CFSR_LSPERR_Msk)
    {
        offset += sprintf(fault_report + offset, " - Fault occurred during floating-point lazy state preservation.\n");
    }
    if(cfsr & SCB_CFSR_STKERR_Msk)
    {
        offset += sprintf(fault_report + offset, " - Stacking has caused a Bus fault.\n");
    }
    if(cfsr & SCB_CFSR_UNSTKERR_Msk)
    {
        offset += sprintf(fault_report + offset, " - Unstacking has caused a Bus fault.\n");
    }
    if(cfsr & SCB_CFSR_IMPRECISERR_Msk)
    {
        offset += sprintf(fault_report + offset, " - Data bus error has occurred, but the return address in the stack is not related to the fault.\n");
    }
    if(cfsr & SCB_CFSR_PRECISERR_Msk)
    {
        offset += sprintf(fault_report + offset, " - Data bus error has occurred, and the return address points to the instruction that caused the fault.\n");
    }
    if(cfsr & SCB_CFSR_IBUSERR_Msk)
    {
        offset += sprintf(fault_report + offset, " - Instruction bus error.\n");
    }
    offset += sprintf(fault_report + offset, "Usage fault status:\n");
    if(cfsr & SCB_CFSR_DIVBYZERO_Msk)
    {
        offset += sprintf(fault_report + offset, " - The processor has executed an SDIV or UDIV instruction with a divisor of 0.\n");
    }
    if(cfsr & SCB_CFSR_UNALIGNED_Msk)
    {
        offset += sprintf(fault_report + offset, " - The processor has made an unaligned memory access.\n");
    }
    if(cfsr & SCB_CFSR_NOCP_Msk)
    {
        offset += sprintf(fault_report + offset, " - Attempted to access a coprocessor.\n");
    }
    if(cfsr & SCB_CFSR_INVPC_Msk)
    {
        offset += sprintf(fault_report + offset, " - Illegal attempt to load of EXC_RETURN to the PC.\n");
    }
    if(cfsr & SCB_CFSR_INVSTATE_Msk)
    {
        offset += sprintf(fault_report + offset, " - Attempted to execute an instruction that makes illegal use of the EPSR.\n");
    }
    if(cfsr & SCB_CFSR_UNDEFINSTR_Msk)
    {
        offset += sprintf(fault_report + offset, " - The processor has attempted to execute an undefined instruction.\n");
    }

    // Print the complete fault report
    printf("%s", fault_report);

    abort();
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern LPTIM_HandleTypeDef hlptim1;
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim17;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

    abort();
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */
    __asm volatile(
        "TST    LR, #0b0100;      "
        "ITE    EQ;               "
        "MRSEQ  R0, MSP;          "
        "MRSNE  R0, PSP;          "
        "MOV    R1, LR;           "
        "B      ReportHardFault;  ");
  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */
    __asm volatile(
        "TST    LR, #0b0100;      "
        "ITE    EQ;               "
        "MRSEQ  R0, MSP;          "
        "MRSNE  R0, PSP;          "
        "MOV    R1, LR;           "
        "B      ReportHardFault;  ");
  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */
    __asm volatile(
        "TST    LR, #0b0100;      "
        "ITE    EQ;               "
        "MRSEQ  R0, MSP;          "
        "MRSNE  R0, PSP;          "
        "MOV    R1, LR;           "
        "B      ReportHardFault;  ");
  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */
    __asm volatile(
        "TST    LR, #0b0100;      "
        "ITE    EQ;               "
        "MRSEQ  R0, MSP;          "
        "MRSNE  R0, PSP;          "
        "MOV    R1, LR;           "
        "B      ReportHardFault;  ");
  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32H7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(SAI_FS_IRQ_Pin);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles TIM17 global interrupt.
  */
void TIM17_IRQHandler(void)
{
  /* USER CODE BEGIN TIM17_IRQn 0 */

  /* USER CODE END TIM17_IRQn 0 */
  HAL_TIM_IRQHandler(&htim17);
  /* USER CODE BEGIN TIM17_IRQn 1 */

  /* USER CODE END TIM17_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* Forward declaration of the callback function */
void USART3_IRQHandler_Callback(void);

/**
 * @brief This function handles USART3 global interrupt.
 */
void USART3_IRQHandler(void)
{
    /* USER CODE BEGIN USART3_IRQn 0 */

    /* USER CODE END USART3_IRQn 0 */

    if(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_ORE))
    {
        __HAL_UART_CLEAR_FLAG(&huart3, UART_CLEAR_OREF);
    }

    if(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_FE))
    {
        __HAL_UART_CLEAR_FLAG(&huart3, UART_CLEAR_FEF);
    }

    if(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_NE))
    {
        __HAL_UART_CLEAR_FLAG(&huart3, UART_CLEAR_NEF);
    }

    if(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_PE))
    {
        __HAL_UART_CLEAR_FLAG(&huart3, UART_CLEAR_PEF);
    }
    /* USER CODE BEGIN USART3_IRQn 1 */

    /* USER CODE END USART3_IRQn 1 */
}

void LPTIM1_IRQHandler(void)
{
    HAL_LPTIM_IRQHandler(&hlptim1);
}

/* USER CODE END 1 */
