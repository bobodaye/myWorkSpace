 #include <time.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <signal.h>
 #include <unistd.h>
 #include <sys/select.h>

 #define BUFFSIZE 80

 void sig_int(int signo);
 void err_sys(const char *p_error);

 void sig_alrm(int signo)
 {
     char s[] ="ALARM received";
     psignal(signo, s);
     return;
 }

int main(int argc, char **argv)
{
    int            maxfdp1;
    fd_set         rset;
    sigset_t       sigmask;
    ssize_t        nread;
    char           buf[BUFFSIZE];
    sigset_t zeromask;
    sigset_t sigset;
    signal(SIGALRM, sig_alrm);
    signal(SIGINT, sig_int);
     //initialize signal set and addition SIGALRM into sigset
    if(sigemptyset(&sigset) == -1)
        err_sys("sigemptyet");
    if(sigaddset(&sigset, SIGINT) == -1)
        err_sys("sigaddset");
    if(sigemptyset(&zeromask) == -1)
        err_sys("sigemptyset");
#if 1
    //if(sigprocmask(SIG_BLOCK, &sigset, NULL) == -1)
    //    err_sys("sigemptyset");
    if(sigaddset(&sigset, SIGALRM) == -1)
        err_sys("sigaddset");
    //sigprocmask(SIG_UNBLOCK, &sigset, NULL);
#endif
    alarm(1);
    //sleep(3);
    FD_ZERO(&rset);
    FD_SET(STDIN_FILENO, &rset);
    maxfdp1 = STDIN_FILENO + 1;
    if (pselect(maxfdp1, &rset, NULL, NULL, NULL, &sigset) <= 0)
    // if (select(maxfdp1, &rset, NULL, NULL, NULL) <= 0)
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

void err_sys(const char *p_error)
{
    perror(p_error);
    exit(1);
}
