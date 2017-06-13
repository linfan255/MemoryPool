#ifndef LIST_H
#define LIST_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
	char songName[1024];
	int id;
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
		head->id = 1;
		head->prev = NULL;
		head->next = NULL;

		tail = head;
	}	
	else {
		node* tmp = (node*)malloc(sizeof(node));
		strcpy(tmp->songName, filename);
		tmp->id = tail->id + 1;
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
	node *it;
	int id = 1;
	for(it = head; it != NULL; it = it->next) {
		printf("%d: %s\n", it->id, it->songName);
	}
}

#endif
