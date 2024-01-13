#include "hashtable.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
void * ctor(const void *item) {
    return strcpy(malloc(strlen(item) +1),item);
}
void dtor(void *item) {
    free(item);
}
int main() {
    char buffer[1000];
    Hashtable ht;
    FILE * tests;
    char * find;
    tests = fopen("tests.txt","r");
        ht = hashtable_create(ctor,dtor);
    while(fgets(buffer,sizeof(buffer),tests)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        hashtable_insert(ht,buffer,strlen(buffer));
        printf("found : %s\n",(char*)hashtable_search(ht,buffer,strlen(buffer)));
    }
    /* now delete and search*/
    rewind(tests);
    while(fgets(buffer,sizeof(buffer),tests)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        hashtable_remove(ht,buffer,strlen(buffer));
        find = (char*)hashtable_search(ht,buffer,strlen(buffer));
        if(find == NULL) {
            printf("%s not found\n",buffer);
        }
    }
    return 0;
}