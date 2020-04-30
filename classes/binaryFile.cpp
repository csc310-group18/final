#include "binaryFile.h"
#include "list.h"
#include "customErrorClass.h"


/**************************** PUBLIC: Constructor ****************************/
binaryFile::binaryFile(){
    binaryFileName = "";
    numEmployees = 0;
    departments = new list[NUM_DEPARTMENTS];
}

/**************************** PUBLIC: Destructor ****************************/
binaryFile::~binaryFile(){
    int i = 0;
    for( i = 0; i < NUM_DEPARTMENTS; i++ ){
        if( &departments[i] != nullptr ){
            list *currDept = &departments[i];
            currDept->deleteList();
        }
    }
}

/*****************************************************************************************/
/*                                   PUBLIC FUNCTIONS                                    */
/*****************************************************************************************/

/**************************** PUBLIC: readData ****************************/
void binaryFile::readData(string inputFileName){

    fstream inputFile;
    binaryFileName = inputFileName.substr(0, inputFileName.find(".")) + "_binary.txt";

    inputFile.open(inputFileName, ios::in);
    
    // Create binary file with input txt file data
    if( inputFile.is_open() ){
        try{

            // Read records from txt file into department lists
            p_ReadData(inputFile);

            // Sort each linked list
            p_SortData();      

            // Write each list to binary file
            p_WriteBinary(); 

            // Uncomment to test binary > array functionality
            /*
            p_ReadBinary();
            p_PrintArray(dataArray);
            */

        } catch(myException &exc){
            throw exc;
        }
    } else {
        throw myException("Cannot open input file. File does not exist.", SYSTEM_FAILURE);
    }

}

/**************************** PUBLIC: findEmployee ****************************/
bool binaryFile::findEmployee(int department, int number){

    int retOffset = -1;
    bool retValue = false;

    try{

        retOffset = p_FindEmployee(e_DEPT(department), number);
    } catch(myException &exc){

        throw exc;
    }

    if( retOffset == -1 ){
        
        retValue = false;
    } else {

        retValue = true;
    }

    return retValue;
}

/**************************** PUBLIC: getEmployeeDetails ****************************/
s_EMPLOYEE binaryFile::getEmployeeDetails(int department, int number){
    
    s_EMPLOYEE retEmployee;

    try{
        retEmployee = p_GetEmployeeDetails(e_DEPT(department), number);
        
    } catch(myException &exc){

        throw exc;
    }

    return retEmployee;
}

/**************************** PUBLIC: getTotalEmployees ****************************/
int binaryFile::getTotalEmployees(){
    
    return this->numEmployees;
}

/**************************** PUBLIC: updateEmployeeName ****************************/
bool binaryFile::updateEmployeeName(s_EMPLOYEE employeeToUpdate){

    bool retValue = false;
    
    try{
        retValue = p_UpdateEmployeeName(employeeToUpdate);

    } catch(myException &exc){
        
        throw exc;
    }
    
    return retValue;
}

/*****************************************************************************************/
/*                                  PRIVATE FUNCTIONS                                    */
/*****************************************************************************************/

/**************************** PRIVATE: p_ReadData ****************************/
void binaryFile::p_ReadData(fstream &inputFile){
    
    string inputLine; // buffer for each line in txt file
    int commaArray[2], i = 0, employeeNum = 0, employeeDept = 0;
    string employeeName;
    s_EMPLOYEE newEmployee; 

    // Read records into their department's linked list 
    while( getline(inputFile, inputLine) ){
        commaArray[0] = -1;
        commaArray[1] = -1;
        commaArray[0] = inputLine.find(",");
        commaArray[1] = inputLine.find(",", commaArray[0]+1);

        if( commaArray[0] == -1 || commaArray[1] == -1 ){
            
            string failure = "";
            string commaErr = "Could not convert employee record from text to binary (line must have 2 commas).";
            failure += commaErr;

            if( newEmployee.number ){
                string lastEmployeeMsg = "Last employee to convert: " + to_string(newEmployee.number);
                failure += " " + lastEmployeeMsg;
            }
            throw myException(failure, SYSTEM_FAILURE);

        } else {
            
            employeeName = "";
            employeeNum = -1, employeeDept = -1;

            employeeDept = atoi(inputLine.substr(0, commaArray[0]).c_str());
            employeeNum = atoi(inputLine.substr(commaArray[0]+1, commaArray[1]-1).c_str());
            employeeName = inputLine.substr(commaArray[1]+1, inputLine.length());

            try{
                if( employeeDept < 0 || employeeDept >= NUM_DEPARTMENTS ){

                    string msg = "Failed to add employee " + to_string(employeeNum) + " (department number is invalid)";
                    throw myException(msg, ERROR);
                    
                } else if( employeeName.length() > MAX_NAME_LENGTH ){

                    string msg = "Failed to add employee " + to_string(employeeNum) + " (name exceeds 30 characters)";
                    throw myException(msg, ERROR);

                } else if( employeeNum < 0 ){

                    string msg = "Failed to add employee (employee number less than 0)";
                    throw myException(msg, ERROR);

                } else {


                    newEmployee.department = e_DEPT(employeeDept);
                    newEmployee.number = employeeNum;
                    employeeName.copy(newEmployee.name, employeeName.size()); // copy input string to char array
                    newEmployee.name[employeeName.size()] = '\0'; // terminate char array
                    
                    departments[employeeDept].appendEmployee(newEmployee);

                    numEmployees++; // keep track of total employee count

                    if( employeeName.length() == 0 ){
                        string msg = "Employee " + to_string(employeeNum) + " added with no name";
                        throw myException(msg, WARNING);
                    }
                    
                }
            } catch(myException &e){
                if( e.retrieveCode() >= 3 ){
                    throw e;
                } else{
                    cout<<e.what()<<endl;
                }
            }
        }

    }
}

/**************************** PRIVATE: p_PrintArray ****************************/
void binaryFile::p_PrintArray(s_EMPLOYEE *arr ){
    int i = 0;
    for(  i = 0; i < numEmployees; i++ ){
        cout<<arr[i].department<<" ";
        cout<<arr[i].number<<" ";

        for( int x = 0; x < (int) strlen(arr[i].name); x++)
            cout<<arr[i].name[x];
        cout<<endl;
    }
}

/**************************** PRIVATE: p_WriteBinary ****************************/
void binaryFile::p_WriteBinary(){

    fstream outputFile;
    outputFile.open(binaryFileName, ios::out|ios::binary);

    if( outputFile.is_open() ){

        int i = 0, j = 0;

        indexArray =  new int [NUM_DEPARTMENTS];

        for( i = 0; i < NUM_DEPARTMENTS; i++ ){
            // record current position in the file as the index for the current department
            indexArray[i] = outputFile.tellp();

            if( &departments[i] != nullptr ){
                try{
                    list *currDept = &departments[i];
                    s_NODE *currNode;
                    s_EMPLOYEE currEmployee; // s_EMPLOYEE struct buffer

                    // traverse through each department linked list
                    for( currNode = currDept->getHead(); currNode != nullptr; currNode = currNode->next ){
                        
                        // get s_EMPLOYEE struct from each list s_NODE
                        currEmployee = currNode->employee;

                        // write employeeBuffer to binary file
                        outputFile.write((char*)&currEmployee, sizeof(s_EMPLOYEE));
                    }
                    // deallocate list when finished writing binary
                    currDept->deleteList(); 

                }
                catch(myException &exc ){
                    throw exc;
                }
            }
        }

        outputFile.close();
    } else {
        throw myException("Cannot open ouput file.", ERROR);
    }
}

/**************************** PRIVATE: p_ReadBinary ****************************/
void binaryFile::p_ReadBinary(){
    fstream dataFile;

    // Initialize array
    dataArray = new s_EMPLOYEE[numEmployees];

    // Open file
    dataFile.open(binaryFileName, ios::in|ios::binary);
    
    // Read binary data into dataArray
    if( dataFile.is_open() ){
         try{

            dataFile.read((char*)dataArray, sizeof(s_EMPLOYEE) * numEmployees);
            dataFile.close();
        } catch(myException &exc){

            throw exc;
        }
    } else {
        throw myException("Cannot open binary file.", ERROR);
    }

}

/**************************** PRIVATE: p_SortData ****************************/
void binaryFile::p_SortData(){

    int i = 0;
    for( i = 0; i < NUM_DEPARTMENTS; i++ ){

        list *currDept;
        currDept = &departments[i];

        if( currDept == nullptr ){
            //throw myException("Department list is empty");
            //cout<< "Department " << e_DEPT(i) << " is empty" <<endl;
            return;

        } else if (currDept->isSorted() == 1 ){
            //throw myException("Department already sorted");
            //cout<< "Department " << e_DEPT(i) << " already sorted" <<endl;
            return;
        } else {
            //cout<< "Sorting department: " << e_DEPT(i) <<endl;
            currDept->sortList();
        }
    }
}

/**************************** PRIVATE: p_FindEmployee ****************************/
int binaryFile::p_FindEmployee(e_DEPT department, int number){
    
    fstream dataFile;
    s_EMPLOYEE tempEmployee;
    int retOffset = -1;
    int tempOffset;
    dataFile.open(binaryFileName, ios::in|ios::binary);
    

    if( dataFile.is_open() ){
        // Use index to move to the appropriate spot for the department
        dataFile.seekg(indexArray[(int)department]);
        
        // Record the current position in the file and read the first employee
        tempOffset = dataFile.tellp();
        dataFile.read((char*)&tempEmployee, sizeof(s_EMPLOYEE));
        
        // Check each employee in the department until the employee number found
        // or the current employee number is greater than the employee number
        while( !dataFile.eof() && tempEmployee.department == department 
                && tempEmployee.number <= number &&  retOffset == -1 ){
            
            // If employee is found, record the current offset as the offset to return
            if( tempEmployee.number == number ){
                retOffset = tempOffset;
            }

            // Record the current position in the file and read employee structure
            tempOffset = dataFile.tellp();
            dataFile.read((char*)&tempEmployee, sizeof(s_EMPLOYEE));
        }

    }

    dataFile.close();

    return retOffset;
}

/**************************** PRIVATE: p_GetEmployeeDetails ****************************/
s_EMPLOYEE binaryFile::p_GetEmployeeDetails(e_DEPT department, int number){
   
    fstream dataFile;
    s_EMPLOYEE retEmployee;
    int offset;
    
    // Retrieve the offset in the file for the employee 
    offset = p_FindEmployee(department, number);

    // Move to the appropriate position in file using offest and read in employee 
    if( offset >=  0 ){
        dataFile.open(binaryFileName, ios::in|ios::binary);
        dataFile.seekg(offset, ios::beg);
        dataFile.read((char*)&retEmployee, sizeof(s_EMPLOYEE));  
    } else {
        throw myException("Cannot get employee details. Employee does not exist.", WARNING);
    }

    return retEmployee;
}

/**************************** PRIVATE: p_UpdateEmployeeName ****************************/
bool binaryFile::p_UpdateEmployeeName(s_EMPLOYEE employee){

    fstream dataFile;
    bool retValue = false;
    int offset; 
    
    // Retrieve the offset in the file for the employee 
    offset = p_FindEmployee(employee.department, employee.number);

    // Move to the appropriate position in file using offest and write in employee with updated name
    if( offset != -1 ){
        
        dataFile.open(binaryFileName, ios::in|ios::out|ios::binary);

        if( dataFile.is_open() ){
            dataFile.seekp(offset, ios::beg);
            dataFile.write((char*)&employee, sizeof(s_EMPLOYEE));
            retValue = true;
        }
        dataFile.close();
    }    

    return retValue;
}

/*****************************************************************************************/
/*                                   STATIC FUNCTIONS                                    */
/*****************************************************************************************/

/**************************** STATIC: charArrayToString ****************************/
string binaryFile::charArrayToString(char employeeName[]){

    string name = "";

    if( &employeeName != nullptr ){

        int nameLength = 0;
        nameLength = strlen(employeeName);

        int i = 0;
        for( i = 0; i < nameLength; i++ ){
            name += employeeName[i];
        }
    }
    return name;
}

/**************************** STATIC: getTotalDepartments ****************************/
int binaryFile::getTotalDepartments(){
    
    return NUM_DEPARTMENTS;
}

/**************************** STATIC: getDepartmentString ****************************/
string binaryFile::getDepartmentString(int deptNum){
    
    string departmentString[] = {"ACCOUNTING", "BUSINESS", "HUMAN RESOURCES", "SALES", "PRODUCTION"};
    
    if( deptNum >= 0 && deptNum < binaryFile::getTotalDepartments() ){
        return departmentString[deptNum];
    } else {
        throw myException("Department number out of range", ERROR);
    }
}

/**************************** STATIC: getMaxNameLenght ****************************/
int binaryFile::getMaxNameLength(){

    return MAX_NAME_LENGTH;
}

/**************************** STATIC: stringToCharArray ****************************/
bool binaryFile::stringToCharArray(s_EMPLOYEE &employee, string newName){

    int maxLength = 0;
    maxLength = binaryFile::getMaxNameLength();
    
    if( newName.length() > maxLength ){
        throw myException("New name must be 30 characters or less.", ERROR);
    }

    try{
        int x = 0;

        // Zero out the current name
        for( x = 0; x < maxLength; x++ ){
            employee.name[x] = '\0';
        }

        // Add string to char array in employee struct
        for( x = 0; x < newName.length(); x++ ){
            employee.name[x] = newName[x];
        }

    } catch(exception &e){
        throw myException(e.what(), ERROR);
        return false;
    }

    return true;
}
