/*
 * Copyright (c) 2024 Jan Wilmans.
 */

extern "C"
{
#include "named_semaphore.h"
}

#include <string>
#include <string_view>

class Barrier
{
public:
    Barrier(std::string_view unique_handle);
    ~Barrier();

    void post();
    void wait();


private:
    std::string get_handle_filename(std::string_view id);

    sem_t * m_semaphore = nullptr;
};
