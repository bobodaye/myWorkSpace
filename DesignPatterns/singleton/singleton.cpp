/*************************************************************************
	> File Name: singleton.cpp
	> Author: BoLiu
	> Mail: 
	> Created Time: Fri 29 Sep 2017 05:50:36 PM CST
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "singleton.h"

using namespace std;

#define THREAD_NUM 4

pthread_t tid[THREAD_NUM];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void thread_wait();
void* worker(void*);
void err_quit(int err, const char* s);

Singleton* Singleton::CreateInstance()
{
    if(NULL == instance)
    {
        pthread_mutex_lock(&lock);
        if(NULL == instance)
            instance = new Singleton;
        pthread_mutex_unlock(&lock);
    }
    return instance;
}

int main()
{
    int err;

    for(int i = 0; i < THREAD_NUM; ++i)
    {
        err = pthread_create(&tid[i], NULL, worker, NULL);
        if(0 != err)
            err_quit(err, "thread create error");
    }
    thread_wait();
    cout << "main thread finish\n";
    return 0;
}

void* worker(void* /*arg*/)
{
    Singleton* instance = NULL;
    instance = Singleton::CreateInstance();
    printf("%0x\n", (unsigned int)instance);
    pthread_exit(NULL);
}

void thread_wait()
{
    int err;
    for(int i = 0; i < THREAD_NUM; ++i)
    {
        err = pthread_join(tid[i], NULL);
        if(0 != err)
            err_quit(err, "thread join error");
    }
}

void err_quit(int err, const char* s)
{
    fprintf(stderr, "%s %s\n", s, strerror(err));
    exit(1);
}
