/* Entry Point */
ENTRY(Reset_Handler)

/* Specify the memory areas */
MEMORY
{
  DTCMRAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 128K
  RAM (xrw)          : ORIGIN = 0x24000000, LENGTH = 512K
  RAM_D2 (xrw)       : ORIGIN = 0x30000000, LENGTH = 288K
  RAM_D3 (xrw)       : ORIGIN = 0x38000000, LENGTH = 64K
  ITCMRAM (xrw)      : ORIGIN = 0x00000000, LENGTH = 64K
  FLASH (rx)         : ORIGIN = 0x8000000,  LENGTH = 128K
  QSPI (rx)          : ORIGIN = 0x90000000, LENGTH = 0x1E0000
  OTA (rw)           : ORIGIN = 0x901E0000, LENGTH = 0x1E0000
  NVS (rw)           : ORIGIN = 0x903C0000, LENGTH = 0x40000
}

/* Highest address of the user mode stack */
_estack = ORIGIN(DTCMRAM) + LENGTH(DTCMRAM);    /* end of RAM */
/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x400;      /* required amount of heap  */
_Min_Stack_Size = 0x2000; /* required amount of stack */

/* Stack limit for overflow detection */
__StackLimit = _estack - _Min_Stack_Size;

/* Define output sections */
SECTIONS
{
  /*--------------------------------------------------------------
                .isr_vector => ITCMRAM @ FLASH
  --------------------------------------------------------------*/

  /* The startup code goes first into ITCMRAM */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >ITCMRAM AT> FLASH

  /*--------------------------------------------------------------
                      OVERRIDEN .bss
  --------------------------------------------------------------*/

  .dtcmram : 
  {
    . = ALIGN(4);
    _begin_dtcmram = .;
    *(.bss.ucHeap)
    . = ALIGN(4);
    _end_dtcmram = .;
  } >DTCMRAM

  /*--------------------------------------------------------------
                      OVERRIDEN .bss (DMA)
  --------------------------------------------------------------*/

  .bss_in_dma_ram (NOLOAD) :
  {
    . = ALIGN(4);
    _begin_bss_in_dma_ram = .;
    *(.bss._temp_dma_buffer.0)
    *(.bss.dns_table)
    *(.bss.cy_log)
    *(.bss.socket_ipv6_multicast_memberships)
    *(.bss.lwip_stats)
    *(.bss._exti_callbacks_info)

    *(.bss.connected_ap_details)
    *(.bss.huart3)
    *(.bss.huart4)
    *(.bss.hspi4)
    *(.bss.hspi1)
    *(.bss.r_buffer)
    *(.bss.eth1_ip_handle)
    *(.bss.sta_ip_handle)

    *(.bss.pxReadyTasksLists)
    *(.bss.Idle_Stack.2)
    *(.bss.Timer_TCB.1)
    *(.bss.Timer_Stack.0)
    *(.bss.memp_memory_TCP_PCB_base)
    *(.bss.memp_stats_TCP_PCB)
    *(.bss.memp_memory_TCP_PCB_LISTEN_base)
    *(.bss.memp_memory_TCP_SEG_base)
    *(.bss.memp_memory_TCPIP_MSG_API_base)
    *(.bss.memp_memory_IGMP_GROUP_base)
    *(.bss.memp_memory_ND6_QUEUE_base)
    *(.bss.memp_memory_IP6_REASSDATA_base)
    *(.bss.memp_memory_MLD6_GROUP_base)
    *(.bss.scan_handler)
    *(.bss.__sf)
    *(.bss.memp_stats_TCP_SEG)
    *(.data.__global_locale)
    *(.data.impure_data)
    *(.bss.hlptim1)
    
    *dma.c.obj*(.bss*)
    *quadspi.c.obj*(.bss*)
    *cy_network_mw_core.c.obj*(.bss*)

    . = ALIGN(4);
    _end_bss_in_dma_ram = .;
  } >RAM

  /*--------------------------------------------------------------
                      OVERRIDEN .bss (DMA)
  --------------------------------------------------------------*/

  .bss_in_ram_d2 (NOLOAD) :
  {
    . = ALIGN(4);
    _begin_bss_in_ram_d2 = .;
    
    *parameter*(.bss*)
    *uart*(.bss*)
    *transmitter*(.bss*)
    *receiver*(.bss*)

    *(.bss.socket_ipv4_multicast_memberships)
    *(.bss.memp_memory_SYS_MBOX_base)
    *(.bss.memp_memory_NETCONN_base)
    *(.bss.memp_memory_POOL_1792_base)
    *(.bss.memp_memory_POOL_128_base)
    *(.bss.memp_memory_POOL_4096_base)

    *(.bss.hci_uart_cb)
    *(.bss.parameters_data)
    *(.bss.bt_trace_buf)
  
    . = ALIGN(4);
    _end_bss_in_ram_d2 = .;
  } >RAM_D2

  /*--------------------------------------------------------------
                      OVERRIDEN .text => FLASH
  --------------------------------------------------------------*/

  .text_startup :
  {
    . = ALIGN(4);
    *(.flash_text*)
    
    *quadspi.c.obj*(.text*)
    
    *startup_stm32h750xx.c.obj*(.text*)

    *(.text.main)
    *(.text.SystemClock_Config)
    *(.text.PeriphCommonClock_Config)
    *(.text.Error_Handler)
    *(.text.deregister_tm_clones)
    *(.text.register_tm_clones)
    *(.text.__do_global_dtors_aux)
    *(.text.frame_dummy)
    *(.text.NMI_Handler)
    *(.text.HardFault_Handler)
    *(.text.MemManage_Handler)
    *(.text.BusFault_Handler)
    *(.text.UsageFault_Handler)
    *(.text.DebugMon_Handler)
    *(.text.__NVIC_SetPriorityGrouping)
    *(.text.__NVIC_GetPriorityGrouping)
    *(.text.__NVIC_SetPriority)
    *(.text.NVIC_EncodePriority)
    *(.text.HAL_NVIC_SetPriorityGrouping)
    *(.text.HAL_NVIC_SetPriority)
    *(.text.HAL_RCC_OscConfig)
    *(.text.HAL_RCC_ClockConfig)
    *(.text.HAL_RCC_GetPCLK2Freq)
    *(.text.HAL_RCC_GetClockConfig)
    *(.text.HAL_MspInit)
    *(.text.HAL_Init)
    *(.text.HAL_GetREVID)
    *(.text.HAL_GPIO_DeInit)
    *(.text.HAL_RCCEx_PeriphCLKConfig)
    *(.text.RCCEx_PLL2_Config)
    *(.text.RCCEx_PLL3_Config)
    *(.text.HAL_QSPI_MspInit)
    *(.text.HAL_QSPI_MspDeInit)
    *(.text.qspi_setClockPrescaler)
    *(.text.BSP_QSPI_Init)
    *(.text.BSP_QSPI_GetStatus)
    *(.text.BSP_QSPI_EnableMemoryMappedMode)
    *(.text.QSPI_ResetMemory)
    *(.text.QSPI_WriteEnable)
    *(.text.QSPI_AutoPollingMemReady)
    *(.text.QSPI_QuadMode)
    *(.text.QSPI_HighPerfMode)
    *(.text.HAL_QSPI_Init)
    *(.text.HAL_QSPI_DeInit)
    *(.text.HAL_QSPI_Command)
    *(.text.HAL_QSPI_Transmit)
    *(.text.HAL_QSPI_Receive)
    *(.text.HAL_QSPI_AutoPolling)
    *(.text.HAL_QSPI_MemoryMapped)
    *(.text.HAL_QSPI_SetTimeout)
    *(.text.QSPI_WaitFlagStateUntilTimeout)
    *(.text.QSPI_Config)
    *(.text.HAL_TIM_Base_Init)
    *(.text.HAL_TIM_OC_DelayElapsedCallback)
    *(.text.HAL_TIM_IC_CaptureCallback)
    *(.text.HAL_TIM_PWM_PulseFinishedCallback)
    *(.text.HAL_TIM_TriggerCallback)
    *(.text.TIM_Base_SetConfig)
    *(.text.HAL_InitTick)
    *(.text.__libc_init_array)
    *(.text.Reset_Handler)
    *(.text.zero_loop)
    *(.text.SystemInit)
    *(.text.HAL_TIM_Base_MspInit)
    *(.text.HAL_PWREx_ConfigSupply)
    *(.text._init)
    *(.text.__EH_FRAME_BEGIN__)
    *(.text._fini)
    *(.text.memset)
    *(.text.__HAL_TIMEx_BreakCallback_veneer)
    *(.text.__HAL_TIMEx_Break2Callback_veneer)
    *(.text.__HAL_TIMEx_CommutCallback_veneer)

    *(.text.SCB_EnableICache)
    *(.text.SCB_EnableDCache)

    *(.text.__udivmoddi4)
    *libc_a-memchr.o*(.text*)
    
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    *libg_nano.a:*(.text*)
    *libgcc.a:*(.text*)

    *(.text.ReportHardFault)
    *(.text.bsp_breakpoint)
    *(.text.sprintf)
    *(.text.printf)

    *(.text.copy_memory_section)
    *(.text.HAL_TIMEx_CommutCallback)
    *(.text.HAL_TIMEx_BreakCallback)
    *(.text.HAL_TIMEx_Break2Callback)
    *(.text.__io_getchar)
    *(.text.__stub)

    *stm32h7xx_it.c.obj*(.text*)
    
    *(.text.__enable_irq)
    . = ALIGN(4);
  } >FLASH

  /*--------------------------------------------------------------
                      OVERRIDEN .rodata => FLASH
  --------------------------------------------------------------*/

  .rodata_startup :
  {
    . = ALIGN(4);
    
    *libg_nano.a:*(.rodata*)
    *libgcc.a:*(.rodata*)

    . = ALIGN(4);
  } >FLASH

  /*--------------------------------------------------------------
                OVERRIDEN .data => DTCMRAM @ FLASH
  --------------------------------------------------------------*/
 
  _load_data_startup = LOADADDR(.data_startup);
  .data_startup :
  {
    . = ALIGN(4);
    _start_data_startup = .;
    *(.data.uwTickPrio)
    *(.data.uwTickFreq)
    *(.data.SystemCoreClock)
    *(.data.SystemD2Clock)

    *libg_nano.a:*(.data*)
    *libgcc.a:*(.data*)

    . = ALIGN(4);
    _end_data_startup = .;
  } >DTCMRAM AT> FLASH

  /*--------------------------------------------------------------
                 OVERRIDEN .text => ITCMRAM @ QSPI
  --------------------------------------------------------------*/

  _load_itcmramfunc_from_qspi = LOADADDR(.itcmramfunc_from_qspi);
  .itcmramfunc_from_qspi :
  {
    . = ALIGN(4);
    _start_itcmramfunc_from_qspi = .;

    *(.text.SDMMC1_IRQHandler)
    *(.text.stm32_cyhal_sdio_irq_handler)
    *(.text.cy_rtos_set_semaphore)
    
    *(.text.enter_critical_section)
    *(.text.HAL_TIM_Base_Stop)
    *(.text.HAL_TIM_IC_Start_IT)
    *(.text.HAL_TIM_ReadCapturedValue)
    *(.text.__NVIC_DisableIRQ)
    *(.text.HAL_GPIO_TogglePin)
    *(.text.HAL_GPIO_EXTI_Callback)
    *(.text.__disable_irq)
    *(.text.__get_PRIMASK)
    *(.text.__set_PRIMASK)
    *(.text.exit_critical_section)
    *(.text.semaphore_signal)
    *(.text.whd_cdc_send_ioctl)

    *(.text.SDMMC1_IRQHandler)
    *(.text.whd_bus_packet_available_to_read)
    *(.text.whd_bus_sdio_packet_available_to_read)
    *(.text.whd_chip_get_chip_id)
    *(.text.whd_kso_enable)
    *(.text.whd_bus_write_register_value)
    *(.text.whd_bus_sdio_write_register_value)
    *(.text.whd_bus_sdio_transfer)
    *(.text.whd_bus_sdio_cmd52)
    *(.text.whd_network_send_ethernet_data)
    *(.text.whd_proto_tx_queue_data)
    *(.text.whd_cdc_tx_queue_data)
    *(.text.whd_send_to_bus)
    *(.text.whd_sdpcm_set_next_buffer_in_queue)
    *(.text.whd_thread_notify)
    *(.text.whd_bus_is_flow_controlled)
    *(.text.whd_sdpcm_get_next_buffer_in_queue)
    *(.text.whd_bus_send_buffer)
    *(.text.whd_bus_sdio_send_buffer)
    *(.text.whd_bus_transfer_bytes)
    *(.text.whd_bus_sdio_transfer_bytes)
    *(.text.whd_bus_write_backplane_value)
    *(.text.whd_bus_sdio_write_backplane_value)
    *(.text.whd_thread_receive_one_packet)
    *(.text.whd_bus_read_frame)
    *(.text.whd_bus_sdio_read_frame)
    *(.text.whd_sdpcm_has_tx_packet)
    *(.text.whd_host_buffer_get)
    *(.text.whd_bus_read_register_value)
    *(.text.whd_bus_sdio_read_register_value)
    *(.text.whd_mem_memset)
    *(.text.whd_bus_set_state)
    *(.text.get_whd_var)
    *(.text.get_sdiod_core_base_address)
    *(.text.whd_bus_read_backplane_value)
    *(.text.whd_bus_sdio_read_backplane_value)
    *(.text.whd_bus_set_backplane_window)
    *(.text.whd_bus_sdio_set_backplane_window)
    *(.text.whd_bus_sdio_cmd53)
    *(.text.cy_host_buffer_get)
    *(.text.SDMMC_ConfigData)
    *(.text._stm32_sdio_cmd_rw_extended)
    *(.text.cy_rtos_semaphore_get)
    *(.text.convert_ms_to_ticks)
    *(.text.whd_buffer_get_current_piece_data_pointer)
    *(.text.cy_buffer_get_current_piece_data_pointer)
    *(.text.whd_mem_memcpy)
    *(.text._stm32_sdio_convert_block_size)
    *(.text.whd_delayed_bus_release_schedule_update)
    *(.text.whd_sdpcm_process_rx_packet)
    *(.text.whd_buffer_get_current_piece_size)
    *(.text.cy_buffer_get_current_piece_size)
    *(.text.whd_sdpcm_update_credit)
    *(.text.whd_bus_set_flow_control)
    *(.text.cyhal_sdio_bulk_transfer)
    *(.text.stm32_cyhal_sdio_irq_handler)
    *(.text.whd_bus_sdio_irq_handler)
    *(.text.netbuf_free)
    *(.text.lwip_sendto)
    *(.text._stm32_sdio_find_optimal_block_size)
    *(.text.cyhal_system_critical_section_enter)
    *(.text.__disable_irq)
    *(.text.cyhal_system_critical_section_exit)
    *(.text.whd_process_bdc)
    *(.text.whd_network_process_ethernet_data)
    *(.text.cy_network_process_ethernet_data)
    *(.text.whd_wifi_is_ready_to_transceive)
    *(.text.whd_wifi_get_ap_is_up)
    *(.text.whd_thread_notify_irq)
    *(.text.whd_thread_func)
    *(.text.whd_thread_send_one_packet)  
    *(.text.whd_set_error_handler_locally)
    *(.text.whd_bus_wait_for_wlan_event)

    *(.text.cy_worker_thread_func)

    *(.text.sockaddr_to_ipaddr_port)
    *(.text.pbuf_init_alloced_pbuf)
    *(.text.mld6_lookfor_group)
    *(.text.wifioutput)
    *(.text.etharp_query)
    *(.text.pbuf_ref)
    *(.text.sys_arch_protect)
    *(.text.sys_arch_unprotect)
    *(.text.pbuf_free)
    *(.text.mem_free)
    *(.text.__retarget_lock_acquire_recursive)
    *(.text.stm32_lock_acquire)
    
    *(.text.udp_sendto_if_chksum)
    *(.text.udp_sendto_if_src_chksum)
    *(.text.pbuf_add_header)
    *(.text.pbuf_add_header_impl)
    *(.text.ip_chksum_pseudo_partial)
    *(.text.inet_chksum_pseudo_partial)
    *(.text.inet_cksum_pseudo_partial_base)
    *(.text.etharp_input)
    *(.text.etharp_update_arp_entry)
    *(.text.ethernet_output)
    *(.text.ethernet_input)
    *(.text.ip6_input)
    *(.text.lwip_htonl)
    *(.text.netbuf_alloc)
    *(.text.pbuf_alloc)
    *(.text.mem_malloc)
    *(.text.lwip_htons)
    *(.text.lwip_chksum_copy)
    *(.text.lwip_standard_chksum)
    *(.text.netconn_send)
    *(.text.netconn_apimsg)
    *(.text.tcpip_send_msg_wait_sem)
    *(.text.lwip_netconn_do_send)
    *(.text.udp_sendto_chksum)
    *(.text.ip4_route)
    *(.text.sys_check_core_locking)
    *(.text.ip4_output_if_src)
    *(.text.ip4_output_if_opt_src)
    *(.text.inet_chksum)
    *(.text.etharp_output)
    *(.text.tcpip_input)
    *(.text.tcpip_inpkt)
    *(.text.tcpip_thread)
    *(.text.tcpip_thread_handle_msg)
    *(.text.tcpip_timeouts_mbox_fetch)
    *(.text.sys_check_timeouts)
    *(.text.sys_arch_mbox_fetch)
    *(.text.pbuf_realloc)
    *(.text.pbuf_dup)
    *(.text.pbuf_copy)
    *(.text.ip4_input)
    *(.text.ip4_input_accept)
    *(.text.raw_input)
    *(.text._sbrk)
    *(.text.inet_chksum_pbuf)
    *(.text.ip4_output_if)
    *(.text.ip4_output_if_opt)

    *(.text.cyhal_sdio_send_cmd)
    *(.text._stm32_sdio_cmd_rw_direct)
    *(.text.SDMMC_SendCommand)
    *(.text._stm32_sdio_get_cmd_resp5)
    *(.text.SDMMC_GetCommandResponse)
    *(.text.SDMMC_GetResponse)

    *portable/GCC/ARM_CM4F/port.c.obj*(.text*)
    *whd_bus_common.c.obj*(.text*)
    *tasks.c.obj*(.text*)
    *portable/MemMang/heap_4.c.obj*(.text*)

    *(.text.device_config_is_transmitter)
    *(.text.HAL_RCCEx_GetPLL3ClockFreq)
    *(.text.TIM17_IRQHandler)
    *(.text.sys_now)
    *(.text.memp_free)
    *(.text.do_memp_free_pool)
    *(.text.lwip_cyclic_timer)
    *(.text.sys_timeout_abs)
    *(.text.memp_malloc)
    *(.text.do_memp_malloc_pool)
    *(.text.sys_timeouts_sleeptime)
    *(.text.ip_reass_tmr)
    *(.text.etharp_tmr)
    *(.text.dns_tmr)
    *(.text.dns_check_entries)
    *(.text.dns_check_entry)
    *(.text.lwip_recvfrom)
    *(.text.lwip_recvfrom_udp_raw)
    *(.text.netconn_recv_udp_raw_netbuf_flags)
    *(.text.netconn_recv_data)
    *(.text.cy_wcm_get_associated_client_list)
    *(.text.cy_rtos_mutex_get)
    *(.text.whd_wifi_get_associated_client_list)
    *(.text.whd_proto_get_ioctl_buffer)
    *(.text.whd_cdc_get_ioctl_buffer)
    *(.text.whd_proto_get_ioctl)
    *(.text.whd_cdc_get_ioctl)
    *(.text.whd_cdc_send_ioctl)
    *(.text.whd_bus_use_status_report_scheme)
    *(.text.whd_sdpcm_get_packet_to_send)
    *(.text.SCB_CleanDCache_by_Addr)
    *(.text.whd_buffer_release)
    *(.text.cy_buffer_release)
    *(.text.cy_rtos_time_get)
    *(.text.whd_mem_malloc)
    *(.text.SCB_InvalidateDCache_by_Addr)
    *(.text.SCB_CleanInvalidateDCache_by_Addr)
    *(.text.whd_mem_free)
    *(.text.whd_buffer_add_remove_at_front)
    *(.text.cy_buffer_add_remove_at_front)
    *(.text.pbuf_header)
    *(.text.pbuf_header_impl)
    *(.text.pbuf_remove_header)
    *(.text.whd_process_cdc)
    *(.text.whd_process_bdc_event)

    *(.text.whd_bus_sdio_read_frame)
    *(.text.whd_bus_sdio_blhs)
    *(.text.whd_bus_sdio_cmd53)
    *(.text.whd_bus_sdio_packet_available_to_read)
    *(.text.whd_bus_sdio_cmd52)
    *(.text.whd_bus_sdio_wake_interrupt_present)
    *(.text.whd_bus_sdio_transfer)
    *(.text.whd_bus_sdio_blhs_wait_d2h)
    *(.text.whd_bus_sdio_send_buffer)
    *(.text.whd_bus_sdio_oob_irq_handler)
    *(.text.whd_bus_sdio_irq_handler)
    *(.text.whd_bus_sdio_read_register_value)
    *(.text.whd_bus_sdio_write_register_value)
    *(.text.whd_bus_sdio_transfer_bytes)
    *(.text.whd_bus_sdio_irq_enable)
    *(.text.whd_bus_sdio_poke_wlan)
    *(.text.whd_bus_sdio_ack_interrupt)

    *(.text.etharp_request)
    *(.text.etharp_request_dst)

    *(.text.udp_input)
    *(.text.udp_input_local_match)
    *(.text.ip_chksum_pseudo)
    *(.text.inet_chksum_pseudo)
    *(.text.inet_cksum_pseudo_base)
    *(.text.recv_udp)
    *(.text.sys_mbox_trypost)
    *(.text.event_callback)
    *(.text.pbuf_copy_partial)
    *(.text.lwip_sock_make_addr)
    *(.text.netbuf_delete)

    *(.text.HAL_GPIO_EXTI_IRQHandler)
    *(.text.HAL_DMA_IRQHandler)
    *(.text.HAL_DMAEx_MUX_IRQHandler)

    *(.text.NVIC_SetPendingIRQ)
    *(.text.xSemaphoreGiveFromISR)
    *(.text.xQueueGiveFromISR)
    *(.text.portYIELD_FROM_ISR)

    *libm.a:*(.text*)

    *cy_worker_thread.c.obj*(.text*)
    *timers.c.obj*(.text*)

    *(.text.__get_PRIMASK)
    *(.text.__NVIC_SetPendingIRQ)
    *(.text.DMA1_Stream1_IRQHandler)
    
    . = ALIGN(4);
    _end_itcmramfunc_from_qspi = .;
  } >ITCMRAM AT> QSPI

  /*--------------------------------------------------------------
                .ramfunc_itcmram => ITCMRAM @ FLASH
  --------------------------------------------------------------*/

  _load_ramfunc_itcmram = LOADADDR(.ramfunc_itcmram);
  .ramfunc_itcmram :
  {
    . = ALIGN(4);
    _start_ramfunc_itcmram = .;
    *(.RamFunc)        /* .RamFunc sections */
    *(.RamFunc*)       /* .RamFunc* sections */
    *(.ramfunc_itcmram*)

    *(.text.memcpy)
    *(.text.__NVIC_EnableIRQ)
    *crtfastmath.o*(.text*)

    . = ALIGN(4);
    _end_ramfunc_itcmram = .;
  } >ITCMRAM AT> FLASH

  /*--------------------------------------------------------------
                 OVERRIDEN .text => RAM_D2 @ QSPI
  --------------------------------------------------------------*/

  _load_ram_d2_func_from_qspi = LOADADDR(.ram_d2_func_from_qspi);
  .ram_d2_func_from_qspi :
  {
    . = ALIGN(4);
    _start_ram_d2_func_from_qspi = .;

    *whd_utils.c.obj*(.rodata*)

    . = ALIGN(4);
    _end_ram_d2_func_from_qspi = .;
  } >RAM_D2 AT> QSPI

  /*--------------------------------------------------------------
                 OVERRIDEN .text => RAM_D3 @ QSPI
  --------------------------------------------------------------*/

  _load_ram_d3_func_from_qspi = LOADADDR(.ram_d3_func_from_qspi);
  .ram_d3_func_from_qspi :
  {
    . = ALIGN(4);
    _start_ram_d3_func_from_qspi = .;

    *logger.c*(.text*)

    . = ALIGN(4);
    _end_ram_d3_func_from_qspi = .;
  } >RAM_D3 AT> QSPI

  /*--------------------------------------------------------------
                 OVERRIDEN .text => RAM @ FLASH
  --------------------------------------------------------------*/

  _load_ramfunc_from_flash = LOADADDR(.ramfunc_from_flash);
  .ramfunc_from_flash :
  {
    . = ALIGN(4);
    _start_ramfunc_from_flash = .;

    *(.text.HAL_TIM_Base_Start_IT)
    *(.text.HAL_GPIO_Init)
    *(.text.HAL_Delay)
    *(.text.HAL_IncTick)
    *(.text.HAL_GetTick)
    *(.text.HAL_NVIC_EnableIRQ)
    *(.text.HAL_TIM_PeriodElapsedCallback)
    *(.text.TIM17_IRQHandler)
    *(.text.HAL_TIM_IRQHandler)

    *(.text.HAL_RCC_GetHCLKFreq)
    *(.text.HAL_RCC_GetSysClockFreq)
    *(.text.HAL_RCC_GetPCLK1Freq)
    *(.rodata.D1CorePrescTable)

    *(.text.__ISB)
    *(.text.__DSB)
    
    *(.ramfunc_from_flash*)
    *trace.c.obj*(.text*)

    *(.iplt*)
    *(.v4_bx*)
    *(.vfp11_veneer*)

    *(.text.RCCEx_PLL3_Config*)
    *(.text.RCCEx_PLL3_Config*)
    *(.text.RCCEx_PLL2_Config*)
    *(.text.HAL_RCC_GetSysClockFreq*)

    *(.text.__cyg_profile_func_enter*)
    *(.text.__cyg_profile_func_exit*)
    *(.text.trace_record*)
    
    . = ALIGN(4);
    _end_ramfunc_from_flash = .;
  } >RAM AT> FLASH
  
  /*--------------------------------------------------------------
                 OVERRIDEN .text => RAM @ QSPI
  --------------------------------------------------------------*/

  _load_ramfunc_from_qspi = LOADADDR(.ramfunc_from_qspi);
  .ramfunc_from_qspi :
  {
    . = ALIGN(4);
    _start_ramfunc_from_qspi = .;
    *(.RamFunc)        /* .RamFunc sections */
    *(.RamFunc*)       /* .RamFunc* sections */
    *(.ramfunc_from_qspi*)

    *(.text.HAL_SPI_TransmitReceive)
    *(.text.HAL_DMA_Abort_IT)
    *(.text.HAL_DMA_Start_IT)
    *(.text.HAL_TIM_Base_Stop_IT)
    *(.text.DMA_SetConfig)
    *(.text.HAL_GPIO_WritePin)
    *(.text.HAL_NVIC_DisableIRQ)
    *(.text.HAL_DMA_Abort_IT)
    *(.text.HAL_TIM_Base_Stop_IT)
    *(.text.TIM8_BRK_TIM12_IRQHandler)
    *(.text.DMAMUX1_OVR_IRQHandler)
    *(.text.HAL_DMAEx_MUX_IRQHandler)
    *(.text.EXTI4_IRQHandler)

    *(.text.__io_putchar)
    *(.text.HAL_UART_Transmit)
    *(.text.UART_WaitOnFlagUntilTimeout)
    *(.text.UART_EndRxTransfer)

    *(.text.DMA1_Stream0_IRQHandler)
    *(.text.HAL_DMA_IRQHandler)
    *(.text.is_init_done)
    *(.text.HAL_GPIO_WritePin)
    *(.text.get_delay_ticks)

    *(.text.ip4_addr_isbroadcast_u32)
    *(.text.xPortIsInsideInterrupt)
    *(.text.__retarget_lock_release_recursive)
    *(.text.stm32_lock_release)
    *(.text.sys_mutex_unlock)
    *(.text.sys_sem_signal)
    *(.text.err_to_errno)
    *(.text.construct_and_send_packet)
    *(.text.get_socket)
    *(.text.tryget_socket)
    *(.text.tryget_socket_unconn)
    *(.text.tryget_socket_unconn_nouse)
    *(.text.sys_mutex_lock)
    *(.text.netconn_err)
    *(.text.HAL_TIM_IC_Start_IT)
    *(.text.bsp_delay_us)
    *(.text.TIM2_IRQHandler)
    *(.text.HAL_TIM_IC_CaptureCallback)
    *(.text.HAL_TIM_ReadCapturedValue)
    *(.text.HAL_GPIO_TogglePin)
    *(.text.cy_rtos_semaphore_set)
    *(.text.is_in_isr)
    *(.text.__get_IPSR)
    *(.text.cy_worker_thread_enqueue)
    *(.text.__set_PRIMASK)
    *(.text.cy_rtos_queue_put)
    *(.text.ap_callback_handler)
    *(.text.cy_log_msg)
    *(.text.invoke_app_callbacks)
    *(.text.cy_rtos_queue_get)
    *(.text.cy_network_register_ip_change_cb)
    *(.text.udp_connect)
    *(.text.HAL_TIM_OC_Start)
    *(.text.HAL_TIM_ConfigClockSource)

    *croutine.c.obj*(.text*)
    *event_groups.c.obj*(.text*)
    *list.c.obj*(.text*)
    *queue.c.obj*(.text*)
    *stream_buffer.c.obj*(.text*)
    *CMSIS_RTOS_V2/cmsis_os2.c.obj*(.text*)

    *syscalls.c.obj*(.text*)
    *network.c.obj*(.text*)
    *newlib_lock_glue.c.obj*(.text*)

    *(.text.print)
   
    *(.text.USART3_IRQHandler_Callback)
    *(.text.netifapi_arp_add)
    *(.text.etharp_add_static_entry)
    *(.text.udp_bind)
    *(.text.udp_new_port)

    *(.text.whd_sdpcm_get_available_credits)
    *(.text.ap_link_events_handler)
    *(.text.whd_allow_wlan_bus_to_sleep)
    *(.text.cy_rtos_mutex_set)
    *(.text.igmp_tmr)
    *(.text.icmp_input)
    *(.text.etharp_find_entry)
    *(.text.etharp_raw)
    *(.text.etharp_output_to_arp_index)
    *(.text.igmp_lookfor_group)
    *(.text.whd_bus_poke_wlan)
    *(.text.whd_ensure_wlan_bus_is_up)
    *(.text.whd_bus_is_up)

    *whd_bus_sdio_protocol.c.obj*(.text*)

    . = ALIGN(4);
    _end_ramfunc_from_qspi = .;
  } >RAM AT> QSPI
  
  /*--------------------------------------------------------------
                      .text => QSPI
  --------------------------------------------------------------*/

  _load_text_in_qspi = LOADADDR(.text);
  .text :
  {
    . = ALIGN(4);
    _start_text_in_qspi = .;
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.force_text_in_qspi)
    . = ALIGN(4);
    _end_text_in_qspi = .;
    _etext = .;
  } >RAM AT>QSPI

  /*--------------------------------------------------------------
                    OVERRIDEN .rodata => QSPI
  --------------------------------------------------------------*/

  .rodata_in_qspi :
  {
    . = ALIGN(4);
    *(.rodata.wifi_firmware_image_data)
    *(.rodata.wifi_nvram_image)
    *(.rodata.brcm_patchram_buf)
    *(.rodata.parameters_data_default)
    *(.rodata.parameters_gatt_database)
    *cybt_hci_rx_task*(.rodata)
    . = ALIGN(4);
  } >QSPI

  /*--------------------------------------------------------------
                  .rodata => RAM @ QSPI
  --------------------------------------------------------------*/

  _load_rodata = LOADADDR(.rodata);
  .rodata :
  {
    . = ALIGN(4);
    _start_rodata = .;
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */

    . = ALIGN(4);
    _end_rodata = .;
  } >RAM AT> QSPI

  /*--------------------------------------------------------------
                    .data => DTCMRAM @ QSPI
  --------------------------------------------------------------*/

  _load_data = LOADADDR(.data);
  .data :
  {
    . = ALIGN(4);
    _start_data = .;
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    . = ALIGN(4);
  } >DTCMRAM AT> QSPI

  /*--------------------------------------------------------------
               .ram_dma => RAM_D3
  --------------------------------------------------------------*/

  .ram_dma (NOLOAD) :
  {
    _begin_ram_dma = .;
    . = ALIGN(4);
    *(.ram_dma)
    *(.ram_dma*)
    . = ALIGN(4);
    _end_ram_dma = .;
  } >RAM_D3

  /*--------------------------------------------------------------
               .ram_d2 => RAM_D2 0x30000000: 288K
  --------------------------------------------------------------*/

  .ram_d2 (NOLOAD) :
  {
    . = ALIGN(4);
    *(.ram_d2)
    *(.ram_d2*)
    . = ALIGN(4);
  } >RAM_D2

  /*--------------------------------------------------------------
                      .ARM sections
  --------------------------------------------------------------*/

  .ARM.extab : 
  {
    . = ALIGN(4);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } >QSPI

  .ARM : 
  {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } >FLASH

  .preinit_array : 
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } >FLASH

  .init_array : 
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } >FLASH

  .fini_array : 
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } >FLASH

  /*--------------------------------------------------------------
                .tdata => DTCMRAM @ QSPI
  --------------------------------------------------------------*/

 /* Initialized TLS data section */
  .tdata : ALIGN(4)
  {
    *(.tdata .tdata.* .gnu.linkonce.td.*)
    . = ALIGN(4);
    _end_data = .;        /* define a global symbol at data end */
    PROVIDE(__data_end = .);
    PROVIDE(__tdata_end = .);
    . = ALIGN(4);
  } >DTCMRAM AT> QSPI

  PROVIDE( __tdata_start = ADDR(.tdata) );
  PROVIDE( __tdata_size = __tdata_end - __tdata_start );

  PROVIDE( __data_start = ADDR(.data) );
  PROVIDE( __data_size = __data_end - __data_start );

  PROVIDE( __tdata_source = LOADADDR(.tdata) );
  PROVIDE( __tdata_source_end = LOADADDR(.tdata) + SIZEOF(.tdata) );
  PROVIDE( __tdata_source_size = __tdata_source_end - __tdata_source );

  PROVIDE( __data_source = LOADADDR(.data) );
  PROVIDE( __data_source_end = __tdata_source_end );
  PROVIDE( __data_source_size = __data_source_end - __data_source );

  PROVIDE(__QSPI_START = ORIGIN(QSPI));
  PROVIDE(__QSPI_END = ORIGIN(QSPI) + LENGTH(QSPI));
  PROVIDE(__QSPI_SIZE = LENGTH(QSPI));

  PROVIDE(__OTA_START = ORIGIN(OTA));
  PROVIDE(__OTA_END = ORIGIN(OTA) + LENGTH(OTA));
  PROVIDE(__OTA_SIZE = LENGTH(OTA));

  PROVIDE(__NVS_START = ORIGIN(NVS));
  PROVIDE(__NVS_END = ORIGIN(NVS) + LENGTH(NVS));
  PROVIDE(__NVS_SIZE = LENGTH(NVS));

  /*--------------------------------------------------------------
                .tbss => DTCMRAM
  --------------------------------------------------------------*/

  /* Uninitialized data section */
  .tbss (NOLOAD) : ALIGN(4)
  {
     /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.tbss .tbss.*)
    . = ALIGN(4);
    PROVIDE( __tbss_end = . );
  } >DTCMRAM

  PROVIDE( __tbss_start = ADDR(.tbss) );
  PROVIDE( __tbss_size = __tbss_end - __tbss_start );
  PROVIDE( __tbss_offset = ADDR(.tbss) - ADDR(.tdata) );

  PROVIDE( __tls_base = __tdata_start );
  PROVIDE( __tls_end = __tbss_end );
  PROVIDE( __tls_size = __tls_end - __tls_base );
  PROVIDE( __tls_align = MAX(ALIGNOF(.tdata), ALIGNOF(.tbss)) );
  PROVIDE( __tls_size_align = (__tls_size + __tls_align - 1) & ~(__tls_align - 1) );
  PROVIDE( __arm32_tls_tcb_offset = MAX(8, __tls_align) );
  PROVIDE( __arm64_tls_tcb_offset = MAX(16, __tls_align) );

  /*--------------------------------------------------------------
                .bss => DTCMRAM
  --------------------------------------------------------------*/

  .bss (NOLOAD) : ALIGN(4)
  {
    *(.bss)
    *(.bss*)
    *(COMMON)

      . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
      PROVIDE( __bss_end = .);
  } >DTCMRAM
  PROVIDE( __non_tls_bss_start = ADDR(.bss) );

  PROVIDE( __bss_start = __tbss_start );
  PROVIDE( __bss_size = __bss_end - __bss_start );

  /*--------------------------------------------------------------
                ._user_heap_stack => DTCMRAM
  --------------------------------------------------------------*/

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack (NOLOAD) :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >DTCMRAM

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a:* ( * )
    libm.a:* ( * )
    libgcc.a:* ( * )
  }
}
