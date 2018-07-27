#ifndef SKIP_LIST_H
#define SKIP_LIST_H

struct skipListNode{
    
    int value ; 
    int nodeCounts ;      // 这个值只有在作为跳跃表每层第一个节点时只有用
    struct skipListNode *next    ;  //指向下一个节点
    struct skipListNode *subLayer;  //指向跳跃表的下一层节点
}; 

struct skipListNode *createSkipList() ;
bool insertValue(struct skipListNode *slhead,int value ) ;
    













#endif 