#include "include/AirportDataFile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>

using namespace std;

//Private methods
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
    fields[fieldIndex] = field.str(); //add final field
}

string AirportDataFile::decodeString(string s){
    //Remove opening and closing quotes
    s.erase(0, 1);
    s.erase(s.length()-1, 1);

    //Remove one of each set of two quotes
    while(int i = s.find("\"\"") != string::npos){
        s.erase(i, 1);
    }
    return s;
}

string AirportDataFile::encodeString(string s){
    //Add additional quotes to escape quote character
    for(unsigned int i=0; i<s.size(); i++){
        if(s.at(i)=='\"'){
            s.insert(i, "\"");
            i++; //account for insert
        }
    }

    //Add opening and closing quotes
    s.insert(0, "\"");
    s.insert(s.size(), "\"");
    return s;
}

//Constructor
AirportDataFile::AirportDataFile(string filePath) : filePath(filePath) {}

//Public methods
bool AirportDataFile::load(list<Airport>& airports){
    //Open file
    ifstream file(filePath);
    if(!file.is_open()){
        return false;
    }

    //Extract header
    getline(file, headers); //save header for writing

    //Parse file data
    string line;
    int lineCount = 1;
    while(getline(file, line)){
        //Read line
        string fields[13];
        splitCSVLine(fields, line);

        //Attempt to create Airport
        int field = 0; //track which field fails
        try{
            Airport a;
            a.setType(static_cast<Airport::Type>(stoi(fields[field]))); field++;
            a.setName(decodeString(fields[field])); field++;
            if(fields[field] != ""){ a.setElevation(stoi(fields[field])); } field++;
            a.setContinent(fields[field]); field++;
            a.setCountry(fields[field]); field++;
            a.setRegion(fields[field]); field++;
            a.setMunicipality(decodeString(fields[field])); field++;
            a.setICAOCode(fields[field]); field++;
            a.setIATACode(fields[field]); field++;
            a.setGPSCode(fields[field]); field++;
            a.setLocalCode(fields[field]); field++;
            if(fields[field] != ""){ a.setLatitude(stod(fields[field])); } field++;
            if(fields[field] != ""){ a.setLongitude(stod(fields[field])); } field++;
            airports.push_back(a);
        }catch (invalid_argument& e){ //erroneous
            cout << "Failed to read Airport at line " << lineCount 
                 << ", field " << field << " (" << fields[field]
                 << ") : " << e.what() << "!\n";
        }catch (out_of_range& e){ //too small/large
            cout << "Failed to read Airport at line " << lineCount 
                 << ", field " << field << " (" << fields[field]
                 << ") : " << e.what() << "!\n";
        }
        lineCount++;
    }

    cout << "Succesfully loaded " << lineCount-1 << " of " << airports.size() << " rows!\n";
    return true;
}

bool AirportDataFile::save(const list<Airport>& airports){
    //Open file
    ofstream file(filePath);
    if(!file.is_open()){
        return false;
    }

    //Write data
    file << headers << endl; //write saved header
    for(Airport a: airports){
        //Ternaries for complex fields
        string elevation = (a.getElevation() == SHRT_NULL) ? "" : to_string(a.getElevation());
        string latitude = isnan(a.getLatitude()) ? "" : to_string(a.getLatitude());
        string longitude = isnan(a.getLongitude()) ? "" : to_string(a.getLongitude());

        //Write airport
        file << static_cast<int>(a.getType()) << ","
             << encodeString(a.getName()) << ","
             << elevation << ","
             << a.getContinent() << ","
             << a.getCountry() << ","
             << a.getRegion() << ","
             << encodeString(a.getMunicipality()) << ","
             << a.getICAOCode() << ","
             << a.getIATACode() << ","
             << a.getGPSCode() << ","
             << a.getLocalCode() << ","
             << latitude << ","
             << longitude << endl;
    }

    return true;
}