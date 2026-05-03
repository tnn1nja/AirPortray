#include "include/AirPortray.h"
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

const string dataFilePath = "data/airports.csv";

int main(){
    try{
        AirPortray airPortray(dataFilePath);
        airPortray.openMainMenu(); //start main loop
        return EXIT_SUCCESS;
    }catch (runtime_error& e){ //cant open file
        cout << "Unable to start program, " << e.what() << endl;
        return EXIT_FAILURE;
    }
}