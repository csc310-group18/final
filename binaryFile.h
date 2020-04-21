#ifndef __BINARY_FILE__H__
#define __BINARY_FILE__H__

#include "customErrorClass.h"
#include <iostream>
#include <fstream>

typedef enum Department{
    ACCOUNTING,
    BUSINESS,
    HUMAN_RESOURCES,
    SALES,
    PRODUCTION
}e_DEPT;

typedef struct Employee{
    e_DEPT department;
    int number;
    string name;
}s_EMPLOYEE;

class binaryFile{
    
    public:
        binaryFile(void);
        void readData(string);
        void sortData(void);
        bool findEmployee(e_DEPT, int);
        s_EMPLOYEE getEmployeeDetails(e_DEPT, int);
        bool updateEmployeeName(s_EMPLOYEE);

    private:
        string binaryFileName;

        void p_ReadData(fstream&);
        void p_SortData(void);
        int  p_FindEmployee(e_DEPT, int);
        s_EMPLOYEE p_GetEmployeeDetails(e_DEPT, int);
        bool p_UpdateEmployeeName(s_EMPLOYEE);
};

#endif