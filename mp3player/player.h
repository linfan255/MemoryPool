#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "list.h"

pid_t pid, pid2;

//madplay -q -o wav:- songsName | aplay
void play(char *filename) {
	char songsName[35] = "./songs/";
	strcat(songsName, filename);

	int pfd[2];
	if(pipe(pfd) == -1)
	  perror("pipe");

	pid2 = fork();
	if(pid2 < 0)
	  perror("fork");

	if(pid2 == 0) {
		close(pfd[0]);
		dup2(pfd[1], 1);
		execlp("madplay", "madplay", "-q", "-o", "wav:-", songsName, NULL);
	}
	else {
		close(pfd[1]);
		dup2(pfd[0], 0);
		execlp("aplay", "aplay", NULL);
	}
}

static void sig_child() {
	pid_t pid;
	while((pid = waitpid(-1, NULL, WNOHANG)) > 0)
	  printf("clear child %d\n", pid);
}

void Play(char *filename) {
	signal(SIGCHLD, sig_child);
	pid = fork();
	if(pid == 0) {
		play(filename);
	}
}

void initList() {
	system("ls ./songs > songlist");
	FILE *fp = fopen("songlist", "r");
	
	char buf[1024];
	while(fgets(buf, 1024, fp) != NULL) {
		sscanf(buf, "%s\n", buf);		//去掉'\n'
		insert(buf);
	}
//	print();
	fclose(fp);
}


#endif
