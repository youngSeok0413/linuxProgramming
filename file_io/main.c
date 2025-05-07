#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

/*simple copy and paste program*/

int main(int argc, int **argv){

    int fd1 = open("./org.txt", O_RDWR|O_APPEND);
    if(fd1 < 0){
        perror(argv[1]);
        return -1;
    }
    int fd2 = open("./cpy.txt", O_RDWR|O_TRUNC);
    if(fd2 < 0){
        perror(argv[1]);
        return -1;
    }

    int n = 0;
    char buf[1024];
    while((n = read(fd1, buf, sizeof(buf))) > 0){
        write(fd2, buf, n);
    }

    return 0;
}