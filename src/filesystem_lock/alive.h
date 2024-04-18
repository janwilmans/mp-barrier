/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#pragma once

extern "C"
{
#include "pthread_barrier.h"
}

#include <chrono>
#include <filesystem>
#include <functional>
#include <string_view>

class Alive
{
public:
    using unexpected_termination_callback = std::function<void()>;
    explicit Alive(std::filesystem::path unique_filename, unexpected_termination_callback callback = {});

    Alive(const Alive &) = delete;
    Alive & operator=(const Alive &) = delete;
    Alive(Alive &&) = delete;
    Alive & operator=(Alive &&) = delete;

    ~Alive();

private:
    std::filesystem::path m_name;
    int m_fd = -1;
};

[[nodiscard]] bool is_alive(std::filesystem::path unique_filename);
void wait_for_alive(std::filesystem::path unique_filename);
[[nodiscard]] bool wait_for_alive(std::filesystem::path unique_filename, std::chrono::milliseconds timeout);
