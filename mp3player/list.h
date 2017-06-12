#ifndef LIST_H
#define LIST_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
	char songName[1024];
	struct Node *next;
	struct Node *prev;
} node;

node *head = NULL;
node *tail = NULL;
node *curr = NULL;

void insert(char *filename) {
	if(head == NULL && tail == NULL) {
		head = (node *)malloc(sizeof(node));
		strcpy(head->songName, filename);
		head->prev = NULL;
		head->next = NULL;

		tail = head;
	}	
	else {
		node* tmp = (node*)malloc(sizeof(node));
		strcpy(tmp->songName, filename);
		tmp->prev = tail;
		tmp->next = NULL;
		tail->next = tmp;
		tail = tmp;
	}
}

void destroy() {
	node *tmp;
	while(tail != NULL) {
		tmp = tail->prev;
		free(tail);
		tail = tmp;
	}
	tail = head = NULL;
}

void nextSong() {
	printf("cd to next song\n");
}

void print() {	//遍历链表中元素，测试用
	if(head == NULL) {
		printf("list empty\n");
		return;
	}
	printf("normal:\n");
	for(node* it = head; it != NULL; it = it->next) {
		printf("%s\n", it->songName);
	}
	printf("inverse:\n");
	for(node* it = tail; it != NULL; it = it->prev)
	  printf("%s\n", it->songName);

	printf("the head = %s\n", head->songName);
	printf("the tail = %s\n", tail->songName);
}

#endif
