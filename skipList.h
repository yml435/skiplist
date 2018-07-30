#ifndef SKIP_LIST_H
#define SKIP_LIST_H


#define MIN_INT  -0xFFFF

struct skipListNode{

    int value ; 
    struct skipListNode *next    ;  //指向下一个节点
    struct skipListNode *subLayer;  //指向跳跃表的下一层节点
}; 

struct skipListLevelHead{   //这里每层增加了一个头节点
    
    struct skipListNode *nxt; 
    int    nodeNum ; 
    struct skipListLevelHead *subLayer; 
    struct skipListLevelHead *upLayer; 
}; 
struct skipListNode *createSkipList() ;
bool insertValue(struct skipListNode *slhead,int value ) ;
bool deleteValue(struct skipListNode **slhead,int value) ; 
void destoryLinkList(struct skipListNode *list_node) ; 

#endif 