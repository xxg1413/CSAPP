##第10章 家庭作业

##10.6

    #include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    int main()
    {
        int fd1, fd2;
        fd1 = open("../footbar.txt", O_RDONLY, 0);
        fd2 = open("../foo.txt", O_RDONLY, 0);
        close(fd2);
        fd2 = open("../baz.txt",O_RDONLY,0);
        printf("fd2 = %d\n", fd2); //fd1=3,fd2=4 0,1,2为系统默认
        exit(0);
    }

##10.7

    #include "csapp.h"
    int main()
    {
        int n;
        rio_t rio;
        char buf[MAXLINE];
        rio_readinitb(&rio, STDIN_FILENO);
        whle((n= rio_readn(&rio, buf, MAXBUF)) != 0)
            Rio_writen(STDOUT_FILENO, buf, MAXBUF);
        return 0;
    }

##10.8
根据文件描述符找文件或者fstat函数

    #include <stdio.h>
    #include <unistd.h>
    #include <sys/stat.h>
    int main(int argc,char **argv)
    {
        struct stat stat;
        char *type,*readok;
        fstat(argv[1],&stat);  //fstat接收文件描述符
        if(S_ISREG(stat.st_mode))
            type = "reg";
        else if(S_ISDIR(stat.st_mode))
            type = "dir";
        else 
            type = "other";
        if(stat.st_mode & S_IRUSR)
            readok = "yes";
        else
            readok = "no";
        printf("type:%s,read: %s\n",type,readok);
        return 0;
    }

根据文件描述符找文件，请阅读 [这篇博文](http://daige.me/2014/09/get-the-path-of-a-process/),根据/proc/getpid()/fd，可以readlink到文件名

##10.9
在执行命令时：  

    unix> fstatcheck 3 < foo.txt

shell创建一个子进程，打开foot.txt，把文件内容重定向到标准输入，占用了文件描述
符3,运行完毕之后，父进程再接管输出结果

    if (Fork() == 0) { /* Child */
        /* The Shell may be run these code? */
        fd = Open("foo.txt", O_RDONLY, 0); /打开foo.txt fd=3
        Dup2(fd, STDIN_FILENO); //重定向
        Close(fd); //关闭 fd释放
        Execve("fstatcheck", argv, envp);
    }

##10.10
增加一个可选的参数infile，输出到标准输出，就需要打开文件并把fd重定向到标准输出

    #include "../csapp.h"
    int main(int argc, char **argv)
    {
            int n;
            rio_t rio;
            char buf[MAXLINE];
            if (argc > 2) 
            {
                    fprintf(stderr, "usage: %s [filename]\n", argv[0]);
                    return -1;
            }
            /* 这里将标准输入的文件描述符，重定位到输入文件的描述符 */
            if (argc == 2) 
            {
                    char *filename = argv[1];
                    int fd = Open(filename, O_RDONLY, 0);
                    int ret = dup2(fd, STDIN_FILENO); /* 将标准输入重定位到 fd */
                    if (ret < 0) 
                    {
                            perror("dup2");
                            return -1;
                    }
            }
            /*将标准输入拷贝到标准输出 */
            Rio_readinitb(&rio, STDIN_FILENO);
            while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
                    Rio_writen(STDOUT_FILENO, buf, n);
            return 0;
    }


