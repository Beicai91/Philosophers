#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int shared_var = 0;
sem_t semaphore;

void *reader(void *arg) {
    while (1) {
        sem_wait(&semaphore); // Enter critical section
        printf("Reader read value: %d\n", shared_var);
        sem_post(&semaphore); // Exit critical section
        usleep(100000); // Sleep for 100ms
    }
    return NULL;
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&semaphore); // Enter critical section
        shared_var++;
        //printf("Writer updated value to: %d\n", shared_var);
        sem_post(&semaphore); // Exit critical section
        usleep(150000); // Sleep for 150ms
    }
    return NULL;
}

int main() {
    pthread_t reader_thread, writer_thread;

    sem_unlink("semaphore");
    sem_open("semaphore", O_CREAT, 0600, 1);

    if (pthread_create(&reader_thread, NULL, reader, NULL) != 0) {
        perror("Failed to create reader thread");
        return EXIT_FAILURE;
    }

    if (pthread_create(&writer_thread, NULL, writer, NULL) != 0) {
        perror("Failed to create writer thread");
        return EXIT_FAILURE;
    }

    pthread_join(reader_thread, NULL);
    pthread_join(writer_thread, NULL);

    sem_close(&semaphore);
    sem_unlink("semaphore");
    return EXIT_SUCCESS;
}
