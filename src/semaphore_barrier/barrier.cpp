/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include "barrier.h"

#include "fmt/core.h"
#include <string>
#include <string_view>


Barrier::Barrier(std::string_view unique_handle)
{
    m_semaphore = create_named_semaphore(get_handle_filename(unique_handle).c_str());
}

Barrier::~Barrier()
{
    sem_close(m_semaphore);
}

// sem_wait() // decrements the semaphore counter, or waits if it is already 0
// set_post() // atomically increments the counter

void Barrier::post()
{
    // sem_timedwait()
    sem_post(m_semaphore);
}


// count is the semaphore count to wait for
void Barrier::wait()
{
    // sem_timedwait()
    sem_wait(m_semaphore);
}

std::string Barrier::get_handle_filename(std::string_view id)
{
    return fmt::format("/mp.semaphore.barrier.{}", id);
}
