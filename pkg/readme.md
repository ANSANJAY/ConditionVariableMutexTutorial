
# 📜 Producer-Consumer Problem with Queue

## 🚀 Introduction
This program demonstrates the classic producer-consumer problem where multiple threads share access to a common resource, in this case, a queue. The project uses POSIX threads (pthreads) for thread management and synchronization.

## 🎯 Problem Statement
- The program launches 4 threads: 2️⃣ consumer threads and 2️⃣ producer threads.
- All 4 threads interact with a shared resource - a Queue of integers 📥.
- Producer threads produce a random integer and add it to the Queue, while Consumer threads remove an integer from the Queue.
- The maximum size of the Queue is set to 5.

### 🔒 Constraints:

1. Producers hold the Queue until it's full.
2. Consumers consume the entire Queue and do not release it until it's empty.
3. Consumers signal 📢 the Producers when the Queue is exhausted, and Producers signal 📢 the Consumers when the Queue is full.

## 📖 Explanation of the Code

### 1. `new_int()`
This function generates a new integer sequentially, starting from 1.

### 2. 🌍 Global Variables
- `struct Queue_t *Q`: This is the global Queue used by all threads.
- Naming variables `prod1`, `prod2`, `cons1`, `cons2`: These are used to name the threads for better logs and understanding.

### 3. `prod_fn(void *arg)`
This is the function that producer threads run. 🏭

- The function first tries to acquire a lock on the queue.
- If the queue is full, the thread waits (blocks itself) until signaled by a consumer thread.
- If the queue is empty, the producer produces integers and pushes them to the queue until it's full.
- After filling up the queue, it signals the consumer threads and releases the lock.

### 4. `cons_fn(void *arg)`
This is the function that consumer threads run. 🛒

- The function tries to acquire a lock on the queue.
- If the queue is empty, the thread waits (blocks itself) until signaled by a producer thread.
- Once the queue is full, the consumer starts consuming the integers from the queue until it's empty.
- After emptying the queue, it signals the producer threads and releases the lock.

### 5. `main()`
The main function initializes the queue and sets the thread attributes to JOINABLE mode. It then creates two producer and two consumer threads. After starting all threads, it waits for all of them to finish.

## 🛠 Compilation
To compile the project:
```
gcc -g -c Queue.c -o Queue.o
gcc -g -c prod_cons_on_Q_Solution.c -o prod_cons_on_Q_Solution.o
gcc -g prod_cons_on_Q_Solution.o Queue.o -o exe -lpthread
```

## 🧠 Algorithm Breakdown

1. Initialize the shared Queue.
2. Start 2 producer threads and 2 consumer threads in JOINABLE mode.
3. Each producer thread tries to lock the queue.
   - If the queue is full, it waits.
   - If the queue is empty, it fills the queue with integers until full, then signals the consumers.
4. Each consumer thread tries to lock the queue.
   - If the queue is empty, it waits.
   - If the queue is full, it consumes all integers until the queue is empty, then signals the producers.
5. Once all threads finish, the program terminates.

## 🌟 Conclusion
The solution efficiently handles the producer-consumer problem using mutexes and condition variables for synchronization. The extensive use of `printf` statements helps in understanding the flow and for debugging purposes.

--- 

Adding emojis can make your README more visually appealing and engaging! However, it's important to ensure that the added emojis are contextually appropriate and do not overcrowd the content.
