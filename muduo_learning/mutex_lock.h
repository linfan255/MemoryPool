#ifndef TOYS_MUTEX_H
#define TOYS_MUTEX_H

#include <pthread.h>
#include "util.h"

class MutexLock {
public:
    MutexLock() : _mutex() {
        pthread_mutex_init(&_mutex, NULL);
    }
    ~MutexLock() {
        pthread_mutex_destroy(&_mutex);
    }

    MutexLock(const MutexLock& other) = delete;
    MutexLock& operator=(const MutexLock& other) = delete;

    // @attention: lock and unlock should only be called by LockGuard !!
    void lock() {
        pthread_mutex_lock(&_mutex);
        _current_tid = pthread_self();
    }
    void unlock() {
        _current_tid = 0;
        pthread_mutex_unlock(&_mutex);
    }
    bool hold_by_this_thread() {
        return _current_tid == pthread_self();
    }

private:
    pthread_mutex_t _mutex;
    pthread_t _current_tid;

    DEISALLOW_COPY_AND_ASSIGN(Mutex);
};

class MutexLockGuard {
public:
    MutexLockGuard(const MutexLock& mutex) : _mutex(mutex) {
        _mutex.lock();
    }
    ~MutexLockGuard() {
        _mutex.unlock();
    }

private:
    MutexLock& _mutex;
    DISALLOW_COPY_AND_ASSIGN(MutexLockGuard);
};

#define MutexLockGuard(Type)    \
        static_assert(false, "need MuexLockGuard name here")

#endif
