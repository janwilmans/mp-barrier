/*
 * Copyright (c) 2024 Jan Wilmans.
 */

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
    std::string get_handle_filename(std::string_view id);

    std::string m_name;
    sem_t * m_semaphore = nullptr;
};
