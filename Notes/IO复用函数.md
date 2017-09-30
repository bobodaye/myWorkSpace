# IO复用函数

## 1.pselect函数

### 1.函数原型

```c
#include <sys/select.h>
#include <signal.h>
#include <time.h>
int pselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, 
            const struct timespec *timeout, const sigset_t *sigmask);
返回；若有就绪描述符则为其数目，若超时则为0，若出错则为-1.
```
### 2.相对于select函数的变化

1. pselect使用timespec结构，而不使用timeval结构

```c
struct timespec {							struct timeval {
    time_t tv_sec;	//秒						   long tv_sec;	//秒
	long tv_nsec;	//纳秒					  long tv_usec;   //微秒				   
};										   };
```

2. pselect函数增加了第六个参数，一个指向信号掩码的指针。

   下面我们具体分析第六个参数的作用，分析之前先介绍几款要用到的API。

   ```c
    #include <signal.h>
    int sigemptyset(sigset_t *set);	//将信号集set清空
    int sigaddset(sigset_t *set, int signum);	//将信号signum添加到集合set中，linux中信号即整数
    int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
   ```

   1. sigprocmask函数的作用是**获取**或者**改变**调用它的线程的**信号掩码**。

   2. 它的行为取决于参数`how`，如下：

      1.`SIG_BLOCK` ，将当前集合`set`中的信号设置为**阻塞**。

      2.`SIG_UNBLOCK` ，对当前集合`set`中的阻塞信号设置为**非阻塞**。

      3.`SIG_SETMASK` ，作用同1。

   3. 如果参数`oldset`非NULL，原来信号掩码的值被存放在`oldset`中。

   4. 小结：

      ```c
      1.ready = pselect(nfds, &readfds, &writefds, &exceptfds, timeout, &sigmask);
      2.//等价于自动执行以下的调用
      3.sigset_t origmask;
      4.
      5.sigprocmask(SIG_SETMASK, &sigmask, &origmask);
      6.ready = select(nfds, &readfds, &writefds, &exceptfds, timeout);
      7.sigprocmask(SIG_SETMASK, &origmask, NULL);
      ```

      **注意：**

      这里讲解有个前提，即信号已经通过`signal`或者`sigaction`函数与信号处理函数绑定。

      1. 第一行中如果`sigmask`中没有添加信号，则pselect不会屏蔽任何信号，即如果当pselect函数阻塞时，如果用户假设`CTRL+C` 发送`SIGINT`信号，那么就会执行对应信号处理函数，当信号处理函数返回时pselect函数返回会发生`EINTER`错误。

      2. 第一行中如果`sigmask`添加了信号（**非阻塞**），那么同上用户发送信号`SIGINT`，对应的信号处理函数不会执行，因为pselect会屏蔽参数`sigmask`中的信号。

         **分析：**因为上面已经说明过<u>等价调用</u>，第一步`sigmask`中信号被设置为阻塞（如果`sigmask`中没有添加信号，就不屏蔽任何信号），原来的信号被保存到`origmask`中，`origmask`中其实没有添加信号，就是一个空的信号集，**因为信号被设置了阻塞，所以你发送sigmask中的信号不会有任何响应**，第6行，所以就会阻塞在select函数上，直到监听文件描述符上有事件发生，第7行，再将进程信号设置为`origmask`，即不屏蔽任何信号，如果之前产生过`sigmask`中的信号，那么依次调用对应信号处理函数。

   5. 代码实践

   ```c
    #include <stdio.h> 
    #include <time.h>
    #include <stdlib.h>
    #include <signal.h>
    #include <unistd.h>
    #include <sys/select.h>

    #define BUFFSIZE 80

    void sig_int(int signo);	//SIGINT信号处理函数
    void sig_alrm(int signo);	//SIGALRM信号处理函数
    void err_sys(const char *p_error);	//错误处理

   int main(int argc, char **argv)
   {
       int            maxfd;
       fd_set         rset;
       ssize_t        nread;
       char           buf[BUFFSIZE];
       sigset_t sigset;
       signal(SIGINT, sig_int);	//注册信号函数
       signal(SIGALRM, sig_alrm);	//同上
        //initialize signal set and addition SIGALRM into sigset
       if(sigemptyset(&sigset) == -1)
           err_sys("sigemptyet");
       if(sigaddset(&sigset, SIGALRM) == -1)
           err_sys("sigaddset");
     	if(sigaddset(&sigset, SIGINT) == -1)
           err_sys("sigaddset");
       alarm(1);	//定时1秒发送SIGALRM信号
       FD_ZERO(&rset);
       FD_SET(STDIN_FILENO, &rset);
       maxfd = STDIN_FILENO;	//STDIN_FILENO,标准输入fd = 0
       if (pselect(maxfd + 1, &rset, NULL, NULL, NULL, &sigset) <= 0)
           err_sys("pselect error");
       if (FD_ISSET(STDIN_FILENO, &rset))
       {
       	if ((nread = read(STDIN_FILENO, buf, BUFFSIZE)) == -1)
           	err_sys("read error");
       	if (write(STDOUT_FILENO, buf, nread) != nread)
           	err_sys("write error");
       }
       exit(0);
   }

   void sig_int(int signo)
   {
       char s[] ="INT received";
       psignal(signo, s);
       return;
   }

   void sig_alrm(int signo);
   {
        char s[] ="ALARM received";
        psignal(signo, s);
        return;
   }

   void err_sys(const char *p_error)
   {
       perror(p_error);
       exit(1);
   }
   ```

   说明：这个演示*Demo*效果为无论产生`SIGALRM`信号还是用户终端上发送`SIGINT`信号，pselect函数都不会返回一个`EINTER`错误，当用户终端输入任意字符串回车时，pselect函数返回，`oldmask`中的信号被重新设置，然后产生的信号的信号处理函数会依次执行。

   测试用例：

   ```
   ^Chello
   ALARM received: Alarm clock
   INT received: Interrupt
   hello
   ```


