#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sorted-list.h"

//testing the insert
void testingProgram (SortedListPtr tester,void* pointer1) {
    if(SLInsert(tester,pointer1) == 1) {
        printf("INSERTED\n");
    }
    else
        printf("NOT INSERTED\n");
}

//testing the remove
void testingProgram2 (SortedListPtr tester,void* pointer1) {
    if(SLRemove(tester,pointer1) == 1) {
        printf("REMOVED\n");
    }
    else
        printf("NOT REMOVED\n");
}

int stringCompare(void* vist1, void* vist2) {
    char* sist1 = (char *)vist1;
    char* sist2 = (char *)vist2;
    return strcmp(sist1, sist2);
}




int compareDubs(void* b1, void* b2) {
    double* g1 = (double*)b1;
    double* g2 = (double*)b2;

    if (*g1 < *g2)
        return -1;
    else if (*g1 > *g2)
        return 1;
    else return 0;
}

void destroyDubs(void* ptr){
    free(ptr);
}


void stringDestroy(void* ptr){
   free(ptr);
}




void printSL(SortedListPtr ptr) {
    SortedListPtr curr = ptr->front;
    while (curr != NULL) {
        printf("%G\n",*(double*)curr->dat);
        curr = curr->nxt;
    }
    return;
}

void printSL2(SortedListPtr ptr) {
    SortedListPtr curr = ptr->front;
    while (curr != NULL) {
        printf("%s\n", (char*)curr->dat);
        curr = curr->nxt;
    }
    return;
}

int main() {
//mem alloc for dubs
    double* test1 = (double*)malloc(sizeof(double)); double* test2 = (double*)malloc(sizeof(double));double* test3 = (double*)malloc(sizeof(double));
    double* test4 = (double*)malloc(sizeof(double));
    
    *test1 = 7.8; *test2 = 27.9; *test3 = 7.9; *test4 = 42.4;

    void* pointer1 = test1; void* pointer2 = test2;  void* pointer3 = test3;
    void* pointer4 = test4;

    SortedListPtr tester = SLCreate(compareDubs, destroyDubs);

    testingProgram(tester,pointer1);testingProgram(tester,pointer2);
    testingProgram(tester,pointer1);testingProgram(tester,pointer2);
    testingProgram(tester,pointer3); testingProgram(tester,pointer4);
    testingProgram(tester,pointer3);
    
    printSL(tester);

    SortedListIteratorPtr SortedL = SLCreateIterator (tester);
    printf("FIRST NODE IS: %G\n",*(double*)SortedL->nodeCurr->dat);
    
    SLNextItem(SortedL);
    printf("SECOND NODE IS: %G\n",*(double*)SortedL->nodeCurr->dat);

    char* test5 = (char*)malloc(sizeof(char)); char* test6 = (char*)malloc(sizeof(char));
    char* test7 = (char*)malloc(sizeof(char)); char* test8 = (char*)malloc(sizeof(char));
    
    test5 = "jello";
    test6 = "apple";
    test7 = "pharmacy";
    test8 = "zoo";

    void* pointer5 = test5;
    void* pointer6 = test6;
    void* pointer7 = test7;
    void* pointer8 = test8;

    SortedListPtr tester2 = SLCreate(stringCompare, stringDestroy);

    testingProgram(tester2,pointer5);
    testingProgram(tester2,pointer6);
    testingProgram(tester2,pointer7);
    testingProgram(tester2,pointer8);
    testingProgram(tester2,pointer8);

    printSL2(tester2);
    SortedListIteratorPtr StringIter = SLCreateIterator (tester2);

    printf("Iterator Test %s\n",(char*)SLGetItem(StringIter));
    printf("Iterator Test %s\n",(char*)SLNextItem(StringIter));
    printf("Iterator Test %s\n",(char*)SLNextItem(StringIter));
    
    testingProgram2(tester2,pointer5);

    printf("Testing Iterator on Node that was removed %s\n",(char*)SLGetItem(StringIter));

    printSL2(tester2);
    SLNextItem(StringIter);

    SLDestroy(tester);
    SLDestroy(tester2);

    SLDestroyIterator(SortedL);
    SLDestroyIterator(StringIter);
    return 0;
}