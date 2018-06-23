#include "stdbool.h"


//#############################################################################
//                               STRUCTS USED
//#############################################################################

typedef struct user_pos user_pos;
typedef struct bucket bucket;
typedef struct hashtable hashtable;

//#############################################################################
//                               HASHTABLE METHODS
//#############################################################################

hashtable * create();
hashtable * create_size(int size);
void insert(hashtable *hashtable, char *nick, int position_in_file);
void insert2(hashtable *hashtable, user_pos *a);
user_pos *get_item(hashtable *hashtable, char *nick);
int contains(hashtable *hashtable, char *nick);
void delete_item(hashtable *ht, char *nick);
void print_table(hashtable *hashtable);
bool load_factor(hashtable *ht);
void delete_hashtable(hashtable *ht);
hashtable *resize_hashtable(hashtable *ht);
