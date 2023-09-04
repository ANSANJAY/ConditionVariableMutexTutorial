
# Producer-Consumer Problem with Condition Variables and Mutexes 📚

## Overview 🌐
This repository is focused on an in-depth understanding of how condition variables and mutexes are used to solve the Producer-Consumer problem in a multithreaded environment.

---

## Key Concepts 🗝️

### Consumer and Producer Threads 👥
- **Consumer Thread (T1)**: Consumes elements from a shared queue.
- **Producer Thread (T2)**: Produces elements and pushes them into the shared queue.

### Shared Resource 🎛️
- A shared queue accessed by both consumer and producer threads.
- To provide mutual exclusion, it has associated **mutex** and **condition variable**.

### Condition Variable and Mutex 🛡️
- **Mutex**: Provides mutual exclusion.
- **Condition Variable**: Used for synchronization between threads.

### Predicate 📝
- A condition tested by the thread to check the state of the shared resource.
- Required for mutual exclusion.

---

## Detailed Explanation 📝

### Consumer Thread Steps 🛠️

1. **Step S1**: Consumer thread grabs a lock on the queue.
2. **Step S2**: Checks the state of the queue. If empty, it will get blocked.
3. **Step S3**: Invokes `pthread_condition_wait()` to block itself when queue is empty.

### Producer Thread Steps 🛠️

1. **Step S6**: Producer thread grabs a lock on the queue.
2. **Step S7**: Checks the state of the queue. If not full, pushes new element into the queue.
3. **Step S8**: Sends signal to the condition variable, notifying the consumer thread.
4. **Step S9**: Unlocks the mutex.

---

## Interview Questions ❓ with Answers ✅

### What is a Mutex and why is it required? 🤔
- **Answer**: A Mutex (Mutual Exclusion) is a synchronization primitive used to avoid concurrent access to a shared resource. It's required to ensure that one thread at a time can access the shared resource.

### How does a Condition Variable work in this context? 🤔
- **Answer**: The condition variable allows threads to block themselves when a certain condition is not met and wake up when signaled by another thread, achieving coordination.

### What is a Predicate and how is it used? 🤔
- **Answer**: A Predicate is a condition that the thread checks to see the state of the shared resource. In this example, it's used by the Consumer thread to check whether the queue is empty.

### What are the Critical Sections in this problem? 🤔
- **Answer**: Critical sections are portions of code where the shared resource is accessed. In this context, for the consumer, it's where it consumes an element; for the producer, it's where it pushes a new element into the queue.

### How are Mutex and Condition Variable related in this context? 🤔
- **Answer**: Mutex ensures mutual exclusion, whereas the condition variable ensures coordination between the threads. Both are used together to solve the Producer-Consumer problem effectively.

---

Feel free to use this as your revision guide for understanding condition variables and mutexes in the context of the Producer-Consumer problem! 📘
