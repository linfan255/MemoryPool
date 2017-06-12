#include <stdio.h>
#include "player.h"

int main(int argc, char **argv) {
	initList();
	int op;
	curr = head;

	int isPlaying = 0, init = 1;	//标识当前是否正在播放
	for(;;) {
		scanf("%d", &op);

		switch(op) {
			case 0:
				if(isPlaying)
				  kill(pid, SIGKILL);
				isPlaying = 0;
				return 0;

			case 1:
				if(init) {
					isPlaying = 1;
					init = 0;
					Play(curr->songName);
				}
				else {
					if(isPlaying) {
						isPlaying = 0;
						kill(pid, SIGSTOP);
					}
					else {
						isPlaying = 1;
						kill(pid, SIGCONT);	
					}
				}
				break;

			case 2:
				if(isPlaying) {
					kill(pid, SIGKILL);
					isPlaying = 0;
				}
			
				isPlaying = 1;
				curr = curr->next;
				if(curr == NULL)	curr = head;
				printf("playing %s\n", curr->songName);
				Play(curr->songName);
				break;

			case 3:
				if(isPlaying) {
					kill(pid, SIGKILL);
					isPlaying = 0;
				}
				
				isPlaying = 1;
				curr = curr->prev;
				if(curr == NULL)	curr = tail;
				printf("playing %s\n", curr->songName);
				Play(curr->songName);
				break;

			case 9:
				printf("pid2 = %d,pid = %d,isPlaying = %d,init = %d\n", pid2, pid, isPlaying, init);
				break;
			default:	break;
		}
	}
	return 0;
}
