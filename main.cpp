#include"skipList.h"
#include<iostream>
#include<string.h>
#include <cstdlib>
#include <ctime>
void testsubLayerPonter(skipList list) {

    int *searchedValue = new int[100000];
    memset(searchedValue, 0, sizeof(int) * 100000);
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
    clock_t start_time, end_time;
	skipList listPointer = (createSkipList()); 
    skipList *list = &listPointer;
    start_time = clock();
    for (int i = 0; i < 10000; i++) {
        int *insertVal = new int(i); 
        insertValue(list, i, insertVal, freeValue);
    }
    end_time = clock();
    std::cout << "创建消耗时间: " << (double)(end_time - start_time) / CLOCKS_PER_SEC << std::endl;
    /*printSkipList(*list);
    testsubLayerPonter(*list);
    for (int i = 0; i < 9000; i++) {
        deleteValue(list, i);
    }
    printSkipList(*list);
    testsubLayerPonter(*list);
    destoryLinkList(*list);*/

    start_time = clock();
    for (int i = 0; i < 10000; i++) {
        searchKey(*list, i);    
    }
    end_time = clock(); 
    std::cout << "查询消耗时间: " << (double)(end_time - start_time) / CLOCKS_PER_SEC << std::endl;
}
