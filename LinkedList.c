#include "LinkedList.h"
#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct following{
    char nick[6];
    int last_message;
    bool first_time;
    struct following *next;
}following;

typedef struct user{
    char nick[6];
    char name[26];
    int n_messages;
    int n_following;
    int n_followers;
    following *arr_following;
    following *arr_unfollowed;
}user;

/*
 * Insere um novo node do tipo following
 * na "frente" da linked list O(1)
 */

void add(following** head_ref, char *string, int x, bool first_time) {
    following* new_node = malloc(sizeof(following));
    strcpy(new_node->nick, string);
    new_node->last_message = x;
    new_node->first_time = first_time;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}


/*
 * Procura na linked list por uma dada string O(n)
 */

bool find(following *head, char *string) {
    following *current = head;
    if (current == NULL) {
        return false;
    }else{
        if(strcmp(current->nick, string) == 0)
            return true;
    }
    while (current->next != NULL) {
        if (strcmp(current->nick, string) == 0)
            return true;
        current = current->next;
    }
    return false;
}


following *get_node(following *head, char *string){
    following *current = head;
    while (current != NULL) { //percorre a linked list que contem os seguidos
        if(strcmp(current->nick, string) == 0){
            return current;
        }
        current = current->next;
    }
    return NULL;
}


/*
 * Remove um dado node da linked list O(n)
 */

bool removeNode(following **head, char *string) {
    if (*head == NULL) return false;

    following *tmp = *head;
    following* prev = NULL;

    while (strcmp(tmp->nick, string) != 0 && tmp->next != NULL) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (strcmp(tmp->nick, string) == 0) {
        if (prev)
            prev->next = tmp->next;
        else
            *head = tmp->next;
        free(tmp);
        return true;
    }

    return false;
}


/*
 * Elimina uma dada linked list O(n)
 */

void deleteList(following ** head_ref) {
    following* current = *head_ref;
    following* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}


/*
 * Faz print de uma linked list do tipo following O(n)
 */

void printReverse(following* head) {
    if (head == NULL)
        return;
    printReverse(head->next);
    printf("%s (%d lidas)\n", head->nick, head->last_message);
}

void printReverse2(following* head, user *tmp, hashtable * active_users){
    if (head == NULL)
        return;
    printReverse2(head->next, tmp, active_users);
    if(contains(active_users, head->nick) != -1){
        user *followed = get_item(active_users, head->nick);
        int num_new_messages = followed->n_messages - head->last_message;
        if(num_new_messages == 0){
            if(strcmp(tmp->nick, followed->nick)==0 && head->first_time){
                printf("mensagen nova de %s (%s): %d\n", followed->nick, followed->name, followed->n_messages);
                head->first_time = false;
            }else
                printf("sem mensagens novas de %s (%s)\n", followed->nick, followed->name);
        }else if(num_new_messages == 1){
            printf("mensagens novas de %s (%s): %d\n", followed->nick, followed->name, followed->n_messages);
        }else if(num_new_messages > 1){
            printf("mensagens novas de %s (%s): %d a %d\n", followed->nick, followed->name, head->last_message+1, followed->n_messages);
        }
        head->last_message = followed->n_messages;
    }else{
        printf("utilizador %s desactivado\n", head->nick);
        tmp->n_following--;
        removeNode(&tmp->arr_following, head->nick); // remove da lista dos seguidos
    }
}


/*
 * Calcula o tamanho de uma dada linked list O(n)
 */

int list_size(following* head){
    int count = 0;  // Initialize count
    following* current = head;  // Initialize current
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

/*int main(){
    following *head = NULL;
    add(&head, "miguel", 0);
    add(&head, "luis", 0);
    add(&head, "ricardo", 0);
    printf("size: %d\n", list_size(head));
    printReverse(head);
    printf("\n\n");
    removeNode(head, "miguel");
    printf("size: %d\n", list_size(head));
    printReverse(head);
    return 0;
}*/
