#pragma once

#include <string>
#include <vector>
#include "AirportRepository.h"

#define MAX_RESULTS 32

class AirPortray{
    private:
        AirportRepository* repository;

        void awaitInput();
        void resetConsole();

        std::string truncateString(std::string, unsigned int);
        void openAirportDisplayMenu(std::vector<Airport*>);

        int openMenu(std::string, std::string[], int);
        void openRootMenu();
        void openSearchMenu();
        void openSortMenu();
        void openAnalyseMenu();

    public:
        AirPortray(std::string);
        ~AirPortray();
        void run();
};