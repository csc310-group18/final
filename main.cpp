#include <iostream>
#include "binaryFile.h"
#include "customErrorClass.h"

using namespace std;

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



    return 0;
}