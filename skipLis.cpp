#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct skipListNode *mallocSkipListNode(){
    
    struct skipListNode * sklist = ( struct skipListNode*)malloc( sizeof(struct skipListNode));
    if ( sklist == NULL){
        assert ( sklist == NULL);
        return NULL ; 
    }
    memset( (char*)sklist,0,sizeof(struct skipListNode));
    return sklist; 
}
struct skipListLevelHead *mallocSkipListHead(){
    
    struct skipListLevelHead * slhead = ( struct skipListLevelHead*)malloc( sizeof(struct skipListLevelHead));
    if (slhead == NULL){
        assert( slhead ==NULL );
        return NULL ; 
    }
    slhead -> nxt = NULL; 
    slhead -> nodeNum = 0; 
    slhead -> subLayer = NULL; 
    slhead -> upLayer = NULL; 
    return slhead ; 
    
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
bool freeSkipListHead (struct skipListLevelHead *slhead){
    
    if (slhead == NULL ){
        return false ; 
    }
    free(slhead);
    return true; 
}

struct skipListLevelHead *createSkipList(){
    
    return  mallocSkipListHead();     
}

bool liftNodes( struct skipListLevelHead *slhead , struct skipListNode *insertNode ){
    
    if ( isLiftNode()){
        
        return false; 
    }
    int skiplevelCount = 1; //因为这个跳跃表的层次至少为 1  
    if ( slhead == NULL ) {
        
        return false ; 
    }
    struct skipListLevelHead *headnode = slhead ; 
    struct skipListNode *subnode = insertNode ;  //保存下一层新增的节点 
    while( headnode -> subLayer != NULL ){   //计算跳跃表层数

        headnode = headnode -> subLayer ; 
    }
    /*
        这里的基本方法是从最底层开始提升新插入的节点，每个层都要提升
        这里是在已经有的跳跃层里面进行提升，这种情况下就只需要在新的
        层级里面建立新的跳跃节点就可以了。
    */
    while ( headnode != slhead ) { //处理至少两层的情况,因为这里在已经存在的表层里面提升
        
        headnode = headnode -> upLayer ; 
        struct skipListNode *node = headnode->next;  
        struct skipListNode *pre  = node; 
        while(node -> value <= insertNode -> value){

            pre = node; 
            node = node -> next; 
        }
        struct skipListNode *newnode = mallocSkipListNode(); 
        newnode -> subLayer = subnode; 
        newnode -> value = insertNode -> value; 
        pre -> next = newnode; 
        newnode -> next = node; 
        headnode -> nodeNum ++ ; 
        subnode = newnode; 
    }
    //这里开始提升新的跳跃层，如果最上层的节点数目大于SKIPLEVEL_THRESHOLD
    
    if ( slhead -> nodeNum > SKIPLEVEL_THRESHOLD ){
        
        struct skipListLevelHead *levelhead = mallocSkipListHead(); 
        levelhead -> subLayer = slhead ; 
        levelhead -> subLayer -> upLayer = levelhead ; 
        struct skipListNode *downnode = slhead -> next ;
        struct skipListNode *pre = levelhead -> next; 
        while (downnode != NULL ){
            
            if ( isLiftNode() == false ){
                downnode = downnode -> next ; 
                continue ; 
            }
            struct *newnode = mallocSkipListNode(); 
            newnode -> value = downnode -> value ; 
            newnode -> subLayer = downnode; 
            if ( levelhead -> next == NULL ){
                
                levelhead -> next = newnode ;
            } else {
                pre -> next = newnode ; 
            }
            levelhead -> nodeNum ++ ; 
            pre = newnode ; 
            downnode = downnode -> next; 
        }
        
    }
}

bool insertValue(struct skipListLevelHead *slhead,int value ){
    
    if (slhead  == NULL ){
        return false; 
    }
    struct skipListNode * insertNode = mallocSkipListNode();
    insertNode -> value = value; 
    
    if (slhead -> next == NULL ){ //对空的跳跃表的处理
        
        slhead -> next = insertNode ; 
        slhead -> nodeNum ++ ; 
        liftNodes(slhead,insertNode); 
        return true; 
    }
    struct skipListLevelHead *levelhead = slhead; 
    struct skipListNode * pre = levelhead -> next ; 
    struct skipListNode * node = pre; 
    while( node -> subLayer != NULL ){  //因为插入是插入到最底层，最底层的长度肯定比上面长度要长的
        while (( node != NULL )&&( node -> value <= value )){
            pre = node ;  
            node = node -> next; 
        }
        node = pre -> subLayer ; 
        levelhead = levelhead -> subLayer; 
    } 
    
    while (( node != NULL )&&( node -> value <= value )){  //这里是对最底层的操作 
        pre = node ; 
        node = node -> next; 
    }
    insertNode -> next = node;
    pre -> next = insertNode; 
    levelhead -> nodeNum ++ ;
    liftNodes(slhead,insertNode); 
    
    return true; 
}

bool deleteValue(struct skipListLevelHead *slhead,int value){
    
    if (slhead == NULL || *slhead == NULL ){
        return false; 
    }
    struct skipListNode *node = slhead -> next; 
    
    while( node -> subLayer != NULL ){
        while( node != NULL ){
            
            if ( node -> value == value ){
                if ( node == *slhead ){ //头节点的特殊处理
                    
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
                    node = *slhead; 
                }else{ //处理非头节点
                
                    struct skipListNode *nextnode = node ; //这个地方和下面的算法有关
                    if (node -> next != NULL ){
                        while (node != NULL ){
                            
                            struct skipListNode *tmp = node->next; 
                            node -> value = tmp -> value; 
                            node -> next = tmp -> next; 
                            node -> subLayer = tmp -> subLayer; 
                            node = node -> subLayer ; 
                            freeSkipListNode(tmp);
                        }
                        node = nextnode; 
                    }else{ //最后一个节点
                        struct skipListNode *levelhead = *slhead;  
                        while (node !=NULL ){
                            
                            struct skipListNode *pre = levelhead; 
                            while ( pre -> next != node ){
                                pre = pre -> next; 
                            }
                             = NULL; 
                            node = node -> subLayer; 
                            freeSkipListNode(pre -> next); 
                            pre -> next = NULL; 
                            levelhead = levelhead -> subLayer; 
                        }
                        node = NULL; 
                    } 
                }
            }
        }
    }
} 

void destoryLinkList(struct skipListNode *list_node){
    
    if (list == NULL ){
        return ; 
    }
    skipListNode *nxtsl_node= list -> next ;
    freeSkipListNode(list_node) ;
    destoryLinkList(nxtsl_node) ; 
}


