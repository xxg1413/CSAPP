ssize_t  rio_readn(int fd, void *usrbuf, size_t n)
{
	size_t nleft = n; 
	ssize_t nread;

	char *bufp = usrbuf;

	while(nleft > 0)
	{
		if(nread = read(fd,bufp,nleft) < 0) //每次读取剩下的字节
		{
			if( errno == EINTR) //被信号中断
				nread = 0; //归零
			else
				return -1;
		}
		else if( nread == 0) //遇到EOF 跳出循环
				break;

		nleft -= nread;
		bufp += nread;
	}

	return (n - nleft);  
}

ssize_t rio_writen(int fd, void *usrbuf,size_t n)
{
	size_t nleft = n;
	ssize_t nwritten;
	char *bufp = usrbuf;

	while(nleft > 0)
	{
		if(nwritten = write(fd,bufp,nleft) < 0)
		{
			if(errno == EINTR)
				nwritten = 0;
			else
				return -1;
		}

		nleft -= nwritten;
		bufp += nwritten;
	}

	return n;
}


void rio_readinitb(rio_t *rp, int fd)
{
	rp->rio_fd = fd;
	rp->rio_cnt = 0;
	rp->rio_bufptr = rp->rio_buf;
}

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
	int cnt;

	while(rp->rio_cnt <= 0) //buf为空
	{
		rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));

		if( rp->rio_cnt < 0)
		{
			if( errno != EINTR)
				return -1;
		}
		else if( rp->rio_cnt == 0)  //EOF 结尾
			return 0;
		else
			rp->rio_bufptr = rp->rio_buf;
	}


	cnt = n;
	if( rp->rio_cnt < n)
	{
		cnt =rp->rio_cnt;
	}

	memcpy(usrbuf, rp->rio_bufptr,cnt);
	rp->rio_bufptr += cnt;
	rp->rio_cnt -= cnt;

	return cnt;
}

ssize_t rio_readinitb(rio_t *rp,void *usrbuf,size_t maxlen)
{
	int n,rc;
	char c,*bufp = usrbuf;

	for(n=1; n < maxlen; n++)
	{
		if((rc = rio_read(rp,&c,1)) == 1)
		{
			*bufp++ = c;
			if( c == '\n')
				break;
		}
		else if( rc == 0)
		{
			if( n == 1)
				return 0;
			else
				break;
		}
		else
			return -1;
	}
	*bufp = 0;

	return 0;
}