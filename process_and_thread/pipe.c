#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
    pid_t pid;
    int pfd[2];
    char line[BUFSIZ];
    int status;


    if(pipe(pfd) < 0){
        return -1;
    }

    if((pid = fork()) < 0){
        perror("[ERROR] : fork()");
        return -1;
    }
    else if(pid == 0){
        //child process
        close(pfd[0]);
        dup2(pfd[1], 1); //표준 출력(1) => pipe로 변경(pfd[1]), 리다이렉션
        /*
        int dup2(int oldfd, int newfd);
        oldfd	복제할 기존 파일 디스크립터
        newfd	새롭게 사용할 디스크립터 (기존 것이면 닫은 뒤 사용)
        dup2()는 newfd가 이미 열린 상태라면 자동으로 close(newfd)를 호출한 후 oldfd를 복제함
        이후 newfd와 oldfd는 동일한 열린 파일을 공유하게 되며, 동일한 오프셋을 사용함
        */

        execl("/bin/date", "date", NULL);
        close(pfd[1]);
        _exit(127);
    }
    else{
        close(pfd[1]);
        if(read(pfd[0], line, BUFSIZ) < 0){
            return -1;
        }
        printf("parent : %s", line);

        close(pfd[0]);
        waitpid(pid, &status, 0);
    }

    return 0;
}