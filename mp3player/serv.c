#include "unp.h"
#include <string.h>

void solveReq(int sockfd);

int main(int argc, char **argv) {
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);

	for(;;) {
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
		if((childpid = Fork()) == 0) {
			Close(listenfd);
			solveReq(connfd);
			exit(0);
		}
		Close(connfd);
	}
}

void solveReq(int sockfd) {
	ssize_t n;
	char buf[2048];

	if(recv(sockfd, buf, 2048, 0) < 0)
	  perror("serv recv error");
	sscanf(buf, "%s\n", buf);

	char songName[50] = "./servsong/";
	strcat(songName, buf);
	printf("client require song:%s\n", songName);

	int fd;
	if((fd = open(songName, O_RDONLY)) < 0)
	  perror("srv open error");

	while((n = read(fd, buf, 2048)) > 0)
	  if(send(sockfd, buf, n, 0) != n)
		perror("serv write error");

	if(n < 0)
	  perror("serv read error");
	exit(0);
}
