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

class binaryFile{
    
    public:
        binaryFile(void);
        ~binaryFile(void);
        void readData(string);
        bool findEmployee(int, int);
        s_EMPLOYEE getEmployeeDetails(int, int);
        bool updateEmployeeName(s_EMPLOYEE);

        static int getMaxNameLength(void);
        static string getDepartmentString(int);
        static string charArrayToString(char[]);
        static bool stringToCharArray(s_EMPLOYEE &employee, string);

    private:
        string binaryFileName; 
        int numEmployees; // track total employee count
        list* departments; // array of lists for temporary storage before writing binary 
        s_EMPLOYEE *dataArray; // used for testing binary > array functionality
        int* indexArray; // track start of each department in binary file

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