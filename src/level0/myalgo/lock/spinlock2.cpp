#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <sys/time.h>

// need C++ 11
#include <atomic>

/*

MAX 10000000LL

Using lock : NOP LOCK
Shared variable value is : 13520596
Elapsed time: 0 s 344064 us

Using lock : SPIN LOCK
Shared variable value is : 40000000
Elapsed time: 3 s 416560 us

Using lock : MUTEX LOCK
Shared variable value is : 40000000
Elapsed time: 4 s 172376 us


*/

#define MAX 10000000LL

#ifdef USE_SPIN_LOCK
const char *g_lock_type = "SPIN LOCK";

class Spin_lock
{
public:
    Spin_lock( void );
    void lock( void );
    bool try_lock( void );
    void unlock( void );
private:
    std::atomic<bool> d_atomic_bool;
};

Spin_lock::Spin_lock()
{
    d_atomic_bool.store( false, std::memory_order_relaxed );
    return;
}
void Spin_lock::lock( void )
{
    while( d_atomic_bool.exchange( true, std::memory_order_acquire ) ) 
    {
        while( 1 ) {
            _mm_pause(); // pause指令 延迟时间大约是12纳秒
            if( !d_atomic_bool.load( std::memory_order_relaxed ) ) break; 
            std::this_thread::yield(); // 在无其他线程等待执行的情况下，延迟时间113纳秒
            // 在有其他线程等待执行情况下，将切换线程·
            if( !d_atomic_bool.load( std::memory_order_relaxed ) ) break; 
            continue;
        }
        continue;
    }
    return;
}
bool Spin_lock::try_lock( void )
{
    return !d_atomic_bool.exchange( true, std::memory_order_acquire );
}
void Spin_lock::unlock( void )
{
    d_atomic_bool.store( false, std::memory_order_release ); // 设置为false
    return;
}

Spin_lock g_spin_lock;


#define lock spin_lock
#define unlock spin_unlock
bool g_spin_mutex = false;

void spin_lock()
{
    g_spin_lock.lock();
}

void spin_unlock()
{
    g_spin_lock.unlock();
}

#elif defined(USE_MUTEX_LOCK)
const char *g_lock_type = "MUTEX LOCK";
#define lock mutex_lock
#define unlock mutex_unlock
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void mutex_lock()
{
    pthread_mutex_lock(&g_mutex);
}

void mutex_unlock()
{
    pthread_mutex_unlock(&g_mutex);
}
#else
const char *g_lock_type = "NOP LOCK";
#define lock nop_lock
#define unlock nop_unlock

void nop_lock()
{
    // do nothing
}

void nop_unlock()
{
    // do nothing
}

#endif // USE_MUTEX_LOCK




void test();
void* run(void *arg);

// Shared resource
long long g_val = 0;

class Timer
{
public:
    Timer()
    {
        gettimeofday(&_start, NULL);
    }

    ~Timer()
    {
        gettimeofday(&_end, NULL);
        int sec = (int)(_end.tv_sec - _start.tv_sec);
        int eusec = _end.tv_usec;
        int susec = _start.tv_usec;
        
        if (eusec < susec)
        {
            assert(sec > 0);
            eusec += 1000000;
            sec--;
        }
        int usec = eusec - susec;
        
        printf("Elapsed time: %d s %d us\n", sec, usec);
    }
private:
    struct timeval _start;
    struct timeval _end;
};

int main()
{
    printf("Using lock : %s\n", g_lock_type);
    Timer timer;
    // test();
    pthread_t ts[4];
    for (int loop = 0; loop < 4; loop++)
    {
        int ret = pthread_create(&ts[loop], NULL, run, NULL);
        assert(ret >= 0);

    }
    for (int loop = 0; loop < 4; loop++)
    {
        (void)pthread_join(ts[loop], NULL);
    }
    printf("Shared variable value is : %lld\n", g_val);

#ifdef USE_MUTEX_LOCK  
    pthread_mutex_destroy(&g_mutex);
#endif // USE_MUTEX_LOCK
    return 0;
}

void test()
{
    bool ret = false;
    bool lock = false;
    ret = __sync_bool_compare_and_swap(&lock, false, true);
    assert(ret == true);
    assert(lock == true);
    ret = __sync_bool_compare_and_swap(&lock, false, true);
    assert(ret == false);
    assert(lock == true);
    ret = __sync_bool_compare_and_swap(&lock, true, false);
    assert(ret == true);
    assert(lock == false);
}

void* run(void *arg)
{
    long long count = 0;
    for (; count < MAX; ++count)
    {
        lock();
        g_val++;
        unlock();
    }
}

