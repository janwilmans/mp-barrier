project(mp-barrier)

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

enable_testing()
include(CTest)

if (NOT BUILD_IN_TREE)

    message(STATUS "Building ${PROJECT_NAME} as standalone project")

    include(FetchContent)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    message(STATUS "Fetch content for FMT")
    FetchContent_Declare(fmt
      GIT_REPOSITORY https://github.com/fmtlib/fmt.git
      GIT_TAG 8.1.1
    )

    FetchContent_MakeAvailable(fmt)

endif()

find_package(Threads REQUIRED)
include(CMakeLists.warnings.cmake)

#add_compile_options(-fsanitize=address)
#add_link_options(-fsanitize=address)

#add_compile_options(-fsanitize=thread -g -O1)
#add_link_options(-fsanitize=thread)

add_subdirectory(pthread_barrier)
add_subdirectory(filesystem_lock)
add_subdirectory(semaphore)
