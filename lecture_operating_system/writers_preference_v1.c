#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define ITER 10000
void *readers(void *arg);
void *writers(void *arg);

sem_t x;
sem_t y;
sem_t m;
sem_t wsem;
sem_t rsem;
int readercount = 0;
int writercount = 0;

int main() {
  pthread_t tid1, tid2;
  sem_init(&m, 0, 1);
  sem_init(&x, 0, 1);
  sem_init(&y, 0, 1);
  sem_init(&wsem, 0, 1);
  sem_init(&rsem, 0, 1);

  pthread_create(&tid1, NULL, readers, NULL);
  pthread_create(&tid2, NULL, writers, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
}

/* thread routin */
void *readers(void *arg) {
  for (int i = 0; i < ITER; i++) {
    sem_wait(&rsem);
    sem_wait(&x);
    readercount++;
    if (readercount == 1) {
      sem_wait(&wsem);
    }
    sem_post(&x);
    sem_post(&rsem);

    sem_wait(&x);
    readercount--;
    if (readercount == 0) {
      sem_post(&wsem);
    }
    sem_post(&x);
  }
  return NULL;
}

void *writers(void *arg) {
  for (int i = 0; i < ITER; i++) {

    sem_wait(&y);
    writercount++;
    if (writercount == 1) {
      sem_wait(&rsem);
    }
    sem_post(&y);
    sem_wait(&wsem);
    printf("Writer!\n");
    sem_post(&wsem);

    sem_wait(&y);
    writercount--;
    if (writercount == 0) {
      sem_post(&rsem);
    }
    sem_post(&y);
  }
  return NULL;
}