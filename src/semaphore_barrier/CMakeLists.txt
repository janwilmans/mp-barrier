
add_library(named_semaphore_barrier_c_library
  named_semaphore.c
)

target_link_libraries(named_semaphore_barrier_c_library
  PUBLIC
    pthread
    rt
)

add_executable(mp-semaphore-barrier
    alive.cpp
    lifecycle.cpp
    barrier.cpp
    main.cpp
)

find_package(Threads REQUIRED)

target_link_libraries(mp-semaphore-barrier
  PRIVATE
    Threads::Threads
    fmt::fmt
    named_semaphore_barrier_c_library
    mp_barrier_c_library
)

add_executable(alive_main
    alive.cpp
    alive_test.cpp
)

target_link_libraries(alive_main
  PRIVATE
    Threads::Threads
    fmt::fmt
    named_semaphore_barrier_c_library
    mp_barrier_c_library
)
