#include "include/AirPortray.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>

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

void AirPortray::drawDivider(int size){
    for(int i=0;i<size;i++){
        cout << "-";
    }
    cout << endl;
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
    cout << INDENT;
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
    resetConsole();
    drawTitle("Add Airport");

    cout << INDENT;
    drawDivider(15);
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