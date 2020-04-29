#include <iostream>
#include "binaryFile.h"
#include "customErrorClass.h"
#include <fstream>

using namespace std;

void printEmployeeDetails(s_EMPLOYEE employee);

int main(int argc, char *argv[]){

    string mainDataFilename = "";

    // Get file name for employee data
    if (argc == 2) {
        mainDataFilename = argv[1]; // from command line arg if present
    } 
    else {
        mainDataFilename = "data/smallOutput.txt"; 
        //mainDataFilename = "data/mediumOutput.txt";
        //mainDataFilename = "data/largeOutput.txt";
        //mainDataFilename = "data/largeOutput_unsorted.txt";
    }

    // Read data from txt file
    binaryFile records;
    try{
        records.readData(mainDataFilename);  // all employee records
    }catch(myException &e){
        cerr<<e.what()<<endl;
    }

    // Open test records file
    string testRecordsFilename;
    testRecordsFilename = mainDataFilename.substr(0, mainDataFilename.find(".")) + "_TestRecords.txt";
    fstream testRecordsFile;
    testRecordsFile.open(testRecordsFilename, ios::in);
    
    // Exit if test records file failed to open
    if( testRecordsFile.is_open() == false ){
        string msg = "Could not open <" + testRecordsFilename + "> for reading";
        myException e = myException(msg, SYSTEM_FAILURE);
        cerr << e.what() <<endl;
        exit(1);
    }

    // Get number of employees from test Data
    int numEmployees = 0;
    testRecordsFile >> numEmployees;

    // Output results from each test record
    int i = 0;
    int employeeDept = 0, employeeNum = 0;
    string employeeName = "";
    s_EMPLOYEE employee;
    s_EMPLOYEE updatedEmployee;

    for( i = 0; i < numEmployees; i++ ){
        testRecordsFile >> employeeDept;
        testRecordsFile >> employeeNum;

        // Search for employee record
        bool employeeFound = false;
        employeeFound = records.findEmployee(employeeDept, employeeNum);
    
        if( employeeFound ){

            cout<<"Employee found"<<endl;
            
            // Store employee details in local struct
            employee = records.getEmployeeDetails(employeeDept, employeeNum);

            // Print employee details
            if( &employee.name != nullptr ){
                printEmployeeDetails(employee);
            }
            
            // Change characters of employee name in local struct
            bool employeeUpdated = false;
            try{
                int x = 0;
                for( x = 0; x < strlen(employee.name); x++ ){
                    employee.name[x] = 'A';
                }
            }catch(exception &e){
                cerr<<e.what()<<endl;
            }

            // Pass locally updated struct to class
            employeeUpdated = records.updateEmployeeName(employee);

            // Print results
            if( employeeUpdated ){

                cout<<"Employee updated"<<endl;

                // Get updated employee from binary file
                updatedEmployee = records.getEmployeeDetails(employeeDept, employeeNum);

                // Uncomment to print employee details again to make sure update worked
                // printEmployeeDetails(employee);

            } else {
                cout<<"Employee not updated"<<endl;
            }
            
        } else {
            cout<<"Employee not found"<<endl;
        }

        cout<<"------------------------------"<<endl;

    }

    return 0;
}

void printEmployeeDetails(s_EMPLOYEE employee){
    // Print employee details
    if ( &employee.name != nullptr ){
        cout<<"*******EMPLOYEE DETAILS*******"<<endl;
        cout<<"\tDepartment: "<<binaryFile::getDepartmentString(employee.department)<<endl;
        cout<<"\tEmployee Number: "<<employee.number<<endl;
        cout<<"\tEmployee Name: "<<binaryFile::charArrayToString(employee.name)<<endl;
    } else {
        cout<<"Employee structure invalid"<<endl;
    }
}

