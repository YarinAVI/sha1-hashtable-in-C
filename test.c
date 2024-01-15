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
    int c = 1;
    tests = fopen("tests.txt","r");
        ht = hashtable_create(ctor,dtor);
    while(fgets(buffer,sizeof(buffer),tests)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        find = hashtable_insert(ht,buffer,strlen(buffer));
        if(find == NULL)
            printf("hashtable collision detected for:'%s'\n",buffer);   
        else
            printf("found : %s\n",(char*)hashtable_search(ht,buffer,strlen(buffer)));
        c++;
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
    
    hashtable_destroy(&ht);
    return 0;
}