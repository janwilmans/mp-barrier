/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include "alive.h"
#include "barrier.h"
#include "lifecycle.h"

#include "fmt/core.h"

#include <chrono>
#include <thread>
#include <unistd.h>

void alive_create()
{
    fmt::print(stderr, "alive_create\n");
    Alive alive("main.test");

    fmt::print(stderr, "hang forever\n");
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void alive_check()
{
    fmt::print(stderr, "waiting for process to start...\n");
    wait_for_alive("main.test");
    fmt::print(stderr, "Process started! I'm done.\n");
}

int main(int argc, char * argv[])
{
    if (argc > 1)
    {
        alive_check();
    }
    else
    {
        alive_create();
    }
}
