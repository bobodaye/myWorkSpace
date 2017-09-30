/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Fri 05 May 2017 07:08:10 PM CST
 ************************************************************************/

#define _GNU_SOURCE 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>
#include "server.h"

int main(int argc, char* argv[])
{
    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(-1);                    
    }
    int i = 0;
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

    struct client_data* users = (struct client_data*)malloc(sizeof(struct client_data) * FD_LIMIT);
    struct pollfd fds[USER_LIMIT + 1];
    int user_counter = 0;
    for(i = 1; i < USER_LIMIT + 1; i++)
    {
        fds[i].fd = -1;
        fds[i].events = 0;
    }
    fds[0].fd = listenfd;
    fds[0].events = POLLIN | POLLERR;
    fds[0].revents = 0;

    while(1)
    {
        ret = poll(fds, user_counter + 1, -1);
        if(ret < 0) {
            printf("poll failure\n");
            break;
        }
        for(i = 0; i < user_counter + 1; i++)
        {
            if((fds[i].fd == listenfd) && (fds[i].revents & POLLIN)) {
                struct sockaddr_in client_address;
                socklen_t client_addrlen = sizeof(client_address);
                int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlen);
                if(connfd < 0) {
                    printf("errno is: %d\n", errno);
                    continue;
                }
                /*如果请求太多，则关闭新到的连接*/
                if(user_counter >= USER_LIMIT) {
                    const char* info = "too many users\n";
                    printf("%s\n", info);
                    send(connfd, info, strlen(info), 0);
                    close(connfd);
                    continue;
                }
                user_counter++;
                users[connfd].address = client_address;
                setnonblocking(connfd);
                fds[user_counter].fd = connfd;
                fds[user_counter].events = POLLIN | POLLERR | POLLRDHUP;
                fds[user_counter].revents = 0;
                printf("comes a new user, now have %d users\n", user_counter);
            }
            else if(fds[i].revents & POLLERR) {
               printf("get an error form %d\n", fds[i].fd);
               char errors[100];
               memset(errors, '\0', 100);
               socklen_t length = sizeof(errors);
               if(getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, &errors, &length) < 0) {
                   printf("get socket option failed\n");
               }
               continue;
            }
            else if(fds[i].revents & POLLRDHUP) {
                /*如果客户端关闭连接，则服务器也关闭对应的连接，并将用户总数减1*/
                users[fds[i].fd] = users[fds[user_counter].fd];
                close(fds[i].fd);
                fds[i] = fds[user_counter];
                user_counter--;
                i--;
                printf("a client left\n");
            }
            else if(fds[i].revents & POLLIN) {
                int connfd = fds[i].fd;
                memset(users[connfd].buf, '\0', BUFFER_SIZE);
                ret = recv(connfd, users[connfd].buf, BUFFER_SIZE, 0);
                if(ret < 0) {
                    /*如果读操作出错，则关闭连接*/
                    if(errno != EAGAIN) {
                        close(connfd);
                        users[connfd] = users[fds[user_counter].fd];
                        fds[i] = fds[user_counter];
                        user_counter--;
                        i--;
                    }
                }
                else if(0 == ret) {
                }
                else {
                    users[connfd].buf[ret - 1] = '\0';
                    printf("get %d bytes of client data [%s] from %d\n", ret, users[connfd].buf, connfd);
                    int j = 1;
                    /*如果接受到客户端数据，则通知其他socket连接准备写数据*/
                    for(; j <= user_counter; j++)
                    {
                        if(connfd == fds[j].fd)
                            continue;
                        fds[j].events |= ~POLLIN; //注销当前fd上的读写事件？
                        fds[j].events |= POLLOUT;
                        ///fds[j].events = (fds[j].events & ~POLLIN);
                        users[fds[j].fd].write_buf = users[connfd].buf;
                    }
                }
            }
            else if(fds[i].revents & POLLOUT) {
                int connfd = fds[i].fd;
                if(NULL == users[connfd].write_buf)
                    continue;
                send(connfd, users[connfd].write_buf, strlen(users[connfd].write_buf), 0);
                users[connfd].write_buf = NULL;
                //fds[i].events = (fds[i].events & ~POLLOUT);
                fds[i].events |= ~POLLOUT;
                fds[i].events |= POLLIN;
            }
        }
    }
    free(users);
    close(listenfd);
    return 0;
}

