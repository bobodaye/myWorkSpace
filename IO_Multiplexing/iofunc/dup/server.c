/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Thu 04 May 2017 09:16:49 AM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    if(argc != 2){
        fprintf(stderr, "usage: %s <port>.\n", argv[0]);
        exit(-1);                    
    }
    int ret = 0;
    socklen_t addrlen = 0;
    unsigned short port = atoi(argv[1]);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(-1 != listenfd);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
                                    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    ret = bind(listenfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    assert(-1 != ret);

    ret = listen(listenfd, 5);
    assert(-1 != ret);

    struct sockaddr_in client_addr;
    socklen_t client_addrlen = sizeof(client_addr);

    int connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_addrlen);
    if(connfd < 0) {
        printf("errno is %d\n", errno);
    }
    else {
        close(STDOUT_FILENO);
        dup(connfd);
        printf("abcd\n");
        close(connfd);
    }
    close(listenfd);
    return 0;
}
