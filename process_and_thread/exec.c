#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
        return -1;
    }

    if (pid == 0) {
        // 자식 프로세스
        printf("자식 프로세스: 'ls -l' 실행\n");
        execlp("ls", "ls", "-l", NULL);  // 현재 프로세스를 ls 명령으로 덮어쓰기

        // execlp 실패 시 아래 코드 실행됨
        perror("execlp error");
        return -1;
    } else {
        // 부모 프로세스
        wait(NULL);  // 자식이 끝날 때까지 대기
        printf("부모 프로세스: 자식 종료 확인\n");
    }

    return 0;
}
