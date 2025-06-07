#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define MAX 30

int buffer[MAX];
int count = 0;
int in = 0;
int out = 0;

pthread_mutex_t mutex;
pthread_cond_t empty;
pthread_cond_t full;

void put(int item) {
  buffer[in] = item;
  in = (in + 1) % MAX;
  count++;
  printf("PUT: %d (count=%d)\n", item, count);
}

int get() {
  int item = buffer[out];
  out = (out + 1) % MAX;
  count--;
  printf("GET: %d (count=%d)\n", item, count);
  return item;
}

void *producer(void *arg) {
  int item = 0;
  while (1) {
    pthread_mutex_lock(&mutex);

    while (count == MAX) {
      pthread_cond_wait(&full, &mutex);
    }

    put(item++);

    pthread_cond_signal(&empty);

    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *consumer(void *arg) {
  while (1) {
    pthread_mutex_lock(&mutex);

    while (count == 0) {
      pthread_cond_wait(&empty, &mutex);
    }

    int item = get();

    pthread_cond_signal(&full);

    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main() {
  pthread_t prod_tid, cons_tid;

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&empty, NULL);
  pthread_cond_init(&full, NULL);

  pthread_create(&prod_tid, NULL, producer, NULL);
  pthread_create(&cons_tid, NULL, consumer, NULL);

  pthread_join(prod_tid, NULL);
  pthread_join(cons_tid, NULL);

  return 0;
}