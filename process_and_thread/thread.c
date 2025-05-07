#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 스레드에서 실행할 함수
void *thread_function(void *arg) {
    int thread_num = *((int *)arg);
    printf("Thread %d: 시작됨\n", thread_num);
    sleep(1); // 작업 시뮬레이션
    printf("Thread %d: 종료됨\n", thread_num);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_args[3];

    for (int i = 0; i < 3; i++) {
        thread_args[i] = i + 1;
        int result = pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
        if (result != 0) {
            perror("pthread_create 실패");
            exit(EXIT_FAILURE);
        }
    }

    // 메인 스레드는 모든 스레드가 끝날 때까지 대기
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("모든 스레드 종료\n");
    return 0;
}
