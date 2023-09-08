# Thread Synchronization Using Condition Variables :notebook_with_decorative_cover:

## Overview :mega:

We focus on understanding how condition variables are used in thread synchronization. Condition variables are fundamental for writing multithreaded programs and are extensively used alongside mutexes for advanced thread synchronization techniques.

## Key Points :pushpin:

1. **Condition Variables**: Used for blocking a thread as well as signaling a thread.
   - **Blocking**: Halting the execution of a thread.
   - **Signaling**: Resuming the execution of a blocked thread.
   
2. **Steps to Block a Thread**: Two main steps
    1. **Lock a Mutex**: A thread must first lock a mutex to block itself.
    2. **Invoke `pthread_cond_wait` API**: This API takes the condition variable and the locked mutex as arguments.
   
3. **Behind-the-Scenes of `pthread_cond_wait`**: Two important actions
   - The calling thread gets blocked.
   - The mutex is unlocked and declared available for other threads.
  
4. **Steps to Signal a Thread**: Also a three-step process
   1. **Lock the Mutex**: Must be the same mutex locked by the blocked thread.
   2. **Invoke `pthread_cond_signal` API**: Signals the condition variable to resume a blocked thread.
   3. **Unlock the Mutex**: The signaling thread unlocks the mutex.
  
5. **States of Thread**: When signaled
   - **Ready to Execute State**: Moves to this state when signaled.
   - **Actually Execute State**: Moves to this state when the mutex is released by the signaling thread.
   
6. **Mutex Lock and Unlock**:
   - Mutex gets automatically unlocked when a thread is blocked.
   - Mutex gets locked when the blocked thread moves from "Ready to Execute" to "Actually Execute."

## Interview Questions :question:

### Q1: What is the role of a condition variable in thread synchronization?

#### Answer :point_down:
Condition variables are used for blocking and signaling threads. They allow threads to halt their execution (`blocking`) and to resume from a halted or blocked state (`signaling`).

### Q2: Can you describe the steps for blocking a thread using a condition variable?

#### Answer :point_down:
Certainly. Blocking a thread using a condition variable involves two key steps:
1. **Lock a Mutex**: The thread first locks a mutex.
2. **Invoke `pthread_cond_wait`**: The thread then calls the `pthread_cond_wait` API, passing in the condition variable and the locked mutex as arguments.

### Q3: What are the two actions that `pthread_cond_wait` performs behind the scenes?

#### Answer :point_down:
When `pthread_cond_wait` is invoked, it does two things:
1. The calling thread gets blocked.
2. The mutex that was locked by the calling thread gets automatically unlocked, making it available for other threads.

### Q4: Describe the process of signaling a blocked thread to resume its execution.

#### Answer :point_down:
Signaling a blocked thread involves three steps:
1. **Lock the Mutex**: The signaling thread first locks the mutex.
2. **Invoke `pthread_cond_signal` API**: The signaling thread calls this API to signal the condition variable.
3. **Unlock the Mutex**: Finally, the signaling thread unlocks the mutex, allowing the blocked thread to move to the "Actually Execute" state.

### Q5: What happens when a blocked thread receives a signal?

#### Answer :point_down:
When a blocked thread receives a signal, it moves from the "Blocked" state to the "Ready to Execute" state. It will move to the "Actually Execute" state once the signaling thread releases the mutex. Upon this, the mutex is immediately locked by the thread that just got signaled, and it begins its execution.
