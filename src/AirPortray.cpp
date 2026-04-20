#include "include/AirPortray.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

AirPortray::AirPortray(string dataFilePath){
    repository = new AirportRepository(dataFilePath);
}

void AirPortray::run(){
    openRootMenu();
}

void AirPortray::drawHeader(){
    system("cls");
    cout << "-+= N.S.E. AirPortray: Airport Search Engine =+-\n\n";
}

int AirPortray::openMenu(string options[], int size){
    int choice = -1;
    bool castable = false;
    do{
        //Display Options
        drawHeader();
        for(int i=0; i<size; i++){
            cout << "\t" <<  i+1 << ". " << options[i] << endl;
        }
        cout << "\t0. Exit\n"
             << "\n\t   Choice: ";
        
        //Get Input
        string input;
        getline(cin, input);
        
        //Validate Input
        try{
            choice = stoi(input);
            castable = true;
        }catch(invalid_argument e){}
    }while(!castable || choice < 0 || choice > size);

    return choice;
}

void AirPortray::openRootMenu(){
    string options[] = {"Search Airport by Country"};
    int choice = openMenu(options, 1);
}

string AirPortray::truncateString(string s, unsigned int i){
    if(s.length() > i){
        s.erase(i-3);
        s = s + "...";
    }
    return s;
}

void AirPortray::displayAirports(vector<Airport*> airports){
    //Draw headers
    cout << left << fixed << endl
         << setw(3) << "" << " | " //index
         << setw(14) << "Type" << " | "
         << setw(32) << "Name" << " | "
         << "Elevation | "
         << "Continent | "
         << "Country | " 
         << "Region | " 
         << setw(20) << "Municipality" << " | "
         << "ICAO Code | "
         << "IATA Code | " 
         << "GPS Code | " 
         << "Local Code | " 
         << "Coordinates"
         << endl;
        
    //Draw Seperator
    for(int i=0; i<190; i++){
        cout << "-";
    }
    cout << endl;

    //Draw Rows
    unsigned int count = 0;
    for(;count<MAX_RESULTS && count<airports.size(); count++){
        Airport* a = airports.at(count);
        cout << right << setw(2) << count+1 << left << ". | "
            << setw(14) << Airport::typeToString(a->getType()) << " | "
            << setw(32) << truncateString(a->getName(), 32) << " | "
            << setw(5) << a->getElevation() << setw(4) << "ft" << " | "
            << setw(9) << a->getContinent() << " | "
            << setw(7) << a->getCountry() << " | "
            << setw(6) << a->getRegion() << " | "
            << setw(20) << truncateString(a->getMunicipality(), 20) << " | "
            << setw(9) << a->getICAOCode() << " | "
            << setw(9) << a->getIATACode() << " | "
            << setw(8) << a->getGPSCode() << " | "
            << setw(10) << a->getLocalCode() << " | "
            << setprecision(3) << a->getLatitude() << ", "
            << setprecision(3) << a->getLongitude()
            << endl;
    }

    //Draw Footer
    cout << endl << "[Displaying " << count << " of " << airports.size()
         << " results]" << endl;
}