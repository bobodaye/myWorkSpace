/*************************************************************************
	> File Name: server.h
	> Author: 
	> Mail: 
	> Created Time: Sat 29 Apr 2017 10:44:55 AM CST
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

#define MAX_EVENT_SIZE 1024
#define BUFFER_SIZE 10
#define TRUE 1
#define FALSE 0
typedef int bool;


int setnonblocking(int fd);
void addfd(int epollfd, int fd, bool enable_et);
void lt(struct epoll_event* events, int number, int epollfd, int listenfd);
void et(struct epoll_event* events, int number, int epollfd, int listenfd);

#endif
