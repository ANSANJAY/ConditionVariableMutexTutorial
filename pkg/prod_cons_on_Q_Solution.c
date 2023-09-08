#if 0

Problem Statement :
====================
Write a program which launches 4 threads - 2 consumer threads and 2 producer threads. Threads
are created in JOINABLE Mode.
All 4 threads act on a shared resource - A Queue of integers. Producer threads produce
a random integer and add it to Queue, Consumer threads remove an integer from the Queue.
Maximum size of the Queue is 5.

Following are the constraints applied :

1. When producer threads produce an element and add it to the Queue, it does not release the Queue
untill the Queue is full i.e producer thread release the Queue only when it is full

2. When consumer threads consume an element from the Queue, it consumes the entire Queue and
do not release it until the Queue is empty.

3. Consumer Signals the Producers when Queue is Exhausted, Producers Signals the Consumers when Queue	
becomes full

Guidelines :
Use as many printfs as possible, so you can debug the program easily

Conmpile and Run :
gcc -g -c Queue.c -o Queue.o
gcc -g -c Assignment_prod_cons_on_Q_Solution.c -o Assignment_prod_cons_on_Q_Solution.o
gcc -g Assignment_prod_cons_on_Q_Solution.o Queue.o -o exe -lpthread
 
#endif

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include "Queue.h"

// Function to generate a new integer
static int new_int() {
	static int a = 0;
	a++;
	return a;
}

struct Queue_t *Q; // Global Queue variable

// Naming the threads for better logs
static const char *prod1 = "TP1";
static const char *prod2 = "TP2";
static const char *cons1 = "TC1";
static const char *cons2 = "TC2";

// Producer function
static void *
prod_fn(void *arg) {
	char *th_name = (char *)arg;

	printf("Thread %s waiting to lock the Queue\n", th_name);
	pthread_mutex_lock(&Q->q_mutex); // Acquire the lock
	printf("Thread %s locks the Queue\n", th_name);

	// Check if the queue is full
	while (is_queue_full(Q)) {
		printf("Thread %s blocks itself, Q is already Full\n", th_name);
		pthread_cond_wait(&Q->q_cv, &Q->q_mutex); // Wait until signaled
		printf("Thread %s wakes up, checking the Queue status again\n", th_name);
	}

	// Check if the queue is empty, only then produce
	assert(is_queue_empty(Q));
	int i;
	while(!is_queue_full(Q)) { 
		i = new_int();
		printf("Thread %s produces new integer %d\n", th_name, i);
		enqueue(Q, (void *)i); 
		printf("Thread %s pushed integer %d in Queue, Queue size = %d\n", th_name, i, Q->count);
	}
	
	// Signal the waiting threads after filling up the queue
	printf("Thread %s Filled up the Queue, signalling and releasing lock\n", th_name);
	pthread_cond_broadcast(&Q->q_cv); 
	pthread_mutex_unlock(&Q->q_mutex); 
	printf("Thread %s finished, and exit\n", th_name);
	return NULL;
}

// Consumer function
static void *
cons_fn(void *arg) {
	char *th_name = (char *)arg;

	printf("Thread %s waiting to lock the Queue\n", th_name);
	pthread_mutex_lock(&Q->q_mutex); 
	printf("Thread %s locks the Queue\n", th_name);

	// Check if the queue is empty
	while (is_queue_empty(Q)) {
		printf("Thread %s blocks itself, Q is already empty\n", th_name);
		pthread_cond_wait(&Q->q_cv, &Q->q_mutex); 
		printf("Thread %s wakes up, checking the Queue status again\n", th_name);
	}

	// Start consuming only if the queue is full
	assert(is_queue_full(Q));

	int i;
	while(!is_queue_empty(Q)) {
		i = (int)deque(Q);
		printf("Thread %s consumes an integer %d, Queue size = %d\n", th_name, i, Q->count);
	}
	
	// Signal the other threads after consuming
	printf("Thread %s Drains the entire Queue, sending signal to Blocking Threads\n", th_name);
	pthread_cond_broadcast(&Q->q_cv);
	
	printf("Thread %s releasing lock\n", th_name);
	pthread_mutex_unlock(&Q->q_mutex);
	printf("Thread %s finished, and exit\n", th_name);
	return NULL;
}

int main(int argc, char **argv) {
	Q = initQ(); // Initializing the queue

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_t prod_th1, prod_th2; // Two producer threads
	pthread_t cons_th1, cons_th2; // Two consumer threads

	// Create producer and consumer threads
	pthread_create(&prod_th1, &attr, prod_fn, (void *)prod1);
	pthread_create(&prod_th2, &attr, prod_fn, (void *)prod2);
	pthread_create(&cons_th1, &attr, cons_fn, (void *)cons1);
	pthread_create(&cons_th2, &attr, cons_fn, (void *)cons2);

	// Wait for all threads to finish
	pthread_join(prod_th1, 0);
	pthread_join(prod_th2, 0);
	pthread_join(cons_th1, 0);
	pthread_join(cons_th2, 0);

	printf("Program Finished\n");
	pthread_exit(0);
	return 0;
}
