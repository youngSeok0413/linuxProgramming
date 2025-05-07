#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 100

struct msgbuf {
    long mtype;
    char mtext[MSG_SIZE];
};

int main() {
    key_t key = ftok("msgqueue", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    // 메시지 보내기
    struct msgbuf message;
    message.mtype = 1;
    strcpy(message.mtext, "Hello IPC Message Queue");
    msgsnd(msgid, &message, sizeof(message.mtext), 0);
    printf("Sent: %s\n", message.mtext);

    // 메시지 받기
    msgrcv(msgid, &message, sizeof(message.mtext), 1, 0);
    printf("Received: %s\n", message.mtext);

    // 메시지 큐 삭제
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
