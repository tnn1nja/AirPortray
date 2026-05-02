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
        //Contructor(s)
        AirportDataFile(std::string);

        //Public Methods
        bool load(std::list<Airport>&);
        bool save(const std::list<Airport>&);
};