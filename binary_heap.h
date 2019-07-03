#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct heap {
    int size;
    int capacity;
    int *h;
}heap;


heap *create_heap(int capacity);
int minimun(heap *h);
int extract_min(heap *h);
void decrease_key(heap *h, int i, int key);
void add(heap *h, int item);
void print_heap(heap *h);
void destroyHeap(heap *h);
