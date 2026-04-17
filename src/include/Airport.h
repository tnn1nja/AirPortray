#pragma once

#include <string>

enum class AirportType;

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
        std::string ICAOCode;
        std::string IATACode;
        std::string GPSCode;
        std::string localCode;
        double coordinates[2];

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
        void setICAO(std::string);
        void setIATA(std::string);
        void setGPSCode(std::string);
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
        std::string getICAO();
        std::string getIATA();
        std::string getGPSCode();
        std::string getLocalCode();
        std::string getCoordinates();
};