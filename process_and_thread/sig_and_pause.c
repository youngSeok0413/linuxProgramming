#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void sigintHandler(int signum){
    printf("\n[핸들러] SIGINT(%d) 수신\r\n", signum);
}

int main(){

    signal(SIGINT, sigintHandler); //signal에 대한 반응 등록

    printf("프로세스 실행 중 ... Ctrl+C로 SIGINT 발생\r\n");

    while(1){
        pause(); //시그널이 도착할 때까지 현재 프로세스 일시 중단(sleep)
        printf("다시 깨어남!!\r\n");
    }

    return 0;
}