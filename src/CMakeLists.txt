project(mp-barrier)

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

if (NOT BUILD_VCENTER_TREE)

    message(STATUS "Building ${PROJECT_NAME} as standalone project")

    include(FetchContent)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    FetchContent_Declare(fmt
      GIT_REPOSITORY https://github.com/fmtlib/fmt.git
      GIT_TAG 8.1.1
    )

    FetchContent_MakeAvailable(fmt)

endif()

#add_compile_options(-fsanitize=address)
#add_link_options(-fsanitize=address)

#add_compile_options(-fsanitize=thread -g -O1)
#add_link_options(-fsanitize=thread)

add_library(mp_barrier_c_library
  pthread_barrier.c
)

target_link_libraries(mp_barrier_c_library
  PUBLIC
    pthread
    rt
)


add_executable(mp-barrier
    barrier.cpp
    main.cpp
)

find_package(Threads REQUIRED)

target_link_libraries(mp-barrier
  PRIVATE
    Threads::Threads
    fmt::fmt
    mp_barrier_c_library
)
