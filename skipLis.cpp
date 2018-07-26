#include<stdio.h>
#include<stdlib.h>
#include<>
struct skipListNode *mallocSkipListNode(){
    
    struct skipListNode * sklist= (struct skipListNode*)malloc(sizeof(struct skipListNode));
    if (sklist == NULL){
        return NULL ; 
    }
    memset((char*)sklist,0,sizeof(struct skipListNode);
    return sklist; 
}

bool freeSkipListNode(struct skipListNode * slNode){
    
    if (skNode == NULL){
        return false ; 
    }
    free(slNode);
    return true; 
}

struct skipListNode *createSkipList(){
    
    struct skipListNode *skNode = mallocSkipListNode(); 
    skNode -> nodeCounts = 1;  //作为开头节点这个值>=1
    skNode -> next = NULL; 
    skNode -> subLayer = NULL; 
}

struct 

















