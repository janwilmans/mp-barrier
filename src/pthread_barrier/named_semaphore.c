/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include "named_semaphore.h"

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include <semaphore.h>
#include <sys/stat.h>

sem_t * create_named_semaphore(const char * file)
{
    sem_t * semaphore = sem_open(file, O_CREAT, S_IRUSR | S_IWUSR, 0);
    if (semaphore == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    return semaphore;
}

bool is_existing_named_semaphore(const char * file)
{
    return sem_open(file, 0) != SEM_FAILED;
}
