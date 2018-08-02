
#include "skipList.h"

struct skipListNode *mallocSkipListNode(){
    
    struct skipListNode * sklist = ( struct skipListNode*)malloc( sizeof(struct skipListNode));
    if ( sklist == NULL){
        assert ( sklist == NULL);
        return NULL ; 
    }
    sklist -> next = NULL ; 
    sklist -> key = 0; 
    sklist -> subLayer = NULL ; 
    sklist -> freeValFun = NULL; 
    return sklist; 
}
struct skipListLevelHead *mallocSkipListHead(){
    
    struct skipListLevelHead * slhead = ( struct skipListLevelHead*)malloc( sizeof(struct skipListLevelHead));
    if (slhead == NULL){
        assert( slhead ==NULL );
        return NULL ; 
    }
    slhead -> next = NULL; 
    slhead -> nodeNum = 0; 
    slhead -> subLayer = NULL; 
    slhead -> upLayer = NULL; 
    return slhead ; 
    
}
bool isLiftNode(){
    int randVal = rand(); 
    if (randVal % 2 == 0) {
        return true; 
    }
    else {
        return false;  
    }
}


bool freeSkipListNode(struct skipListNode * slNode){
    
	if (slNode == NULL) {
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

bool liftNodes( struct skipListLevelHead **slhead , struct skipListNode *insertNode ){
    
    if ( isLiftNode() == false ){
        
        return false; 
    }
    
    if ( slhead == NULL || *slhead == NULL ) {
        
        return false ; 
    }
    struct skipListLevelHead *headnode = *slhead ; 
    struct skipListNode *subnode = insertNode ;  //保存下一层新增的节点 
    while( headnode -> subLayer != NULL ){      //获得最底层的跳跃层

        headnode = headnode -> subLayer ; 
    }
    /*
        这里的基本方法是从最底层开始提升新插入的节点，每个层都要提升
        这里是在已经有的跳跃层里面进行提升，这种情况下就只需要在新的
        层级里面建立新的跳跃节点就可以了。
    */
    while ( headnode != *slhead ) { //处理至少两层的情况,因为这里在已经存在的表层里面提升
        
        headnode = headnode -> upLayer ; 
        struct skipListNode *node = headnode->next;  
        struct skipListNode *pre  = node; 
        while(node && node -> key <= insertNode -> key){
            pre = node; 
            node = node -> next; 
        }
        struct skipListNode *newnode = mallocSkipListNode(); 
        newnode -> subLayer = subnode; 
        newnode -> key = insertNode -> key; 
        newnode -> value = insertNode -> value; 
        pre -> next = newnode; 
        newnode -> next = node; 
        headnode -> nodeNum ++ ; 
        subnode = newnode; 
    }
    //这里开始提升新的跳跃层，如果最上层的节点数目大于SKIPLEVEL_THRESHOLD
    
    if ( (*slhead) -> nodeNum > SKIPLEVEL_THRESHOLD ){
        
        struct skipListLevelHead *levelhead = mallocSkipListHead(); 
        levelhead -> subLayer = *slhead ; 
        levelhead -> subLayer -> upLayer = levelhead ; 
        struct skipListNode *downnode = (*slhead) -> next ;
        struct skipListNode *pre = levelhead -> next; 
        while (downnode != NULL ){
            if ( isLiftNode() == false ){
                downnode = downnode -> next ; 
                continue ; 
            }
	        struct  skipListNode  *newnode = mallocSkipListNode(); 
            newnode -> key = downnode -> key ; 
            newnode -> value = downnode ->value; 
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
        *slhead = levelhead; 
    }
}

bool insertValue(struct skipListLevelHead **slhead,int key ,void *value, void(*freevaluefunction)(void* )){
    
    if (slhead  == NULL || *slhead == NULL){
        return false; 
    }
    struct skipListNode * insertNode = mallocSkipListNode();
    insertNode -> freeValFun = freevaluefunction;
    insertNode -> key = key; 
    insertNode -> value = value; 
    if ((*slhead) -> next == NULL ){ //对空的跳跃表的处理
        
        (*slhead) -> next = insertNode ; 
        (*slhead) -> nodeNum ++ ; 
        liftNodes(slhead,insertNode); 
        return true; 
    }
    struct skipListLevelHead *levelhead = *slhead; 
    struct skipListNode * pre = levelhead -> next ; 
    struct skipListNode * node = pre; 
    while( node -> subLayer != NULL ){  //因为插入是插入到最底层，最底层的长度肯定比上面长度要长的
        while (( node != NULL )&&( node -> key <= key )){
            pre = node ;  
            node = node -> next; 
        }
        node = pre -> subLayer ; 
        levelhead = levelhead -> subLayer; 
    } 
    
    while (( node != NULL )&&( node -> key <= key )){  //这里是对最底层的操作 
        pre = node ; 
        node = node -> next; 
    }
    insertNode -> next = node;
    pre -> next = insertNode; 
    levelhead -> nodeNum ++ ;
    liftNodes(slhead,insertNode); 
    
    return true; 
}

bool deleteValue(struct skipListLevelHead **slhead,int key){
    
    if (slhead == NULL ){
        return false; 
    }
    struct skipListLevelHead * levelhead = *slhead ; 
    struct skipListNode * node = (*slhead) -> next ; 
    struct skipListNode * pre = node ; 
    while ( node != NULL ){
        
        if ( node -> key  > key ){
            pre = pre -> subLayer ; 
            node = pre ; 
            levelhead = levelhead -> subLayer; 
        }else if ( node -> key == key ){
            break; 
        }else {
            pre = node ; 
            node = node -> next ; 
        }
    }
    while ( node != NULL && node -> key == key ){
        
        struct skipListNode * freenode = node ; 
        if (pre == node  ) { //说明是首节点
            
            levelhead -> next = node -> next ;
            node = node -> subLayer ; 
            pre = node ;  
        }else {
            
            pre -> next = node -> next; 
            node = node -> subLayer ; 
            pre  = pre -> subLayer; 
        }
        if (freenode->freeValFun != NULL) {
            freenode->freeValFun(freenode->value);
        }
        freeSkipListNode(freenode); 
        /*
        if (levelhead -> next == NULL ){ //说明存在空的头节点了
            
            if (levelhead -> upLayer != NULL ){
                levelhead -> upLayer -> subLayer = levelhead -> subLayer ; 
            }
            if (levelhead -> subLayer != NULL ){
                levelhead -> subLayer -> upLayer = levelhead -> upLayer ; 
            }
        }*/
        levelhead = levelhead -> subLayer ; 
    }
    while ((*slhead)->next == NULL) {
        struct skipListLevelHead * head = (*slhead);
        (*slhead) = (*slhead)->subLayer; 
        freeSkipListHead(head); 
    }
    return true; 
} 
void destorySkipList(struct skipListNode* sknode ){
    
    if (sknode == NULL ){
        return ; 
    }
    skipListNode * nxtsknode = sknode -> next ; 
    if (sknode->freeValFun != NULL) {
        sknode->freeValFun(sknode->value);
    }
    freeSkipListNode(sknode); 
    destorySkipList(nxtsknode); 
}
void destoryLinkList(struct skipListLevelHead *sklist){
    
	if (sklist == NULL) {
        return ; 
    }
    struct skipListLevelHead *levelhead = sklist ; 
    while ( levelhead != NULL ){
        
        destorySkipList(levelhead -> next ); 
	    levelhead = levelhead -> subLayer; 
    }
}

void* searchKey(struct skipListLevelHead *slhead, int key) {

    if (slhead == NULL) {
        return NULL;
    }
    void *searchedVal = NULL; 
    struct skipListLevelHead * levelhead = slhead;
    struct skipListNode * node = slhead ->next;
    struct skipListNode * pre = node;

    while (node != NULL) {

        if (node->key  > key) {
            pre = pre->subLayer;
            node = pre;
            levelhead = levelhead->subLayer;
        }
        else if (node->key == key) {
            searchedVal =  node->value;
        }
        else {
            pre = node;
            node = node->next;
        }
    }
    return searchedVal;
}