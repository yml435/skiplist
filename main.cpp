#include"skipList.h"
#include<iostream>

void testsubLayerPonter(skipList list) {

    bool searchedValue[1024] = { false };

    while (list != NULL) {
        
        struct skipListNode *node = list->next; 
        while (node != NULL) {
            if (searchedValue[node->value] == true) {
                node = node->next; 
                continue; 
            }
            std::cout << node->value << ","; 
            struct skipListNode * subnode = node->subLayer; 
            while (subnode != NULL) {
                std::cout << subnode->value << ",";
                assert(node->value == subnode->value);
                subnode = subnode->subLayer; 
                
            }
            searchedValue[node->value] = true; 
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
            
            std::cout << node->value << ", "; 
            node = node->next; 
        }
        std::cout << std::endl; 
   
        list = list -> subLayer;
    } 
}
int main(){
	skipList listPointer = (createSkipList()); 
    skipList *list = &listPointer;
    for (int i =0 ; i< 100 ;i++)
	    insertValue(list, i); 
    
    //printSkipList(*list);
    testsubLayerPonter(*list);

}
