#pragma once

#include <list>
#include "include/Airport.h"

class AirportData{
    public:
        void loadCSVData(std::list<Airport>&);
        void saveCSVData(std::list<Airport>&);
};