#pragma once

#include <string>

enum class AirportType{
    BALLOONPORT,
    CLOSED,
    HELIPORT,
    LARGE_AIRPORT,
    MEDIUM_AIRPORT,
    SEAPLANE_BASE,
    SMALL_AIRPORT
};

class Airport {
    private:
        //Attributes
        AirportType type;
        std::string name, continent, country, region, municipality,
                    ICAOCode, IATACode, GPSCode, localCode;
        short elevation;
        double coordinates[2];

        //Private Methods
        void assertNoBackslash(const std::string&);
        void assertLength(const std::string&, int);

    public:
        //Constructor(s)
        Airport();

        //Setters
        void setAirportType(AirportType);
        void setName(std::string);
        void setElevation(short);
        void setContinent(std::string);
        void setCountry(std::string);
        void setRegion(std::string);
        void setMunicipality(std::string);
        void setICAOCode(std::string);
        void setIATACode(std::string);
        void setGPSCode(std::string);
        void setLocalCode(std::string);
        void setCoordinates(double*);

        //Getters
        AirportType getAirportType();
        std::string getName();
        short getElevation();
        std::string getContinent();
        std::string getCountry();
        std::string getRegion();
        std::string getMunicipality();
        std::string getICAOCode();
        std::string getIATACode();
        std::string getGPSCode();
        std::string getLocalCode();
        double* getCoordinates();
};