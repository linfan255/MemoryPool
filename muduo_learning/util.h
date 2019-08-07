#include <pthread.h>

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

    void lock() {
        pthread_mutex_lock(&_mutex);
    }
    void unlock() {
        pthread_mutex_unlock(&_mutex);
    }

private:
    pthread_mutex_t _mutex;
};

class MutexLockGuard {
public:
    MutexLockGuard(MutexLock& mutex) : _mutex(mutex) {
        _mutex.lock();
    }
    ~MutexLockGuard() {
        _mutex.unlock();
    }

    MutexLockGuard(const MutexLockGuard&) = delete;
    MutexLockGuard& operator=(const MutexLockGuard&) = delete;

private:
    MutexLock& _mutex;
};
