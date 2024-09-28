/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include "alive.h"
#include "barrier.h"

#include "fmt/core.h"

#include <chrono>
#include <thread>
#include <unistd.h>

using namespace std::chrono_literals;

void alive_create()
{
    Alive alive("/tmp/main.test");
    fmt::print(stderr, "I'm alive ...press ctrl-c within 3 seconds to test the 'unexpected shutdown' scenario.\n");
    {
        Alive unexpected_shutdown_demo("/tmp/main.shutdown", [] {
            fmt::print("program ended unexpectedly !!\n");
        });
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    fmt::print(stderr, "Looping forever, ...press ctrl-c to stop.\n");

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void alive_check()
{
    fmt::print(stderr, "waiting up to 10 seconds for process to start...\n");
    if (wait_for_alive("/tmp/main.test", 10000ms))
    {
        fmt::print(stderr, "Process started! I'm done.\n");
        return;
    }
    fmt::print(stderr, "Timeout after 10 seconds... I'm done waiting.\n");
}

int main(int argc, char * /*argv*/[])
{
    fmt::print("usage: alive_test <wait>\n");
    fmt::print("   if 'wait' is given, the program waits for an instance of the program without 'wait' to start.\n");

    if (argc > 1)
    {
        alive_check();
    }
    else
    {
        alive_create();
    }
}
