#pragma once

#include <string>
#include <climits>

#define SHRT_NULL SHRT_MAX
#define NUM_AP_TYPES 8

class Airport {
    public:
        //Statics
        enum Type{
            BALLOONPORT,
            CLOSED,
            HELIPORT,
            LARGE_AIRPORT,
            MEDIUM_AIRPORT,
            SEAPLANE_BASE,
            SMALL_AIRPORT,
            UNKNOWN
        };
        static std::string typeToString(Type);
        static std::string typeToString(int);

    private:
        //Attributes
        Type type;
        std::string name, continent, country, region, municipality,
                    ICAOCode, IATACode, GPSCode, localCode;
        short elevation;
        double latitude, longitude;

        //Private Methods
        void assertNoBackslash(const std::string&);
        void assertLength(const std::string&, unsigned int);

    public:
        //Constructor
        Airport();

        //Setters
        void setType(Type);
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
        void setLatitude(double);
        void setLongitude(double);

        //Getters
        Type getType();
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
        double getLatitude();
        double getLongitude();
};