#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

static int g_var = 1;
char str[] = "PID";

int main(){

    int var = 92;
    pid_t pid;

    if((pid = fork()) < 0){
        perror("[ERROR] : fork()");
        return -1;
    }
    else if(pid == 0){
        //child process
        g_var++;
        var++;
        printf("Parent %s from Child process(%d), %d\r\n", str, getpid(), getppid());
    }
    else{
        //parent process
        printf("Child %s from Parent process(%d), %d\r\n", str, getpid(), pid);
    }

    printf("pid=%d, Global var = %d, var =%d\r\n", getpid(), g_var, var);

    return 0;
}