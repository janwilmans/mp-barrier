/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#pragma once

extern "C"
{
#include "pthread_barrier.h"
}

#include <chrono>
#include <functional>
#include <string>
#include <string_view>

class Alive
{
public:
    Alive(std::string_view id);
    ~Alive();

private:
    std::string m_name;
    int m_fd = -1;
};

[[nodiscard]] bool is_alive(std::string_view unique_handle);
void wait_for_alive(std::string_view unique_handle);
[[nodiscard]] bool wait_for_alive(std::string_view unique_handle, std::chrono::milliseconds timeout);
