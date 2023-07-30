# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(lvgl)

add_subdirectory(drivers)

include_directories(src/)
include_directories(src/ui)


FILE(GLOB ui_sources src/ui/*.c)
target_sources(app PRIVATE ${ui_sources})

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
