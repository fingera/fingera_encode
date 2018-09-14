cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_STANDARD 99)
set(C_STANDARD_REQUIRED ON)

option(BUILD_TESTING "Enable test (depends on googletest)." OFF)
option(BUILD_VALGRIND "Enable valgrind (depends on BUILD_TESTING)." OFF)
option(BUILD_EXTERNAL "Enable build external" ON)

if (${BUILD_EXTERNAL} STREQUAL "ON")
  add_subdirectory(external)
endif()

add_library(fingera_encode
  src/hex.c
  src/base32.c
  src/bech32.c
  src/base64.c
  src/base58.c
  src/compress.c
  src/eos_name.c
)

target_link_libraries(fingera_encode fingera_header)
target_include_directories(fingera_encode
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (${BUILD_TESTING} STREQUAL "ON")
  include(CTest)
  add_subdirectory(tests)
endif()
