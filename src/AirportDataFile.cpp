#include "include/AirportDataFile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

AirportDataFile::AirportDataFile(string filePath) : filePath(filePath) {}

void AirportDataFile::splitCSVLine(string(&fields)[13], string line){
    int fieldIndex = 0;
    ostringstream field;
    bool inQuotes = false;

    for(char c: line){
        if(c == '\"'){
            inQuotes = !inQuotes;
        }
        if(!inQuotes && c == ','){
            fields[fieldIndex] = field.str();
            fieldIndex++;
            field.str(""); //reset field
        }else{
            field << c;
        }
    }
    fields[fieldIndex] = field.str();
}

void AirportDataFile::load(list<Airport>& airports){
    //Open file
    ifstream file(filePath);
    if(!file.is_open()){
        cout << "Unable to open file: " << filePath << endl;
        return;
    }

    //Parse file data
    string line;
    getline(file, headers);
    while(getline(file, line)){
        string fields[13];
        splitCSVLine(fields, line);
        try{
            Airport a;
            a.setType(static_cast<AirportType>(stoi(fields[0])));
            a.setName(fields[1]);
            a.setElevation(stoi(fields[2]));
            a.setContinent(fields[3]);
            a.setCountry(fields[4]);
            a.setRegion(fields[5]);
            a.setMunicipality(fields[6]);
            a.setICAOCode(fields[7]);
            a.setIATACode(fields[8]);
            a.setGPSCode(fields[9]);
            a.setLocalCode(fields[10]);
            a.setLatitude(stod(fields[11]));
            a.setLongitude(stod(fields[12]));
        }catch (invalid_argument& e){
            cout << e.what();
        }
    }
}