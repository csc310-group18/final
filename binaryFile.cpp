#include "binaryFile.h"
#include "list.h"
#include "customErrorClass.h"

/**************************** PUBLIC: Constructor ****************************/
binaryFile::binaryFile() {
    binaryFileName = "";
    numEmployees = 0;
    departments = new list[NUM_DEPARTMENTS];
}

/*******************************************************************/

/**************************** PUBLIC: readData ****************************/
void binaryFile::readData(string inputFileName) {

    fstream inputFile;
    binaryFileName = inputFileName.substr(0, inputFileName.find(".")) + "_binary.txt";

    inputFile.open(inputFileName, ios::in);
    
    // Create binary file with input txt file data
    if (inputFile.is_open()) {
        try {

            // Read records from txt file into department lists
            p_ReadData(inputFile);
            
            // Sort each linked list
            p_SortData();      

            // Write each list to binary file
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
    else {

        throw myException("Cannot open input file. File does not exist.", ERROR);
    }




}

/**************************** PUBLIC: sortData ****************************/
/*
void binaryFile::sortData(){

    bool retValue = false;

    try{

        p_SortData();
    }
    catch( myException &exc ){

        throw(exc.what(), exc.retrieveCode());
    }

}
*/

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
    
    string inputLine; // buffer for each line in txt file
    int commaArray[2], i = 0, employeeNum = 0, employeeDept = 0;
    string employeeName;
    s_EMPLOYEE newEmployee; 

    // Read records into their department's linked list 
    while (getline(inputFile, inputLine)) {
        commaArray[0] = inputLine.find(",");
        commaArray[1] = inputLine.find(",", commaArray[0]+1);

        employeeDept = atoi(inputLine.substr(0, commaArray[0]).c_str());
        employeeNum = atoi(inputLine.substr(commaArray[0]+1, commaArray[1]-1).c_str());
        employeeName = inputLine.substr(commaArray[1]+1, inputLine.length());

        if (employeeName.length() > MAX_NAME_LENGTH) {
            throw myException( "Employee name exceeds 30 characters", ERROR);
        } else if (employeeDept < 0 || employeeDept >= NUM_DEPARTMENTS) {
            throw myException( "Department number is invalid", ERROR);
        } else {
            numEmployees++;

            newEmployee.department = e_DEPT(employeeDept);
            newEmployee.number = employeeNum;
            employeeName.copy(newEmployee.name, employeeName.size());
            newEmployee.name[employeeName.size()] = '\0';
            
            try {
                departments[employeeDept].appendEmployee(newEmployee);
            }
            catch (myException &e){
                cout << e.what() << endl;
            }
        }
    }
}

/**************************** PRIVATE: p_PrintArray ****************************/
void binaryFile::p_PrintArray(s_EMPLOYEE *arr) {
    int i = 0;
    for ( i = 0; i < numEmployees; i++ ){
        cout<<arr[i].department<<" ";
        cout<<arr[i].number<<" ";

        for (int x = 0; x < (int) strlen(arr[i].name); x++)
            cout << arr[i].name[x];
        cout << endl;
        //cout<<arr[i].name<<endl;
    }
}

/**************************** PRIVATE: p_WriteBinary ****************************/
void binaryFile::p_WriteBinary(){
    fstream outputFile;
    outputFile.open(binaryFileName, ios::out|ios::binary);

    if(outputFile.is_open()) {

        int i = 0, j = 0;

        for (i = 0; i < NUM_DEPARTMENTS; i++) {
            if (&departments[i] != nullptr) {
                try {
                    list *currDept = &departments[i];
                    s_NODE *currNode;
                    s_EMPLOYEE currEmployee; // s_EMPLOYEE struct buffer

                    // traverse through each department linked list
                    for (currNode = currDept->getHead(); currNode != nullptr; currNode = currNode->next) {
                        
                        // get s_EMPLOYEE struct from each list s_NODE
                        currEmployee = currNode->employee;

                        // write employeeBuffer to binary file
                        outputFile.write((char*)&currEmployee, sizeof(s_EMPLOYEE));
                    }
                    // deallocate list when finished writing binary
                    currDept->deleteList(); 

                }
                catch(myException &exc) {
                    throw (exc.what(), exc.retrieveCode());
                }
            }
        }

        outputFile.close();
    }
    else {
        throw myException("Cannot open ouput file.", ERROR);
    }
}

/**************************** PRIVATE: p_ReadBinary ****************************/
void binaryFile::p_ReadBinary() {
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
    else {
        throw myException("Cannot open binary file.", ERROR);
    }

}

/**************************** PRIVATE: p_SortData ****************************/
void binaryFile::p_SortData() {

    int i = 0;
    for (i = 0; i < NUM_DEPARTMENTS; i++) {

        list *currDept;
        currDept = &departments[i];
        if (currDept == nullptr) {
            cout << "Department " << e_DEPT(i) << " is empty." << endl;

        } else if (currDept->isSorted() == 1) {
            cout << "Department " << e_DEPT(i) << " already sorted." << endl;
        }
        else {
            cout << "Sorting department: " << e_DEPT(i) << endl;
            currDept->sortList();
        }

    }
}

/**************************** PRIVATE: p_FindEmployee ****************************/
int binaryFile::p_FindEmployee(e_DEPT department, int number) {
    
    int retOffset = -1;

    return retOffset;
}

/**************************** PRIVATE: p_GetEmployeeDetails ****************************/
s_EMPLOYEE binaryFile::p_GetEmployeeDetails(e_DEPT department, int number) {
   
    s_EMPLOYEE retEmployee;

    return retEmployee;
}

/**************************** PRIVATE: p_UpdateEmployeeName ****************************/
bool binaryFile::p_UpdateEmployeeName(s_EMPLOYEE employee) {

    bool retValue = false;

    return retValue;
}

