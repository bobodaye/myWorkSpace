/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Fri 05 May 2017 06:48:57 PM CST
 ************************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>

#define BUFFER_SIZE 64

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "usage: %s <port>.\n", argv[0]);
        exit(-1);
    }
    int ret = 0;
    unsigned short port = atoi(argv[1]);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(struct sockaddr_in));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(-1 != fd);

    ret = connect(fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    if(ret < 0) {
        printf("connection failed!\n");
        close(fd);
        return -1;
    }
    struct pollfd fds[2];
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    fds[1].fd = fd;
    fds[1].events = POLLIN | POLLRDHUP;

    char read_buf[BUFFER_SIZE] = { 0 };
    int pipefd[2];
    ret = pipe(pipefd);
    assert(-1 != ret);

    while(1)
    {
        ret = poll(fds, 2, -1);
        if(ret < 0) {
            printf("poll failure\n");
            break;
        }
        if(fds[1].revents & POLLRDHUP) {
            printf("server close the connection\n");
            break;
        }
        if(fds[1].revents & POLLIN) {
            memset(read_buf, '\0', BUFFER_SIZE);
            ret = recv(fds[1].fd, read_buf, BUFFER_SIZE, 0);
            printf("get %d bytes data: %s\n", ret, read_buf);
        }
        if(fds[0].revents & POLLIN) {
            splice(STDIN_FILENO, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE);
            splice(pipefd[0], NULL, fds[1].fd, NULL, 32768, SPLICE_F_MORE);
        }
    }
    close(fd);
    return 0;
}


