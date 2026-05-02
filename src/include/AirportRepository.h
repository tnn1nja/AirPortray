#pragma once

#include "Airport.h"
#include "AirportDataFile.h"
#include <vector>
#include <functional>
#include <algorithm>

class AirportRepository{
    private:
        std::list<Airport> airports;
        AirportDataFile* dataFile;
        bool dirty;

    public:
        AirportRepository(std::string);
        ~AirportRepository() {};

        void save();
        template <typename SortType>
        void sortByField(std::vector<Airport*>& airports, std::function<SortType(Airport*)> getField){
            //definition included in header because of template
            auto comparator = [getField](Airport* a1, Airport* a2){return getField(a1) < getField(a2);};
            sort(airports.begin(), airports.end(), comparator);
        }

        std::vector<Airport*> getSomeAirports();
};