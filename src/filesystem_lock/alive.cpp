/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include "alive.h"

#include "fmt/core.h"
#include <string>
#include <string_view>

#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>

#include <chrono>
#include <filesystem>
#include <thread>

Alive::Alive(std::filesystem::path unique_filename, unexpected_termination_callback callback) :
    m_name(unique_filename)
{
    if (callback && std::filesystem::exists(m_name.c_str()))
    {
        callback();
    }

    m_fd = open(m_name.c_str(), O_RDWR | O_CREAT, 0666);
    flock(m_fd, LOCK_EX); // lock the handle, automatically released when if the process ends for any reason.
}


Alive::~Alive()
{
    // fails if it was never created, but thats fine, ignore it.
    flock(m_fd, LOCK_UN);
    close(m_fd);
    unlink(m_name.c_str());
}

bool is_file_handled_locked(int fd)
{
    // if we can not lock, that that means it is already locked.
    return flock(fd, LOCK_EX | LOCK_NB) == -1;
}

bool is_alive(std::filesystem::path unique_filename)
{
    int fd = open(unique_filename.c_str(), O_RDWR | O_CREAT, 0666);
    if (fd == -1)
    {
        fmt::print(stderr, "could not find {}\n", unique_filename.string());
        return false;
    }
    bool result = is_file_handled_locked(fd);
    close(fd);
    return result;
}

bool wait_for_alive(std::filesystem::path unique_filename, std::chrono::milliseconds timeout)
{
    auto time_limit = std::chrono::steady_clock::now() + timeout;
    while (std::chrono::steady_clock::now() < time_limit)
    {
        if (is_alive(unique_filename))
        {
            return true;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return false;
}

void wait_for_alive(std::filesystem::path unique_filename)
{
    while (!is_alive(unique_filename))
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
