#pragma once

#include <list>
#include <string>
#include "Airport.h"

class AirportDataFile{
    private:
        //Attributes
        std::string filePath;
        std::string headers;

        //Private Methods
        void splitCSVLine(std::string(&)[13], std::string);
        std::string decodeString(std::string);
        std::string encodeString(std::string);

    public:
        //Public Methods
        AirportDataFile(std::string);
        void load(std::list<Airport>&);
        void save(std::list<Airport>&);
};