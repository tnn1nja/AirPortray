#include "include/AirPortray.h"
#include <string>

const std::string dataFilePath = "data/airports.csv";

int main(){
    AirPortray airPortray(dataFilePath);
    airPortray.run();
    return 0;
}