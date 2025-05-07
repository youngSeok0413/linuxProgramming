#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5
#define NUM_INCREMENTS 100000

int counter = 0;               // 공유 자원
pthread_mutex_t mutex;         // 뮤텍스 객체

void *increment_counter(void *arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        pthread_mutex_lock(&mutex);   // 임계 영역 진입
        counter++;
        pthread_mutex_unlock(&mutex); // 임계 영역 이탈
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // 뮤텍스 초기화
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("뮤텍스 초기화 실패");
        return 1;
    }

    // 스레드 생성
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
            perror("스레드 생성 실패");
            return 1;
        }
    }

    // 모든 스레드 종료 대기
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // 결과 출력
    printf("최종 counter 값: %d (예상: %d)\n", counter, NUM_THREADS * NUM_INCREMENTS);

    // 뮤텍스 제거
    pthread_mutex_destroy(&mutex);

    return 0;
}
