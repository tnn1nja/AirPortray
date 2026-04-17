#ifndef AIRPORTDATAFILE_H
#define AIRPORTDATAFILE_H

#include <list>
#include <string>
#include "Airport.h"

class AirportDataFile{
    private:
        std::string filePath;

    public:
        AirportDataFile(std::string filePath);
        void load(std::list<Airport>&);
        void save(std::list<Airport>&);
};

#endif