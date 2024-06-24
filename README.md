# Philosophers
The Philosophers project aims to help us have a basic understanding of <br>
- process synchronization (or the sychronization between multiple threads of a process), <br>
- the problems related to the synchronization (ex. race condition - a situation where multiple threads or processes try to access shared data, deadlock) <br>
- the solutions (Use of mutex or semaphore + Careful design of cooperation between threads/processes) <br>

About race condition in bonus:
If you add -fsanitize=thread -g to compile the program, TSan will report a race condition over variable "meal_time" between eat() and monitor_death(). However the meal_time is well protected by a semaphore. After some reseach online and discussion, it's possible that it's a false positive of TSan when semaphore is used. To further prove this possibility, I wrote test.c which is a simple two-thread process with the shared variable well protected by semaphore, but TSan reports a race condition anyway. If you encounter the same problem and have some new findings, please feel free to leave me a message so that I can improve the bonus part. Thanks in advance!

Useful links:<br>
[Process synchronization, its problems and solutions](https://www.youtube.com/watch?v=ph2awKa8r5Y&list=PLBlnK6fEyqRjDf_dmCEXgl6XjVKDDj0M2) <br>
[Threads, mutex and programmation concurrency in C](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/) <br>
[Difference between process and thread](https://www.geeksforgeeks.org/difference-between-process-and-thread/) <br>
[Mutex VS Semaphore](https://www.youtube.com/watch?v=8wcuLCvMmF8) <br>
