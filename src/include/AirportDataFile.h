#pragma once

#include <list>
#include <string>
#include "Airport.h"

class AirportDataFile{
    private:
        std::string filePath;
        std::string headers[12];

    public:
        AirportDataFile(std::string filePath);
        void load(std::list<Airport>&);
        void save(std::list<Airport>&);
};