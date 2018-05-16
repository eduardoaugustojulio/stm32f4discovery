cmake_minimum_required(VERSION 2.8)

IF(NOT CMAKE_CROSSCOMPILING)
  message(FATAL_ERROR "Cross compiling only. Please use -DCMAKE_TOOLCHAIN_FILE=/PATH/TO/TOOLCHAIN_FILE .")
ENDIF(NOT CMAKE_CROSSCOMPILING)

set(LIBOPENCM3_DIR ${CMAKE_SOURCE_DIR}/libopencm3)
add_custom_target(libopencm3 make WORKING_DIRECTORY ${LIBOPENCM3_DIR})
include_directories(${LIBOPENCM3_DIR}/include)
link_directories(${LIBOPENCM3_DIR}/lib)

set(LINKER_SCRIPT_DIR "${LIBOPENCM3_DIR}/lib/stm32/f4/stm32f405x6.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${PROCESSOR_FLAGS} -T ${LINKER_SCRIPT_DIR} ${LD_FLAGS}")

function(add_bin_from_elf bin elf)
  add_custom_target(${bin} ALL ${CMAKE_OBJCOPY} -Obinary ${elf} ${bin} DEPENDS ${elf})
endfunction(add_bin_from_elf)

function(bin_size bins)
	foreach(bin ${bins})
		add_custom_command(TARGET ${bin} POST_BUILD 
			COMMAND ${CMAKE_SIZE} --format=berkeley ${bin})
	endforeach()
endfunction(bin_size)

add_subdirectory(helloWord)
add_subdirectory(cpp)
