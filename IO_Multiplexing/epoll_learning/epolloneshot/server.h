/*************************************************************************
	> File Name: server.h
	> Author: 
	> Mail: 
	> Created Time: Sat 29 Apr 2017 04:35:26 PM CST
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

#define MAX_EVENT_SIZE 1024
#define BUFFER_SIZE 1024
typedef int bool;
#define TRUE 1
#define FALSE 0

typedef struct fds {
    int epollfd;
    int sockfd;
}fds;

int setnonblocking(int fd);
void addfd(int epollfd, int fd, bool oneshot);
void reset_oneshot(int epollfd, int fd);
void* worker(void* arg);

#endif
