#include <iostream>
#include "binaryFile.h"

using namespace std;

int main(int argc, char *argv[]){

    binaryFile records;

    // Read data from txt file
    try {
        records.readData("smallOutput.txt");
    }
    catch( myException &exc ){
        cout<<exc.what()<<endl;
    }



    return 0;
}