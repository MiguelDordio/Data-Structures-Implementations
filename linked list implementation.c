#include <stdio.h>
#include <stdlib.h>

typedef struct point{
    int x;
    int y;
    struct point *next;
}point;


point *head = NULL;


void add(point** head_ref, int x, int y) {
    point* new_node = malloc(sizeof(point));
    new_node->x = x;
    new_node->y = y;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void deleteList(point ** head_ref) {
    point* current = *head_ref;
    point* next;
    int i = 0;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
        i++;
    }
    *head_ref = NULL;
}

void printReverse(point* head) {
    if (head == NULL)
        return;
    printReverse(head->next);
    printf("x: %d, y: %d\n", head->x, head->y);
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

int main() {
    add(&head, 4, 5);
    add(&head, 6, 7);
    add(&head, 8, 9);
    add(&head, 10, 11);
    int size = list_size(head);
    printReverse(head);
    printf("size: %d\n", size);
}


