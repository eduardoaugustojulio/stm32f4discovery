cmake_minimum_required(VERSION 2.8)
project(cpp)

set(SRCS_PATH 	"${CMAKE_CURRENT_SOURCE_DIR}/src")
include_directories(${SRCS_PATH})
file(GLOB SRCS  "${SRCS_PATH}/*.cpp")

add_executable(${PROJECT_NAME}.elf ${SRCS})
target_link_libraries(${PROJECT_NAME}.elf opencm3_stm32f4)

add_bin_from_elf(${PROJECT_NAME}.bin ${PROJECT_NAME}.elf)
bin_size(${PROJECT_NAME}.elf)
