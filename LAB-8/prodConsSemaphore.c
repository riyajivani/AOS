#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 3 // Size of the shared buffer

int buffer[BUFFER_SIZE];

int in = 0, out = 0;

sem_t mutex, empty, full;

void* producer() {
    int item;
    for (int i = 0; i < 5; i++) {
        item = i; // Produce item
        sem_wait(&empty); // Wait if the buffer is full
        sem_wait(&mutex); // Enter critical section

        // Produce item into the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        printf("Produced item %d by thread %ld\n", item, pthread_self());

        sem_post(&mutex); // Exit critical section
        sem_post(&full); // Signal that the buffer is not empty
    }
    pthread_exit(NULL);
}


void* consumer() {
    int item;
    for (int i = 0; i < 5; i++) {
        sem_wait(&full); // Wait if the buffer is empty
        sem_wait(&mutex); // Enter critical section

        // Consume item from the buffer
        item = buffer[out];
        printf("Consumed item %d by thread %ld\n", item, pthread_self());
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex); // Exit critical section
        sem_post(&empty); // Signal that the buffer is not full
    }
    pthread_exit(NULL);
}

int main() {
    sem_init(&mutex, 0, 1); //for mutual exclusion
    sem_init(&empty, 0, BUFFER_SIZE); // empty semaphore for buffer 
    sem_init(&full, 0, 0); // initialize full semaphore to 0

    pthread_t producers[2]; // three producer threads
    pthread_t consumers[2]; // three consumer threads

    for (int i = 0; i < 2; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

