/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Sun 30 Apr 2017 10:05:02 AM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "server.h"

/*
 * 修改文件描述符为非阻塞
 */
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

/*
 * 将fd上的EPOLLIN和EPOLLET事件注册到epollfd指示的epoll内核事件表中
 * 参数oneshot指定是否注册fd上的EPOLLONESHOT事件
 */
void addfd(int epollfd, int fd, bool oneshot)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if(oneshot) {
        event.events |= EPOLLONESHOT;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

/*重置fd上的事件，这样操作之后，尽管fd上的EPOLLONESHOT事件被注册
 * 但是OS仍然会触发fd上的EPOLLIN事件，且只触发一次
 */
void reset_oneshot(int epollfd, int fd)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

/*工作线程*/
void* worker(void* arg)
{
    int sockfd = ((fds*)arg)->sockfd;
    int epollfd = ((fds*)arg)->epollfd;
    printf("start new thread to receive data on fd: %d\n", sockfd);
    char buf[BUFFER_SIZE];
    /*循环读取sockfd上的数据，直到遇到EAGAIN错误*/
    while(1)
    {
        memset(buf, '\0', BUFFER_SIZE);
        int ret = recv(sockfd, buf, BUFFER_SIZE, 0);
        if(0 == ret) {
            close(sockfd);
            printf("Message: client closed the connection\n");
            break;
        }
        else if(ret < 0) {
            if(EAGAIN == errno) {
                reset_oneshot(epollfd, sockfd);
                printf("read later\n");
                break;
            }
        }
        else {
            printf("get content: %s\n", buf);
            /*休眠3秒，模拟数据处理过程*/
            sleep(3);
        }
    }
    printf("end thread receiving data on fd: %d\n", sockfd);
    pthread_exit(NULL);
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
    /*
     * 注意，监听socket listenfd上是不能注册EPOLLONESHOT事件的
     * 否则，应用程序只能处理一个客户连接
     * 因为后续的客户连接请求将不再触发listenfd上的EPOLLIN事件
     */
    addfd(epollfd, listenfd, FALSE);
    while(1)
    {
        int ret = epoll_wait(epollfd, events, MAX_EVENT_SIZE, -1);
        if(ret < 0) {
            printf("epoll failure\n");
            break;
        }
        for(int i = 0; i < ret; i++)
        {
            int sockfd = events[i].data.fd;
            if(listenfd == sockfd) {
                struct sockaddr_in client_address;
                socklen_t client_addrlen = sizeof(client_address);
                int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlen);
                /*对每个非监听文件描述符都注册EPOLLONESHOT事件*/
                addfd(epollfd, connfd, TRUE);
            }
            else if(events[i].events & EPOLLIN) {
                pthread_t thread;
                fds new_worker;
                new_worker.sockfd = sockfd;
                new_worker.epollfd = epollfd;
                /*启动一个工作线程为sockfd服务*/
                pthread_create(&thread, NULL, worker, (void*)&new_worker);
            }
            else {
                printf("something else happened\n");
            }
        }
    }
    close(listenfd);
    return 0;
}
