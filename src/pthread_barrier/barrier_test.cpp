/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include "barrier.h"

#include "fmt/core.h"

#include <atomic>
#include <chrono>
#include <signal.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

std::atomic<bool> end_program;

void create_barrier()
{
    end_program = false;
    Barrier barrier("software_trigger", 2); // wait for three processes
    fmt::print("created barrier for 2 waiters...\n");
    while (!end_program)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    fmt::print("done.\n");
}

void wait_at_barrier()
{
    Barrier barrier("software_trigger"); // wait for three processes
    fmt::print("{} holding at barrier\n", getpid());
    barrier.wait();
    fmt::print("{} passed barrier\n", getpid());
}


extern "C" void signal_handler(int signal)
{
    printf("\nCaught signal %d\n", signal);
    end_program = true;
}

int main(int argc, char * /*argv*/[])
{
    signal(SIGINT, signal_handler);

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
