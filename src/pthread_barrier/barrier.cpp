/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include "barrier.h"

#include "fmt/core.h"
#include <string>
#include <string_view>
#include <sys/mman.h>
#include <unistd.h>

Barrier::Barrier(std::string_view unique_handle, unsigned count)
{
    m_name = get_handle_filename(unique_handle);
    m_shm_fd = create_shared_memory_handle(m_name.c_str());
    m_shared_barrier = create_shared_barrier(m_shm_fd, count);
    m_unlink = true;
}

Barrier::Barrier(std::string_view unique_handle)
{
    m_name = get_handle_filename(unique_handle);
    m_shm_fd = open_shared_memory_handle(m_name.c_str());
    m_shared_barrier = get_shared_barrier(m_shm_fd);
}

void Barrier::wait()
{
    pthread_barrier_wait(&(m_shared_barrier->barrier));
}

Barrier::~Barrier()
{
    close(m_shm_fd);
    if (m_unlink)
    {
        shm_unlink(m_name.c_str());
    }
}

std::string Barrier::get_handle_filename(std::string_view id)
{
    return fmt::format("/mp.pthread.barrier.{}", id);
}
