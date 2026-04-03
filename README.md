# Async Job Processing System in C++

## Overview

This project implements a simple job processing system in C++ that executes multiple tasks in parallel using a pool of worker threads.

Instead of processing tasks one by one, the system distributes work across multiple workers, improving performance and efficiency.

---

## Problem Statement

In many real-world systems, a large number of independent tasks need to be processed efficiently (for example, background jobs, data processing, or request handling).

A single-threaded approach becomes slow as the workload increases.

This project demonstrates how to:
- Queue incoming tasks
- Execute them concurrently using multiple workers
- Safely manage shared resources

---

## How It Works

1. Jobs are submitted to a shared queue  
2. Multiple worker threads continuously monitor the queue  
3. Each worker picks up a job and executes it  
4. Results are returned asynchronously  

---

## Key Features

- Multi-threaded execution using worker threads  
- Thread-safe task queue using mutex and condition variables  
- Asynchronous result retrieval using futures  
- Graceful shutdown of worker threads  
- Simple job tracking and logging  

---

## Project Structure

async-job-system-cpp/
├── include/
│   ├── EventLoop.h
│   ├── EventLoop.tpp
│   └── Job.h
├── src/
│   └── EventLoop.cpp
├── main.cpp
├── README.md

---

## Example Output

[Job Submitted] ID: 1  
[Job Submitted] ID: 2  
[Processing] Job 1 on thread ...  
[Processing] Job 2 on thread ...  
[Completed] Job 1 result = 1  
[Completed] Job 2 result = 4  

Note: Execution order may vary due to parallel processing.

---

## How to Run

Compile:

g++ main.cpp src/EventLoop.cpp -Iinclude -o app

Run:

./app

---

## Concepts Demonstrated

- Multithreading in C++
- Producer-Consumer pattern
- Thread synchronization (mutex, condition variables)
- Asynchronous programming using futures
- Task scheduling and execution

---

## Limitations

- No task prioritization
- No persistence (in-memory only)
- Fixed number of worker threads

---

## Future Improvements

- Add task priority scheduling
- Add delayed/scheduled jobs
- Implement dynamic thread pool resizing
- Add logging and monitoring system

---

## What I Learned

- How to design a system that executes tasks in parallel
- How to avoid race conditions in multi-threaded programs
- How to coordinate threads safely using synchronization primitives
- How asynchronous task execution works in practice