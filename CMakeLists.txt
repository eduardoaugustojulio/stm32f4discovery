cmake_minimum_required(VERSION 2.8)
project(stm32f4 C)

IF(NOT CMAKE_CROSSCOMPILING)
  message(FATAL_ERROR "Cross compiling only. Please use -DCMAKE_TOOLCHAIN_FILE=/PATH/TO/TOOLCHAIN_FILE .")
ENDIF(NOT CMAKE_CROSSCOMPILING)

add_definitions(-DSTM32F4)
set(COMMON_FLAGS "-mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -specs=nosys.specs")
set(CMAKE_C_FLAGS "-g -O2 -Wall -std=c11 ${COMMON_FLAGS} ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "-g -02 -std=c++11 ${COMMON_FLAGS} ${CMAKE_CXX_FLAGS}")

set(LIBOPENCM3_DIR ${CMAKE_SOURCE_DIR}/libopencm3)
add_custom_target(libopencm3 make WORKING_DIRECTORY ${LIBOPENCM3_DIR})
include_directories(${LIBOPENCM3_DIR}/include)
link_directories(${LIBOPENCM3_DIR}/lib)

set(LINKER_SCRIPT_DIR "${LIBOPENCM3_DIR}/lib/stm32/f4/stm32f405x6.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT_DIR} -nostartfiles --specs=rdimon.specs")

function(add_bin_from_elf bin elf) 
  add_custom_target(${bin} ALL ${CMAKE_OBJCOPY} -Obinary ${elf} ${bin} DEPENDS ${elf})
endfunction(add_bin_from_elf)

add_subdirectory(helloWord)

