cmake_minimum_required (VERSION 2.6)
project (sputnik)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(Allegro5 REQUIRED)

set (sputnik_VERSION_MAJOR 0)
set (sputnik_VERSION_MINOR 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/sputnik_config.h.in"
  "${PROJECT_BINARY_DIR}/sputnik_config.h"
)

include_directories(
  "${PROJECT_BINARY_DIR}"
  "${ALLEGRO5_INCLUDE_DIR}"
)

add_executable(sputnik sputnik.cpp)
target_link_libraries(sputnik ${ALLEGRO_LIBRARY})
