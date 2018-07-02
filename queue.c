#include "queue.h"
#include "btree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct btNode{
    int numKeys;    /* how many keys does this node contain? */
    int isLeaf;     /* is this a leaf node? 1 = true, 0 = false */
    int pos_in_disk;
    element *keys; /* holds the keys of the node */
    int *kids;  /* holds the children of the node */
}btNode;

typedef struct queue{
    int size;
    int front;
    int rear;
    int itemCount;
    btNode *list;
}queue;

queue *createQueue(int size){
    queue *q;
    if((q = malloc(sizeof(queue))) == NULL)
        return NULL;
    if((q->list = malloc(sizeof(btNode) * size)) == NULL)
        return NULL;
    q->size = size;
    q->front = 0;
    q->rear = -1;
    q->itemCount = 0;
    return q;
}

btNode peek(queue *q) {
    return q->list[q->front];
}

bool isEmpty(queue *q) {
    return q->itemCount == 0;
}

bool isFull(queue *q) {
    return q->itemCount == q->size;
}

int size(queue *q) {
    return q->itemCount;
}

void insert(queue *q ,btNode data) {

    if(!isFull(q)) {

        if(q->rear == q->size-1) {
            q->rear = -1;
        }

        q->list[++q->rear] = data;
        q->itemCount++;
    }
}

btNode removeData(queue *q) {
    btNode data = q->list[q->front++];

    if(q->front == q->size) {
        q->front = 0;
    }

    q->itemCount--;
    return data;
}
