/*
 * Copyright (c) 2024 Jan Wilmans.
 */

#include "lifecycle.h"

#include "fmt/core.h"
#include <string>
#include <string_view>

Lifecycle::Lifecycle(std::string_view unique_handle, unexpected_termination_callback callback) :
    m_name(get_handle_filename(unique_handle))
{
    if (is_existing_named_semaphore(m_name.c_str()))
    {
        callback();
    }
    m_semaphore = create_named_semaphore(m_name.c_str());
}

Lifecycle::~Lifecycle()
{
    // fails if it was never created, but thats fine, ignore it.
    sem_close(m_semaphore);

    if (sem_unlink(m_name.c_str()) == -1)
    {
        perror("sem_unlink");
        exit(EXIT_FAILURE);
    }
}

std::string Lifecycle::get_handle_filename(std::string_view id)
{
    return fmt::format("/mp.lifecycle.{}", id);
}
