#ifndef SKIP_LIST_H
#define SKIP_LIST_H
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define SKIPLEVEL_THRESHOLD   20

struct skipListNode{

    int key ; 
    void *value; 
    struct skipListNode *next    ;  //ָ����һ���ڵ�
    struct skipListNode *subLayer;  //ָ����Ծ�����һ��ڵ�
    void(*freeValFun)(void* value); //�������Ծ��ڵ�ֵ���ͷ�ָ��
}; 

typedef struct skipListLevelHead {   //����ÿ��������һ��ͷ�ڵ�
    
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