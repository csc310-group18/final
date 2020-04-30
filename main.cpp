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

            bool employeeUpdated = false;
            bool localNameChanged = false;

            // Update employee name
            try{
                // Change employee name in local struct
                localNameChanged = binaryFile::stringToCharArray(employee, "Hello World");

                // Update the binary file
                if( localNameChanged == true ){
                    employeeUpdated = records.updateEmployeeName(employee);
                }

            }catch(myException &e){
                cerr<<e.what()<<endl;
            }

            // Print results
            if( employeeUpdated ){

                cout<<"Employee updated"<<endl;

                // Uncomment to confirm update to binary file
                /*
                updatedEmployee = records.getEmployeeDetails(employeeDept, employeeNum);
                printEmployeeDetails(updatedEmployee);
                */

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