#include "include/AirPortray.h"
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

const string dataFilePath = "data/airports.csv";

int main(){
    try{
        AirPortray airPortray(dataFilePath);
        airPortray.run();
        return 0;
    }catch (runtime_error& e){
        cout << "Unable to start program, cannot find file at: " << dataFilePath << endl;
        return 1;
    }
}