
add_library(mp_primitives_c_library
  pthread_barrier.c
  named_semaphore.c
  shared_memory.c
)

target_link_libraries(mp_primitives_c_library
  PUBLIC
    pthread
    rt
)

target_include_directories(mp_primitives_c_library PUBLIC .)

add_executable(barrier_test
    barrier.cpp
    barrier_test.cpp
)

target_link_libraries(barrier_test
  PRIVATE
    Threads::Threads
    fmt::fmt
    mp_primitives_c_library
)
