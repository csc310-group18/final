#ifndef __LIST__H__
#define __LIST__H__

#include <iostream>
#include "dataStructs.h"

using namespace std;

class list
{
    public:
        list();
        ~list();
        int deleteList();
        int appendEmployee(s_EMPLOYEE);
        int printList();
        void sortList();
        int getTotalNodes();
        int isSorted();

        node *getHead();

    private:
        // variables
        s_NODE *p_Head;
        s_NODE *p_Tail;

        int p_TotalNodes;
        int p_IsSorted;

        // methods
        s_NODE *p_CreateNode(s_EMPLOYEE);
        s_NODE *p_GetHead();
        s_NODE *p_GetTail();
        int p_InsertNode(s_EMPLOYEE);
        int p_DeleteList();
        int p_DeleteNode(s_NODE*);
        int p_InsertionSort();

};

#endif