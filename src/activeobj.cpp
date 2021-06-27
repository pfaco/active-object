#include "activeobj/activeobj.h"

namespace activeobj
{

void MessageQueue::enqueue(Message msg)
{
    std::lock_guard<std::mutex> lock(m);
    q.push(msg);
    cv.notify_one();
}

Message MessageQueue::dequeue(void)
{
    std::unique_lock<std::mutex> lock(m);
    while(q.empty())
    {
      cv.wait(lock);
    }
    Message msg = q.front();
    q.pop();
    return msg;
}

ActiveObject::ActiveObject() :
    running{false},
    queue{},
    t{&ActiveObject::run, this}
{}

ActiveObject::~ActiveObject() {
    post([&](){ running = false; });
    t.join();
}

void ActiveObject::post(Message msg) {
    queue.enqueue(msg);
}

void ActiveObject::run() {
    while (running) {
        auto msg = queue.dequeue();
        msg();
    }
}

}
