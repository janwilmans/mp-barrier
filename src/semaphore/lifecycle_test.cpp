/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include "lifecycle.h"

#include "fmt/core.h"

#include <chrono>
#include <thread>

int main(int /*argc*/, char * /*argv*/[])
{
    fmt::print("press ctrl-c within 3 seconds and restart this program to see we detect an unexpected program end.\n");

    Lifecycle lifecycle("mp_lifecycle_test", [] {
        fmt::print("program ended unexpectedly !!\n");
    });

    std::this_thread::sleep_for(std::chrono::seconds(3));
    fmt::print("done.\n");
}
