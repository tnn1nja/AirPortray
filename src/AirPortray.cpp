#include "include/AirPortray.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <sstream>

using namespace std;

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


AirPortray::AirPortray(string dataFilePath){
    repository = new AirportRepository(dataFilePath);
}

AirPortray::~AirPortray(){
    delete(repository);
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

void AirPortray::openMainMenu(){
    awaitInput();
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
        cout << INDENT << INDENT << i+1 << ". " << Airport::typeToString(i) << endl;
    }
    cout << INDENT << INDENT << i+1 << ". Unknown" << endl;
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
        a.setType(static_cast<Airport::Type>(stoi(fields[field])-1)); field++;
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
    auto airports = repository->getAirports();
    string input;

    string options[]{
        "Partial Name",
        "Partial Municipality",
        "Full IATA Code",
        "Type",
        "Coordinates within Radius",
        "Full Country Code",
        "Return to Main Menu"
    };
    switch(openMenu("Search Airports", options, 7)){
        case 1:
            cout << INDENT << "Enter Partial Name: ";
            getline(cin, input);
            repository->filterByField(airports, [input](Airport* a){
                return (a->getName().find(input)!= string::npos);
            });
            repository->sortByField<int>(airports, [input](Airport* a){
                return a->getName().find(input);
            });
            openAirportDisplayMenu(airports);
            break;

        case 2:
            cout << INDENT << "Enter Partial Municipality: ";
            getline(cin, input);
            repository->filterByField(airports, [input](Airport* a){
                return (a->getMunicipality().find(input)!= string::npos);
            });
            repository->sortByField<int>(airports, [input](Airport* a){
                return a->getMunicipality().find(input);
            });
            openAirportDisplayMenu(airports);
            break;

        case 3:
            cout << INDENT << "Enter Full IATA Code: ";
            getline(cin, input);
            repository->filterByField(airports, [input](Airport* a){
                return (a->getIATACode() == input);
            });
            openAirportDisplayMenu(airports);
            break;

        case 4:{
            cout << INDENT << divider(25) << endl;
            int i = 0;
            for(; i < NUM_AP_TYPES-1; i++){
                cout << INDENT << INDENT << i+1 << ". " << Airport::typeToString(i) << endl;
            }
            cout << INDENT << INDENT << i+1 << ". Unknown" << endl;
            cout << INDENT << divider(25) << endl << endl;

            cout << INDENT << "Enter Type: ";
            getline(cin, input);
            try{
                repository->filterByField(airports, [input](Airport* a){
                    return (a->getType() == static_cast<Airport::Type>(stoi(input)-1));
                });
                openAirportDisplayMenu(airports);
            }catch(invalid_argument& e){
                cout << endl << "Invalid Type, aborting search.\n";
                awaitInput();
            }
            break;
        }
        case 5:
            try{
                double latitude, longitude, radius;

                cout << INDENT << "Enter Latitude: ";
                getline(cin, input);
                latitude = stod(input);

                cout << INDENT << "Enter Longitude: ";
                getline(cin, input);
                longitude = stod(input);

                cout << INDENT << "Enter Radius (m): ";
                getline(cin, input);
                radius = stoi(input);

                repository->filterByDistanceFromCoordinates(airports, latitude, longitude, radius);
                repository->sortByDistanceFromCoordinates(airports, latitude, longitude);
                openAirportDisplayMenu(airports);
            }catch(invalid_argument& e){
                cout << endl << "Invalid value, aborting search.\n";
                awaitInput();
            }catch(out_of_range& e){
                cout << endl << "Invalid value, aborting search.\n";
                awaitInput();
            }
            break;

        case 6:
            cout << INDENT << "Enter Full Country Code: ";
            getline(cin, input);
            repository->filterByField(airports, [input](Airport* a){
                return (a->getCountry() == input);
            });
            openAirportDisplayMenu(airports);
            break;
    }
}

void AirPortray::openSortMenu(){
    auto airports = repository->getAirports();
    string input;

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
            repository->sortByField<string>(airports, [](Airport* a){return a->getName();});
            openAirportDisplayMenu(airports);
            break;
        case 2:
            repository->sortByField<Airport::Type>(airports, [](Airport* a){return a->getType();});
            openAirportDisplayMenu(airports);
            break;
        case 3:
            repository->sortByField<string>(airports, [](Airport* a){return a->getCountry();});
            openAirportDisplayMenu(airports);
            break;
        case 4:
            repository->sortByField<short>(airports, [](Airport* a){return a->getElevation();});
            openAirportDisplayMenu(airports);
            break;
        case 5:
            double latitude, longitude;
            try{
                cout << INDENT << "Enter Latitude: ";
                getline(cin, input);
                latitude = stod(input);

                cout << INDENT << "Enter Longitude: ";
                getline(cin, input);
                longitude = stod(input);

                repository->sortByDistanceFromCoordinates(airports, latitude, longitude);
                openAirportDisplayMenu(airports);
            }catch(invalid_argument& e){
                cout << endl << "Invalid value, aborting search.\n";
                awaitInput();
            }
            break;
    }
}

void AirPortray::openAnalyseMenu(){
    auto airports = repository->getAirports();

    string options[]{
        "Find Highest and Lowest Elevations",
        "Find Airports with Missing IATA Codes",
        "Calculate Distance Between Airports",
        "Calculate Airport Count by Type",
        "Return to Main Menu"
    };
    switch(openMenu("Analyse Airports", options, 5)){
        case 1:
            resetConsole();
            drawTitle("Highest and Lowest Elevations");
            repository->sortByField<short>(airports, [](Airport* a){return a->getElevation();});
            repository->filterByField(airports, [](Airport* a){return a->getElevation() != SHRT_NULL;});
            cout << INDENT << INDENT << "The highest airport is \"" << airports.back()->getName()
                 << "\" which is " << airports.back()->getElevation() << "ft above sea-level." << endl;
            cout << INDENT << INDENT << "The lowest airport is \"" << airports.front()->getName()
                 << "\" which is " << airports.front()->getElevation() << "ft above sea-level." << endl;
            awaitInput();
            break;

        case 2:
            repository->filterByField(airports, [](Airport* a){return a->getIATACode() == "";});
            openAirportDisplayMenu(airports);
            break;

        case 3:{
            resetConsole();
            drawTitle("Highest and Lowest Elevations");
            string input;
            cout << INDENT << INDENT << "Enter First Airport IATA Code: ";
            getline(cin, input);
            Airport* a1 = repository->getAirportByIATA(input);

            cout << INDENT << INDENT << "Enter Second Airport IATA Code: ";
            getline(cin, input);
            Airport* a2 = repository->getAirportByIATA(input);

            if(a1 == nullptr || a2 == nullptr){
                cout << endl << "Invalid IATA Code, aborting search.\n";
            }else{
                cout << endl << INDENT << INDENT << "Distance: "
                    << repository->calculateDistanceBetweenAirports(a1, a2) << " m" << endl;
            }
                
            awaitInput();
            break;
        }
        case 4:
            resetConsole();
            drawTitle("Airport Count By Type");
            auto countByType = repository->calculateAirportCountByType();
            for(auto i: countByType){
                cout << INDENT << INDENT << left << setw(17)
                     << ((Airport::typeToString(i.first) == "" ? "Unknown" : Airport::typeToString(i.first)) + ":")
                     << i.second << endl;
            }
            awaitInput();
            break;
    }
}