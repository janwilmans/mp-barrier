/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#pragma once

#include <pthread.h>

#include "shared_memory.h"

typedef struct
{
    pthread_barrier_t barrier;
} shared_barrier;

shared_barrier * create_shared_barrier(int shm_fd, int barrier_count);
shared_barrier * get_shared_barrier(int shm_fd);
