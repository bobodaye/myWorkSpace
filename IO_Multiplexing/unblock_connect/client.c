/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Thu 04 May 2017 09:52:20 AM CST
 ************************************************************************/

#include <stdio.h>
#include "client.h"
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>


int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = O_NONBLOCK | old_option;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

/*
 * 超时连接函数
 * 函数成功时返回已经处于连接状态的socket，失败返回-1
 */
int unblock_connect(const char* ip, int port, int time)
{
    int ret = 0;
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_addr.sin_addr);
    server_addr.sin_port = htons(port);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int fdopt = setnonblocking(sockfd);
    ret = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(0 == ret) {
        /*如果连接成功，则恢复sockfd的属性，并立即返回之*/
        printf("connect with server immediately\n");
        fcntl(sockfd, F_SETFL, fdopt);
        return sockfd;
    }
    else if(errno != EINPROGRESS) {
        /*如果连接没有立即建立，那么只有当errno是EINPROGRRESS时才表示连接还在进行，否则出错返回*/
        printf("unblock connect not support\n");
        return -1;
    }
    fd_set writefds;
    struct timeval timeout;

    FD_ZERO(&writefds);
    FD_SET(sockfd, &writefds);

    timeout.tv_sec = time;
    timeout.tv_usec = 0;

    ret = select(sockfd + 1, NULL, &writefds, NULL, &timeout);
    if(ret <= 0) {
        /*select超时或出错，立即返回*/
        printf("connection time out\n");
        close(sockfd);
        return -1;
    }
    if(!FD_ISSET(sockfd, &writefds)) {
        printf("no events on sockfd found\n");
        close(sockfd);
        return -1;
    }
    int error = 0;
    socklen_t length = sizeof(error);
    /*调用getsockopt来获取并清除sockfd上的错误*/
    if(getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &length) < 0) {
        printf("get socket option failed\n");
        close(sockfd);
        return -1;
    }
    /*错误号不为0表示连接出错*/
    if(0 != error) {
        printf("connection failed after select with the error: %d\n", error);
        close(sockfd);
        return -1;
    }
    /*连接成功*/
    printf("connection ready after select with the socket: %d\n", sockfd);
    fcntl(sockfd, F_SETFL, fdopt);
    return sockfd;
}

int main(int argc, char* argv[])
{
    if(argc <= 2)
    {
        printf("usage: %s ip_address port_number\n", argv[0]);
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    int sockfd = unblock_connect(ip, port, 10);
    if(sockfd < 0) {
        return 1;
    }
    close(sockfd);
    return 0;
}
