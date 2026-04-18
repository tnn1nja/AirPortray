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
    getline(file, headers);

    string line;
    int lineCount = 1;
    while(getline(file, line)){
        string fields[13];
        splitCSVLine(fields, line);
        int field = 0;
        try{
            Airport a;
            a.setType(static_cast<AirportType>(stoi(fields[0]))); field++;
            a.setName(fields[1]); field++;
            a.setElevation(stoi(fields[2])); field++;
            a.setContinent(fields[3]); field++;
            a.setCountry(fields[4]); field++;
            a.setRegion(fields[5]); field++;
            a.setMunicipality(fields[6]); field++;
            a.setICAOCode(fields[7]); field++;
            a.setIATACode(fields[8]); field++;
            a.setGPSCode(fields[9]); field++;
            a.setLocalCode(fields[10]); field++;
            a.setLatitude(stod(fields[11])); field++;
            a.setLongitude(stod(fields[12])); field++;
        }catch (invalid_argument& e){
            cout << "Failed to read Airport at line " << lineCount 
                 << ", field " << field << ": " << e.what() << "!\n";
        }
        lineCount++;
    }
}