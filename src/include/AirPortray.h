#pragma once

#include <string>
#include <list>
#include "AirportRepository.h"

class AirPortray{
    private:
        AirportRepository* repository;

        std::string truncateString(std::string, unsigned int);
        void displayAirports(std::list<Airport*>);
    public:
        AirPortray(std::string);
        void run();
};