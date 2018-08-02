#ifndef SKIP_LIST_H
#define SKIP_LIST_H
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define SKIPLEVEL_THRESHOLD   20

struct skipListNode{

    int key ; 
    void *value; 
    struct skipListNode *next    ;  //指向下一个节点
    struct skipListNode *subLayer;  //指向跳跃表的下一层节点
    void(*freeValFun)(void* value); //这个是跳跃表节点值的释放指针
}; 

typedef struct skipListLevelHead {   //这里每层增加了一个头节点
    
	struct skipListNode *next; 
	int    nodeNum; 
	struct skipListLevelHead *subLayer; 
	struct skipListLevelHead *upLayer; 
}*skipList; 

struct skipListLevelHead *createSkipList() ;
bool insertValue(struct skipListLevelHead **slhead,int key ,void *value, void(*freevaluefunction)(void*));
bool deleteValue(struct skipListLevelHead **slhead,int key ) ; 
void* searchKey(struct skipListLevelHead *slhead, int key);
void destoryLinkList(struct skipListLevelHead *slhead) ; 
#endif 