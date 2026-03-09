cmake_minimum_required(VERSION 3.22)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()


set(CMAKE_PROJECT_NAME stm32h7_cubemx)


set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)


project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})


enable_language(C ASM)


add_executable(${CMAKE_PROJECT_NAME})

set(CMAKE_CUSTOM_SOURCE_DIR "${PROJECT_SOURCE_DIR}")
set(COMPONENT_LIB ${CMAKE_PROJECT_NAME})

# Define hardware revisions
add_compile_definitions(HARDWARE_ID_PROTOTYPE=1)
set(HARDWARE_ID 1 CACHE STRING "Hardware revision")
add_compile_definitions(HARDWARE_ID=${HARDWARE_ID})

add_compile_definitions(APP_VERSION_MAJOR=0)
add_compile_definitions(APP_VERSION_MINOR=1)
add_compile_definitions(APP_VERSION_BUILD=0)

add_definitions(-DCOMPONENT_LWIP -DHAVE_SNPRINTF)
add_compile_definitions(_GNU_SOURCE)

add_subdirectory(cmake/stm32cubemx)

set_source_files_properties(
    startup_stm32h750xx.c
    Core/Src/main.c
    PROPERTIES COMPILE_FLAGS "-O0"
)

target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    newlib_lock_glue.c
    Drivers/CMSIS/DSP/Source/FilteringFunctions/arm_biquad_cascade_df2T_f32.c
    Drivers/CMSIS/DSP/Source/FilteringFunctions/arm_biquad_cascade_df2T_init_f32.c
    Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_f32.c
    Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.c
    Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.c
    Drivers/CMSIS/DSP/Source/TransformFunctions/arm_bitreversal2.c
    Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.c
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    Drivers/CMSIS/DSP/Include
    Core/Inc
)

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}
    DEPENDS STM32H750XX_FLASH.ld
)
