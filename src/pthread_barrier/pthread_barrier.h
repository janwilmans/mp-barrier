/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include <pthread.h>

typedef struct {
    pthread_barrier_t barrier;
} shared_barrier;

int create_shared_memory_handle(const char* file);
int open_shared_memory_handle(const char* file);
shared_barrier * create_shared_barrier(int shm_fd, int barrier_count);
shared_barrier * get_shared_barrier(int shm_fd);
