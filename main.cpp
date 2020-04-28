#include <iostream>
#include "binaryFile.h"
#include "customErrorClass.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){

    binaryFile records;
    string mainDataFilename = "smallOutput.txt";
    string testRecordsFilename;
    testRecordsFilename = mainDataFilename.substr(0, mainDataFilename.find(".")) + "_TestRecords.txt";

    fstream testRecordsFile;

    // Read data from txt file
    records.readData(mainDataFilename);  // contains all employee records

    // Open test records file
    testRecordsFile.open(testRecordsFilename, ios::in);
    
    // Exit if test records file failed to open
    if (testRecordsFile.is_open() == false){
        string msg = "Could not open <" + testRecordsFilename + "> for reading";
        myException e = myException(msg, SYSTEM_FAILURE);
        cerr << e.what() << endl;
        exit(1);
    } 

    // Get number of employees from test Data
    int numEmployees = 0;
    testRecordsFile >> numEmployees;

    // Output results from each test record
    int i = 0;
    int deptBuffer = 0, employeeNumBuffer = 0;

    for (i = 0; i < numEmployees; i++){
        testRecordsFile >> deptBuffer;
        testRecordsFile >> employeeNumBuffer;

        bool employeeFound;
        employeeFound = records.findEmployee(deptBuffer, employeeNumBuffer);
        if (employeeFound) {
            cout << "Employee found" << endl;
        } else {
            cout << "Employee not found" << endl;
        }

        //string employeeName = records.findEmployee(deptBuffer, employeeNumBuffer);
        // TODO: modify findEmployee()so it returns a string
        // and print employee details

        bool employeeUpdated;
        //employeeUpdated = records.updateEmployeeName(deptBuffer, employeeNumBuffer);
        //TODO: modify updateEmployeeName to take (int int)
        if (employeeFound) {
            cout << "Employee updated" << endl;
        } else {
            cout << "Employee not updated" << endl;
        }

    }






    // Get data file name

    /*
    if (argc == 2) {
        mainDataFile = argv[1];
    } 
    else {
        mainDataFile = "smallOutput.txt";
        
        //filename = "mediumOutput.txt";
        //filename = "largeOutput.txt";
        //filename = "largeOutput_unsorted.txt";
    }

    */


    
    // Create employees array with test data

    // smallOutput
    /*
    s_EMPLOYEE employees[] = {{ ACCOUNTING     , 45731, "Leona"   }, { BUSINESS       , 37503, "Briar"   }, 
                            { HUMAN_RESOURCES, 58509, "Kailey"  }, { SALES          , 58510, "Liv"     },
                            { PRODUCTION     , 44258, "Anthony" }, { ACCOUNTING     , 18738, "Hunter"  },
                            { BUSINESS       , 63006, "Annabel" }, { HUMAN_RESOURCES, 757  , "Layton"  }, 
                            { SALES          , 68263, "Maxim"   }, { PRODUCTION     , 65898, "Rex"     }};
    
    */
    // mediumOutput
    /*
    s_EMPLOYEE employees[] = {{ ACCOUNTING     , 243013, "Amina"   }, { BUSINESS       , 135016, "Dax"    },
                            { HUMAN_RESOURCES, 15013 , "Kaleb"   }, { SALES          , 105013, "Violeta" },
                            { PRODUCTION     , 297008, "Huxley"  }, { ACCOUNTING     , 139708, "Benicio" },
                            { BUSINESS       , 250506, "Amari"   }, { HUMAN_RESOURCES, 206998, "Cory"    },
                            { SALES          , 6011  , "Zariyah" }, { PRODUCTION     , 243119, "Mariana" }};

    */

    // largeOutput
    /*
    s_EMPLOYEE employees[] = {{ ACCOUNTING     , 205009, "Isabelle" }, { BUSINESS       , 25013, "Amiya"    }, 
                        { HUMAN_RESOURCES, 189715, "Donald"   }, { SALES          , 155012, "Virginia" }, 
                        { PRODUCTION     , 430017, "Magnolia" }, { ACCOUNTING     , 205508, "Meadow"   }, 
                        { BUSINESS       , 335014, "Crosby"   }, { HUMAN_RESOURCES, 430013, "Clara"    }, 
                        { SALES          , 5014  , "Watson"   }, { PRODUCTION     , 433415, "Kyler"    }};

    */
/*

    try {
        records.readData(mainDataFile);     // Read data from txt file
        records.outputData(employees, numEmployees); // Output test data
    }
    catch (myException &exc) {
        cout<<exc.what()<<endl;
    }

*/
   



    return 0;
}