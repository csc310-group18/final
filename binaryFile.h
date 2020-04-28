#ifndef __BINARY_FILE__H__
#define __BINARY_FILE__H__

#include "customErrorClass.h"
#include "dataStructs.h"
#include "list.h"
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

class binaryFile {
    
    public:
        binaryFile(void);
        void readData(string);
        bool findEmployee(e_DEPT, int);
        s_EMPLOYEE getEmployeeDetails(e_DEPT, int);
        bool updateEmployeeName(s_EMPLOYEE);

        static void findEmployeeOutput(binaryFile, e_DEPT, int);
        static string departmentString(Department);
        static void getEmployeeDetailsOutput(binaryFile, e_DEPT, int);
        static void updateEmployeeNameOutput(binaryFile, s_EMPLOYEE);

    private:
        string binaryFileName;
        int numEmployees;
        list *departments;
        s_EMPLOYEE *dataArray; // created with binary file data
        int * indexArray;

        void p_ReadData(fstream&);
        void p_PrintArray(s_EMPLOYEE*);
        void p_WriteBinary();
        void p_ReadBinary();
        void p_SortData(void);
        int  p_FindEmployee(e_DEPT, int);
        s_EMPLOYEE p_GetEmployeeDetails(e_DEPT, int);
        bool p_UpdateEmployeeName(s_EMPLOYEE);

        
};

#endif