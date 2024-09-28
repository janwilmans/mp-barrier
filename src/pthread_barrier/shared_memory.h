/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#pragma once

#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>

int create_shared_memory_handle(const char * file);
int open_shared_memory_handle(const char * file);

bool set_object_size(int fd, off_t size);
void * map_into_address_space(int fd, size_t size);
