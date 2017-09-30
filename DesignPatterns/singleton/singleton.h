/*************************************************************************
	> File Name: singleton.h
	> Author: 
	> Mail: 
	> Created Time: Fri 29 Sep 2017 05:46:34 PM CST
 ************************************************************************/

#ifndef _SIGLETON_H
#define _SIGLETON_H

#include <string.h>

class Singleton {
    static Singleton* instance;
public:
    static Singleton* CreateInstance();
private:
    Singleton() = default;
};

Singleton* Singleton::instance = NULL;

#endif
