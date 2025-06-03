#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define NUM 5

/*
Sol1:
철학자 4명만 한 방에 들어가도록 제약을 걸어서, Circular Wait을 제거함.
*/

sem_t forks[NUM]; // forks. 공유자원임. 이 문제에선 Binary Semaphore를 나타냄.
sem_t room;

void pickup(int philosopher_num) { sem_wait(&forks[philosopher_num % NUM]); }

void putdown(int philosopher_num) { sem_post(&forks[philosopher_num % NUM]); }

void thinking(int philosopher_num) {
  printf("philosopher %d is thinking\n", philosopher_num);
  return;
}

void eating(int philosopher_num) {
  printf("philosopher %d is eating\n", philosopher_num);
  return;
}

void *philosopher(void *arg) {
  int philosopher_num;
  philosopher_num = (unsigned long int)arg;

  while (1) {
    sem_wait(&room);
    pickup(philosopher_num);
    printf("philosopher %d picks up the fork %d.\n", philosopher_num,
           philosopher_num);
    pickup(philosopher_num + 1);
    printf("philosopher %d picks up the fork %d.\n", philosopher_num,
           (philosopher_num + 1) % NUM);

    eating(philosopher_num);

    putdown(philosopher_num);
    printf("philosopher %d puts down the fork %d.\n", philosopher_num,
           (philosopher_num + 1) % NUM);
    putdown(philosopher_num + 1);
    printf("philosopher %d puts down the fork %d.\n", philosopher_num,
           philosopher_num);
    sem_post(&room);

    thinking(philosopher_num);
  }
  return NULL;
}

int main() {
  // 스레드 ID 배열 선언
  pthread_t threads[NUM];

  for (int i = 0; i < NUM; i++) {
    // 세마포어 변수들을 초기화함.
    // 두 번째 인자의 0은 스레드간 공유자원을 의미하며, 세 번째 인자의 1은
    // 세마포어 초깃값을 나타낸다.
    // 즉, 포크 1개를 사용할 수 있다는 의미다.
    sem_init(&forks[i], 0, 1);
  }

  sem_init(&room, 0, 4);

  for (unsigned long int i = 0; i < NUM; i++) {
    pthread_create(&threads[i], NULL, philosopher, (void *)i);
  }

  for (int i = 0; i < NUM; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("NO DEADLOCK\n");
  return 0;
}