/*************************************************************************
	> File Name: server.h
	> Author: 
	> Mail: 
	> Created Time: Fri 05 May 2017 07:08:52 PM CST
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

#define USER_LIMIT 5
#define BUFFER_SIZE 64
#define FD_LIMIT 65535

struct client_data {
    struct sockaddr_in address;
    char* write_buf;
    char buf[BUFFER_SIZE];
};

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = O_NONBLOCK | old_option;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

#endif
