#ifndef SKIP_LIST_H
#define SKIP_LIST_H
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define MIN_INT               -0xFFFF
#define SKIPLEVEL_THRESHOLD   5
struct skipListNode{

    int value ; 
    struct skipListNode *next    ;  //ָ����һ���ڵ�
    struct skipListNode *subLayer;  //ָ����Ծ�����һ��ڵ�
}; 

typedef struct skipListLevelHead {   //����ÿ��������һ��ͷ�ڵ�
    
	struct skipListNode *next; 
	int    nodeNum; 
	struct skipListLevelHead *subLayer; 
	struct skipListLevelHead *upLayer; 
}*skipList; 
struct skipListLevelHead *createSkipList() ;
bool insertValue(struct skipListLevelHead **slhead,int value ); 
bool deleteValue(struct skipListLevelHead **slhead,int value) ; 
void destoryLinkList(struct skipListLevelHead *slhead) ; 

#endif 