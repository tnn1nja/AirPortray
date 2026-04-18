#include "include/AirportDataFile.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

AirportDataFile::AirportDataFile(string filePath) : filePath(filePath) {}

void AirportDataFile::splitCSVLine(string(&fields)[12], string line){
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

    //Save headers
    getline(file, headers);

    //Read file data
    string line;
    int count = 0;
    while(getline(file, line)){
        string fields[12];
        splitCSVLine(fields, line);
        if(count < 5){
            for(string field: fields){
                cout << field << "| ";
            }
            cout << endl;
            count++;
        }
    }
}