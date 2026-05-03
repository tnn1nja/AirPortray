#include "include/AirPortray.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <sstream>

using namespace std;

AirPortray::AirPortray(string dataFilePath){
    repository = new AirportRepository(dataFilePath);
}

AirPortray::~AirPortray(){
    delete(repository);
}

void AirPortray::run(){
    awaitInput();
    openRootMenu();
}


void AirPortray::awaitInput(){
    string input;
    cout << "\nPress ENTER to continue...";
    getline(cin, input);
}

void AirPortray::resetConsole(){
    system("cls");
    cout << "-+= N.S.E. AirPortray: Airport Search Engine =+-\n\n";
}

void AirPortray::drawTitle(string title){
    cout << INDENT << "-+= " << title << " =+-\n\n";
}

string AirPortray::divider(int size){
    ostringstream oss;
    for(int i=0;i<size;i++){
        oss << "-";
    }
    return oss.str();
}

int AirPortray::openMenu(string title, string options[], int size){
    int choice = -1;
    bool castable = false;
    do{
        //Display Options
        resetConsole();
        drawTitle(title);
        for(int i=0; i<size-1; i++){
            cout << INDENT << INDENT <<  i+1 << ". " << options[i] << endl;
        }
        cout << INDENT << INDENT << "0. " << options[size-1] << "\n"
             << "\n" << INDENT << "Choice: ";
        
        //Get Input
        string input;
        getline(cin, input);
        
        //Validate Input
        try{
            choice = stoi(input);
            castable = true;
        }catch(invalid_argument e){}
    }while(!castable || choice < 0 || choice > size-1);

    cout << "\n";
    return choice;
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
    resetConsole();
    drawTitle("Results");
    cout << left << fixed << INDENT
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
    cout << INDENT << divider(190) << endl;

    //Draw Rows
    unsigned int count = 0;
    for(;count<MAX_RESULTS && count<airports.size(); count++){
        Airport* a = airports.at(count);
        string elevation = (a->getElevation() == SHRT_NULL) ? "" : to_string(a->getElevation());
        string latitude = (a->getLatitude() == NAN) ? "" : to_string(a->getLatitude());
        string longitude = (a->getLongitude() == NAN) ? "" : to_string(a->getLongitude());

        cout << INDENT << right << setw(2) << count+1 << left << ". | "
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

void AirPortray::openRootMenu(){
    bool exit = false;
    while(!exit){
        string options[]{
            "Search Airports",
            "Sort Airports",
            "Analyse Airports",
            "Add Airport",
            "Save and Exit",
            "Exit Without Saving"
        };
        switch(openMenu("Main Menu", options, 6)){
            case 1:
                openSearchMenu();
                break;
            case 2:
                openSortMenu();
                break;
            case 3:
                openAnalyseMenu();
                break;
            case 4:
                openAddAirportMenu();
                break;
            case 5:
                try{
                    repository->save();
                    cout << "All changes succesfully saved!";
                    exit = true;
                }catch(runtime_error& e){
                    cout << "Unable to save, " << e.what() << "\nAborting exit...\n";
                    awaitInput();
                }
                break;
            case 0:
                exit = true;
                break;
        }
    }
}

void AirPortray::openAddAirportMenu(){
    //Draw Title and Instructions
    resetConsole();
    drawTitle("Add Airport");
    cout << INDENT << divider(35) << endl
         << INDENT << "Enter nothing for missing values.\n"
         << INDENT << "Airport Types:\n";
    int i = 0;
    for(; i < NUM_AP_TYPES-1; i++){
        cout << INDENT << INDENT << i << ". " << Airport::typeToString(static_cast<Airport::Type>(i)) << endl;
    }
    cout << INDENT << INDENT << i << ". Unknown" << endl;
    cout << INDENT << divider(35) << endl << endl;

    //Get Inputs
    string titles[13] = {
        "Type", "Name", "Elevation (ft)", "Continent", "Country Code",
        "Region", "Municipality", "ICAO Code", "IATA Code", "GPS Code",
        "Local Code", "Latitude", "Longitude"
    };
    string fields[13];
    for(int i=0; i< 13; i++){
        cout << INDENT << titles[i] << ": ";
        getline(cin, fields[i]);
    }
    int field = 0;

    //Try to Create Airport
    try{
        Airport a;
        a.setType(static_cast<Airport::Type>(stoi(fields[field]))); field++;
        a.setName(fields[field]); field++;
        if(fields[field] != ""){ a.setElevation(stoi(fields[field])); } field++;
        a.setContinent(fields[field]); field++;
        a.setCountry(fields[field]); field++;
        a.setRegion(fields[field]); field++;
        a.setMunicipality(fields[field]); field++;
        a.setICAOCode(fields[field]); field++;
        a.setIATACode(fields[field]); field++;
        a.setGPSCode(fields[field]); field++;
        a.setLocalCode(fields[field]); field++;
        if(fields[field] != ""){ a.setLatitude(stod(fields[field])); } field++;
        if(fields[field] != ""){ a.setLongitude(stod(fields[field])); } field++;
        repository->addAirport(a);
        cout << endl << "Airport successfully added!" << endl;
    }catch (invalid_argument& e){
        cout << endl << "Failed to add airport, invalid " << titles[field] << ": " << e.what() << "." << endl;
    }

    //Pause
    awaitInput();
}

void AirPortray::openSearchMenu(){
    string options[]{
        "Partial Name",
        "Partial Municipality",
        "IATA Code",
        "Type",
        "Coordinates within Radius",
        "Country Code",
        "Return to Main Menu"
    };
    switch(openMenu("Search Airports", options, 7)){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
    }
}

void AirPortray::openSortMenu(){
    string options[]{
        "Name",
        "Type",
        "Country Code",
        "Elevation",
        "Proximity to Coordinates",
        "Return to Main Menu"
    };
    switch(openMenu("Sort Airports", options, 6)){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
    }
}

void AirPortray::openAnalyseMenu(){
    string options[]{
        "Find Highest and Lowest Elevations",
        "Find Airports with Missing IATA Codes",
        "Calculate Distance Between Airports",
        "Calculate Airport Count by Type",
        "Return to Main Menu"
    };
    switch(openMenu("Analyse Airports", options, 5)){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
    }
}