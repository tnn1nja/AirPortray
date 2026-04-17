#pragma once

#include <string>
#include "include/AirportRepository.h"

class AirPortray{
    private:
        AirportRepository airportRepository;
    public:
        AirPortray(std::string);
        void run();
};