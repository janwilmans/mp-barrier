/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include "barrier.h"

#include "fmt/core.h"
#include <string>
#include <string_view>


Barrier::Barrier(std::string_view unique_handle, int count)
{
    m_shm_fd = create_shared_memory_handle(get_handle_filename(unique_handle).c_str());
    m_shared_barrier = create_shared_barrier(m_shm_fd, count);
}

Barrier::Barrier(std::string_view unique_handle)
{
    m_shm_fd = open_shared_memory_handle(get_handle_filename(unique_handle).c_str());
    m_shared_barrier = get_shared_barrier(m_shm_fd);
}

void Barrier::wait()
{
    pthread_barrier_wait(&(m_shared_barrier->barrier));
}

std::string Barrier::get_handle_filename(std::string_view id)
{
    return fmt::format("/mp.pthread.barrier.{}", id);
}
