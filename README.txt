Title: Individual Program 2
Name: Sage Lyon

Description:
- Fork-join
    - In this program, the parent thread prints "parent: begin" and then creates a child thread which prints "child"
    - Only after the child prints its message does the parent print the message "parent: end"
    - This is accomplished using a semaphore which is initialized to 0.
    - After the child prints its message, it executes sem_push() which will trigger the parent to stop waiting and finish executing.

- Rendezvous
    - In this program, there are two threads that both stop at a rendezvous point in the code. 
    - When one thread enters the rendezvous point, it waits until the other thread enters before they both continue. 
    - This is done using two semaphores.
    - Child one will post to semaphore one and then wait on semaphore two. Child two posts to semaphore two and then waits on semaphore one.

- Barrier
    - In this program, there are 1+ threads that all must stop at a barrier and are only allowed to continue when all other threads reach the barrier.
    - This is accomplished with two semaphores (lock and barrier_lock) and two integers (thread_count and num_threads).
    - When each thread reaches the barrier, they increment the thread_count (the lock semaphore is used to ensure there is no race condition).
    - If the thread_count is less than the total number of threads (num_threads), the thread will call sem_wait() on the barrier_lock semaphore.
    - Once all the threads have reached the barrier, the last thread will not wait and will call sem_push() on the barrier_lock before returning.
    - A thread will be released and will then call sem_push() before returning, releasing another thread.
    - This will continue until all threads are released.

Instructions:
- To compile the programs, run the command: make. 
- This will create three executables: fork-join, rendezvous, barrier.
- To run the fork-join program, run the command: ./fork-join
- To run the rendezvous program, run the command: ./rendezvous
- To run the barrier program, run the command: ./barrier <number of threads (must be greater than 0)>


