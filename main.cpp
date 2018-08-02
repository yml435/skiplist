#include"skipList.h"
#include<iostream>
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
    
    printSkipList(*list);

}
