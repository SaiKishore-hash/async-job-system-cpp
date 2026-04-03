#pragma once
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <thread>
#include <future>

class EventLoop {
private:
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop = false;

    std::vector<std::thread> workers;

public:
    EventLoop(int numThreads);

    template <typename Func>
    auto submit(Func f) -> std::future<decltype(f())>;

    void shutdown();
};

#include "EventLoop.tpp"