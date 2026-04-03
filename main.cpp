#include "EventLoop.h"
#include "Job.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

std::mutex print_mtx;

int main() {
    EventLoop loop(3);

    std::vector<std::future<std::string>> results;

    for (int i = 1; i <= 5; i++) {
        Job job{i, "compute"};

        {
            std::lock_guard<std::mutex> lock(print_mtx);
            std::cout << "[Job Submitted] ID: " << job.id << "\n";
        }

        auto future = loop.submit([job]() {
            {
                std::lock_guard<std::mutex> lock(print_mtx);
                std::cout << "[Processing] Job " << job.id 
                          << " on thread " << std::this_thread::get_id() << "\n";
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            int result = job.id * job.id;

            return "Job " + std::to_string(job.id) + 
                   " result = " + std::to_string(result);
        });

        results.push_back(std::move(future));
    }

    for (auto &f : results) {
        std::string res = f.get();

        std::lock_guard<std::mutex> lock(print_mtx);
        std::cout << "[Completed] " << res << "\n";
    }

    loop.shutdown();

    return 0;
}