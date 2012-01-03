cmake_minimum_required (VERSION 2.6)
project (sputnik)

file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.h)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(Allegro5 REQUIRED)
find_package(Eigen3 REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-Wall")
endif()

set(sputnik_VERSION_MAJOR 0)
set(sputnik_VERSION_MINOR 1)

configure_file (
    "${PROJECT_SOURCE_DIR}/sputnik_config.h.in"
    "${PROJECT_BINARY_DIR}/sputnik_config.h"
)

include_directories(
    "${PROJECT_BINARY_DIR}"
    "${ALLEGRO5_INCLUDE_DIR}"
)

add_executable(sputnik ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(sputnik ${ALLEGRO5_LIBRARIES})

