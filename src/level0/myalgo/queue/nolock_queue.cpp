/*

g++ -g -o lockfree_queue lockfree_queue.cpp

需求。
线程安全的无锁队列，先入先出。

// 入队
enqueue()

// 出队
dequeue

*/

#include <stdio.h>
#include <assert.h>

#define DEBUG_PRINT(format, ...) printf((format), ##__VA_ARGS__)

void test();

template <typename T>
class Queue
{
    class Node
    {
    public:
        Node(T val)
        {
            _val = val;
            _next = NULL;
        }
        T _val;
        Node *_next;
    };
public:
    Queue()
    {
        _head = NULL;
        _tail = NULL;
    }

    ~Queue()
    {
        if (_dummyh)
            delete _dummyh;
        if (_dummyt)
            delete _dummyt;
    }

    // 目的只操作尾指针
    void enqueue(T val)
    {
        Node *n = new Node(val);
        if (_head == NULL)
        {
            _head = n;
            _tail = n;
        }
        else
        {
            _tail->_next = n;
            _tail = n;
        }
    }

    // head出队列
    // @return true 有元素出队； false 无元素出队
    bool dequeue(T &val)
    {
        bool ret = false;
        if (_head != NULL)
        {
            val = _head->_val;
            delete _head;
            
            _head = _head->_next;
            if (_head == NULL) 
            {
                _tail = _head;
            }
            ret = true;
        }
        return ret;
    }

    bool is_empty() { return _head == NULL; }
private:
    Node *_head;
    Node *_tail;
};

int main()
{
    test();
    return 0;
}

void test()
{
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    while (!q.is_empty())
    {
        int val = 0;
        bool b = q.dequeue(val);
        assert(b == true);
        printf("val = %d\n", val);
    }
    
}

