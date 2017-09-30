/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Thu 04 May 2017 07:48:49 PM CST
 ************************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
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

    ret = bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    assert(-1 != ret);

    ret = listen(listenfd, 5);
    assert(-1 != ret);

    struct sockaddr_in client_address;
    socklen_t client_addrlen = sizeof(client_address);

    int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlen);
    if(connfd < 0) {
        printf("errno is: %d\n", errno);
    }
    else {
        int pipefd[2];
        ret = pipe(pipefd);
        assert(-1 != ret);
        ret = splice(connfd, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE);
        assert(-1 != ret);
        ret = splice(pipefd[0], NULL, connfd, NULL, 32768, SPLICE_F_MORE);
        assert(-1 != ret);
        close(connfd); 
    }
    close(listenfd);
    return 0;
}
