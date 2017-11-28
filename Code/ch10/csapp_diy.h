#define RIO_BUFSIZE 8192

typedef struct 
{
	int rio_fd;
	int rio_cnt;
	char *rio_bufptr;
	char rio_buf[RIO_BUFSIZE];
};

