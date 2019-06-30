#include "binary_heap.h"

int getLeftChildIndex(int parentIndex){ return 2 * parentIndex + 1; }

int getRightChildIndex(int parentIndex){ return 2 * parentIndex + 2; }

int getParentIndex(int childIndex){ return (childIndex - 1) / 2; }

bool hasLeftChild(heap *h, int index){ return getLeftChildIndex(index) < h->capacity; }

bool hasRightChild(heap *h, int index){ return getRightChildIndex(index) < h->capacity; }

bool hasParent(int index){ return getParentIndex(index) >= 0; }

int leftChild(heap *h, int index){ return h->h[getLeftChildIndex(index)]; }

int rightChild(heap *h, int index){ return h->h[getRightChildIndex(index)]; }

int parent(heap *h, int index){ return h->h[getParentIndex(index)]; }


void swap(int *heap, int indexOne, int indexTwo){
    int tmp = heap[indexOne];
    heap[indexOne] = heap[indexTwo];
    heap[indexTwo] = tmp;
}

heap *increseHeapSize(heap *h){
    h->capacity += 10;
    int *items = realloc(h->h, sizeof(int) * (h->capacity));
    h->h = items;
    return h;
}

void heapifyDown(heap *h) {
    int index = 0;
    while(hasLeftChild(h, index)){
        int smallerChildIndex = getLeftChildIndex(index);
        if(hasRightChild(h, index) && rightChild(h, index) < leftChild(h, index))
            smallerChildIndex = getRightChildIndex(index);

        if(h->h[index] < h->h[smallerChildIndex])
            break;
        else
            swap(h->h, index, smallerChildIndex);

        index = smallerChildIndex;
    }
}

void heapifyUp(heap *h) {
    int index = h->size-1;
    while(hasParent(index) && parent(h, index) > h->h[index]){
        swap(h->h, getParentIndex(index), index);
        index = getParentIndex(index);
    }
}

heap *create_heap(int capacity){
    heap *h = malloc(sizeof(heap));
    assert(h != NULL);
    h->h = malloc(sizeof(int) * capacity);
    assert(h->h != NULL);
    h->size = 0;
    h->capacity = capacity;
    return h;
}

int minimun(heap *h){
    assert(h->size > 0);
    return h->h[0];
}

int extract_min(heap *h){
    assert(h->size > 0);
    int item = h->h[0];
    h->h[0] = h->h[h->size-1];
    h->size--;
    heapifyDown(h);
    return item;
}

void add(heap *h, int item){
    if(h->size == h->capacity)
        h = increseHeapSize(h);
    h->h[h->size] = item;
    h->size++;
    heapifyUp(h);
}

void print_heap(heap *h){
    for(int i = 0; i < h->size; i++)
        printf("%d ", h->h[i]);
    printf("\n");
}

int main(){
    heap *h = create_heap(2);
    add(h, 2);
    add(h, 3);
    add(h, 6);
    add(h, 4);
    print_heap(h);
    add(h, 1);
    print_heap(h);
    extract_min(h);
    print_heap(h);
}


