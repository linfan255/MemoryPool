#include <stdio.h>
#include "player.h"

void showMenu(char *filename) {
	system("clear");
	printf("\n\n\n\n\n");
	printf("                                  0--exit\n");
	printf("                             1--play/stop\n");
	printf("                                  2--next\n");
	printf("                                  3--prev\n");
	printf("\n");
	printf("                        ==========playing %s===========\n", filename);
}

int main(int argc, char **argv) {
	initList();
	curr = head;

	isPlaying = 0, init = 1;	//标识当前是否正在播放
	for(;;) {
		op = -1;
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
					showMenu(curr->songName);
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
				showMenu(curr->songName);
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
				showMenu(curr->songName);
				Play(curr->songName);
				break;

			case 9:
				printf("pid2 = %d,pid = %d,isPlaying = %d,init = %d\n", pid2, pid, isPlaying, init);
				break;
			default:	break;
		}
		destroy();
	}
	return 0;
}
