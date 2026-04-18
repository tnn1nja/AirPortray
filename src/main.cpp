#include "include/AirPortray.h"
#include <string>

using namespace std;

const string dataFilePath = "data/airports.csv";

int main(){
    AirPortray airPortray(dataFilePath);
    airPortray.run();
    
    return 0;
}