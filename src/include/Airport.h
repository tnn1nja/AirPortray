#pragma once

#include <string>

enum AirportType;

class Airport {
    private:
        //Attributes
        AirportType type;
        std::string name;
        short elevation;
        std::string continent;
        std::string country;
        std::string region;
        std::string municipality;
        std::string icaoCode;
        std::string iataCode;
        std::string gpsCode;
        std::string localCode;
        double coordinates[2];

    public:
        //Setters
        void setAirportType(AirportType);
        void setName(std::string);
        void setElevation(short);
        void setContinent(std::string);
        void setCountry(std::string);
        void setRegion(std::string);
        void setMunicipality(std::string);
        void setIcao(std::string);
        void setIata(std::string);
        void setGpsCode(std::string);
        void setLocalCode(std::string);
        void setCoordinates(double[2]);

        //Getters
        AirportType getAirportType();
        std::string getName();
        short getElevation();
        std::string getContinent();
        std::string getCountry();
        std::string getRegion();
        std::string getMunicipality();
        std::string getIcao();
        std::string getIata();
        std::string getGpsCode();
        std::string getLocalCode();
        std::string getCoordinates();
};