#ifndef NET_H
#define NET_H

#include "unp.h"
#include "list.h"

void require(FILE *fp, int sockfd) {
	char sendline[2048], recvline[2048], buf[2048];
	
	printf("please input the song you want to get:");
	Fgets(sendline, 2048, fp);	
	sscanf(sendline, "%s\n", sendline);
	insert(sendline);
	
	char path[30] = "./songs/";
	strcat(path, sendline);
	
	if(send(sockfd, sendline, 2048, 0) < 0)
	  perror("client send error");

	int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0666); //发送要下载的歌曲名字
	if(fd < 0)
	  perror("client open error");

	int n;
	while((n = recv(sockfd, buf, 2048, 0)) > 0)
	  if(write(fd, buf, n) != n)
		perror("client write error");

	if(n < 0)
	  perror("client read error");
}

void getSongFromServ() {
	int sockfd;
	struct sockaddr_in servaddr;

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
	require(stdin, sockfd);
}

#endif
