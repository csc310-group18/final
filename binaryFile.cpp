#include "binaryFile.h"

/**************************** PUBLIC: Constructor ****************************/
binaryFile::binaryFile(){
    binaryFileName = "";
    numEmployees = 0;
}

/*******************************************************************/

/**************************** PUBLIC: readData ****************************/
void binaryFile::readData(string inputFileName){

    fstream inputFile;
    binaryFileName = inputFileName.substr(0, inputFileName.find(".")) + "_binary.txt";

    inputFile.open(inputFileName, ios::in);
    
    // Create binary file with input txt file data
    if( inputFile.is_open() ){
        try{

            // Read records from txt file into employeeArray
            p_ReadData(inputFile);

            // Print employeeArray
            //p_PrintArray(employeeArray);

            // Write records from employeeArray to binary file
            p_WriteBinary(); 

            // Read records from binary file into dataArray
            p_ReadBinary(); 

            // Print dataArray
            p_PrintArray(dataArray);
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

    string inputLine;

    // Scan file to determine number of records
    while( getline(inputFile, inputLine) ){
        numEmployees++;
    }

    // Return file pointer to start of file
    inputFile.clear();
    inputFile.seekg(0,ios::beg);

    // Create array to store employees
    employeeArray = new s_EMPLOYEE[numEmployees];

    // Read records into employee array
    int commaArray[2], i = 0, inputLineNumber = 0, inputLineDept = 0;
    string inputLineName;

    while( getline(inputFile, inputLine) ){
        commaArray[0] = inputLine.find(",");
        commaArray[1] = inputLine.find(",", commaArray[0]+1);

        inputLineDept = atoi(inputLine.substr(0, commaArray[0]).c_str());
        inputLineNumber = atoi(inputLine.substr(commaArray[0]+1, commaArray[1]-1).c_str());
        inputLineName = inputLine.substr(commaArray[1]+1, inputLine.length());

        // Add record to employee array 
        // if name is 30 characters or less
        if( inputLineName.length() <= 30 ){
            employeeArray[i].department = e_DEPT(inputLineDept);
            employeeArray[i].number = inputLineNumber;
            employeeArray[i].name = inputLineName;
        }else{
            // reduce employee count
            numEmployees--;
        }

        i++;
    }
}

/**************************** PRIVATE: p_PrintArray ****************************/
void binaryFile::p_PrintArray(s_EMPLOYEE *arr){
    int i = 0;
    for ( i = 0; i < numEmployees; i++ ){
        cout<<arr[i].department<<" ";
        cout<<arr[i].number<<" ";
        cout<<arr[i].name<<endl;
    }
}

/**************************** PRIVATE: p_WriteBinary ****************************/
void binaryFile::p_WriteBinary(){
    fstream outputFile;
    outputFile.open(binaryFileName, ios::out|ios::binary);

    if( outputFile.is_open() ){
         try{

            outputFile.write((char*)employeeArray, sizeof(s_EMPLOYEE) * numEmployees);
            outputFile.close();
        }
        catch( myException &exc ){

            throw (exc.what(), exc.retrieveCode());
        }
    }
    else{

        throw myException("Cannot open ouput file.", ERROR);
    }
}

/**************************** PRIVATE: p_ReadBinary ****************************/
void binaryFile::p_ReadBinary(){
    fstream dataFile;

    // Create data array to store binary data
    dataArray = new s_EMPLOYEE[numEmployees];

    dataFile.open(binaryFileName, ios::in|ios::binary);

    if( dataFile.is_open() ){
         try{

            dataFile.read((char*)dataArray, sizeof(s_EMPLOYEE) * numEmployees);
            dataFile.close();
        }
        catch( myException &exc ){

            throw (exc.what(), exc.retrieveCode());
        }
    }
    else{

        throw myException("Cannot open binary file.", ERROR);
    }

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