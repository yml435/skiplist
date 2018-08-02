#include"skipList.h"
#include<iostream>

void testsubLayerPonter(skipList list) {

    bool searchedValue[1024] = { false };

    while (list != NULL) {
        
        struct skipListNode *node = list->next; 
        while (node != NULL) {
            if (searchedValue[node->key] == true) {
                node = node->next; 
                continue; 
            }
            std::cout << node->key << ","; 
            struct skipListNode * subnode = node->subLayer; 
            while (subnode != NULL) {
                std::cout << subnode->key << ",";
                assert(node->key == subnode->key);
                subnode = subnode->subLayer; 
            }
            searchedValue[node->key] = true; 
            std::cout << std::endl; 
            node = node->next;         
        }
        list = list->subLayer; 
    }
}

void printSkipList(skipList list) {

    int levelCount = 0; 
    while (list != NULL) {
        
        levelCount++; 
        std::cout << "第 " << levelCount << " 层" << std::endl; 
        struct skipListNode *node = list->next; 
        while (node != NULL) {
            
            std::cout << node->key << ", "; 
            assert( node->key == *((int*)(node->value))); 
            node = node->next; 
        }
        std::cout << std::endl; 
   
        list = list -> subLayer;
    } 
}
void freeValue(void *value) {
    free(value);
}
int main(){
	skipList listPointer = (createSkipList()); 
    skipList *list = &listPointer;
    for (int i = 0; i < 100; i++) {
        int *insertVal = new int(i); 
        insertValue(list, i, insertVal, freeValue);
    }
    printSkipList(*list);
    testsubLayerPonter(*list);
    for (int i = 0; i < 90; i++) {
        deleteValue(list, i);
    }
    printSkipList(*list);
    testsubLayerPonter(*list);
    destoryLinkList(*list);
}
