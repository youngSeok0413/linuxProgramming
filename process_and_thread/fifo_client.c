#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFOFILE "fifo"

int main(){

    int n, fd;
    char buf[BUFSIZ];

    if((fd = open(FIFOFILE, O_WRONLY)) < 0){
        return -1;
    }

    while((n = read(0, buf, BUFSIZ)) > 0){ //표준 입력으로부터 글자 입력
        write(fd, buf, n); //말 그대로 입력 창에서 받은 것을 그대로 출력(단축키 등도 그대로 먹힘)
    }

    close(fd);

    return 0;
}