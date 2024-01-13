/**
 * @file hashtable.h
 * @author Yarin Avisidris 
 * @brief SHA1 based generic hashtalbe in C , 4bit encoding
 * @version 0.1
 * @date 2024-01-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __HASHTABLE_H_YARIN__
#define __HASHTABLE_H_YARIN__

#include <stddef.h>
typedef struct hashtable * Hashtable;

/**
 * @brief creates a new hasshtable
 * 
 * @param ctor ctor function ( user function) how to copy an item to the hashtable
 * @param dtor dtor function ( user function) how to delete an item in the hashtable
 * @return Hashtable 
 */
Hashtable hashtable_create(void * (*ctor)(const void *copy),void (*dtor)(void *item));
/**
 * @brief inserts a new item to the hashtable
 * 
 * @param ht the hashtable
 * @param item pointer to the item
 * @return void* returns a pointer to the item that was just inserted
 */
void * hashtable_insert(Hashtable ht,const void * item,const size_t item_size);
/**
 * @brief deletes an item from the hashtable
 * 
 * @param ht the hashtable
 * @param item pointer to the item to delete
 */
void hashtable_remove(Hashtable ht,void * item,const size_t item_size);
/**
 * @brief searchs in the hashtable
 * 
 * @param ht the hashtable
 * @param item the item
 * @param item_size  the item size
 * @return void* returns a pointer to the found item or NULL if not found.
 */
void * hashtable_search(Hashtable ht, const void *item, const size_t item_size);
/**
 * @brief destroys the hasdhtable and the items inside it using user provided dtor function
 * 
 * @param ht the hashtable
 */
void hashtable_destroy(Hashtable * ht);
#endif