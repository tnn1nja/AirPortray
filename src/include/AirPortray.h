#pragma once

#include <string>
#include <vector>
#include "AirportRepository.h"

#define MAX_RESULTS 32

class AirPortray{
    private:
        AirportRepository* repository;

        void drawHeader();
        std::string truncateString(std::string, unsigned int);
        void displayAirports(std::vector<Airport*>);
        void openRootMenu();
    public:
        AirPortray(std::string);
        void run();
};