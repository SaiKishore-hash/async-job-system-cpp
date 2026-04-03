#include "EventLoop.h"

EventLoop::EventLoop(int numThreads) {
    for (int i = 0; i < numThreads; i++) {
        workers.emplace_back([this]() {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(this->mtx);

                    this->cv.wait(lock, [this]() {
                        return this->stop || !this->tasks.empty();
                    });

                    if (this->stop && this->tasks.empty())
                        return;

                    task = this->tasks.front();
                    this->tasks.pop();
                }

                task();
            }
        });
    }
}

void EventLoop::shutdown() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        stop = true;
    }

    cv.notify_all();

    for (std::thread &worker : workers) {
        worker.join();
    }
}