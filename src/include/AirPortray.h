#pragma once

#include "Airport.h"
#include "AirportRepository.h"
#include <string>
#include <vector>

#define MAX_RESULTS 40 //max results in a display panel
#define INDENT "    " //malf the size of \t

class AirPortray{
    private:
        //Attributes
        AirportRepository* repository;

        //Private methods
        void awaitInput();
        void resetConsole(std::string);
        std::string divider(int);
        int openMenu(std::string, const std::string[], int);
        std::string truncateString(std::string, unsigned int);
        void openAirportDisplayMenu(const std::vector<Airport*>&);

    public:
        //Contructor and destructor
        AirPortray(std::string);
        ~AirPortray();

        //Public methods
        void openMainMenu();
        void openAddAirportMenu();
        void openSearchMenu();
        void openSortMenu();
        void openAnalyseMenu();
        void openHighestAndLowestElevationMenu();
        void openCalculateDistanceMenu();
        void openCountByTypeMenu();
};