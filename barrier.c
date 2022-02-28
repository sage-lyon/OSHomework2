#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common_threads.h"

// If done correctly, each child should print their "before" message
// before either prints their "after" message. Test by adding sleep(1)
// calls in various locations.

// You likely need two semaphores to do this correctly, and some
// other integers to track things.

typedef struct __barrier_t {
    sem_t lock, barrier_lock;
    int num_threads, thread_count;
} barrier_t;


// the single barrier we are using for this program
barrier_t b;

void barrier_init(barrier_t *b, int num_threads) {
    // lock is initialized to 1 so that the first thread that accesses it will be allowed to continue
    sem_init(&b->lock, 0, 1);
    // barrier_lock is initialized to 0 so that the all threads will wait until another calls sem_post
    sem_init(&b->barrier_lock, 0, 0);
    b->num_threads = num_threads;
    b->thread_count = 0;
}

void barrier(barrier_t *b) {

    // the lock semaphore is used to lock the critical section that increments the thread_count
    sem_wait(&b->lock);
    b->thread_count++;
    sem_post(&b->lock);

    // all threads execept the last thread to enter the barrier must wait on the barrier_lock
    if(b->thread_count < b->num_threads)
        sem_wait(&b->barrier_lock);

    // the last thread to enter the barrier calls sem_post on the barrier_lock releasing another thread 
    // each thread that is released will repeat this action until all other threads are released
    sem_post(&b->barrier_lock);
}

//
// XXX: don't change below here (just run it!)
//
typedef struct __tinfo_t {
    int thread_id;
} tinfo_t;

void *child(void *arg) {
    tinfo_t *t = (tinfo_t *) arg;
    printf("child %d: before\n", t->thread_id);
    barrier(&b);
    printf("child %d: after\n", t->thread_id);
    return NULL;
}


// run with a single argument indicating the number of 
// threads you wish to create (1 or more)
int main(int argc, char *argv[]) {
    assert(argc == 2);
    int num_threads = atoi(argv[1]);
    assert(num_threads > 0);

    pthread_t p[num_threads];
    tinfo_t t[num_threads];

    printf("parent: begin\n");
    barrier_init(&b, num_threads);
    
    int i;
    for (i = 0; i < num_threads; i++) {
	t[i].thread_id = i;
	Pthread_create(&p[i], NULL, child, &t[i]);
    }

    for (i = 0; i < num_threads; i++) 
	Pthread_join(p[i], NULL);

    printf("parent: end\n");
    return 0;
}

