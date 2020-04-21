#include "binaryFile.h"

/**************************** PUBLIC: Constructor ****************************/
binaryFile::binaryFile(){
    binaryFileName = "";
}

/*******************************************************************/

/**************************** PUBLIC: readData ****************************/
void binaryFile::readData(string inputFileName){
   
    fstream inputFile;
    inputFile.open(inputFileName, ios::in);
    
    if( inputFile.is_open() ){
        try{

            p_ReadData(inputFile);
        }
        catch( myException &exc ){

            throw (exc.what(), exc.retrieveCode());
        }
    }
    else{

        throw myException("Cannot open input file. File does not exist.", ERROR);
    }
}

/**************************** PUBLIC: sortData ****************************/
void binaryFile::sortData(){

    bool retValue = false;

    try{

        p_SortData();
    }
    catch( myException &exc ){

        throw(exc.what(), exc.retrieveCode());
    }

}

/**************************** PUBLIC: findEmployee ****************************/
bool binaryFile::findEmployee(e_DEPT department, int number){

    int retOffset = -1;
    bool retValue = false;

    try {

        retOffset = findEmployee(department, number);
    }
    catch( myException &exc ){

        throw myException(exc.what(), exc.retrieveCode());
    }

    if ( retOffset == -1 ){
        
        retValue = false;
    }
    else{

        retValue = true;
    }

    return retValue;
}

/**************************** PUBLIC: getEmployeeDetails ****************************/
s_EMPLOYEE binaryFile::getEmployeeDetails(e_DEPT department, int number){
    
    s_EMPLOYEE retEmployee;

    if ( findEmployee(department, number) ){

        try{

            retEmployee = p_GetEmployeeDetails(department, number);
        }
        catch( myException &exc ){

            throw myException(exc.what(), exc.retrieveCode());
        }
    }
    else{

        throw myException("Cannot get employee details. Employee does not exist.");
    }

    return retEmployee;
}

/**************************** PUBLIC: updateEmployeeName ****************************/
bool binaryFile::updateEmployeeName(s_EMPLOYEE employee){

    bool retValue = false;

    try{

        retValue = p_UpdateEmployeeName(employee);
    }
    catch( myException &exc ){
        
        throw myException(exc.what(), exc.retrieveCode());
    }
    
    return retValue;
}

/*******************************************************************/

/**************************** PRIVATE: p_ReadData ****************************/
void binaryFile::p_ReadData(fstream &inputFile){

}

/**************************** PRIVATE: p_SortData ****************************/
void binaryFile::p_SortData(){

}

/**************************** PRIVATE: p_FindEmployee ****************************/
int binaryFile::p_FindEmployee(e_DEPT department, int number){
    
    int retOffset = -1;

    return retOffset;
}

/**************************** PRIVATE: p_GetEmployeeDetails ****************************/
s_EMPLOYEE binaryFile::p_GetEmployeeDetails(e_DEPT department, int number){
   
    s_EMPLOYEE retEmployee;

    return retEmployee;
}

/**************************** PRIVATE: p_UpdateEmployeeName ****************************/
bool binaryFile::p_UpdateEmployeeName(s_EMPLOYEE employee){

    bool retValue = false;

    return retValue;
}