#include "linked_list.h"


linked_list *create_new(){
    linked_list *linked;
    if((linked = malloc(sizeof(linked_list))) == NULL)
        return NULL;
    linked->head = NULL;
    linked->size = 0;
    return linked;
}


bool empty(linked_list *linked){
    return linked->head == NULL;
}


bool exists(linked_list *linked, char *airport_code){
    node *tmp_node = linked->head;

    while(tmp_node != NULL && strcmp(tmp_node->airport_code, airport_code) != 0){
        if(tmp_node->next == NULL) {
            return false;
        }else
            tmp_node = tmp_node->next;
    }

    return true;
}


node *get_node(linked_list *linked, char *airport_code){
    node *tmp_node = linked->head;

    while(tmp_node != NULL && strcmp(tmp_node->airport_code, airport_code) != 0){
        if(tmp_node->next == NULL) {
            return NULL;
        }else
            tmp_node = tmp_node->next;
    }

    return tmp_node;
}

void insert_new(linked_list *linked, char *airport_code){

    node *new_node = malloc(sizeof(node));
    strcpy(new_node->airport_code, airport_code);
    new_node->flights_size = 0;
    new_node->flight_time = 0;
    new_node->flights = malloc(sizeof(flight) * 20);
    new_node->next = linked->head;

    linked->size++;
    linked->head = new_node;

}

bool delete(linked_list *linked, char *airport_code) {
    if (linked->head == NULL) return false;

    node *tmp = linked->head;
    node *prev = NULL;

    while (strcmp(tmp->airport_code, airport_code) != 0 && tmp->next != NULL) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (strcmp(tmp->airport_code, airport_code) == 0) {
        if (prev)
            prev->next = tmp->next;
        else
            linked->head = tmp->next;
        free(tmp);
        linked->size--;
        return true;
    }

    return false;
}


void pop(linked_list *linked){
    if(linked->head != NULL){
        if(linked->head->next != NULL){
            linked->head = linked->head->next;
        }else{
            linked->head = NULL;
        }
        linked->size--;
    }
}


void print(linked_list *linked) {
    printf("\nlinked list size: %d\n", linked->size);
    if (linked->head == NULL)
        return;
    node *current = linked->head;
    while(current != NULL){
        printf("airport: %s\n", current->airport_code);
        if(current->next == NULL)
            return;
        current = current->next;
    }
}
