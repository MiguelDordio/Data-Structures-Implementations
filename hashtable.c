#include "hashtable.h"

#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include "string.h"
#include "stdbool.h"
#include "stdlib.h"

#define initial_size 3500000
#define max 3000000
#define NICKSIZE 6

typedef struct user_pos {
    char nick[NICKSIZE];
    int position_in_file;
}user_pos;

typedef struct bucket{
    user_pos *info;
}bucket;

typedef struct hashtable{
    int size;
    int elements;
    bucket **buckets;
}hashtable;


/*
 * Inicializa uma hashtable2 com:
 * tamanho: pre-definido
 * elementos: 0
 */

hashtable * create() {
    hashtable *htable;
    if((htable = malloc(sizeof(hashtable))) == NULL)
        return NULL;
    if((htable->buckets = malloc(sizeof(*htable->buckets) * initial_size)) == NULL)
        return NULL;
    htable->size = initial_size;
    htable->elements = 0;
    for(int i=0; i < initial_size; i++){
        htable->buckets[i] = NULL;
    }
    return htable;
}

/*
 * Inicializa uma hashtable2 com:
 * tamanho: size
 * elementos: 0
 */

hashtable * create_size(int size) {
    hashtable *htable;
    if((htable = malloc(sizeof(hashtable))) == NULL)
        return NULL;
    if((htable->buckets = malloc(sizeof(*htable->buckets) * size)) == NULL)
        return NULL;
    htable->size = size;
    htable->elements = 0;
    for(int i=0; i < size; i++){
        htable->buckets[i] = NULL;
    }
    return htable;
}


/*
 * Gera a hash a ser usada pela hashtable2
 * somando o valor de ASCII de cada caracter
 * da string que recebe
 */

unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31*hashval;
    return hashval;
}


/*
 * Verifica se a hashtable2 atingiu o factor carga
 * nesta implementação é 0.5
 */

bool load_factor(hashtable *ht){
    if(ht->elements >= ht->size/2)
        return true;
    return false;
}

/*
 * Verifica se é primo
 */

bool isPrime(int num){
    if(num==2)
        return true;
    if(num % 2==0)
        return false;
    for(int i=3; i<num/i; i+=2){
        if(num%i==0)
            return false;
    }
    return true;
}

/*
 * Encontra o primo mais próximo que é no minimo
 * o dobro do anterior
 */

int Prime_num(int old_size){
    for(int i = old_size*2+1; i < max; i++){
        if(isPrime(i)) {
            return i;
        }
    }
    assert(0); // Tentativa de lidar com nº muito grandes
}


/*
 * Insere os valores recebidos na hashtable2
 */

void insert(hashtable *hashtable, char *nick, int position_in_file){
    int hash_value = hash(nick);
    int new_position = hash_value % hashtable->size;
    if (new_position < 0) new_position += hashtable->size;
    int position = new_position;
    while (hashtable->buckets[position] != NULL && position != new_position - 1) {
        if(hashtable->buckets[position]->info != NULL){
            position++;
            position %= hashtable->size;
        }else{
            break;
        }
    }
    hashtable->buckets[position] = malloc(sizeof(bucket));
    hashtable->buckets[position]->info = malloc(sizeof(user_pos));
    strcpy(hashtable->buckets[position]->info->nick, nick);
    hashtable->buckets[position]->info->position_in_file = position_in_file;
    hashtable->elements++;
}

void insert2(hashtable *hashtable, user_pos *a){
    int hash_value = hash(a->nick);
    int new_position = hash_value % hashtable->size;
    if (new_position < 0) new_position += hashtable->size;
    int position = new_position;
    while (position != new_position - 1 && hashtable->buckets[position] != NULL) {
        if(hashtable->buckets[position]->info != NULL) {
            position++;
            position %= hashtable->size;
        }else
            break;
    }
    hashtable->buckets[position] = malloc(sizeof(bucket));
    hashtable->buckets[position]->info = malloc(sizeof(user_pos));
    hashtable->buckets[position]->info = a;
    hashtable->elements++;
}

/*
 * Indica se um determinado nick está na hashtable2
 */

int contains(hashtable *hashtable, char *nick){
    int hash_value = hash(nick);
    int position = (hash_value % hashtable->size);
    while(position < hashtable->size){
        if(hashtable->buckets[position] == NULL)
            return -1;
        else {
            if (hashtable->buckets[position]->info == NULL)
                position++;
            else if (strcmp(hashtable->buckets[position]->info->nick, nick) == 0)
                return position;
            else
                position++;

        }
        if(position == hashtable->size)
            position = 0;
    }
    assert(!"Unreachable code hit");
}

/*
 * Dado um nick apaga todas as informações
 * sobre da hashtable2
 */

void delete_item(hashtable *ht, char *nick){
    int position = contains(ht, nick);
    if(position != -1){
        ht->buckets[position]->info = NULL;
        ht->elements--;
    }
}

/*
 * Deletes the hashtable2
 */

void delete_hashtable(hashtable *ht) {
    for(int i = 0; i<ht->size; i++){
        if(ht->buckets[i] != NULL && ht->buckets[i]->info != NULL){
            free(ht->buckets[i]->info);
            free(ht->buckets[i]);
        }
    }
    free(ht->buckets);
    free(ht);
}

/*
 * Aumenta a hashtable2 quando atinge o factor carga
 * 1º Copia os items que se encontram na hashtable2
 * para um array tmp
 * 2º Cria uma nova hashtable2 com o novo tamanho
 * 3º Volta a colocar os valores na hashtable2
 */

hashtable *resize_hashtable(hashtable *ht){
    int new_size = Prime_num(ht->size);
    hashtable *new_hashtable = create_size(new_size);
    for(int i = 0; i < ht->size; i++){
        if(ht->buckets[i] != NULL && ht->buckets[i]->info != NULL){
            insert(new_hashtable, ht->buckets[i]->info->nick, ht->buckets[i]->info->position_in_file);
        }
    }
    delete_hashtable(ht);
    return new_hashtable;
}



/*
 * Dado um nick, procura-o na hashtable2
 * e caso o encontre retorna as informações
 * a ele associadas
 */

user_pos *get_item(hashtable *hashtable, char *nick){
    int position = contains(hashtable, nick);
    if(position != -1)
        return hashtable->buckets[position]->info;
    assert(!"Unreachable code hit");
}


/*
 * Representação do estado atual da hashtable2
 */

void print_table(hashtable *hashtable){
    for(int i = 0; i<hashtable->size; i++){
        if(hashtable->buckets[i] != NULL && hashtable->buckets[i]->info != NULL)
            printf("i: %d, nick: %s, position: %d\n",i, hashtable->buckets[i]->info->nick, hashtable->buckets[i]->info->position_in_file);
        else
            printf("i: %d, nick: -\n", i);
    }
    printf("\n");
}
