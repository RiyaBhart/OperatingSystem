#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_TELLERS 3
#define NUM_TRANSACTIONS 5

int account_balance = 1500;
pthread_mutex_t balance_mutex;

void* teller_function(void* arg) {
    int teller_id = *(int*)arg;
    free(arg);
    for (int i = 0; i < NUM_TRANSACTIONS; i++) {
        pthread_mutex_lock(&balance_mutex);
        int transaction = (rand() % 2 == 0) ? 100 : -50;
        account_balance += transaction;
        printf("Teller %d performed a %s of %d. New balance: %d\n",
               teller_id,
               (transaction > 0) ? "deposit" : "withdrawal",
               abs(transaction),
               account_balance);
        pthread_mutex_unlock(&balance_mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tellers[NUM_TELLERS];
    pthread_mutex_init(&balance_mutex, NULL);
    for (int i = 0; i < NUM_TELLERS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&tellers[i], NULL, teller_function, id);
    }
    for (int i = 0; i < NUM_TELLERS; i++) {
        pthread_join(tellers[i], NULL);
    }
    printf("Final account balance: %d\n", account_balance);
    pthread_mutex_destroy(&balance_mutex);
    return 0;
}

