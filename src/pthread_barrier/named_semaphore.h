/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#pragma once

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

// For portable use, a named semaphore should be identified by
//   a name of the form /somename; that is, a null-terminated string
//   of up to NAME_MAX (i.e., 255) characters consisting of an initial
//   slash, followed by one or more characters, none of which are slashes.
sem_t * create_named_semaphore(const char * file);


// return true if the named_semaphore exists
bool is_existing_named_semaphore(const char * file);
