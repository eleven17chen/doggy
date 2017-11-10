#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <sys/time.h>
#include <sched.h>


/*

MAX 10000000LL

Using lock : NOP LOCK
Shared variable value is : 13520596
Elapsed time: 0 s 344064 us

Using lock : SPIN LOCK with out sched_yield
Shared variable value is : 40000000
Elapsed time: 3 s 416560 us

Using lock : SPIN LOCK with sched_yield
Shared variable value is : 40000000
Elapsed time: 1 s 198424 us


Using lock : MUTEX LOCK
Shared variable value is : 40000000
Elapsed time: 4 s 172376 us


*/

#define MAX 10000000LL

#ifdef USE_SPIN_LOCK
const char *g_lock_type = "SPIN LOCK";
#define lock spin_lock
#define unlock spin_unlock
bool g_spin_mutex = false;

#define TRY_TIMES 0

void spin_lock()
{
    bool ret = false;
    int tried = 0;
    do 
    {
        if (g_spin_mutex == true && tried > TRY_TIMES) {
            sched_yield();
            tried = 0;
        }
        tried++;
        ret = __sync_bool_compare_and_swap(&g_spin_mutex, false, true);
    } while (ret != true);
}

void spin_unlock()
{
    g_spin_mutex = false;
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

#define THREAD_COUNT 4

int main()
{
    printf("Using lock : %s\n", g_lock_type);
    Timer timer;
    // test();
    pthread_t ts[THREAD_COUNT];
    for (int loop = 0; loop < THREAD_COUNT; loop++)
    {
        int ret = pthread_create(&ts[loop], NULL, run, NULL);
        assert(ret >= 0);

    }
    for (int loop = 0; loop < THREAD_COUNT; loop++)
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
        // 多线程情况下，g_val++是否安全？需要volatile吗？
        // 看目前测试结果是安全的，但是原理上说的通吗？
        g_val++;
        unlock();
    }
}

