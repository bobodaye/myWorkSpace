/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Thu 04 May 2017 11:41:20 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

char msg[1024] = { 0 };

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "usage: %s <port>.\n", argv[0]);
        exit(-1);
    }
    int ret = 0, fd = 0;
    unsigned short port = atoi(argv[1]);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(struct sockaddr_in));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(-1 != fd);

    ret = connect(fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    assert(-1 != ret);

    ret = recv(fd, msg, sizeof(msg), 0);
    if(0 >= ret) {
        printf("connetion closed\n");
        close(fd);
        return -1;
    }
    printf("get %d bytes: %s\n", ret, msg);
    close(fd);
    return 0;
}
