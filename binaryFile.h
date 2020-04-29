#ifndef __BINARY_FILE__H__
#define __BINARY_FILE__H__

#include "customErrorClass.h"
#include "dataStructs.h"
#include "list.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class binaryFile {
    
    public:
        binaryFile(void);
        void readData(string);
        bool findEmployee(int, int);
        string getEmployeeDetails(int, int);
        bool updateEmployeeName(int, int);
        
        string getDepartment(int);

        /*
        void outputData(s_EMPLOYEE[], int);
        void findEmployeeOutput(e_DEPT, int);
        string departmentString(Department);
        void getEmployeeDetailsOutput(e_DEPT, int);
        void updateEmployeeNameOutput(s_EMPLOYEE);
        */

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