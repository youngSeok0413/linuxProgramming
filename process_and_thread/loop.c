#include <stdio.h>
#include <unistd.h>

int main(){

    for(int i = 0; ; i++){
        printf("%d\r\n", i);
        fflush(NULL);
        sleep(i);
    }

    return 0;
}