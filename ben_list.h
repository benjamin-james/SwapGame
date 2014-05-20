#ifndef BEN_LIST_H
#define BEN_LIST_H
#include "string.h"
typedef struct _Node
{
	size_t size;
	void *data;
	struct _Node *next;
} NODE;
void push(NODE **head, void *data, size_t size);
void append(NODE **head, void *data, size_t size);
void print(NODE **head);
void *pop(NODE **head);
void *peek(NODE **head);
int size(NODE **head);
#endif
