#include "include/AirPortray.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>

using namespace std;

AirPortray::AirPortray(string dataFilePath){
    repository = new AirportRepository(dataFilePath);
}

void AirPortray::run(){
    awaitInput();
}

void AirPortray::awaitInput(){
    string input;
    cout << "\nPress ENTER to continue...";
    getline(cin, input);
}

void AirPortray::clearConsole(){
    system("cls");
    cout << "-+= N.S.E. AirPortray: Airport Search Engine =+-\n\n";
}

int AirPortray::openMenu(string options[], int size){
    int choice = -1;
    bool castable = false;
    do{
        //Display Options
        clearConsole();
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

void AirPortray::openAirportDisplayMenu(vector<Airport*> airports){
    //Draw headers
    clearConsole();
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
        string elevation = (a->getElevation() == SHRT_NULL) ? "" : to_string(a->getElevation());
        string latitude = (a->getLatitude() == NAN) ? "" : to_string(a->getLatitude());
        string longitude = (a->getLongitude() == NAN) ? "" : to_string(a->getLongitude());

        cout << right << setw(2) << count+1 << left << ". | "
            << setw(14)<< Airport::typeToString(a->getType()) << " | "
            << setw(32) << truncateString(a->getName(), 32) << " | "
            << setw(7) << elevation << setw(1) << "ft" << " | "
            << setw(9) << a->getContinent() << " | "
            << setw(7) << a->getCountry() << " | "
            << setw(6) << a->getRegion() << " | "
            << setw(20) << truncateString(a->getMunicipality(), 20) << " | "
            << setw(9) << a->getICAOCode() << " | "
            << setw(9) << a->getIATACode() << " | "
            << setw(8) << a->getGPSCode() << " | "
            << setw(10) << a->getLocalCode() << " | "
            << setprecision(3) << latitude << ", "
            << setprecision(3) << longitude
            << endl;
    }

    //Draw Footer
    cout << endl << "[Displaying " << count << " of " << airports.size()
         << " results]" << endl;

    awaitInput();
}