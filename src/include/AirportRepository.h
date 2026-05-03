#pragma once

#include "Airport.h"
#include "AirportDataFile.h"
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

#define PI 3.14159
#define EARTH_RADIUS 6371000

class AirportRepository{
    private:
        std::list<Airport> airports;
        AirportDataFile* dataFile;
        bool dirty;

    public:
        AirportRepository(std::string);
        ~AirportRepository();

        void save();
        void addAirport(Airport);
        std::vector<Airport*> getAirports();
        void filterByField(std::vector<Airport*>&, std::function<bool(Airport*)>);
        unsigned int calculateDistanceFromCoordinates(Airport*, double, double);
        unsigned int calculateDistanceBetweenAirports(Airport*, Airport*);
        void filterByDistanceFromCoordinates(std::vector<Airport*>&, double, double, unsigned int);
        void sortByDistanceFromCoordinates(std::vector<Airport*>&, double, double);
        std::map<Airport::Type, unsigned int> calculateAirportCountByType();
        Airport* getAirportByIATA(std::string);

        //Template methods (must be implemented in header)
        template <typename FieldType>
        void sortByField(std::vector<Airport*>& airports, std::function<FieldType(Airport*)> getField){
            auto comparator = [getField](Airport* a1, Airport* a2){return getField(a1) < getField(a2);};
            sort(airports.begin(), airports.end(), comparator);
        }
};