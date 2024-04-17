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
    return fmt::format("/tmp/mp.alive.{}", id);
}

Alive::Alive(std::string_view unique_handle) :
    m_name(get_handle_filename(unique_handle))
{
    m_fd = open(m_name.c_str(), O_CREAT | O_RDWR, 0666);
    fmt::print("{} open, trying to lock it\n", m_name);

    auto result = flock(m_fd, LOCK_EX); // lock the handle, automatically released when if the process ends for any reason.
    if (result == 0)
    {
        fmt::print("{} locked\n", m_name);
    }
}

Alive::~Alive()
{
    fmt::print("{} UNlocked\n", m_name);

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
    int fd = open(name.c_str(), O_RDWR, 0666);
    if (fd == -1)
    {
        fmt::print("could not find {}\n", name);
        return false;
    }
    bool result = is_file_handled_locked(fd);
    fmt::print("{} is locked?: {}\n", name, result);

    if (result == false)
    {
        fmt::print("{} not locked, attempt to lock it\n", name);
        flock(fd, LOCK_EX);
        fmt::print("{} locked, now unlock\n", name);
        flock(fd, LOCK_UN);
        fmt::print("{} unlocked\n", name);
    }

    close(fd);
    return result;
}

void wait_for_alive(std::string_view unique_handle)
{
    while (!is_alive(unique_handle))
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
