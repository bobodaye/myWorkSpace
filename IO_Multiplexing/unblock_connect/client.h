/*************************************************************************
	> File Name: client.h
	> Author: 
	> Mail: 
	> Created Time: Thu 04 May 2017 09:46:35 AM CST
 ************************************************************************/

#ifndef _CLIENT_H
#define _CLIENT_H

#define BUFFER_SIZE 1024

int setnonblocking(int fd);
int unblock_connect(const char* ip, int port, int time);

#endif
