#include <stdio.h>
#include <stdlib.h>

typedef struct point{
    int x;
    struct point *next;
}point;


point *head = NULL;


void add(point** head_ref, int x) {
    point* new_node = malloc(sizeof(point));
    new_node->x = x;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void deleteList(point ** head_ref) {
    point* current = *head_ref;
    point* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}

void printReverse(point* head) {
    if (head == NULL)
        return;
    printReverse(head->next);
    printf("x: %d\n", head->x);
}

int list_size(point* head){
    int count = 0;  // Initialize count
    point* current = head;  // Initialize current
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}
