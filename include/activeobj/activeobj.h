#pragma once

#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

namespace activeobj
{

using Message = std::function<void()>;

class MessageQueue
{
public:
    void enqueue(Message msg);
    Message dequeue(void);

private:
    std::queue<Message> q;
    std::mutex m;
    std::condition_variable cv;
};

class ActiveObject
{
public:
    ActiveObject();
    ~ActiveObject();
    void post(Message msg);

private:
    bool running;
    MessageQueue queue;
    std::thread t;

    void run();
};

}
