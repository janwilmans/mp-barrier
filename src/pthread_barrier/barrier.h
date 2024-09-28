/*
 * Copyright (c) 2024 Jan Wilmans.
 */

extern "C"
{
#include "pthread_barrier.h"
}

#include <string>
#include <string_view>

class Barrier
{
public:
    Barrier(std::string_view unique_handle, unsigned count);
    Barrier(std::string_view unique_handle);
    ~Barrier();

    void wait();


private:
    std::string get_handle_filename(std::string_view id);

    int m_shm_fd;
    shared_barrier * m_shared_barrier;
    std::string m_name;
    bool m_unlink = false;
};
