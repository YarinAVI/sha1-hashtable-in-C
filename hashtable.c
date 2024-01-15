/**
 * @file hashtable.c
 * @author Yarin Avisidris
 * @brief SHA1 based generic hashtalbe in C
 * @version 0.1
 * @date 2024-01-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "hashtable.h"
#include "sha1/sha1.h"
#include <stdlib.h>
struct hashtable {
    void * (*ctor)(const void *copy);
    void (*dtor)(void *item);
    void * ptrbase[16];
};

Hashtable hashtable_create(void * (*ctor)(const void *copy),void (*dtor)(void *item)) {
    Hashtable ht = calloc(1,sizeof(struct hashtable));
    ht->ctor = ctor;
    ht->dtor = dtor;
    return ht;
}
void * hashtable_insert(Hashtable ht,const void * item,const size_t item_size){
    int i;
    int index;
    void ** indexer = ht->ptrbase;
    char hash[21];
    SHA1(hash,item,item_size); /* compute sha1 hash on the data*/
    /* now use the sha1 hash to encode an address for the data*/
    for(i=0;i<20;i++) {
        index = hash[i] & 0x0F;
        if (indexer[index] == NULL) {
            indexer[index] = calloc(16,sizeof(void*));
        }
        indexer = indexer[index];
        index = (hash[i] >> 4) & 0x0F;
        if (indexer[index] == NULL) {
            indexer[index] = calloc(16,sizeof(void*));
        }
        indexer = indexer[index];
    }
    if(*indexer)
        return NULL;
    (*indexer) = ht->ctor(item);
    return (*indexer);
}
void * hashtable_search(Hashtable ht, const void *item, const size_t item_size) {
    int i;
    int index;
    void ** indexer = ht->ptrbase;
    char hash[21];
    SHA1(hash,item,item_size); /* compute sha1 hash on the data*/
    for(i=0;i<20;i++) {
        index = hash[i] & 0x0F;
        if (indexer[index] == NULL) {
            return NULL;
        }
        indexer = indexer[index];
        index = (hash[i] >> 4) & 0x0F;
        if (indexer[index] == NULL) {
            return NULL;
        }
        indexer = indexer[index];
    }
    return (*indexer);
}
void hashtable_remove(Hashtable ht,void * item,const size_t item_size) {
    int i;
    int index;
    void ** indexer = ht->ptrbase;
    char hash[21];
    SHA1(hash,item,item_size); /* compute sha1 hash on the data*/
    for(i=0;i<20;i++) {
        index = hash[i] & 0x0F;
        if (indexer[index] == NULL) {
            return;
        }
        indexer = indexer[index];
        index = (hash[i] >> 4) & 0x0F;
        if (indexer[index] == NULL) {
            return;
        }
        indexer = indexer[index];
    }
    ht->dtor(*indexer);
    *indexer = NULL;
}
static void hashtable_destroy_internal(Hashtable  ht, void **indexer , int ptrindex) {
    int i;
    if(ptrindex == 40 && *indexer != NULL ) {
        ht->dtor(*indexer);
    }
    else if(ptrindex == 40) {
        return;
    }
    else {
        for(i=0;i<16;i++) {
            if(indexer[i] != NULL) {
                hashtable_destroy_internal(ht,indexer[i],ptrindex+1);
                free(indexer[i]);
                indexer[i] = NULL;
            }
        }
    }
}
void hashtable_destroy(Hashtable * ht) {
    hashtable_destroy_internal(*ht,(*ht)->ptrbase,0);
    free(*ht);
    *ht = NULL;
}