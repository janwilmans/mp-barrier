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

void create_barrier()
{
    Barrier barrier("software_trigger");
    fmt::print("allow 2\n");
    barrier.post();
    barrier.post();
    fmt::print("done.\n");
}

void wait_at_barrier()
{
    Barrier barrier("software_trigger");
    fmt::print("{} holding at barrier\n", getpid());
    barrier.wait();
    fmt::print("{} passed barrier\n", getpid());
}

int main(int argc, char * argv[])
{
    Alive alive("main.test");

    Lifecycle lifecycle("mp_sem_barrier", [] {
        fmt::print("{} program ended unexpectedly !!\n", getpid());
    });

    if (argc > 1)
    {
        wait_at_barrier();
    }
    else
    {
        create_barrier();
    }
    // barrier.wait(100ms); // timeout

    std::this_thread::sleep_for(std::chrono::seconds(2));
}
