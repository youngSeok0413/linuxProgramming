#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <sys/socket.h>


int main(){

    int ret, fd[2];
    int status;
    char buf[] = "Hello World", line[BUFSIZ];
    pid_t pid;

    ret = socketpair(AF_LOCAL, SOCK_STREAM, 0, fd);
    if(ret == -1){
        return -1;
    }

    printf("socket 1 : %d\n", fd[0]); //하나가 read면 다른 하나가 write인 방식, rw가 정해져 있지는 않다.
    printf("socket 2 : %d\n", fd[1]);

    if((pid = fork()) < 0){
        return -1;
    }
    else if(pid == 0){
        write(fd[1], buf, strlen(buf)+1);
        printf("Data send : %s\n", buf);
        close(fd[1]); 
    }
    else{
        wait(&status); 					/* 자식 프로세스의 종료 대기 */
        read(fd[0], line, BUFSIZ); 		/* 자식 프로세스에서 온 데이터 읽기 */
        printf("Received data : %s\n", line);
        close(fd[0]); 
    }

    return 0;
}