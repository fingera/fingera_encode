
add_executable( test_fingera_encode
  test_hex.cpp
  test_base32.cpp
  test_base58.cpp
  test_base64.cpp
  test_compress.cpp
  test_bech32.cpp
  test_eos_name.cpp
)

target_link_libraries( test_fingera_encode fingera_encode gtest_main )
add_test(NAME test_fingera_encode COMMAND test_fingera_encode)

if (${BUILD_VALGRIND} STREQUAL "ON")
  find_program(VALGRIND "valgrind")
  if(VALGRIND)
    add_custom_target(valgrind
        COMMAND "${VALGRIND}" --leak-check=full --track-fds=yes $<TARGET_FILE:test_fingera_encode>)
  endif()
endif()
