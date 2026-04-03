#pragma once

template <typename Func>
auto EventLoop::submit(Func f) -> std::future<decltype(f())> {
    using ReturnType = decltype(f());

    auto taskPtr = std::make_shared<std::packaged_task<ReturnType()>>(f);

    std::future<ReturnType> result = taskPtr->get_future();

    {
        std::lock_guard<std::mutex> lock(mtx);
        tasks.push([taskPtr]() {
            (*taskPtr)();
        });
    }

    cv.notify_one();

    return result;
}