
#ifndef __DATA_STRUCTS__H__
#define __DATA_STRUCTS__H__

#include <string>
#include <iostream>

using namespace std;

#define NUM_DEPARTMENTS 5
#define MAX_NAME_LENGTH 30

typedef enum Department {
    ACCOUNTING,
    BUSINESS,
    HUMAN_RESOURCES,
    SALES,
    PRODUCTION
} e_DEPT;

typedef struct Employee {
    e_DEPT department; 
    int number; 
    char name[MAX_NAME_LENGTH+1]; 
} s_EMPLOYEE;

typedef struct node {
    s_EMPLOYEE employee;    
    node *next;
    node *previous;
} s_NODE;

#endif