/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include "barrier.h"

#include "fmt/core.h"

#include <chrono>
#include <thread>
#include <unistd.h>

void create_barrier()
{
    Barrier barrier("software_trigger", 2); // wait for three processes
    fmt::print("created barrier for 2 waiters...\n");
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void wait_at_barrier()
{
    Barrier barrier("software_trigger"); // wait for three processes
    fmt::print("{} holding at barrier\n", getpid());
    barrier.wait();
    fmt::print("{} passed barrier\n", getpid());
}

int main(int argc, char * argv[])
{
    if (argc > 1)
    {
        wait_at_barrier();
    }
    else
    {
        create_barrier();
    }
    // barrier.wait(100ms); // timeout
}
