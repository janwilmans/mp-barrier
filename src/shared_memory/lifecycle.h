/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#pragma once

extern "C"
{
#include "named_semaphore.h"
}

#include <functional>
#include <string>
#include <string_view>

class Lifecycle
{
public:
    using unexpected_termination_callback = std::function<void()>;
    Lifecycle(std::string_view id, unexpected_termination_callback callback);
    ~Lifecycle();

private:
    std::string m_name;
    sem_t * m_semaphore = nullptr;
};
