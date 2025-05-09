/*select server*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT 5100

int main(int argc, char **argv){

    int ssock;
    socklen_t clen;
    int n;
    struct sockaddr_in servaddr, cliaddr;
    char mesg[BUFSIZ];
    fd_set readfd;
    int maxfd, client_index, start_index;
    int client_fd[5] = {0, }; 

     /* 서버 소켓 디스크립터 연다. */
    if((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);

    if(bind(ssock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind()");
        return -1;
    }

    if(listen(ssock, 8) < 0) { //클라이언트 접속 대기 최대 8개
        perror("listen()");
        return -1;
    }

    FD_ZERO(&readfd);
    maxfd = ssock;
    client_index = 0;

    do{
        FD_SET(ssock, &readfd);
         for(start_index = 0; start_index < client_index; start_index++) {
            FD_SET(client_fd[start_index], &readfd);
            if(client_fd[start_index] > maxfd)
                maxfd = client_fd[start_index]; 	/* 가장 큰 소켓의 번호를 저장 */
        }
        maxfd++; //순회 하면서 setup 해주기(폴링을 위하여)

        /* select( ) 함수에서 읽기가 가능한 부분만 조사 */
        select(maxfd, &readfd, NULL, NULL, NULL); 	/* 읽기가 가능해질 때까지 블로킹 */
        if(FD_ISSET(ssock, &readfd)) { 			/* 읽기가 가능한 소켓이 서버 소켓인 경우 */
            clen = sizeof(struct sockaddr_in);		/* 클라이언트의 요청 받아들이기 */
            int csock = accept(ssock, (struct sockaddr*)&cliaddr, &clen); //연결 가능한 클라이언트에 대한 정보 제공
            if(csock < 0) {
                perror("accept()");
                return -1;
            } else {
                /* 네트워크 주소를 문자열로 변경 */
                inet_ntop(AF_INET, &cliaddr.sin_addr, mesg, BUFSIZ);
                printf("Client is connected : %s\n", mesg);

                /* 새로 접속한 클라이언트의 소켓 번호를 fd_set에 추가 */
                FD_SET(csock, &readfd);
                client_fd[client_index] = csock;
                client_index++;
                continue;
            }
            if (client_index == 5) break;
        }

        /* 읽기 가능했던 소켓이 클라이언트였던 경우 */
        for(start_index = 0; start_index < client_index; start_index++) {
            /* for 루프를 이용해서 클라이언트들을 모두 조사 */
            if(FD_ISSET(client_fd[start_index], &readfd)) {
                memset(mesg, 0, sizeof(mesg));

                /* 해당 클라이언트에서 메시지를 읽고 다시 전송(Echo) */
                if((n = read(client_fd[start_index], mesg, sizeof(mesg))) > 0) {
                    printf("Received data : %s", mesg);
                    write(client_fd[start_index], mesg, n);
                    close(client_fd[start_index]); 	/* 클라이언트 소켓을 닫는다. */

                    /* 클라이언트 소켓을 지운다. */
                    FD_CLR(client_fd[start_index], &readfd);
                    client_index--;
                }
            }
        }
    }while(strncmp(mesg, "q", 1));

    close(ssock);

    return 0;
}