/*************************************************************************
	> File Name: string.c
	> Author: BoLiu
	> Mail: 
	> Created Time: Sat 03 Dec 2016 02:05:50 PM CST
 ************************************************************************/

#include <stdio.h>
#include <assert.h>

/*
 * 作用：获取串str的长度
*/
int strlen(const char *str)
{
    assert(str != NULL);
    int len = 0;

    while(*str++ != '\0')
    {
        ++len;
    }
    return len;
}

/*
 * 前提：strDes指向的内存至少能够容纳(strlen(strDes) + strlen(strSrc) + 1) bytes
 * 作用：将串strSrc连接到串strDes的末尾，函数本身不保证安全（使用不当会内存溢出）
*/
char *strcat(char *strDes, const char *strSrc)
{
    assert((strDes != NULL) && (strSrc != NULL));
    char *address = strDes;

    while(*strDes != '\0')	//strDes指针指向串strDes的末尾
    {
        ++strDes;
    }
    while((*strDes++ = *strSrc++) != '\0') //依次从串strSrc不断拷贝字符到strDes中，
        ;				   //直到到达strSrc串的末尾

    return address;
}

/*
 * 前提：strDes指向的内存至少能够容纳(strlen(strSrc) + 1) bytes
 * 作用：将串strSrc拷贝到strDes指向的内存空间，函数本身不保证安全（使用不当会内存溢出）
*/
char *strcpy(char *strDes, const char *strSrc)
{
    assert((strDes != NULL) && (strSrc != NULL));
    char *address = strDes;

    while((*strDes++ =*strSrc++) != '\0')
        ;
    return address;
}

/*
 * 作用：按字典序比较串s和串t的大小
*/
int strcmp(const char *s, const char *t)
{
    assert(s != NULL && t != NULL);

    while(*s && *t && *s == *t)
    {
        s++;
        t++;
    }
    return (*s - *t);
}

/*
 * 前提：strDes指向的内存至少能够容纳(strlen(strDes) + count + 1) bytes
 * 作用：将串strSrc的前count个字符连接到串strDes的末尾，函数本身不保证安全（使用不当会内存溢出）
*/
char *strncat(char *strDes, const char *strSrc, int count)
{
    assert((strDes != NULL) && (strSrc != NULL));
    char *address = strDes;

    while(*strDes != '\0')
    {
        ++strDes;
    }
    while(count-- && *strSrc != '\0')
    {
        *strDes++ = *strSrc++;
    }
    *strDes = '\0';
    return address;
}

/*
 * 前提：strDes指向的内存至少能够容纳(count + 1) bytes
 * 作用：将串strSrc的前count个字符拷贝到strDes指向的内存空间，函数本身不保证安全（使用不当会内存溢出）
*/
char *strncpy(char *strDes, const char *strSrc, int count)
{
    assert((strDes != NULL) && (strSrc != NULL));

    char *address = strDes;

    while(count-- && *strSrc != '\0')
    {
        *strDes++ = *strSrc++;
    }
    return address;
}

/*
 * 作用：按字典序比较串s和串t的前count个字符的大小
*/
int strncmp(const char *s, const char *t, int count)
{
    assert(s != NULL && t != NULL);
    while(*s && *t && *s == *t && count--)
    {
        ++s;
        ++t;
    }
    return (*s - *t);
}

/*
 * 前提：dest指向的内存能够容纳count bytes
 * 作用：将src所指向内存的count bytes拷贝到的dest指向的内存
*/
void *memcpy(void *dest, const void *src, int count)
{
    assert((dest != NULL) && (src != NULL));

    void *address = dest;
    while(count--)
    {
        *(char *)dest = *(char *)src;
        dest = (char *)dest + 1;
        src = (char *)src + 1;
    }
    return address;
}

/*
 * 逻辑如下：
 * 1）将src指向内存的count个字节拷贝到的dest指向的内存中
 * 2）如遇到字符c，则在该次拷贝后停止拷贝，函数返回dest中，该字符c下一字符的地址，如果没有遇
 *    到字符c，则返回NULL
*/
void *memccpy(void *dest, const void *src, int c, unsigned int count)
{
    assert((dest != NULL) && (src != NULL));

    while(count--)
    {
        *(char *)dest = *(char *)src;
        if(*(char *)src == (char)c)
        {
            return ((char *)dest + 1);
        }
        dest = (char *)dest + 1;
        src = (char *)src + 1;
    }
    return NULL;
}

/*
 * 作用：计算字符c在buf中第一次出现的位置（地址），然后返回该地址
*/
void *memchr(const void *buf, int c, int count)
{
    assert(buf != NULL);
    while(count--)
    {
        if(*(char *)buf == (char)c)
        {
            return (void *)buf;
        }
        buf = (char *)buf + 1;
    }
    return NULL;
}

/*
 * 作用：比较s指向的内存中每一字节和t指向内存的count bytes
*/
int memcmp(const void *s, const void *t, int count)
{
    assert((s != NULL) && (t != NULL));
    while(*(char *)s && *(char *)t && *(char *)s == *(char *)t && count--);
    {
        s = (char *)s + 1;
        t = (char *)t + 1;
    }
    return (*(char *)s - *(char *)t);
}

/*
 * 作用：将str的前count个字节置为字符c
*/
void *memset(void *str, int c, int count)
{
    assert(str != NULL);
    void *s = str;

    while(count--)
    {
        *(char *)s = (char)c;
        s = (char *)s + 1;
    }
    return str;
}

/*
 *  作用：将src所指向内存的count bytes拷贝到的dest指向的内存(解决了memcpy未解决的内存重叠问题)
*/
void *memmove(void *dest, const void *src, int count)
{
    assert(dest != NULL && src != NULL);
    void *address = dest;

    // 逻辑：
    // 1）在src小于dest前提下，然后判断src+count指向的内存是否与dest指向的内存重叠
    // 2) 如果重叠则从src+count开始复制，复制到dest+count，从后往前拷贝count字节
    if(src < dest && src + count > dest)
    {
        dest = (char *)dest + count - 1;
        src = (char *)src + count - 1;
        while(count--)
        {
            *(char*)dest = *(char *)src;
            dest = (char *)dest - 1;
            src = (char *)src - 1;
        }
    }
    else
    {
        while(count--)
        {
            *(char *)dest = *(char *)src;
            dest = (char *)dest + 1;
            src = (const char *)src + 1;
        }
    }
    return address;
}
