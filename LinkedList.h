#include <stdbool.h>
#include "HashTable.h"

#ifndef COMUNICATION_SYSTEM_LINKEDLIST_H
#define COMUNICATION_SYSTEM_LINKEDLIST_H

#endif //COMUNICATION_SYSTEM_LINKEDLIST_H

//#############################################################################
//                               STRUCTS USED
//#############################################################################

typedef struct following following;
typedef struct user user;

//#############################################################################
//                               LINKED LIST METHODS
//#############################################################################

void add(following** head_ref, char *string, int x, bool first_time);
bool find(following *head, char *string);
following *get_node(following *head, char *string);
bool removeNode(following  **head, char *string);
void deleteList(following ** head_ref);
void printReverse(following* head);
void printReverse2(following* head, user *tmp, hashtable * active_users);
int list_size(following* head);
