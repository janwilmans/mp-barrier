/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include "alive.h"

#include "fmt/core.h"
#include <string>
#include <string_view>

#include <sys/file.h>
#include <sys/mman.h>
#include <unistd.h>

#include <chrono>
#include <thread>

static std::string get_handle_filename(std::string_view id)
{
    return fmt::format("/mp.alive.{}", id);
}

Alive::Alive(std::string_view unique_handle) :
    m_name(get_handle_filename(unique_handle))
{
    m_fd = create_shared_memory_handle(m_name.c_str());
    flock(m_fd, LOCK_EX); // lock the handle, automatically released when if the process ends for any reason.
}

Alive::~Alive()
{
    // fails if it was never created, but thats fine, ignore it.
    flock(m_fd, LOCK_UN);
    close(m_fd);
    shm_unlink(m_name.c_str());
}

bool is_file_handled_locked(int fd)
{
    // if we can not lock, that that means it is already locked.
    return flock(fd, LOCK_EX | LOCK_NB) == -1;
}

bool is_alive(std::string_view unique_handle)
{
    std::string name = get_handle_filename(unique_handle);
    int fd = open_shared_memory_handle(name.c_str());
    if (fd == -1)
    {
        fmt::print(stderr, "could not find {}\n", name);
        return false;
    }
    bool result = is_file_handled_locked(fd);
    close(fd);
    return result;
}

bool wait_for_alive(std::string_view unique_handle, std::chrono::milliseconds timeout)
{
    auto time_limit = std::chrono::steady_clock::now() + timeout;
    while (std::chrono::steady_clock::now() < time_limit)
    {
        if (is_alive(unique_handle))
        {
            return true;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return false;
}

void wait_for_alive(std::string_view unique_handle)
{
    while (!is_alive(unique_handle))
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
