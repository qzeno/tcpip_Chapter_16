/*********************************
    > File Name: sep_serv2.c
    > Author: Zeno
    > Mail:340562424@qq.com 
    > Created Time: 2015年09月27日 星期日 13时46分40秒
 ********************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	FILE *readfp;
	FILE *writefp;

	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	char buf[BUF_SIZE] = {0};
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
	listen(serv_sock, 5);
	clnt_adr_sz = sizeof(clnt_adr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

	readfp = fdopen(clnt_sock, "r");
	writefp = fdopen(dup(clnt_sock), "w");//dup()函数赋值文件描述符

	fputs("FROM SERVER: Hi!\n", writefp);
	fputs("I love U\n", writefp);
	fputs("You are awesome\n", writefp);
	fflush(writefp);
	
	shutdown(fileno(writefp), SHUT_WR);//更改处

	fclose(writefp);
	fgets(buf, sizeof(buf), readfp);
	fputs(buf, stdout);
	fclose(readfp);
	return  0;
}

