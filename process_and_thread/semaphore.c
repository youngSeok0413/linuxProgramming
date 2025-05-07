#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

union semun {
    int val;
};

int main() {
    key_t key = ftok("semaphore", 75);
    int semid = semget(key, 1, 0666 | IPC_CREAT);

    union semun arg;
    arg.val = 1; // 초기 세마포어 값
    semctl(semid, 0, SETVAL, arg);

    struct sembuf p = {0, -1, 0}; // P 연산 (wait)
    struct sembuf v = {0, 1, 0};  // V 연산 (signal)

    // 세마포어 획득 (진입)
    semop(semid, &p, 1);
    printf("Entered critical section\n");
    sleep(2); // 임계 영역

    // 세마포어 반환 (종료)
    semop(semid, &v, 1);
    printf("Exited critical section\n");

    // 세마포어 삭제
    semctl(semid, 0, IPC_RMID);
    return 0;
}
