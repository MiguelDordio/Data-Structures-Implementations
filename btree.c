#include "btree.h"
#include "queue.h"
#include <stdio.h>
#include <malloc.h>


//#############################################################################
//                               STRUCTS
//#############################################################################

typedef struct element{
    int key; /* the key of the element */
    int data; /* that data that each element contains*/
}element;

typedef struct btNode{
    int numKeys;    /* how many keys does this node contain? */
    int isLeaf;     /* is this a leaf node? 1 = true, 0 = false */
    int pos_in_disk;
    element *keys; /* holds the keys of the node */
    int *kids;  /* holds the children of the node */
}btNode;

typedef struct bTree {
    int order; /* order of the B-Tree */
    btNode root; /* root of the B-Tree */
    int node_count;
} bTree;

//#############################################################################
//                               HELPER METHODS
//#############################################################################

/*element * bt_find_max(btNode *node){
    if(node == NULL) {
        return NULL;
    }else if(node->isLeaf) {
        return node->keys[node->numKeys-1];
    }else{
        disk_read(node);
        bt_find_max(node->kids[node->numKeys-1]);
    }
}

element * bt_find_min(btNode node){
    if(node == NULL) {
        return NULL;
    }else if(node->isLeaf) {
        return node.keys[0];
    }else{
        disk_read(node);
        bt_find_min(node.kids[0]);
    }
}

void bt_merge_children(btNode *node, int pos, int order){
    btNode y = node->kids[pos];                     // merge children i
    btNode z = node->kids[pos+1];                   // and pos+1
    y->keys[order] = node->keys[pos];
    for(int j = 1; j < order;j++){                   // transfer kids[pos+1]
        y.keys[order + j] = z.keys[j];             // contents to kids[pos]
    }
    if(!y->isLeaf){
        for(int j = 1; j < order;j++){
            y->kids[order + j] = z.kids[j];
        }
    }
    y->numKeys = 2*order -1;                         // kids[pos] is now full
    for(int j = pos+1; j < node->numKeys;j++){
        node->keys[j-1] = node->keys[j];
    }
    for(int j = pos+2; j < node->numKeys+1;j++){
        node->kids[j-1] = node->kids[j];
    }
    node->numKeys--;
    free(z);                                         // delete old kids[pos+1]
    disk_write(y);
    disk_write(node);
}

void bt_borrow_from_left_sibling(btNode *node, int pos, int order){
    btNode *y = node->kids[pos];                     // node pos`s left
    btNode *z = node->kids[pos-1];                   // sibling is pos-1
    for(int j = order-1; j > 1; j--){                // make room for
        y->keys[j+1] = y->keys[j];                   // new 1st key
    }
    y->keys[1] = node->keys[pos-1];
    node->keys[pos-1] = z->keys[z->numKeys];
    if(!y->isLeaf){
        for(int j = order; j > 1; j--){              // make room for
            y->kids[j+1] = y->kids[j];               // new 1st child
        }
        y->kids[1] = z->kids[z->numKeys+1];
    }
    y->numKeys = order;
    z->numKeys--;
    disk_write(z);
    disk_write(y);
    disk_write(node);
}

void bt_borrow_from_right_sibling(btNode *node, int pos, int order){

}

void bt_delete_safe(btNode *node, element *key, int order){
    int borrowed = -1; //default
    int pos = 1;
    while(pos <= node->numKeys && key->key > node->keys[pos]->key)
        pos++;
    if(pos <= node->numKeys && key->key > node->keys[pos]->key){
        if(node->isLeaf){                                             // case 1
            for(int j = pos; j < node->numKeys -1; j++)               // case 1
                node->keys[j] = node->keys[j+1];                      // case 1
            node->numKeys--;                                          // case 1
            disk_write(node);                                         // case 1
        }else{
            btNode *y = node->kids[pos];
            disk_write(y);
            if(y->numKeys > order-1){                                 // case 2a
                node->keys[pos] = bt_find_max(y);                     // case 2a
                disk_write(node);                                     // case 2a
                free(node->keys[pos]);
            }else{
                btNode *z = node->kids[pos+1];
                disk_read(z);
                if(z->numKeys > order-1){                             // case 2b
                    node->keys[pos] = bt_find_min(z);                 // case 2b
                    disk_write(node);                                 // case 2b
                    free(node->keys[pos]);
                }else{
                    bt_merge_children(node, pos, order);              // case 2c
                    bt_delete_safe(node->kids[pos], key, order);      // case 2c
                }
            }
        }
    }else if(!node->isLeaf){
        int m = -1; //default
        btNode *y = node->kids[pos];
        disk_read(y);
        if(y->numKeys == order-1){
            borrowed = 0;
            if(pos > 1){
                btNode *z = node->kids[pos-1];
                disk_read(z);
                if(z->numKeys > order - 1){                            // case 3a
                    bt_borrow_from_left_sibling(node, pos, order);     // case 3a
                    borrowed = 1;                                      // case 3a
                }else{
                    m = pos - 1;
                }
            }
            if(borrowed == 0 && pos <= node->numKeys){
                btNode *z = node->kids[pos+1];
                disk_read(z);
                if(z->numKeys > order - 1){                            // case 3a
                    bt_borrow_from_right_sibling(node, pos, order);    // case 3a
                    borrowed = 1;                                      // case 3a
                }else{
                    m = pos - 1;
                }
            }
            if(borrowed == 0){                                         // case 3b
                bt_merge_children(node, m, order);                     // case 3b
                y = node->kids[m];                                     // case 3b
            }
        }
        bt_delete_safe(y, key, order);
    }
}*/

btNode disk_read(int disk, int order, FILE *fp){
    btNode read_node;

    int size_of_btNode = (sizeof(int) * 3) + (sizeof(element) * order-1) + (sizeof(int) * order);
    int offset = size_of_btNode * disk;
    fseek(fp, offset, SEEK_SET);


    fread(&read_node.numKeys, sizeof(read_node.numKeys), 1, fp);
    fread(&read_node.isLeaf, sizeof(read_node.isLeaf), 1, fp);
    fread(&read_node.pos_in_disk, sizeof(read_node.pos_in_disk), 1, fp);

    read_node.keys = malloc(sizeof(element) * order-1);
    fread(read_node.keys, sizeof(element), order-1, fp);

    read_node.kids = malloc(sizeof(int) * order);
    fread(read_node.kids, sizeof(int), order, fp);


    return read_node;
}

void disk_write(btNode node, int order, FILE *fp){

    int size_of_btNode = (sizeof(int) * 3) + (sizeof(element) * order-1) + (sizeof(int) * order);
    int offset = size_of_btNode * node.pos_in_disk;
    fseek(fp, offset, SEEK_SET);

    // write the information
    fwrite(&node.numKeys, sizeof(node.numKeys), 1, fp);
    fwrite(&node.isLeaf, sizeof(node.isLeaf), 1, fp);
    fwrite(&node.pos_in_disk, sizeof(node.pos_in_disk), 1, fp);
    fwrite(node.keys, sizeof(element), order-1, fp);
    fwrite(node.kids, sizeof(int), order, fp);
}

btNode new_node(int order, int is_leaf) {
    btNode n;

    n.numKeys = 0;
    n.isLeaf = is_leaf;
    n.keys = malloc((order-1) * sizeof(element));
    for(int i=0; i < order-1; i++){
        n.keys[i].key = -1;
        n.keys[i].data = -1;
    }
    n.kids = malloc((order) * sizeof(int));
    for(int i=0; i < order; i++){
        n.kids[i] = -1;
    }

    return n;
}

void bt_split_child(btNode x, int pos, bTree *tree, FILE *fp){
    int t = (tree->order/2);

    btNode y = disk_read(x.kids[pos], tree->order, fp);
    tree->node_count++;
    y.pos_in_disk = tree->node_count;
    btNode z = new_node(tree->order, y.isLeaf);
    tree->node_count++;
    z.pos_in_disk = tree->node_count;
    z.numKeys = t-1;

    for(int j = 1; j < t-1; j++){
        z.keys[j] = y.keys[j+t];
    }

    if(y.isLeaf == 0){ // if y is not a leaf
        for(int j = 1; j < t; j++){
            z.kids[j] = y.kids[j+t];
        }
    }
    y.numKeys = t-1;

    for(int j = x.numKeys +1; j > pos+1; j--){
        x.kids[j+1] = x.kids[j];
    }
    x.kids[pos+1] = z.pos_in_disk;

    for(int j = x.numKeys; j > pos; j--){
        x.keys[j+1] = x.keys[j];
    }
    x.keys[pos] = y.keys[t];
    y.keys[t].key = -1;
    y.keys[t].data = -1;
    x.numKeys++;

    disk_write(x, tree->order, fp);
    disk_write(y, tree->order, fp);
    disk_write(z, tree->order, fp);
}

btNode bt_insert_nonfull(btNode node, element key, bTree *tree, FILE *fp){

    int pos = node.numKeys;

    if(node.isLeaf == 1){ // if in a leaf insert the new element
        int i = pos-1;
        while(i >= 0 && key.key < node.keys[i].key){
            node.keys[i+1] = node.keys[i];
            node.keys[i].key = -1;
            node.keys[i].data = -1;
            i--;
        }
        if(i+1 != pos){
            node.keys[i+1] = key;
        }else{
            node.keys[pos] = key;
        }
        node.numKeys++;
        disk_write(node, tree->order, fp);
        return node;
    }else{  // otherwise, descend to the appropriate child
        pos--;
        while (pos >= 1 && key.key < node.keys[pos].key) {
            pos--;
        }
        btNode x = disk_read(node.kids[pos], tree->order, fp);
        if(x.numKeys == tree->order -1){  // is this child full?
            bt_split_child(node, pos, tree, fp);
            if(key.key > node.keys[pos].key)
                pos++;
        }
        btNode x2 = disk_read(node.kids[pos], tree->order, fp);
        bt_insert_nonfull(x2, key, tree, fp);
    }
}

//#############################################################################
//                               METHODS
//#############################################################################


bTree *btCreate(FILE *fp, int order){

    bTree *tree; /* creates the "header" of the B-Tree */
    if((tree = malloc(sizeof(bTree))) == NULL)
        return NULL;

    btNode root = new_node(order, true); /* creates the root of the new B-Tree */
    root.pos_in_disk = 0;

    tree->order = order;
    tree->root = root;
    tree->node_count = 0;

    return tree;

}

void btInsert(bTree *tree, element key, FILE *fp){

    btNode root = tree->root;

    if(root.numKeys == tree->order-1){ // if the root is full
        btNode s = new_node(tree->order, 0);
        s.kids[1] = root.pos_in_disk;
        bt_split_child(s, 1, tree, fp);
        s = disk_read(0, tree->order, fp);
        tree->root = s;
        bt_insert_nonfull(s, key, tree, fp);
        //tree->node_count += 2;
    }else{
        tree->root = bt_insert_nonfull(root, key, tree, fp);
    }

}

int btSearch(btNode node, int order, element key, FILE *fp){

    int pos = 1;
    while(pos <= node.numKeys && key.key > node.keys[pos].key){
        pos++;
    }
    if(pos <= node.numKeys && key.key == node.keys[pos].key){
        return node.pos_in_disk;
    }else if(node.isLeaf == 1){
        return -1;
    }else{
        btNode x = disk_read(node.kids[pos], order, fp);
        return btSearch(x, order, key, fp);
    }
}

/*void btDelete(bTree *tree, element *key, int order){

    btNode *root = tree->root;
    bt_delete_safe(root, key, order);
    if(root->numKeys == 0 && !root->isLeaf){
        root = root->kids[1];
        free(tree->root);
        tree->root = root;
    }
}*/

void print_node_keys(btNode node, int order){
    printf("[");
    for(int i = 0; i < order-1; i++){ // insert all the kids os the root in the queue
        printf("key: %d, ", node.keys[i].key);
    }
    printf("]\n");
}

void btPrintTree(bTree *tree, FILE *fp){
    queue *q = createQueue(6);
    //print_node_keys(tree->root, tree->order);
    insert(q, tree->root);

    while(!isEmpty(q)){
        btNode next = removeData(q);
        print_node_keys(next, tree->order);
        for(int i = 0; i < tree->order-1; i++){ // insert all the kids os the next node in the queue
            if(next.kids[i] != -1){
                btNode x = disk_read(next.kids[i], tree->order, fp);
                insert(q, x);
            }
        }
    }
}



int main(){

    element n1 = {.key = 20};
    element n2 = {.key = 30};
    element n3 = {.key = 10};
    element n4 = {.key = 40};

    FILE *fp;
    fp = fopen("file.bin", "wb+");
    bTree *tree = btCreate(fp, 4);
    btInsert(tree, n2, fp);
    btInsert(tree, n1, fp);
    btInsert(tree, n3, fp);

    btNode x = disk_read(0, tree->order, fp);
    printf("\n[");
    for(int i = 0; i < tree->order-1; i++){ // insert all the kids os the root in the queue
        printf("key: %d, ", x.keys[i].key);
    }
    printf("]\n");

    //btInsert(tree, n4, fp);

    //btPrintTree(tree, fp);

    btNode x1 = disk_read(0, tree->order, fp);
    printf("\n[");
    for(int i = 0; i < tree->order-1; i++){ // insert all the kids os the root in the queue
        printf("key: %d, ", x1.keys[i].key);
    }
    printf("]\n");

    return 0;
}
