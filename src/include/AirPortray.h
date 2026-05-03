#pragma once

#include <string>
#include <vector>
#include "AirportRepository.h"

#define MAX_RESULTS 32
#define INDENT "    "

class AirPortray{
    private:
        AirportRepository* repository;

        void awaitInput();
        void resetConsole();
        void drawTitle(std::string);
        std::string divider(int);
        int openMenu(std::string, std::string[], int);
        std::string truncateString(std::string, unsigned int);

        void openAirportDisplayMenu(std::vector<Airport*>);
        void openRootMenu();
        void openAddAirportMenu();
        void openSearchMenu();
        void openSortMenu();
        void openAnalyseMenu();

    public:
        AirPortray(std::string);
        ~AirPortray();
        void run();
};