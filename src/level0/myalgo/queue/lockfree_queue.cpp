/*

g++ -pthread -g -o lockfree_queue lockfree_queue.cpp

需求。
线程安全的无锁队列，先入先出。

// 入队
enqueue()

// 出队
dequeue

*/

#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <sys/time.h>


#define DEBUG_PRINT(format, ...) printf((format), ##__VA_ARGS__)

void test();

template <typename T>
class Queue
{
    class Node
    {
        friend class Queue;
    public:
        Node(T val)
        {
            _val = val;
            _next = NULL;
        }
        T _val;
        Node *_next;
    private:
        Node()
        {
            _next = NULL;
        }
    };
public:
    Queue()
    {
        _dummy = new Node();

        _head = _dummy;
        _tail = _dummy;
    }

    ~Queue()
    {
        if (_dummy)
            delete _dummy;
    }

    // 目的只操作尾指针
    void enqueue(T val)
    {
        Node *newtail = new Node(val);
        // 换成新的队尾
        Node *oldtail = NULL;
        do 
        {
            oldtail = _tail;
        } while (!__sync_bool_compare_and_swap(&_tail, oldtail, newtail));
        
        // 下面的操作是安全的，由于上个语句的成功，
        // 后续所有入队操作，都会操作new tail。
        // oldtail->_next只有这里可以修改。

        // 对于出队操作，如果发生在下面语句完成前，会认为队列空了。
        // 如果发生在下面语句后，则可以拿到新的节点。
        // 并发的情况下，这在语义上是说的通的。
        oldtail->_next = newtail;
    }

    // head出队列
    // @return true 有元素出队； false 无元素出队
    bool dequeue(T &val)
    {       
        bool ret = true;
        Node *oldnext = NULL;
        Node *newnext = NULL;
        do
        {
            if (_head->_next == NULL)
            {
                ret = false;
                break;
            }
    
            oldnext = _head->_next;
            // 下面语句安全，即使此时有人把_head->next改了，指向NULL，oldnext仍然指向旧的_head->next->next
            newnext = oldnext->_next;
        } while (!__sync_bool_compare_and_swap(&_head->_next, oldnext, newnext));

        if (ret)
            val = oldnext->_val;
        return ret;
    }

    bool is_empty() { return _head->_next == NULL; }
    long long len() 
    { 
        long long size = 0;
        Node *current = _head;
        while (current = current->_next)
        {
            size++;
        }
        return size;
    }
private:
    // dummy不可能出队
    Node *_dummy;
    Node *_head;
    Node *_tail;
};

int main()
{
    test();
    return 0;
}

///////////////////////////////////////////////////////
//                 TEST CODE BEGIN                   //
///////////////////////////////////////////////////////

void test1();
void test_enqueue();
void test_dequeue();


void test()
{
    test_enqueue();
    test_dequeue();
}

void test1()
{
    Queue<int> q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    printf("queue len: %lld\n", q.len());

    while (!q.is_empty())
    {
        int val = 0;
        bool b = q.dequeue(val);
        assert(b == true);
        printf("val = %d\n", val);
    }

}

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

Queue<int> g_queue;
#define THREAD_COUNT 4
#define ENQUEUE_COUNT 1000000

void* enqueue_thread(void *arg);
void* dequeue_thread(void *arg);

void test_enqueue()
{
    printf("Testing enqueue\n");
    // 多个线程并发入队，最后看队列的长度是否正确。
    {
        Timer enq_timer;
        pthread_t ts[THREAD_COUNT];
        for (int loop = 0; loop < THREAD_COUNT; loop++)
        {
            int ret = pthread_create(&ts[loop], NULL, enqueue_thread, NULL);
            assert(ret >= 0);
        }
        
        for (int loop = 0; loop < THREAD_COUNT; loop++)
        {
            (void)pthread_join(ts[loop], NULL);
        }
    }

    printf("g_queue len: %lld\n", g_queue.len());

    // 多个线程并发出队，最后看出队长度是否正确。

    // 并发读写怎么设计？
}

void test_dequeue()
{
    printf("Testing dequeue\n");

    int *dequeue_buf[THREAD_COUNT];

    for (int xx = 0; xx < THREAD_COUNT; ++xx)
    {
        dequeue_buf[xx] = new int[ENQUEUE_COUNT];
    }

    // 多个线程并发出队，最后看出队的长度是否正确。
    // 首先调用
    {
        Timer deq_timer;
        pthread_t ts[THREAD_COUNT];
        

        for (int loop = 0; loop < THREAD_COUNT; loop++)
        {
            int ret = pthread_create(&ts[loop], NULL, dequeue_thread, dequeue_buf[loop]);
            assert(ret >= 0);
        }

        for (int loop = 0; loop < THREAD_COUNT; loop++)
        {
            (void)pthread_join(ts[loop], NULL);
        }
    }

    long long sum = 0;
    for (int loop = 0; loop < THREAD_COUNT; loop++)
    {
        for (int validx = 0; validx < ENQUEUE_COUNT; validx++)
        {
            sum += dequeue_buf[loop][validx];
        }
    }

    printf("Dequeue sum is : %lld\n", sum);
}

void* enqueue_thread(void *arg)
{
    for (int loop = 0; loop < ENQUEUE_COUNT; ++loop)
    {
        g_queue.enqueue(loop+1);
    }
}

void* dequeue_thread(void *arg)
{
    int *buf = (int*)arg;
    for (int loop = 0; loop < ENQUEUE_COUNT; ++loop)
    {
        int val = 0;
        bool ret = g_queue.dequeue(val);
        assert(ret && val >= 0);
        buf[loop] = val;
    }
}



