cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name 将项目名称变量存入变量 CMAKE_PROJECT_NAME
set(CMAKE_PROJECT_NAME NwatchCopy)

# Include toolchain file 引入交叉编译工具链配置
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd 记录每个源文件的编译命令
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings 正式声明项目名称  在配置阶段输出当前构建类型，方便确认
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
# 创建一个名为 NwatchCopy 的 可执行文件目标（最终生成 .elf, .hex, .bin）
add_executable(${CMAKE_PROJECT_NAME}
        drivers_bsp/oled/oled.c

        system/Inc/button.h
        system/Src/button.c
        test/test_button.c
        drivers_bsp/button_driver/button_driver.c
        drivers_bsp/button_driver/button_driver.h
        common/ulti.h)

# Add STM32CubeMX generated sources 添加 STM32CubeMX 生成的代码
add_subdirectory(cmake/stm32cubemx)

# Link directories setup 设置链接库搜索路径
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths 用于指定 .a 或 .so 文件的搜索目录
)

# Add sources to executable 添加用户源文件 PRIVATE 表示这些源文件只属于这个目标
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths 添加头文件搜索路径
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    # 编译器会在这个路径下查找 #include "xxx.h"。
        test
        drivers_bsp/oled
        system/Inc
        drivers_bsp/button_driver
        common
)

# Add project symbols (macros)  添加编译宏定义
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries 链接最终依赖的库
# 将前面通过 add_subdirectory 引入的 stm32cubemx 库链接进来
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
