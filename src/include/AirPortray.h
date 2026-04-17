#pragma once

#include <string>
#include "include/AirportRepository.h"

class AirPortray{
    private:
        AirportRepository airportRepository(std::string);
    public:
        AirPortray(std::string);
        void run();
};