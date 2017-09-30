/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Fri 03 Mar 2017 10:17:02 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

char msg[1024] = { 0 };

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "usage: %s <port>.\n", argv[0]);
        exit(-1);
    }
    int ret = 0, fd = 0;
    unsigned short port = atoi(argv[1]);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(struct sockaddr_in));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(-1 != fd);

    ret = connect(fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    assert(-1 != ret);

    int bytes = 0;
    while(scanf("%s", msg) && (bytes = strlen(msg)) > 0)
    {
        if(0 == strcmp("quit", msg)){
            exit(0);
        }
        send(fd, msg, bytes, 0);

        memset(msg, 0, sizeof(msg));
    }
    close(fd);
    return 0;
}
