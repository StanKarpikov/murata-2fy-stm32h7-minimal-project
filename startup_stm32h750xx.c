/*==============================================================================
 Name        : startup_stm32h750xx.c
 Version     : 1.0.0
 Description : An independent startup code for STM32H750 MCUs written in C
--------------------------------------------------------------------------------

 The MIT License (MIT)
 Copyright (c) 2025 Monitor Audio

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
===============================================================================*/

/*======================= Includes ========================*/
#include "stm32h750xx.h"
#include <stdint.h>
#include <stdlib.h>

/*===== define the Reset Clock Control registers bank =====*/
typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t ICSCR;
    volatile uint32_t CRRCR;
    uint32_t RESERVED0;
    volatile uint32_t CFGR;
    uint32_t RESERVED1;
    volatile uint32_t D1CFGR;
    volatile uint32_t D2CFGR;
    volatile uint32_t D3CFGR;
    uint32_t RESERVED2;
    volatile uint32_t PLLCKSELR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t PLL1DIVR;
    volatile uint32_t PLL1FRACR;
    volatile uint32_t PLL2DIVR;
    volatile uint32_t PLL2FRACR;
    volatile uint32_t PLL3DIVR;
    volatile uint32_t PLL3FRACR;
    uint32_t RESERVED3;
    volatile uint32_t D1CCIPR;
    volatile uint32_t D2CCIP1R;
    volatile uint32_t D2CCIP2R;
    volatile uint32_t D3CCIPR;
    uint32_t RESERVED4;
    volatile uint32_t CIER;
    volatile uint32_t CIFR;
    volatile uint32_t CICR;
    uint32_t RESERVED5;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    uint32_t RESERVED6;
    volatile uint32_t AHB3RSTR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB4RSTR;
    volatile uint32_t APB3RSTR;
    volatile uint32_t APB1LRSTR;
    volatile uint32_t APB1HRSTR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB4RSTR;
    volatile uint32_t GCR;
    uint32_t RESERVED7;
    volatile uint32_t D3AMR;
    uint32_t RESERVED8[9];
    volatile uint32_t RSR;
    volatile uint32_t AHB3ENR;
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB4ENR;
    volatile uint32_t APB3ENR;
    volatile uint32_t APB1LENR;
    volatile uint32_t APB1HENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB4ENR;
    uint32_t RESERVED9;
    volatile uint32_t AHB3LPENR;
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB4LPENR;
    volatile uint32_t APB3LPENR;
    volatile uint32_t APB1LLPENR;
    volatile uint32_t APB1HLPENR;
    volatile uint32_t APB2LPENR;
    volatile uint32_t APB4LPENR;
    uint32_t RESERVED10[4];
} rccStruct;

/*==================== Private macros =====================*/
#define HWREG(x) (*((volatile uint32_t *)(x)))

/*================== function prototypes ==================*/
extern int main();
extern void SystemInit();
extern void __libc_init_array();

void Default_Handler() __attribute__((weak));
void Reset_Handler() __attribute__((weak));
void NMI_Handler() __attribute__((weak));
void HardFault_Handler() __attribute__((weak));
void MemManage_Handler() __attribute__((weak));
void BusFault_Handler() __attribute__((weak));
void UsageFault_Handler() __attribute__((weak));
void SVC_Handler() __attribute__((weak));
void DebugMon_Handler() __attribute__((weak));
void PendSV_Handler() __attribute__((weak));
void SysTick_Handler() __attribute__((weak));

void WWDG_IRQHandler() __attribute__((weak));
void PVD_AVD_IRQHandler() __attribute__((weak));
void TAMP_STAMP_IRQHandler() __attribute__((weak));
void RTC_WKUP_IRQHandler() __attribute__((weak));
void FLASH_IRQHandler() __attribute__((weak));
void RCC_IRQHandler() __attribute__((weak));
void EXTI0_IRQHandler() __attribute__((weak));
void EXTI1_IRQHandler() __attribute__((weak));
void EXTI2_IRQHandler() __attribute__((weak));
void EXTI3_IRQHandler() __attribute__((weak));
void EXTI4_IRQHandler() __attribute__((weak));
void DMA1_Stream0_IRQHandler() __attribute__((weak));
void DMA1_Stream1_IRQHandler() __attribute__((weak));
void DMA1_Stream2_IRQHandler() __attribute__((weak));
void DMA1_Stream3_IRQHandler() __attribute__((weak));
void DMA1_Stream4_IRQHandler() __attribute__((weak));
void DMA1_Stream5_IRQHandler() __attribute__((weak));
void DMA1_Stream6_IRQHandler() __attribute__((weak));
void ADC_IRQHandler() __attribute__((weak));
void FDCAN1_IT0_IRQHandler() __attribute__((weak));
void FDCAN2_IT0_IRQHandler() __attribute__((weak));
void FDCAN1_IT1_IRQHandler() __attribute__((weak));
void FDCAN2_IT1_IRQHandler() __attribute__((weak));
void EXTI9_5_IRQHandler() __attribute__((weak));
void TIM1_BRK_IRQHandler() __attribute__((weak));
void TIM1_UP_IRQHandler() __attribute__((weak));
void TIM1_TRG_COM_IRQHandler() __attribute__((weak));
void TIM1_CC_IRQHandler() __attribute__((weak));
void TIM2_IRQHandler() __attribute__((weak));
void TIM3_IRQHandler() __attribute__((weak));
void TIM4_IRQHandler() __attribute__((weak));
void I2C1_EV_IRQHandler() __attribute__((weak));
void I2C1_ER_IRQHandler() __attribute__((weak));
void I2C2_EV_IRQHandler() __attribute__((weak));
void I2C2_ER_IRQHandler() __attribute__((weak));
void SPI1_IRQHandler() __attribute__((weak));
void SPI2_IRQHandler() __attribute__((weak));
void USART1_IRQHandler() __attribute__((weak));
void USART2_IRQHandler() __attribute__((weak));
void USART3_IRQHandler() __attribute__((weak));
void EXTI15_10_IRQHandler() __attribute__((weak));
void RTC_Alarm_IRQHandler() __attribute__((weak));
void TIM8_BRK_TIM12_IRQHandler() __attribute__((weak));
void TIM8_UP_TIM13_IRQHandler() __attribute__((weak));
void TIM8_TRG_COM_TIM14_IRQHandler() __attribute__((weak));
void TIM8_CC_IRQHandler() __attribute__((weak));
void DMA1_Stream7_IRQHandler() __attribute__((weak));
void FMC_IRQHandler() __attribute__((weak));
void SDMMC1_IRQHandler() __attribute__((weak));
void TIM5_IRQHandler() __attribute__((weak));
void SPI3_IRQHandler() __attribute__((weak));
void UART4_IRQHandler() __attribute__((weak));
void UART5_IRQHandler() __attribute__((weak));
void TIM6_DAC_IRQHandler() __attribute__((weak));
void TIM7_IRQHandler() __attribute__((weak));
void DMA2_Stream0_IRQHandler() __attribute__((weak));
void DMA2_Stream1_IRQHandler() __attribute__((weak));
void DMA2_Stream2_IRQHandler() __attribute__((weak));
void DMA2_Stream3_IRQHandler() __attribute__((weak));
void DMA2_Stream4_IRQHandler() __attribute__((weak));
void ETH_IRQHandler() __attribute__((weak));
void ETH_WKUP_IRQHandler() __attribute__((weak));
void FDCAN_CAL_IRQHandler() __attribute__((weak));
void DMA2_Stream5_IRQHandler() __attribute__((weak));
void DMA2_Stream6_IRQHandler() __attribute__((weak));
void DMA2_Stream7_IRQHandler() __attribute__((weak));
void USART6_IRQHandler() __attribute__((weak));
void I2C3_EV_IRQHandler() __attribute__((weak));
void I2C3_ER_IRQHandler() __attribute__((weak));
void OTG_HS_EP1_OUT_IRQHandler() __attribute__((weak));
void OTG_HS_EP1_IN_IRQHandler() __attribute__((weak));
void OTG_HS_WKUP_IRQHandler() __attribute__((weak));
void OTG_HS_IRQHandler() __attribute__((weak));
void DCMI_IRQHandler() __attribute__((weak));
void RNG_IRQHandler() __attribute__((weak));
void FPU_IRQHandler() __attribute__((weak));
void UART7_IRQHandler() __attribute__((weak));
void UART8_IRQHandler() __attribute__((weak));
void SPI4_IRQHandler() __attribute__((weak));
void SPI5_IRQHandler() __attribute__((weak));
void SPI6_IRQHandler() __attribute__((weak));
void SAI1_IRQHandler() __attribute__((weak));
void LTDC_IRQHandler() __attribute__((weak));
void LTDC_ER_IRQHandler() __attribute__((weak));
void DMA2D_IRQHandler() __attribute__((weak));
void SAI2_IRQHandler() __attribute__((weak));
void QUADSPI_IRQHandler() __attribute__((weak));
void LPTIM1_IRQHandler() __attribute__((weak));
void CEC_IRQHandler() __attribute__((weak));
void I2C4_EV_IRQHandler() __attribute__((weak));
void I2C4_ER_IRQHandler() __attribute__((weak));
void SPDIF_RX_IRQHandler() __attribute__((weak));
void OTG_FS_EP1_OUT_IRQHandler() __attribute__((weak));
void OTG_FS_EP1_IN_IRQHandler() __attribute__((weak));
void OTG_FS_WKUP_IRQHandler() __attribute__((weak));
void OTG_FS_IRQHandler() __attribute__((weak));
void DMAMUX1_OVR_IRQHandler() __attribute__((weak));
void HRTIM1_Master_IRQHandler() __attribute__((weak));
void HRTIM1_TIMA_IRQHandler() __attribute__((weak));
void HRTIM1_TIMB_IRQHandler() __attribute__((weak));
void HRTIM1_TIMC_IRQHandler() __attribute__((weak));
void HRTIM1_TIMD_IRQHandler() __attribute__((weak));
void HRTIM1_TIME_IRQHandler() __attribute__((weak));
void HRTIM1_FLT_IRQHandler() __attribute__((weak));
void DFSDM1_FLT0_IRQHandler() __attribute__((weak));
void DFSDM1_FLT1_IRQHandler() __attribute__((weak));
void DFSDM1_FLT2_IRQHandler() __attribute__((weak));
void DFSDM1_FLT3_IRQHandler() __attribute__((weak));
void SAI3_IRQHandler() __attribute__((weak));
void SWPMI1_IRQHandler() __attribute__((weak));
void TIM15_IRQHandler() __attribute__((weak));
void TIM16_IRQHandler() __attribute__((weak));
void TIM17_IRQHandler() __attribute__((weak));
void MDIOS_WKUP_IRQHandler() __attribute__((weak));
void MDIOS_IRQHandler() __attribute__((weak));
void JPEG_IRQHandler() __attribute__((weak));
void MDMA_IRQHandler() __attribute__((weak));
void SDMMC2_IRQHandler() __attribute__((weak));
void HSEM1_IRQHandler() __attribute__((weak));
void ADC3_IRQHandler() __attribute__((weak));
void DMAMUX2_OVR_IRQHandler() __attribute__((weak));
void BDMA_Channel0_IRQHandler() __attribute__((weak));
void BDMA_Channel1_IRQHandler() __attribute__((weak));
void BDMA_Channel2_IRQHandler() __attribute__((weak));
void BDMA_Channel3_IRQHandler() __attribute__((weak));
void BDMA_Channel4_IRQHandler() __attribute__((weak));
void BDMA_Channel5_IRQHandler() __attribute__((weak));
void BDMA_Channel6_IRQHandler() __attribute__((weak));
void BDMA_Channel7_IRQHandler() __attribute__((weak));
void COMP1_IRQHandler() __attribute__((weak));
void LPTIM2_IRQHandler() __attribute__((weak));
void LPTIM3_IRQHandler() __attribute__((weak));
void LPTIM4_IRQHandler() __attribute__((weak));
void LPTIM5_IRQHandler() __attribute__((weak));
void LPUART1_IRQHandler() __attribute__((weak));
void CRS_IRQHandler() __attribute__((weak));
void SAI4_IRQHandler() __attribute__((weak));
void WAKEUP_PIN_IRQHandler() __attribute__((weak));

/*=================== Global variables ====================*/
/* Highest address of the user mode stack */
extern const volatile uint32_t _estack;
/* Stack limit for overflow detection */
extern const volatile uint32_t __StackLimit;
/* start address for the initialization values of the .data section.
defined in linker script */
extern uint32_t _load_data_startup;
/* start address for the .data section. defined in linker script */
extern uint32_t _start_data_startup;
/* end address for the .data section. defined in linker script */
extern uint32_t _end_data_startup;
/* start address for the .bss section. defined in linker script */
extern uint32_t _sbss;
/* end address for the .bss section. defined in linker script */
extern uint32_t _ebss;

extern uint32_t _load_ramfunc_from_flash;
extern uint32_t _start_ramfunc_from_flash;
extern uint32_t _end_ramfunc_from_flash;

extern uint32_t _load_ramfunc_itcmram;
extern uint32_t _start_ramfunc_itcmram;
extern uint32_t _end_ramfunc_itcmram;

/* The Interrupt Vector Table */
__attribute__((section(".isr_vector"))) void (*const g_pfnVectors[])(void) = {
    ((void (*)(void))(&_estack)),
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,

    /* External Interrupts */
    WWDG_IRQHandler,
    PVD_AVD_IRQHandler,
    TAMP_STAMP_IRQHandler,
    RTC_WKUP_IRQHandler,
    FLASH_IRQHandler,
    RCC_IRQHandler,
    EXTI0_IRQHandler,
    EXTI1_IRQHandler,
    EXTI2_IRQHandler,
    EXTI3_IRQHandler,
    EXTI4_IRQHandler,
    DMA1_Stream0_IRQHandler,
    DMA1_Stream1_IRQHandler,
    DMA1_Stream2_IRQHandler,
    DMA1_Stream3_IRQHandler,
    DMA1_Stream4_IRQHandler,
    DMA1_Stream5_IRQHandler,
    DMA1_Stream6_IRQHandler,
    ADC_IRQHandler,
    FDCAN1_IT0_IRQHandler,
    FDCAN2_IT0_IRQHandler,
    FDCAN1_IT1_IRQHandler,
    FDCAN2_IT1_IRQHandler,
    EXTI9_5_IRQHandler,
    TIM1_BRK_IRQHandler,
    TIM1_UP_IRQHandler,
    TIM1_TRG_COM_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM4_IRQHandler,
    I2C1_EV_IRQHandler,
    I2C1_ER_IRQHandler,
    I2C2_EV_IRQHandler,
    I2C2_ER_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    USART3_IRQHandler,
    EXTI15_10_IRQHandler,
    RTC_Alarm_IRQHandler,
    0,
    TIM8_BRK_TIM12_IRQHandler,
    TIM8_UP_TIM13_IRQHandler,
    TIM8_TRG_COM_TIM14_IRQHandler,
    TIM8_CC_IRQHandler,
    DMA1_Stream7_IRQHandler,
    FMC_IRQHandler,
    SDMMC1_IRQHandler,
    TIM5_IRQHandler,
    SPI3_IRQHandler,
    UART4_IRQHandler,
    UART5_IRQHandler,
    TIM6_DAC_IRQHandler,
    TIM7_IRQHandler,
    DMA2_Stream0_IRQHandler,
    DMA2_Stream1_IRQHandler,
    DMA2_Stream2_IRQHandler,
    DMA2_Stream3_IRQHandler,
    DMA2_Stream4_IRQHandler,
    ETH_IRQHandler,
    ETH_WKUP_IRQHandler,
    FDCAN_CAL_IRQHandler,
    0,
    0,
    0,
    0,
    DMA2_Stream5_IRQHandler,
    DMA2_Stream6_IRQHandler,
    DMA2_Stream7_IRQHandler,
    USART6_IRQHandler,
    I2C3_EV_IRQHandler,
    I2C3_ER_IRQHandler,
    OTG_HS_EP1_OUT_IRQHandler,
    OTG_HS_EP1_IN_IRQHandler,
    OTG_HS_WKUP_IRQHandler,
    OTG_HS_IRQHandler,
    DCMI_IRQHandler,
    0,
    RNG_IRQHandler,
    FPU_IRQHandler,
    UART7_IRQHandler,
    UART8_IRQHandler,
    SPI4_IRQHandler,
    SPI5_IRQHandler,
    SPI6_IRQHandler,
    SAI1_IRQHandler,
    LTDC_IRQHandler,
    LTDC_ER_IRQHandler,
    DMA2D_IRQHandler,
    SAI2_IRQHandler,
    QUADSPI_IRQHandler,
    LPTIM1_IRQHandler,
    CEC_IRQHandler,
    I2C4_EV_IRQHandler,
    I2C4_ER_IRQHandler,
    SPDIF_RX_IRQHandler,
    OTG_FS_EP1_OUT_IRQHandler,
    OTG_FS_EP1_IN_IRQHandler,
    OTG_FS_WKUP_IRQHandler,
    OTG_FS_IRQHandler,
    DMAMUX1_OVR_IRQHandler,
    HRTIM1_Master_IRQHandler,
    HRTIM1_TIMA_IRQHandler,
    HRTIM1_TIMB_IRQHandler,
    HRTIM1_TIMC_IRQHandler,
    HRTIM1_TIMD_IRQHandler,
    HRTIM1_TIME_IRQHandler,
    HRTIM1_FLT_IRQHandler,
    DFSDM1_FLT0_IRQHandler,
    DFSDM1_FLT1_IRQHandler,
    DFSDM1_FLT2_IRQHandler,
    DFSDM1_FLT3_IRQHandler,
    SAI3_IRQHandler,
    SWPMI1_IRQHandler,
    TIM15_IRQHandler,
    TIM16_IRQHandler,
    TIM17_IRQHandler,
    MDIOS_WKUP_IRQHandler,
    MDIOS_IRQHandler,
    JPEG_IRQHandler,
    MDMA_IRQHandler,
    0,
    SDMMC2_IRQHandler,
    HSEM1_IRQHandler,
    0,
    ADC3_IRQHandler,
    DMAMUX2_OVR_IRQHandler,
    BDMA_Channel0_IRQHandler,
    BDMA_Channel1_IRQHandler,
    BDMA_Channel2_IRQHandler,
    BDMA_Channel3_IRQHandler,
    BDMA_Channel4_IRQHandler,
    BDMA_Channel5_IRQHandler,
    BDMA_Channel6_IRQHandler,
    BDMA_Channel7_IRQHandler,
    COMP1_IRQHandler,
    LPTIM2_IRQHandler,
    LPTIM3_IRQHandler,
    LPTIM4_IRQHandler,
    LPTIM5_IRQHandler,
    LPUART1_IRQHandler,
    0,
    CRS_IRQHandler,
    0,
    SAI4_IRQHandler,
    0,
    0,
    WAKEUP_PIN_IRQHandler
};

/*================= Function definitions ==================*/
__attribute__((no_instrument_function)) void Default_Handler()
{
#if !ENABLE_INSTRUMENT_BOOT_TEST
    abort();
#endif
}

__attribute__((no_instrument_function)) void Reset_Handler()
{
    /* set stack pointer */
    __asm("    ldr    sp, =_estack");

    /* Fill stack with magic number for overflow detection */
    __asm("    ldr     r0, =_estack\n"
          "    ldr     r1, =__StackLimit\n"
          "    ldr     r2, =0xDEADBEEF\n"
          "    .thumb_func\n"
          "fill_stack_loop:\n"
          "        cmp     r0, r1\n"
          "        it      gt\n"
          "        strgt   r2, [r0, #-4]!\n"
          "        bgt     fill_stack_loop");

    /* Call the clock system initialization function */
    SystemInit();

    /* Copy the data segment initializers from flash to SRAM */
    uint32_t *sidata, *sdata;
    sidata = &_load_data_startup;
    for(sdata = &_start_data_startup; sdata < &_end_data_startup;)
    {
        *sdata++ = *sidata++;
    }

    uint32_t *siramfunc, *sramfunc;
    siramfunc = &_load_ramfunc_from_flash;
    for(sramfunc = &_start_ramfunc_from_flash; sramfunc < &_end_ramfunc_from_flash;)
    {
        *sramfunc++ = *siramfunc++;
    }
 
    uint32_t *sitcmramfunc, *pitcmramfunc;
    sitcmramfunc = &_load_ramfunc_itcmram;
    for(pitcmramfunc = &_start_ramfunc_itcmram; pitcmramfunc < &_end_ramfunc_itcmram;)
    {
        *pitcmramfunc++ = *sitcmramfunc++;
    }

    /* Zero fill the bss segment */
    __asm("    ldr     r0, =_sbss\n"
          "    ldr     r1, =_ebss\n"
          "    mov     r2, #0\n"
          "    .thumb_func\n"
          "zero_loop:\n"
          "        cmp     r0, r1\n"
          "        it      lt\n"
          "        strlt   r2, [r0], #4\n"
          "        blt     zero_loop");

    __asm("    ldr     r0, =_begin_bss_in_dma_ram\n"
          "    ldr     r1, =_end_bss_in_dma_ram\n"
          "    mov     r2, #0\n"
          "    .thumb_func\n"
          "zero_loop_dma:\n"
          "        cmp     r0, r1\n"
          "        it      lt\n"
          "        strlt   r2, [r0], #4\n"
          "        blt     zero_loop_dma");

    __asm("    ldr     r0, =_begin_dtcmram\n"
          "    ldr     r1, =_end_dtcmram\n"
          "    mov     r2, #0\n"
          "    .thumb_func\n"
          "zero_loop_dtcmram:\n"
          "        cmp     r0, r1\n"
          "        it      lt\n"
          "        strlt   r2, [r0], #4\n"
          "        blt     zero_loop_dtcmram");

    /* Zero fill the tbss segment */
    __asm("    ldr     r0, =_sbss\n"
          "    ldr     r1, =__tbss_end\n"
          "    mov     r2, #0\n"
          "    .thumb_func\n"
          "zero_loop_tbss:\n"
          "        cmp     r0, r1\n"
          "        it      lt\n"
          "        strlt   r2, [r0], #4\n"
          "        blt     zero_loop_tbss");

    /* Call static constructors */
    __libc_init_array();

    /* Call the application's entry point */
    main();
}

/* Weak interrupt handlers that call Default_Handler */
__attribute__((no_instrument_function)) void WWDG_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void PVD_AVD_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TAMP_STAMP_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void RTC_WKUP_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void FLASH_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void RCC_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void EXTI0_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void EXTI1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void EXTI2_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void EXTI3_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void EXTI4_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA1_Stream0_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA1_Stream1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA1_Stream2_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA1_Stream3_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA1_Stream4_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA1_Stream5_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA1_Stream6_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void ADC_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void FDCAN1_IT0_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void FDCAN2_IT0_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void FDCAN1_IT1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void FDCAN2_IT1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void EXTI9_5_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM1_BRK_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM1_UP_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM1_TRG_COM_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM1_CC_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM2_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM3_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM4_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void I2C1_EV_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void I2C1_ER_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void I2C2_EV_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void I2C2_ER_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void SPI1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void SPI2_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void USART1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void USART2_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void USART3_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void EXTI15_10_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void RTC_Alarm_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM8_BRK_TIM12_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM8_UP_TIM13_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM8_TRG_COM_TIM14_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM8_CC_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA1_Stream7_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void FMC_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void SDMMC1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM5_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void SPI3_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void UART4_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void UART5_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM6_DAC_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM7_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA2_Stream0_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA2_Stream1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA2_Stream2_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA2_Stream3_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA2_Stream4_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void ETH_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void ETH_WKUP_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void FDCAN_CAL_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA2_Stream5_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA2_Stream6_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA2_Stream7_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void USART6_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void I2C3_EV_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void I2C3_ER_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void OTG_HS_EP1_OUT_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void OTG_HS_EP1_IN_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void OTG_HS_WKUP_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void OTG_HS_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DCMI_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void RNG_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void FPU_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void UART7_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void UART8_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void SPI4_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void SPI5_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void SPI6_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void SAI1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void LTDC_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void LTDC_ER_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMA2D_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void SAI2_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void QUADSPI_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void LPTIM1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void CEC_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void I2C4_EV_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void I2C4_ER_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void SPDIF_RX_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void OTG_FS_EP1_OUT_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void OTG_FS_EP1_IN_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void OTG_FS_WKUP_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void OTG_FS_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMAMUX1_OVR_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void HRTIM1_Master_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void HRTIM1_TIMA_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void HRTIM1_TIMB_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void HRTIM1_TIMC_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void HRTIM1_TIMD_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void HRTIM1_TIME_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void HRTIM1_FLT_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DFSDM1_FLT0_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DFSDM1_FLT1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DFSDM1_FLT2_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DFSDM1_FLT3_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void SAI3_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void SWPMI1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM15_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM16_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void TIM17_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void MDIOS_WKUP_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void MDIOS_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void JPEG_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void MDMA_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void SDMMC2_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void HSEM1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void ADC3_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void DMAMUX2_OVR_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void BDMA_Channel0_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void BDMA_Channel1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void BDMA_Channel2_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void BDMA_Channel3_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void BDMA_Channel4_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void BDMA_Channel5_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void BDMA_Channel6_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void BDMA_Channel7_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void COMP1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void LPTIM2_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void LPTIM3_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void LPTIM4_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void LPTIM5_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void LPUART1_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void CRS_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void SAI4_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void WAKEUP_PIN_IRQHandler()
{
    Default_Handler();
}

__attribute__((no_instrument_function)) void NMI_Handler()
{
    /* Go into an infinite loop */
    while(1)
    {
    }
}

__attribute__((no_instrument_function)) void HardFault_Handler()
{
    /* Go into an infinite loop */
    while(1)
    {
    }
}

__attribute__((no_instrument_function)) void MemManage_Handler()
{
    /* Go into an infinite loop */
    while(1)
    {
    }
}

__attribute__((no_instrument_function)) void BusFault_Handler()
{
    /* Go into an infinite loop */
    while(1)
    {
    }
}

__attribute__((no_instrument_function)) void UsageFault_Handler()
{
    /* Go into an infinite loop */
    while(1)
    {
    }
}

__attribute__((no_instrument_function)) void SVC_Handler()
{
    /* Go into an infinite loop */
    while(1)
    {
    }
}

__attribute__((no_instrument_function)) void DebugMon_Handler()
{
    /* Go into an infinite loop */
    while(1)
    {
    }
}

__attribute__((no_instrument_function)) void PendSV_Handler()
{
    /* Go into an infinite loop */
    while(1)
    {
    }
}

__attribute__((no_instrument_function)) void SysTick_Handler()
{
    /* Go into an infinite loop */
    while(1)
    {
    }
}
