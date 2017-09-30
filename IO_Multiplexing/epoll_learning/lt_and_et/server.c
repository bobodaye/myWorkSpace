/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Sat 29 Apr 2017 10:47:45 AM CST
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
#include "server.h"
/*
 * 将文件描述符设置成非阻塞的
 */
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

/*
 * 将文件描述符fd上的EPOLLIN注册到epollfd指示的内核事件表中
 * 参数enable_fd指定是否对fd启用ET模式
 */
void addfd(int epollfd, int fd, bool enable_et)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if(enable_et) {
        event.events |= EPOLLET;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    //setnonblocking(fd);
}

void lt(struct epoll_event* events, int number, int epollfd, int listenfd)
{
    char buf[BUFFER_SIZE];
    for(int i = 0; i < number; i++)
    {
        int sockfd = events[i].data.fd;
        if(listenfd == sockfd) {
            struct sockaddr_in client_address;
            socklen_t client_addrlen = sizeof(client_address);
            int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlen);
            addfd(epollfd, connfd, FALSE);
        }
        else if(events[i].events & EPOLLIN) {
            /*只要socket读缓存中还有未读出的数据，这段代码就被触发*/
            printf("event trigger once\n");
            memset(buf, '\0', BUFFER_SIZE);
            int ret = recv(sockfd, buf, BUFFER_SIZE, 0);
            if(ret <= 0) {
                close(sockfd);
                continue;
            }
            printf("get %d bytes of content: %s\n", ret, buf);
        }
        else {
            printf("something else happened\n");
        }
    }
}

void et(struct epoll_event* events, int number, int epollfd, int listenfd)
{
    char buf[BUFFER_SIZE];
    for(int i = 0; i < number; i++)
    {
        int sockfd = events[i].data.fd;
        if(listenfd == sockfd) {
            struct sockaddr_in client_address;
            socklen_t client_addrlen = sizeof(client_address);
            int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlen);
            addfd(epollfd, connfd, TRUE); /*对connfd开启ET模式*/
            setnonblocking(connfd);
        }
        else if(events[i].events & EPOLLIN) {
            /*这段代码不会重复触发，所以我们循环读取数据，以确保把socket读缓存所有数据读出*/
            printf("event trigger once\n");
            while(1)
            {
                memset(buf, '\0', BUFFER_SIZE);
                int ret = recv(sockfd, buf, BUFFER_SIZE, 0);
                if(ret < 0) {
                    /*对于非阻塞IO，下面条件成立表示数据已经全部读取完毕，此后，epoll就能再次触发sockfd上的EPOLLIN事件，以驱动下一次读操作*/
                    if((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                        printf("read later\n");
                        break;
                    }
                    close(sockfd);
                    break;
                }
                else if(0 == ret) {
                    close(sockfd);
                }
                else {
                    printf("get %d bytes of content: %s\n", ret, buf);
                }
            }
#if 0
            memset(buf, '\0', BUFFER_SIZE);
            int ret = recv(sockfd, buf, BUFFER_SIZE, 0);
            if(ret <= 0) {
                close(sockfd);
                continue;
            }
            else {
                printf("get %d bytes of content: %s\n", ret, buf);
            }
#endif
        }
        else {
            printf("something else happened\n");
        }
    }
}

int main(int argc, char* argv[])
{
    if(argc != 2){
        fprintf(stderr, "usage: %s <port>.\n", argv[0]);
        exit(-1);                    
    }
    int ret = 0, connfd = 0;
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

    struct epoll_event events[MAX_EVENT_SIZE];
    int epollfd = epoll_create(5);
    assert(-1 != epollfd);
    addfd(epollfd, listenfd, TRUE);

    while(1)
    {
        int ret = epoll_wait(epollfd, events, MAX_EVENT_SIZE, -1);
        if(ret < 0) {
            printf("epoll failure\n");
            break;
        }
        //lt(events, ret, epollfd, listenfd); /*使用LT模式*/
        et(events, ret, epollfd, listenfd); /*使用ET模式*/
        
    }
    close(listenfd);
    return 0;
}
