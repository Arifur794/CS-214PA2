#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sorted-list.h"


 // Creates and allocates space for sorted list. initializing front, nxt, and ptrNum.
 
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df) {
    SortedListPtr SortedL = (SortedListPtr)malloc(sizeof(SortedList));
    SortedL->CompareFuncT = (CompareFuncT)malloc(sizeof(CompareFuncT));
    SortedL->CompareFuncT = cf;
    SortedL->DestructFuncT = (DestructFuncT)malloc(sizeof(DestructFuncT)); 
    SortedL->DestructFuncT = df;
    SortedL->front = (SortedListPtr)malloc(sizeof(SortedListPtr));
    SortedL->front = NULL;
    SortedL->nxt = (SortedListPtr)malloc(sizeof(SortedListPtr));
    SortedL->nxt = NULL;
    SortedL -> ptrNum = 0;
    return SortedL;
}

//Will insert nodes into sorted list or create a front for new sorted list. Returns 1 if successful, 0 otherwise. greatest to smallest order.
 
int SLInsert(SortedListPtr list, void *newObj) {

    SortedListPtr temporary = (SortedListPtr) malloc(sizeof(SortedList));

    temporary->dat = newObj;
    temporary->ptrNum+=1;
   
    if (list->front == NULL) {
        list->front = temporary;
        return 1;
    }
    else {
        if (list->CompareFuncT(list->front->dat, newObj) < 0) { //obj greater than front
            temporary->nxt = list->front;
            list->front = temporary;
            return 1;
        }
        else if (list->CompareFuncT(list->front->dat, newObj) == 0) {  //front and newObj is equal no need to insert dat
            return 0;
        }
        else if (list->CompareFuncT(list->front->dat, newObj) > 0 && list->front->nxt == NULL) { //front greater than
            list->front->nxt = temporary;
            return 1;
        }
        else {
            SortedListPtr current = list->front; //front pointing
            SortedListPtr previous = NULL; 
            while (current->nxt != NULL) {
                int comp = list->CompareFuncT(current->nxt->dat, newObj); //result of comparison
                previous = current; //replace pointers
                if (comp < 0) { //less than 

                    temporary->nxt = previous->nxt;
                    previous->nxt = temporary;
                    return 1;
                }
                else if (comp == 0) { //dat is equal
                    return 0;
                }
                else { //when current->nxt's dat is more than 
                    if (current->nxt->nxt == NULL) { 
                        current->nxt->nxt = temporary; 
                        return 1;
                    }
                    else { 
                        current = current->nxt; //continuing loop for next pointer
                    }
                }
            }
            return 0;
        }
    }
}

//return 1 if remove is succesful 0 otherwise
int SLRemove(SortedListPtr list, void *newObj) {
    if (list->front == NULL) { 
        return 0; 
    }
    else { 
        if (list->CompareFuncT(list->front->dat, newObj) < 0) { //front dat less than 
            return 0; 
        }
        else if (list->CompareFuncT(list->front->dat, newObj) == 0) {  
            if (list->front->nxt == NULL) { //is there anything after front
                if (list->front->ptrNum == 1) {      
                    list->DestructFuncT(list->front);
                }
                list->front = NULL; 
                return 1;
            }
            else { //Is something after front
                SortedListPtr temporary = list->front;
                list->front = list->front->nxt; //item after front becomes new front
                temporary->ptrNum-=1;
                if (temporary->ptrNum == 0) {            
                    list->DestructFuncT(temporary);
                }
                else {
                    list->front->ptrNum+=1;
                }
                return 1;
            }
        }
        else { //when the front's dat is greater than the new object
            if (list->front->nxt == NULL) { 
                return 0; 
            }
            else { 
                SortedListPtr current = list->front; //direct front
                SortedListPtr previous = NULL; //previous pointer
                while (current->nxt != NULL) { 
                    int comp = list->CompareFuncT(current->nxt->dat, newObj); //result of comparison is stored
                    SortedListPtr temporary = current->nxt;
                    previous = current; /* previous pointer becomes currentent pointer*/
                    if (comp < 0) { 
                        return 0; 
                    }
                    else if (comp == 0) { 
                        previous->nxt = previous->nxt->nxt; 
                        temporary->ptrNum-=1;
                        if (temporary->ptrNum==0) {
                            list->DestructFuncT(temporary);
                        }
                        else if (temporary->nxt != NULL) {
                                temporary->nxt->ptrNum+=1;      //if its not null, incrememnt ptr. 
                        }
                        return 1;
                    }
                    else { 
                        if (current->nxt->nxt == NULL) { 
                            return 0; 
                        }
                        else { 
                            current = current->nxt; 
                        }
                    }
                }
            }
            return 0;
        }
    }
}
//when list exists and there is a front, sorted list iterator created, ptrNum will increment by 1

SortedListIteratorPtr SLCreateIterator (SortedListPtr list) {
    SortedListIteratorPtr iter;
    
    if (list == NULL || list->front == NULL) 
        return NULL;
    else {
        iter = (SortedListIteratorPtr) malloc(sizeof(struct SortedListIterator));
        iter->DestructFuncT = (DestructFuncT)malloc(sizeof(DestructFuncT));
        iter->DestructFuncT = list->DestructFuncT;
        iter->nodeCurr = list->front;
        iter->nodeCurr->ptrNum+=1;
    }
    return iter;
}
//this goes to the node in the list that the given iterator is pointing to.  Will return 0 if it doesn't exist else the dat

void* SLGetItem(SortedListIteratorPtr iter) {
    SortedListPtr temporary = iter->nodeCurr;
    if (temporary == NULL){
        return 0;
    }
    else { 
        return temporary->dat;
    }
}


void * SLNextItem(SortedListIteratorPtr iter) {
    SortedListPtr temporary = iter->nodeCurr;
    if (temporary->nxt == NULL) {          
        iter->nodeCurr = NULL;
        temporary->ptrNum-=1;
        if (temporary->ptrNum == 0)
            iter->DestructFuncT(temporary);
        return NULL;
    }
    else {
        iter->nodeCurr = temporary->nxt;
        iter->nodeCurr->ptrNum+=1;
        temporary->ptrNum-=1;
        if (temporary->ptrNum == 0){
            iter->nodeCurr->ptrNum-=1;
            iter->DestructFuncT(temporary);
        }
        return iter->nodeCurr->dat;
    }
}

/*
 *  this will destroy a sorted list when called.
 */
void SLDestroy(SortedListPtr list) {
    free(list);
}

/*
 * this will destroy an iterator when called.
 */
void SLDestroyIterator(SortedListIteratorPtr iter) {
    free(iter);
}