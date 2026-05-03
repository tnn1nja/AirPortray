#pragma once

#include "Airport.h"
#include "AirportRepository.h"
#include <string>
#include <vector>

#define MAX_RESULTS 40
#define INDENT "    "

class AirPortray{
    private:
        //Attributes
        AirportRepository* repository;

        //Private Methods
        void awaitInput();
        void resetConsole();
        void drawTitle(std::string);
        std::string divider(int);
        int openMenu(std::string, std::string[], int);
        std::string truncateString(std::string, unsigned int);
        void openAirportDisplayMenu(std::vector<Airport*>);

    public:
        //Contructor and Destructor
        AirPortray(std::string);
        ~AirPortray();

        //Public Methods
        void openMainMenu();
        void openAddAirportMenu();
        void openSearchMenu();
        void openSortMenu();
        void openAnalyseMenu();
};