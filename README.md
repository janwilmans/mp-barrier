# mp-barrier

Posix provides ADVANCED REALTIME THREADS as an optional feature in the `#include <pthread.h>` header.

note from the documenation:
```
The pthread_barrier_destroy() and pthread_barrier_init() functions are part of the Barriers option and need not be provided on all implementations.
```

A conforming implementation that provides this feature is required to use the Barrier class provided here.

If you are not familiar with the concept of a barrier, a barrier is a synchronization construct that forces threads or processes to wait until all of them have reached a certain point of execution before allowing any/all of them to proceed further.
The idea of this class is that you create a system-wide unique name for a barrier, store it in shared-memory and use it to synchronize different processes.

An interesting problem is this particular Barrier implementation in C++ is that we are not allowed to assume that an object can exist without being created, BUT when you acquire data through shared memory, this is exactly what happens.
C++ does not have mechanisms for ensuring initialization, synchronization and object lifetimes across different processes.

C++ objects have a well-defined lifetime, determined by their scope and storage duration. However, in a shared memory scenario, it's challenging to ensure that the lifetime of objects is properly managed across different processes. For example, deallocating memory for an object in one process while another process accesses it leads to undefined behavior.

For this implemenation I will assume that creating any C++ object in shared memory should be avoided. And I will strictly separate the low-level C operations and C++ wrapper class and make sure to compile them seperatly in their respective language.

## First implememtation, https://github.com/janwilmans/mp-barrier/releases/tag/0.1

The first implementation was using [pthread_barrier_t](https://linux.die.net/man/3/pthread_barrier_init) and it's `PTHREAD_PROCESS_SHARED` [attribute](https://linux.die.net/man/3/pthread_mutexattr_init). After the first tests I realized that it requires that the 'creator' of the barrier needs to 'exist' before the other processes can arrive/wait for the barrier. This then requires to use of some other mechnism (like a named semaphore) to ensure that the barrier exists. Named semaphoresa are a more general synchronization primitive; if we are going to need to need it anyway, then maybe using the `pthread_barrier_t` doesn't make sense anymore. The pthread_barrier_t is a bit cumbersome to use in a multi-proceses scenario, because you need to initialize it in shared memory and then use it from another process by mapping the same shared memory into its address space.

Note: this implementation is incomplete, it does not free any resources and does not take into account that new waiters can arrived before the barrier exists.

## Second implementation

More investigation revealed building your own barrier out of semaphores is not trivial. It would at the very least require the exact same 'dance' of:

* create shared memory handle (shm_open)
* allocate memory / size it properly (ftruncate)
* map it into the process adress space (mmap)
* initialize the structure

If we need that anyway, we may as well used an existing implemenation (pthread_barrier_t), because it has been proven to work.
However, we are going to have to guarentee the 'creator' of the barrier comes first, so we will design an additional mechanism:

## class Alive

The class Alive is takes a normal 'filename', it can be anywhere but need to be writable/lockable and removeable (so you should probably not used the name of your own executable ;)

```
Alive alive("/tmp/main.test");  // this will create the file if it doesn't exist, lock it, and unlock and remove it when the lifetime of the object ends normally (the destructor is called).
```

When the process end normally, it unlocks and removed the file. But when the process dies / ends unexpectedly, the file is automatically unlocked by the kernel (but is not removed).
Because we lock the file, we can check whether the file is locked from another process.

```
if (wait_for_alive("/tmp/main.test", 10000ms))
{
    fmt::print(stderr, "Process started! I'm done.\n");
}
```

This will wait for someone to create the file and lock it or a timeout occurs.

We can also use the side-effects of this to detect if last time we started the process it ended normally.

```
 Alive unexpected_shutdown_demo("/tmp/main.shutdown", [] {
     fmt::print("program ended unexpectedly !!\n");
 });
```

Since the file normally removed, if it already exists during startup, we can conclude the last shutdown was not normal.







 
