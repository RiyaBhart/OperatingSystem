#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int order = 0;
pthread_mutex_t order_mutex;
sem_t chef_slots;

void* customer(void* arg) {
    pthread_mutex_lock(&order_mutex);
    order++;
    printf("Customer placed order #%d\n", order);
    pthread_mutex_unlock(&order_mutex);
    pthread_exit(NULL);
}

void* chef(void* arg) {
    sem_wait(&chef_slots);
    pthread_mutex_lock(&order_mutex);
    if (order > 0) {
        printf("Chef preparing order #%d\n", order);
        sleep(2);
        printf("Chef completed order #%d\n", order);
        order--;
    }
    pthread_mutex_unlock(&order_mutex);
    sem_post(&chef_slots);
    pthread_exit(NULL);
}

int main() {
    pthread_t c[5], ch[5];
    pthread_mutex_init(&order_mutex, NULL);
    sem_init(&chef_slots, 0, 2);

    for (int i = 0; i < 5; i++) pthread_create(&c[i], NULL, customer, NULL);
    for (int i = 0; i < 5; i++) pthread_join(c[i], NULL);

    for (int i = 0; i < 5; i++) pthread_create(&ch[i], NULL, chef, NULL);
    for (int i = 0; i < 5; i++) pthread_join(ch[i], NULL);

    pthread_mutex_destroy(&order_mutex);
    sem_destroy(&chef_slots);
    return 0;
}

