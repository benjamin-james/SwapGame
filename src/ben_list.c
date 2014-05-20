#include "ben_list.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

void append(NODE **head, void *data, size_t size)
{
	if(!(*head))
	{
		push(head,data,size);	//push replaces head node every time
		return;
	}
	NODE *temp = (NODE *)malloc(sizeof(NODE));
	temp->size = size;
	temp->data = malloc(size);
	memcpy(temp->data,data,size);
	temp->next = NULL;
	NODE *t = *head;
	while(t && t->next)
	{
		t = t->next;
	}
	t->next = temp;
}
void push(NODE **head, void *data,size_t size)
{
	NODE *temp = (NODE *)malloc(sizeof(NODE));
	temp->size = size;
	temp->data = malloc(size);
	temp->next = *head;
	memcpy(temp->data,data,size);
	*head = temp;
}
void print(NODE **head)
{
	NODE *temp = *head;
	int n = 0;
	printf("\n");
	while(temp)
	{
		printf("\nElement %d:\tLocation:\t0x%p\tSize:\t%d bytes",++n,temp->data,temp->size);
		temp = temp->next;
	}
}
void *pop(NODE **head)
{
	void *data = NULL;
	NODE *temp = *head;
	if(temp)
	{
		data = malloc(temp->size);
		memcpy(data,temp->data,temp->size);
		*head = temp->next;
		free(temp->data);
		free(temp);
	}
	return data;
}
void *peek(NODE **head)
{
	void *data = NULL;
	NODE *temp = *head;
	if(temp)
	{
		data = malloc(temp->size);
		memcpy(data,temp->data,temp->size);
	}
	return data;
}
int size(NODE **head)
{
	NODE *temp = *head;
	int n;
	for(n = 0; temp; n++) temp = temp->next;
	return n;
}
