cmake_minimum_required(VERSION 3.22)
# Enable CMake support for ASM and C languages
enable_language(C ASM)
# STM32CubeMX generated symbols (macros)
set(MX_Defines_Syms 
	USE_PWR_LDO_SUPPLY 
	USE_HAL_DRIVER 
    MBEDTLS_CONFIG_FILE="mbedtls_config.h"
	STM32H750xx 
    CY_USING_HAL
    COMPONENT_WIFI6
    COMPONENT_LWIP
    BLHS_SUPPORT
    CYBSP_WIFI_CAPABLE
    HAVE_SNPRINTF
    DISABLE_COMMAND_CONSOLE_BT
	STM32_THREAD_SAFE_STRATEGY=4
    $<$<CONFIG:Debug>:DEBUG>
)

# STM32CubeMX generated include paths
set(MX_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/../../MBEDTLS/App
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Device/ST/STM32H7xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/source/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-freertos-integration/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/secure-sockets/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/secure-sockets/source/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/bus_protocols/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/resources/resource_imp/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-connection-manager/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/cy_log/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/JSON_parser/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/linked_list/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/cy_string/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/network/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/include/mbedtls/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/whd-bsp-integration/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/whd-bsp-integration
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/posix/arpa
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/posix/net
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/posix
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/posix/sys
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/stdc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/lwip
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/lwip/apps
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/lwip/priv
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/lwip/prot
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-connection-manager/source/COMPONENT_55500/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/core-lib/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/hal/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/common/Inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/COMPONENT_FREERTOS/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/include/COMPONENT_FREERTOS/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/resources/firmware/COMPONENT_55500/COMPONENT_SM/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/resources/nvram/COMPONENT_55500/COMPONENT_MURATA-2FY/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/resources/clm/COMPONENT_55500/COMPONENT_MURATA-2FY/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-connection-manager/source/COMPONENT_55500
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/resources/resource_imp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/hal/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/common/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/core-lib/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/resources/firmware/COMPONENT_55500/COMPONENT_SM
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/resources/clm/COMPONENT_55500/COMPONENT_MURATA-2FY
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-mfg-test/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/bluetooth_utility/COMPONENT_WICED_BLE/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/command_console/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/rtos/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-mfg-test/source
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-mfg-test/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/bluetooth_utility/COMPONENT_WICED_BLE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/command_console
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf_utility
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/wifi_utility
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/include
)

# STM32CubeMX generated application sources
set(MX_Application_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../MBEDTLS/Target/custom_rng.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/console_task.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/freertos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/lptim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/quadspi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/rng.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/sdmmc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/usart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32h7xx_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32h7xx_hal_msp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32h7xx_hal_timebase_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/sysmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/syscalls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../startup_stm32h750xx.c
)

# STM32 HAL/LL Drivers
set(STM32_Drivers_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/system_stm32h7xx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_lptim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_qspi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_delayblock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rng.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rng_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_sdmmc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mmc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mmc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c
)

# Drivers Midllewares


set(FreeRTOS_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/croutine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/tasks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/timers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
)
set(Connectivity_Src
    # ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/bluetooth_utility/COMPONENT_WICED_BLE/bt_cfg.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/bluetooth_utility/COMPONENT_WICED_BLE/bt_utility.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/command_console/command_console.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/compat/delay.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/compat/gettimeofday.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/compat/inet_ntop.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/compat/inet_pton.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/compat/iperf_error.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/compat/signal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/compat/snprintf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/compat/string.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/rtos/condition.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/rtos/iperf_debug.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/rtos/iperf_getopt_long.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/rtos/iperf_gettimeofday.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/rtos/iperf_sockets.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/rtos/iperf_utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/rtos/thread.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/rtos/usleep.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/Extractor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/Locale.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/ReportCSV.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/ReportDefault.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/Reporter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/SocketAddr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/checkdelay.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/checkpdfs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/checksums.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/histogram.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/igmp_querier.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/pdfs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/sockets_iperf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/stdio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/tcp_window_size.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/wifi_utility/COMPONENT_WCM/wifi_utility.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/command_console/command_utility.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/Client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/Launch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/IperfList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/Listener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/PerfSocket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/Server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/Settings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/checkisoch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/isochronous.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf/src/iperf_main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/command-console/source/iperf_utility/iperf_utility.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-mfg-test/source/mfg_test_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-mfg-test/target/COMPONENT_WCM/mfg_test_comp_ioctl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/resources/firmware/COMPONENT_55500/COMPONENT_SM/55500A1_bin.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/resources/firmware/COMPONENT_55500/COMPONENT_SM/55500A1-mfgtest_bin.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/resources/clm/COMPONENT_55500/COMPONENT_MURATA-2FY/55500A1_clm_blob.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/resources/clm/COMPONENT_55500/55500A1-mfgtest_clm_blob.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/bt-fw/bt-fw-ifx-cyw55500a1/COMPONENT_wlbga_iPA_sLNA_ANT0/btfw.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/COMPONENT_FREERTOS/cyabs_freertos_helpers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/COMPONENT_FREERTOS/cyabs_rtos_freertos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/COMPONENT_FREERTOS/cyabs_freertos_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/cy_worker_thread.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/common/Src/cyhal_system.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/common/Src/wifi_bt_if.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_lptimer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_sdio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_trng.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_syspm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/api_lib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/api_msg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/err.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/if_api.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/netbuf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/netdb.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/netifapi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/sockets.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/tcpip.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/altcp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/altcp_alloc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/altcp_tcp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/def.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/dns.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/inet_chksum.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ip.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/autoip.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/dhcp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/etharp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/icmp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/igmp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/ip4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/ip4_addr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/ip4_frag.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/dhcp6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/ethip6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/icmp6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/inet6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/ip6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/ip6_addr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/ip6_frag.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/mld6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/nd6.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/mem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/memp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/netif.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/pbuf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/raw.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/stats.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/sys.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/tcp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/tcp_in.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/tcp_out.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/timeouts.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/udp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/netif/ethernet.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/whd-bsp-integration/cybsp_wifi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/whd-bsp-integration/COMPONENT_LWIP/cy_network_buffer_lwip.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/aes.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/aesni.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/arc4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/aria.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/asn1parse.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/asn1write.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/base64.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/bignum.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/blowfish.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/camellia.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ccm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/certs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/chacha20.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/chachapoly.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/cipher.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/cipher_wrap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/cmac.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ctr_drbg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/debug.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/des.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/dhm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ecdh.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ecdsa.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ecjpake.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ecp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ecp_curves.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/entropy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/entropy_poll.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/error.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/gcm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/havege.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/hkdf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/hmac_drbg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/md.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/md2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/md4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/md5.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/memory_buffer_alloc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/net_sockets.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/nist_kw.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/oid.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/padlock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pk.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pkcs11.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pkcs12.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pkcs5.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pkparse.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pkwrite.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pk_wrap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/platform.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/platform_util.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/poly1305.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/psa_crypto.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/psa_crypto_driver_wrappers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/psa_crypto_se.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/psa_crypto_slot_management.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/psa_crypto_storage.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/psa_its_file.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ripemd160.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/rsa.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/rsa_internal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/sha1.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/sha256.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/sha512.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_cache.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_ciphersuites.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_cli.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_cookie.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_msg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_srv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_ticket.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_tls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_tls13_keys.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/threading.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/timing.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/version.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/version_features.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/x509.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/x509write_crt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/x509write_csr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/x509_create.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/x509_crl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/x509_crt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/x509_csr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/xtea.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/cy_log/cy_log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/JSON_parser/cy_json_parser.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/linked_list/cy_linked_list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/cy_string/cy_string_utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/network/cy_nw_helper_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/network/COMPONENT_LWIP/cy_nw_helper.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-connection-manager/source/cy_wcm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/bus_protocols/whd_bus.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/bus_protocols/whd_bus_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/bus_protocols/whd_bus_sdio_protocol.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/bus_protocols/whd_bus_spi_protocol.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_ap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_buffer_api.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_cdc_bdc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_chip.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_chip_constants.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_clm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_debug.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_events.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_logging.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_management.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_network_if.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_proto.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_resource_if.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_sdpcm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_thread.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_wifi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_wifi_api.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_wifi_p2p.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_commonring.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_flowring.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/src/whd_ring.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI6/resources/resource_imp/whd_resources.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/secure-sockets/source/cy_tls_weak.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/secure-sockets/source/cy_pkcs_psa_logging.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/secure-sockets/source/COMPONENT_LWIP/cy_secure_sockets.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/secure-sockets/source/COMPONENT_MBEDTLS/iot_crypto.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/secure-sockets/source/COMPONENT_MBEDTLS/cy_tls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/source/cy_ethernetif.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/source/cy_lwip_dhcp_server.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/source/cy_network_mw_core.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-freertos-integration/arch/sys_arch.c
)

# Link directories setup
set(MX_LINK_DIRS

)
# Project static libraries
set(MX_LINK_LIBS 
    STM32_Drivers
    ${TOOLCHAIN_LINK_LIBRARIES}
    FreeRTOS
	Connectivity
	
)
# Interface library for includes and symbols
add_library(stm32cubemx INTERFACE)
target_include_directories(stm32cubemx INTERFACE ${MX_Include_Dirs})
target_compile_definitions(stm32cubemx INTERFACE ${MX_Defines_Syms})

# Create STM32_Drivers static library
add_library(STM32_Drivers OBJECT)
target_sources(STM32_Drivers PRIVATE ${STM32_Drivers_Src})
target_link_libraries(STM32_Drivers PUBLIC stm32cubemx)


# Create FreeRTOS static library
add_library(FreeRTOS OBJECT)
target_sources(FreeRTOS PRIVATE ${FreeRTOS_Src})
target_link_libraries(FreeRTOS PUBLIC stm32cubemx)

# Create Connectivity static library
add_library(Connectivity OBJECT)
target_sources(Connectivity PRIVATE ${Connectivity_Src})
target_link_libraries(Connectivity PUBLIC stm32cubemx)
target_compile_options(Connectivity PRIVATE -include ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/include/cyabs_rtos.h)

# Add STM32CubeMX generated application sources to the project
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MX_Application_Src})

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${MX_LINK_DIRS})

# Add libraries to the project
target_link_libraries(${CMAKE_PROJECT_NAME} ${MX_LINK_LIBS})

# Add the map file to the list of files to be removed with 'clean' target
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

# Validate that STM32CubeMX code is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
