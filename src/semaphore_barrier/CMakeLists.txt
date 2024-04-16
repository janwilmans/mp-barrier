
add_library(named_semaphore_barrier_c_library
  named_semaphore.c
)

target_link_libraries(named_semaphore_barrier_c_library
  PUBLIC
    pthread
    rt
)

add_executable(mp-semaphore-barrier
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
)
