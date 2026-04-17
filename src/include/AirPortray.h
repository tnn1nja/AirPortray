#ifndef AIRPORTRAY_H
#define AIRPORTRAY_H

#include <string>
#include "AirportRepository.h"

class AirPortray{
    private:
        AirportRepository *airportRepository;
    public:
        AirPortray(std::string);
        void run();
};

#endif