#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd1,fd2;
	char c;

	fd1 = open("footbar.txt",O_RDONLY,0);
	fd2 = open("footbar.txt",O_RDONLY,0);

	read(fd2, &c, 1); //读取一个字符

	dup2(fd2,fd1);  //fd1复制了fd2的描述符表项,fd1,fd2拥有同一个文件位置

	read(fd1, &c, 1);  //继续读取一个字符

	printf("c=%c\n", c); //0

	exit(0);
}
