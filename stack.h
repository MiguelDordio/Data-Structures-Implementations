#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#ifndef STACK_STACK_H
#define STACK_STACK_H


typedef struct stack{
    int size;
    int *stack_arr;
    int top;
}stack;


// creates a stack of size: "size"
stack *create(int size);

// checks if the stack is empty
bool empty(stack *s);


// inserts an item in the top of the stack
void push(stack *s, int data);


// deletes an item from the top of the stack
int pop(stack *s);


// returns the item currently at the top of the stack
int top(stack *s);

#endif //STACK_STACK_H
