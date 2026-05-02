#pragma once

#include <string>
#include <vector>
#include "AirportRepository.h"

#define MAX_RESULTS 32

class AirPortray{
    private:
        AirportRepository* repository;

        void clearConsole();
        void awaitInput();
        std::string truncateString(std::string, unsigned int);
        void openAirportDisplayMenu(std::vector<Airport*>);
        int openMenu(std::string[], int);
        void openRootMenu();
    public:
        AirPortray(std::string);
        ~AirPortray();
        void run();
};