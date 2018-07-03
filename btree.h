#include <stdio.h>

#ifndef B_TREE_BTREE_H
#define B_TREE_BTREE_H

#endif //B_TREE_BTREE_H


/* implementation of a B-tree */
typedef struct element element;
typedef struct btNode btNode;
typedef struct bTree bTree;

/* create a new empty tree */
bTree *btCreate(int order);

/* free a tree */
void btDestroy(btNode t);

/* return nonzero if key is present in tree */
int btSearch(btNode node, int order, element key, FILE *fp);

/* insert a new element into a tree */
void btInsert(bTree *tree, element key, FILE *fp);

/* deletes a key from the tree */
void btDelete(bTree *tree, element *key, int order);

/* print all keys of the tree in order */
void btPrintTree(bTree *tree, FILE *fp);