#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable2.h"

#define AIRPORTCODESIZE 5



typedef struct node{
    char airport_code[AIRPORTCODESIZE];
    short flight_time;
    short flights_size;
    flight *flights;
    struct node *next;
}node;


typedef struct linked_list{
    int size;
    node *head;
}linked_list;


linked_list *create_new();

bool empty(linked_list *linked);

node *get_node(linked_list *linked, char *airport_code);

bool exists(linked_list *linked, char *airport_code);

void insert_new(linked_list *linked, char *airport_code);

bool delete(linked_list *linked, char *airport_code);

void print(linked_list *linked);
