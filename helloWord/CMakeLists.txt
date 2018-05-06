cmake_minimum_required(VERSION 2.8)
project(hello-word C)

set(SRCS_PATH 	"${CMAKE_CURRENT_SOURCE_DIR}/src")
add_executable(${PROJECT_NAME}.elf ${SRCS_PATH}/main.c ${SRCS})
target_link_libraries(${PROJECT_NAME}.elf opencm3_stm32f4)
add_bin_from_elf(${PROJECT_NAME}.bin ${PROJECT_NAME}.elf)
