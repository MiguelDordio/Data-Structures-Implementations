#include <stdbool.h>
#include "btree.h"


//#############################################################################
//                               STRUCTS USED
//#############################################################################

typedef struct queue queue;

//#############################################################################
//                               METHODS
//#############################################################################

queue *createQueue(int size);
btNode peek(queue *q);
bool isEmpty(queue *q);
bool isFull(queue *q);
int size(queue *q);
void insert(queue *q ,btNode data);
btNode removeData(queue *q);

