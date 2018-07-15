#include "stack.h"

stack *create(int size){
    stack *s;
    s = malloc(sizeof(stack));

    s->size = size;
    s->top = -1;
    s->stack_arr = malloc(sizeof(int)*size);

    return s;
}

bool empty(stack *s){
    return s->top == -1;
}

void push(stack *s, int data){
    if(s->size != s->top+1){
        s->top = s->top+1;
        s->stack_arr[s->top] = data;
    }else
        printf("overflow\n");
}

int pop(stack *s){
    if(empty(s))
        printf("underflow\n");
    else{
        int del = s->stack_arr[s->top];
        s->top = s->top-1;
        return del;
    }
}

int top(stack *s){
    return s->stack_arr[s->top];
}