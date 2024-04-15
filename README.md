# mp-barrier

Posix provides ADVANCED REALTIME THREADS as an optional feature in the `#include <pthread.h>` header.

note from the documenation:
```
The pthread_barrier_destroy() and pthread_barrier_init() functions are part of the Barriers option and need not be provided on all implementations.
```

A conforming implementation that provides this feature is required to use the Barrier class provided here.

If you are not familiar with the concept of a barrier, a barrier is a synchronization construct that forces threads or processes to wait until all of them have reached a certain point of execution before allowing any/all of them to proceed further.
The idea of this class is that you create a system-wide unique name for a barrier, store it in shared-memory and use it to synchronize different processes.

An interesting problem is this particular Barrier implementation in C++ is that we are not allowed to assume that an object can exist without being created while when you acquire data through shared memory, this is exactly what happens.
C++ does not have mechanisms for ensuring initialization, synchronization and object lifetimes across different processes.

C++ objects have a well-defined lifetime, determined by their scope and storage duration. However, in a shared memory scenario, it's challenging to ensure that the lifetime of objects is properly managed across different processes. For example, deallocating memory for an object in one process wile another process leads to undefined behavior.

For this implemenation I will assume that creating any C++ object in shared memory should be avoided. And I will strictly separate the low-level C operations and C++ wrapper class and make sure to compile them seperatly in their respective language.
