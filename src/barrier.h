/*
 * Copyright (c) 2024 Jan Wilmans.
 */

extern "C" {
    #include "pthread_barrier.h"
}

#include <string_view>

class Barrier
{
public:
    // pass handle as '/dev/shm/barrier_uniqueid'
    Barrier(std::string_view unique_handle, int count);
    Barrier(std::string_view unique_handle);

    void wait();


private:
    std::string get_handle_filename(std::string_view id);

    int m_shm_fd;
    shared_barrier * m_shared_barrier;
};
