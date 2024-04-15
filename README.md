# mp-barrier

Posix provides ADVANCED REALTIME THREADS as an optional feature in the `#include <pthread.h>` header.

note from the documenation:
```
The pthread_barrier_destroy() and pthread_barrier_init() functions are part of the Barriers option and need not be provided on all implementations.
```

A conforming implementation that provides this feature is required to use the Barrier class provided here.

If you are not familiar with the concept of a barrier, a barrier is a synchronization construct that forces threads or processes to wait until all of them have reached a certain point of execution before allowing any/all of them to proceed further.
The idea of this class is that you create a system-wide unique name for a barrier, store it in shared-memory and use it to synchronize different processes.

