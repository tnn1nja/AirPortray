#pragma once

#include <string>
#include <list>
#include "AirportRepository.h"

class AirPortray{
    private:
        AirportRepository *repository;

        void displayAirports(list<Airport&>);
    public:
        AirPortray(std::string);
        void run();
};