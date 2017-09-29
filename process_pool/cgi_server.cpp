/*************************************************************************
	> File Name: cgi_server.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 23 Sep 2017 01:00:44 PM CST
 ************************************************************************/

#include <iostream>
#include "process_pool.h"

using namespace std;

class cgi_conn {
public:
    cgi_conn() {}
    ~cgi_conn() {}

    void init(int epollfd, int sockfd, const struct sockaddr_in& client_addr)
    {
        m_epollfd = epollfd;
        m_sockfd = sockfd;
        m_address = client_addr;
        memset(m_buf, '\0', BUFFER_SIZE);
        m_read_idx = 0;
    }

    void process()
    {
        int idx = 0;
        int ret = -1;
        
        while(1)
        {
            idx = m_read_idx;
            ret = recv(m_sockfd, m_buf + idx, BUFFER_SIZE - 1 - idx, 0);
            if(ret < 0)
            {
                if(errno != EAGAIN)
                {
                    removefd(m_epollfd, m_sockfd);
                }
                break;
            }
            else if(0 == ret)
            {
                removefd(m_epollfd, m_sockfd);
                break;
            }
            else
            {
                m_read_idx += ret;
                printf("user content is: %s\n", m_buf);
                for(; idx < m_read_idx; ++idx)
                {
                    if('\n' == m_buf[idx])
                        break;
                }
                if(idx == m_read_idx)
                {
                    printf("continue read\n");
                    continue;
                }
                m_buf[idx] = '\0';

                char* file_name = m_buf;
                printf("file_name is: %s\n", file_name);
                if(-1 == access(file_name, F_OK))
                {
                    perror("access error");
                    removefd(m_epollfd, m_sockfd);
                    break;
                }
                ret = fork();
                if(-1 == ret)
                {
                    removefd(m_epollfd, m_sockfd);
                    break;
                }
                else if(ret > 0)
                {
                    removefd(m_epollfd, m_sockfd);
                    break;
                }
                else
                {
                    close(STDOUT_FILENO);
                    dup(m_sockfd);
                    execl(m_buf, m_buf, (char*)NULL);
                    exit(0);
                }
            }
        }
    }
private:
    static const int BUFFER_SIZE = 1024;
    static int m_epollfd;
    int m_sockfd;
    struct sockaddr_in m_address;
    char m_buf[BUFFER_SIZE];
    int m_read_idx;
};

int cgi_conn::m_epollfd = -1;

int main(int argc, char* argv[])
{
    if(argc <= 2)
    {
        printf("usage: %s ip_address port_number\n", argv[0]);
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
    assert(-1 != ret);
    ret = listen(listenfd, 5);
    assert(-1 != ret);

    processpool<cgi_conn>* pool = processpool<cgi_conn>::create(listenfd);
    if(pool)
    {
        pool->run();
        delete pool;
    }
    close(listenfd);
    return 0;
}
