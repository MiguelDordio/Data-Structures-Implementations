#include "linked_list.h"

node *search(node *head, int key){
    node *tmp_node = head;

    while(tmp_node != NULL && tmp_node->data != key){
        if(tmp_node->next == NULL) {
            printf("key does not exist\n");
            return NULL;
        }else
            tmp_node = tmp_node->next;
    }

    return tmp_node;
}

node *insert(node *head, int key){

    node *new_node = malloc(sizeof(node));
    new_node->data = key;
    new_node->next = head;

    head = new_node;

    return head;
}

bool delete(node **head, int key) {
    if (*head == NULL) return false;

    node *tmp = *head;
    node *prev = NULL;

    while (tmp->data != key && tmp->next != NULL) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp->data == key) {
        if (prev)
            prev->next = tmp->next;
        else
            *head = tmp->next;
        free(tmp);
        return true;
    }

    return false;
}


void printReverse(node* head) {
    if (head == NULL)
        return;
    printReverse(head->next);
    printf("data: %d\n", head->data);
}
