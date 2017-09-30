/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Thu 04 May 2017 10:49:14 AM CST
 ************************************************************************/

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
#include <sys/sendfile.h>

/*
 * 用sendfile函数传送文件
 */
int main(int argc, char* argv[])
{
    if(argc <= 2){
        fprintf(stderr, "usage: %s <port> <filename>\n", argv[0]);
        exit(-1);                    
    }
    int ret = 0;
    socklen_t addrlen = 0;
    unsigned short port = atoi(argv[1]);
    const char* filename = argv[2];
    int filefd = open(filename, O_RDONLY);
    assert(-1 != filefd);
    struct stat stat_buf;
    fstat(filefd, &stat_buf);

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

    struct sockaddr_in client_addr;
    socklen_t client_addrlen = sizeof(client_addr);

    int connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_addrlen);
    if(connfd < 0) {
        printf("errno is: %d\n", errno);
    }
    else {
        sendfile(connfd, filefd, NULL, stat_buf.st_size);
        close(connfd);
    }
    close(listenfd);
    return 0;
}
