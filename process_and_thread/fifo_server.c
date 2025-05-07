#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFOFILE "fifo"

int main(){

    int n, fd;
    char buf[BUFSIZ];

    unlink(FIFOFILE); //파일의 디렉터리 엔트리(이름)를 제거

    if(mkfifo(FIFOFILE, 0666)){
        return -1;
    }

    if((fd = open(FIFOFILE, O_RDONLY)) < 0){
        return -1;
    }

    while((n = read(fd, buf, BUFSIZ)) > 0){
        printf("%s", buf);
    }

    close(fd);

    return 0;
}