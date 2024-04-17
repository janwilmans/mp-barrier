
add_library(mp_barrier_c_library
  pthread_barrier.c
)

target_link_libraries(mp_barrier_c_library
  PUBLIC
    pthread
    rt
)

target_include_directories(mp_barrier_c_library PUBLIC .)

add_executable(mp-pthread-barrier
    barrier.cpp
    main.cpp
)

find_package(Threads REQUIRED)

target_link_libraries(mp-pthread-barrier
  PRIVATE
    Threads::Threads
    fmt::fmt
    mp_barrier_c_library
)
