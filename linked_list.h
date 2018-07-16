#ifndef LINKEDLIST_LINKED_LIST_H
#define LINKEDLIST_LINKED_LIST_H


#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node{
    int data;
    struct node *next;
}node;

node *search(node *head, int key);

node *insert(node *head, int key);

bool delete(node **head, int key);

void printReverse(node* head);

#endif //LINKEDLIST_LINKED_LIST_H
