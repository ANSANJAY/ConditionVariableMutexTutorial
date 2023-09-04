
# Multithreading and Condition Variables in C

## Table of Contents
1. [Introduction to Condition Variables](#introduction-to-condition-variables)
2. [Multiple Condition Variables](#multiple-condition-variables)
3. [Pthread Condition Broadcast API](#pthread-condition-broadcast-api)
4. [Interview Questions](#interview-questions)

---

## Introduction to Condition Variables 📝

- **What is a Condition Variable?**: A condition variable is often associated with a mutex and a predicate. 🎯
- **Role of Mutex**: Ensures mutual exclusivity when a thread checks the predicate. No other thread should interfere with the predicate during the check. 🔒
- **Rules**: 
  - Many condition variables can be associated with the same mutex.
  - One condition variable cannot be associated with more than one mutex. 🛑

---

## Multiple Condition Variables 🌐

- **Scenario**: 
  - Multiple Threads: `T1`, `T2`, `T3`
  - Each has its own condition variable: `cv1`, `cv2`, `cv3`
  - One resource `R` with one mutex `M`
- **Waiting and Signaling**: 
  - Threads block themselves if the resource is busy.
  - Threads invoke `pthread_condition_wait` API.
  - The signaling thread (`TS`) can signal specific threads to unblock. 🔔

- **Developer Power**: The developer can specifically signal which thread to unblock and execute. 👨‍💻

---

## Pthread Condition Broadcast API 📡

- **Purpose**: Unblocks all threads that are blocked on the same condition variable.
- **Example**: Threads `T1`, `T2`, `T3` blocked on the same condition variable.
- **How it works**: 
  - Signaling thread (`TS`) invokes `pthread_condition_broadcast`.
  - All threads move from blocked to ready state.
  - OS scheduler determines the sequence they get executed in. 🔄

- **Alternative**: Without broadcast, you need to call `pthread_condition_signal` individually for each thread.
- **Lack of Control**: The order in which the threads are unblocked is not in the programmer's control. 🎭

---

## Interview Questions ❓

1. **What is the role of a Mutex in working with condition variables?**
    - **Answer**: The mutex ensures that no other thread interferes with the predicate check, providing mutual exclusivity. 🔐

2. **How can you associate multiple condition variables with the same mutex?**
    - **Answer**: You can associate multiple condition variables with the same mutex by invoking `pthread_condition_wait` for each thread, passing in the mutex and the thread's respective condition variable as arguments. 🔄

3. **What is the `pthread_condition_broadcast` API and when would you use it?**
    - **Answer**: This API is used to signal all threads blocked on the same condition variable to resume execution. It's particularly useful when you want to unblock all waiting threads at once. 🌐

4. **What are the limitations of the `pthread_condition_broadcast` API?**
    - **Answer**: The API doesn't allow you to control the order in which the threads are unblocked; that decision is left to the operating system's scheduling policy. 🛑

5. **How does having individual condition variables for each thread give the programmer more control?**
    - **Answer**: Individual condition variables allow the programmer to selectively unblock threads. This fine-grained control is useful for implementing complex logic. 🔍

---

Feel free to ask for more information or additional questions you might have! 📚