#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
struct skipListNode *mallocSkipListNode(){
    
    struct skipListNode * sklist= (struct skipListNode*)malloc(sizeof(struct skipListNode));
    if (sklist == NULL){
        assert (sklist == NULL);
        return NULL ; 
    }
    memset((char*)sklist,0,sizeof(struct skipListNode);
    return sklist; 
}

bool isLiftNode(){
    
    return (rand()%2) == 1 ? true : false ; 
}


bool freeSkipListNode(struct skipListNode * slNode){
    
    if (skNode == NULL){
        return false ; 
    }
    free(slNode);
    return true; 
}

struct skipListNode *createSkipList(int value){
    
    struct skipListNode *skNode = mallocSkipListNode(); 
    
    skNode -> nodeCounts = 1;  //作为开头节点这个值>=1
    skNode -> next = NULL; 
    skNode -> subLayer = NULL; 
    skNode -> value = value; 
    
    return skNode; 
}

bool liftNodes( struct skipListNode *head , struct skipListNode *insertNode ){
    
    int skiplevelCount = 1; //因为这个跳跃表的层次至少为 1  
    if ( head == NULL ) {
        
        return false ; 
    }
    struct skipListNode *skipLevelHead = head; //跳跃层各起始节点
    struct skipListNode *headnode = skipLevelHead; 
    struct skipListNode *subNode = insertNode ;  //保存下一层新增的节点 
    while( headnode ->next != NULL ){ //计算跳跃表层数
    
        skiplevelCount ++ ; 
        headnode = headnode -> subLayer ; 
    }
    headnode = skipLevelHead ; 
    //这个是在已经有的层里面进行提升
    while ( skiplevelCount > 1 ) {
        
        int skiptolevelCount = skiplevelCount; 
        while( skiptolevelCount > 1 ){
            
            skiptolevelCount --; 
            headnode = headnode -> subLayer; 
        }
        if ( isLiftNode() == false ){ //是否提升该节点
        
            return true ; 
        }
        struct skipListNode *node = headnode;  //这里开始找
        struct skipListNode *pre  = node; 
        while(node -> value <= insertNode -> value){
            
            pre = node; 
            node = node -> next; 
        }
        struct skipListNode *newNode = mallocSkipListNode(); 
        newNode -> value = insertNode -> value; 
        newNode -> next = node ; 
        newNode -> subLayer = subNode ; 
        pre -> next = newNode ;  
        
        subNode = newNode ; 
        skiplevelCount -- ; 
    }
    //提升新的跳跃层
    headnode = head; 
    while( headnode -> next == NULL ){
        
        struct skipListNode *node = headnode; 
        struct skipListNode *pre = node; 
        struct skipListNode *uphead = NULL; 
        struct skipListNode *preNode = NULL;  
        bool  headLifted = false; 
        while( node != NULL ){
            
            if ( isLiftNode() ){
                if ( node == headnode ){
                    
                    headLifted = true; 
                    uphead = mallocSkipListNode(); 
                    uphead -> subLayer = headnode; 
                    uphead -> value = headnode -> value;
                    preNode = uphead;                  
                    
                }else {
                    if ( headLifted == false ){
                        
                        uphead = mallocSkipListNode(); 
                        uphead -> subLayer = headnode; 
                        uphead -> value = headnode -> value;
                        preNode = uphead;  
                    }
                    struct skipListNode *newnode = mallocSkipListNode(); 
                    newnode -> value = node -> value; 
                    newnode -> subLayer = node ; 
                    preNode -> next = newnode; 
                    preNode = newnode; 
                }
            }
            pre = node; 
            node = node -> next; 
        }
        if (preNode == NULL ){
            break; 
        }else{
            
            headnode = uphead; 
        }
    }
}

bool insertValue(struct skipListNode *slhead,int value ){
    
    if (slhead == NULL ){
        return false; 
    }
    struct skipListNode * pre = slhead ; 
    struct skipListNode * node = pre; 
    while( node -> subLayer != NULL ){
        //这一层一直走到该插入位置
        while (( node != NULL )&&( node -> value <= value )){
            pre = node ;  
            node = node -> next; 
        }
        node = pre -> subLayer ; 
    } 
    
    while (( node != NULL )&&( node -> value <= value )){ //这里是对最底层的操作 
        pre = node ; 
        node = node -> next; 
    }
  
    struct skipListNode * insertNode = mallocSkipListNode();
    insertNode -> value = value; 
    insertNode -> next = node; 
    insertNode -> subLayer = NULL; 
    
    pre -> next = insertNode; //插入这个新的节点
    
    liftNodes(slhead,insertNode); //这里就是提升节点,是否产生新的跳跃层等
    
    return true; 
}

bool deleteValue(struct skipListNode **slhead,int value){
    
    if (slhead == NULL || *slhead == NULL ){
        return false; 
    }
    struct skipListNode *pre = *slhead; 
    struct skipListNode *node = pre; 
    
    while( node -> subLayer != NULL ){
        while( node != NULL ){
            
            if ( node -> value == value ){
                if ( node == *slhead ){ //头的特殊处理
                
                    struct skipListNode *sklevelhead = (*slhead) -> subLayer; 
                    struct skipListNode *tmp = *slhead ; 
                    struct skipListNode *preskhead = *slhead; 
                    (*slhead) = tmp -> next; 
                    freeSkipListNode(tmp);
                    while( sklevelhead != NULL ){
                        
                        tmp = sklevelhead -> next; 
                        preskhead -> subLayer = sklevelhead ; 
                        sklevelhead = sklevelhead -> subLayer ; 
                    }
                }else{
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                }
            }
            
            
            
            pre = node ; 
            node = node -> next; 
        }
        
        
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
} 















