
add_executable(alive_test
    alive.cpp
    alive_test.cpp
)

target_link_libraries(alive_test
  PRIVATE
    Threads::Threads
    fmt::fmt
    mp_primitives_c_library
)
