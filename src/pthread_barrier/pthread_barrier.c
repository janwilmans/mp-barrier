/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include "pthread_barrier.h"

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

void set_shared_memory_object_size(int shm_fd, int size)
{
    if (ftruncate(shm_fd, size) == -1)
    {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }
}

void * map_shared_memory_into_address_space(int shm_fd, int size)
{
    void * shm_ptr = mmap(NULL, sizeof(shared_barrier), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    return shm_ptr;
}

shared_barrier * create_shared_barrier(int shm_fd, int barrier_count)
{
    set_shared_memory_object_size(shm_fd, sizeof(shared_barrier));
    void * shm_ptr = map_shared_memory_into_address_space(shm_fd, sizeof(shared_barrier));

    // Initialize the shared data structures
    shared_barrier * shared_data = (shared_barrier *)shm_ptr;
    pthread_barrierattr_t barrier_attr;
    pthread_barrierattr_init(&barrier_attr);
    pthread_barrierattr_setpshared(&barrier_attr, PTHREAD_PROCESS_SHARED);
    pthread_barrier_init(&shared_data->barrier, &barrier_attr, barrier_count);
    return shared_data;
}

shared_barrier * get_shared_barrier(int shm_fd)
{
    set_shared_memory_object_size(shm_fd, sizeof(shared_barrier));
    void * shm_ptr = map_shared_memory_into_address_space(shm_fd, sizeof(shared_barrier));
    return (shared_barrier *)shm_ptr;
}
