/* Bad sharing */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define ITER 10000
#define MAX 30
int x = 0; // x는 현재 버퍼에 있는 아이템 수
void *producer(void *arg);
void *consumer(void *arg);

sem_t m, empty, fill;

/* thread routin */
void *producer(void *arg) {
  for (int i = 0; i < ITER; i++) {
    sem_wait(&empty);
    sem_wait(&m);
    printf("%u: %d\n", (unsigned int)pthread_self(), x);
    if (x < MAX) {
      x++;
    }
    sem_post(&m);
    sem_post(&fill);
  }
  return NULL;
}

void *consumer(void *arg) {
  for (int i = 0; i < ITER; i++) {
    sem_wait(&fill);
    sem_wait(&m);
    printf("%u: %d\n", (unsigned int)pthread_self(), x);
    if (x > 0) {
      x--;
    }
    sem_post(&m);
    sem_post(&empty);
  }
  return NULL;
}

int main() {
  pthread_t tid1, tid2;

  // m은 상호배제용
  sem_init(&m, 0, 1);
  // e는 생산자 제약조건. MAX는 30
  sem_init(&empty, 0, MAX);
  // f는 소비자 제약조건. MIN은 0
  sem_init(&fill, 0, 0);

  pthread_create(&tid1, NULL, producer, NULL);
  pthread_create(&tid2, NULL, consumer, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  if (x != 0) {
    printf("BOOM! counter=%d\n", x);
  } else {
    printf("OK counter=%d\n", x);
  }
}