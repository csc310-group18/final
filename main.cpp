#include <iostream>
#include <iomanip>
#include "binaryFile.h"
#include "customErrorClass.h"

using namespace std;

void smallOutput(binaryFile records){
    //TEST DATA        
    s_EMPLOYEE employees[] = {{ ACCOUNTING     , 45731, "Leona"   }, { BUSINESS       , 37503, "Briar"   }, 
                              { HUMAN_RESOURCES, 58509, "Kailey"  }, { SALES          , 58510, "Liv"     },
                              { PRODUCTION     , 44258, "Anthony" }, { ACCOUNTING     , 18738, "Hunter"  },
                              { BUSINESS       , 63006, "Annabel" }, { HUMAN_RESOURCES, 757  , "Layton"  }, 
                              { SALES          , 68263, "Maxim"   }, { PRODUCTION     , 65898, "Rex"     }};
    int i, numEmployees = 10;
    
    // FIND EMPLOYEE
    cout << endl << "========================================" << endl
                 << "FIND EMPLOYEE" << endl
                 << "========================================" << endl;
    for( i = 0; i < numEmployees; i++){
        cout << left << setw(8) << employees[i].name << ": " ;
        binaryFile::findEmployeeOutput(records, employees[i].department, employees[i].number);
    }
    
    // GET EMPLOYEE DETAILS
    cout << endl << "========================================" << endl
                 << "GET EMPLOYEE DETAILS" << endl
                 << "========================================" << endl;
    for( i = 0; i < numEmployees; i++ ){
        cout << left << setw(8) << employees[i].name << ": " ;
        binaryFile::getEmployeeDetailsOutput(records, employees[i].department, employees[i].number);
    }

    // UPDATE EMPLOYEE NAME
    cout << endl << "========================================" << endl
                 << "UPDATE EMPLOYEE NAME" << endl
                 << "========================================" << endl;
    for( i = 0; i < numEmployees; i++ ){
        cout << left << setw(8) << employees[i].name << ": " ;
        strcat(employees[i].name,"NEW"); 
        binaryFile::updateEmployeeNameOutput(records, employees[i]);   
    }
}

void mediumOutput(binaryFile records){
    // TEST DATA
    s_EMPLOYEE employees[] = {{ ACCOUNTING     , 243013, "Amina"   }, { BUSINESS       , 135016, "Dax"     },
                              { HUMAN_RESOURCES, 15013 , "Kaleb"   }, { SALES          , 105013, "Violeta" },
                              { PRODUCTION     , 297008, "Huxley"  }, { ACCOUNTING     , 139708, "Benicio" },
                              { BUSINESS       , 250506, "Amari"   }, { HUMAN_RESOURCES, 206998, "Cory"    },
                              { SALES          , 6011  , "Zariyah" }, { PRODUCTION     , 243119, "Mariana" }};

    int i, numEmployees = 10;

    // FIND EMPLOYEE
    cout << endl << "========================================" << endl
                 << "FIND EMPLOYEE" << endl
                 << "========================================" << endl;
    for( i = 0; i < numEmployees; i++){
        cout << left << setw(8) << employees[i].name << ": " ;
        binaryFile::findEmployeeOutput(records, employees[i].department, employees[i].number);
    }
    
    // GET EMPLOYEE DETAILS
    cout << endl << "========================================" << endl
                 << "GET EMPLOYEE DETAILS" << endl
                 << "========================================" << endl;
    for( i = 0; i < numEmployees; i++ ){
        cout << left << setw(8) << employees[i].name << ": " ;
        binaryFile::getEmployeeDetailsOutput(records, employees[i].department, employees[i].number);
    }

    // UPDATE EMPLOYEE NAME
    cout << endl << "========================================" << endl
                 << "UPDATE EMPLOYEE NAME" << endl
                 << "========================================" << endl;
    for( i = 0; i < numEmployees; i++ ){
        cout << left << setw(8) << employees[i].name << ": " ;
        strcat(employees[i].name,"NEW"); 
        binaryFile::updateEmployeeNameOutput(records, employees[i]);   
    }
}

void largeOutput(binaryFile records){
    // TEST DATA
    s_EMPLOYEE employees [] = {{ ACCOUNTING     , 205009, "Isabelle" }, { BUSINESS       , 25013, "Amiya"     }, 
                               { HUMAN_RESOURCES, 189715, "Donald"   }, { SALES          , 155012, "Virginia" }, 
                               { PRODUCTION     , 430017, "Magnolia" }, { ACCOUNTING     , 205508, "Meadow"   }, 
                               { BUSINESS       , 335014, "Crosby"   }, { HUMAN_RESOURCES, 430013, "Clara"    }, 
                               { SALES          , 5014  , "Watson"   }, { PRODUCTION     , 433415, "Kyler"    }};
    int i, numEmployees = 10;

    // FIND EMPLOYEE
    cout << endl << "========================================" << endl
                 << "FIND EMPLOYEE" << endl
                 << "========================================" << endl;
    for( i = 0; i < numEmployees; i++){
        cout << left << setw(8) << employees[i].name << ": " ;
        binaryFile::findEmployeeOutput(records, employees[i].department, employees[i].number);
    }
    
    // GET EMPLOYEE DETAILS
    cout << endl << "========================================" << endl
                 << "GET EMPLOYEE DETAILS" << endl
                 << "========================================" << endl;
    for( i = 0; i < numEmployees; i++ ){
        cout << left << setw(8) << employees[i].name << ": " ;
        binaryFile::getEmployeeDetailsOutput(records, employees[i].department, employees[i].number);
    }

    // UPDATE EMPLOYEE NAME
    cout << endl << "========================================" << endl
                 << "UPDATE EMPLOYEE NAME" << endl
                 << "========================================" << endl;
    for( i = 0; i < numEmployees; i++ ){
        cout << left << setw(8) << employees[i].name << ": " ;
        strcat(employees[i].name,"NEW"); 
        binaryFile::updateEmployeeNameOutput(records, employees[i]);   
    }
}

int main(int argc, char *argv[]){

    binaryFile records;
    string filename;

    // Get data file name
    if (argc == 2) {
        filename = argv[1];
    } 
    else {
        filename = "smallOutput.txt";
        //filename = "mediumOutput.txt";
        //filename = "largeOutput.txt";
        //filename = "largeOutput_unsorted.txt";

    }

    // Read data from txt file
    try {
        records.readData(filename);
    }
    catch (myException &exc) {
        cout<<exc.what()<<endl;
    }
    
    if(filename == "smallOutput.txt" || filename == "smallOutput_unsorted.txt"){
        smallOutput(records);
    }
    else if(filename == "mediumOutput.txt" || filename == "mediumOutput_unsorted.txt"){
        mediumOutput(records);
    }   
    else if(filename == "largeOutput.txt" || filename == "largeOutput_unsorted.txt" ){
        largeOutput(records);
    }

    return 0;
}