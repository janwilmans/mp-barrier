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

// For portable use, a shared memory object should be identified by
//   a name of the form /somename; that is, a null-terminated string
//   of up to NAME_MAX (i.e., 255) characters consisting of an initial
//   slash, followed by one or more characters, none of which are slashes.
int create_shared_memory_handle(const char * file)
{
    int shm_fd = shm_open(file, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open_create");
    }
    return shm_fd;
}

int open_shared_memory_handle(const char * file)
{
    int shm_fd = shm_open(file, O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open_read_write");
    }
    return shm_fd;
}
