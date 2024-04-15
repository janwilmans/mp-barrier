/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include "barrier.h"

#include "fmt/core.h"

#include <unistd.h>

void create_barrier()
{
    Barrier barrier("software_trigger", 3); // wait for three processes
    fmt::print("1 holding at barrier\n");
    barrier.wait();
    fmt::print("1 passed barrier\n");
}

void wait_at_barrier()
{
    Barrier barrier("software_trigger"); // wait for three processes
    fmt::print("{} holding at barrier\n", getpid());
    barrier.wait();
    fmt::print("{} passed barrier\n", getpid());
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        wait_at_barrier();
    }
    else
    {
        create_barrier();
    }
    //barrier.wait(100ms); // timeout
}


