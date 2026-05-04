#include "include/AirPortray.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <cmath>

using namespace std;

//Private methods
void AirPortray::awaitInput(){
    cout << "\nPress ENTER to continue...";
    string input;
    getline(cin, input); //disregard enter
}

void AirPortray::resetConsole(){
    system("cls"); //NT specific console clear
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

int AirPortray::openMenu(string title, const string options[], int size){
    int choice = -1;
    bool castable = false;
    do{
        //Display options
        resetConsole();
        drawTitle(title);
        for(int i=0; i<size; i++){
            cout << INDENT << INDENT << ((i==size-1) ? 0 : i+1) << ". " << options[i] << endl;
        }
        cout << "\n" << INDENT << "Choice: ";
        
        //Get input
        string input;
        getline(cin, input);
        
        //Validate input
        try{
            choice = stoi(input);
            castable = true;
        }catch(invalid_argument& e){
        }catch(out_of_range& e){}
    }while(!castable || choice < 0 || choice > size-1);

    if(choice!=0){ cout << "\n"; } //awaitInput already pads
    return choice;
}

string AirPortray::truncateString(string s, unsigned int i){
    if(s.length() > i){
        //Replace final 3 chars with ...
        s.erase(i-3);
        s = s + "...";
    }
    return s;
}

void AirPortray::openAirportDisplayMenu(const vector<Airport*>& airports){
    //Draw header
    resetConsole();
    drawTitle("Results");
    cout << left << fixed << INDENT << INDENT
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
        
    //Draw divider
    cout << INDENT << INDENT << divider(196) << endl;

    //Draw rows
    unsigned int count = 0; //declared in higher scope for footer
    for(;count<MAX_RESULTS && count<airports.size(); count++){
        Airport* a = airports.at(count);
        string elevation = (a->getElevation() == SHRT_NULL) ? "" : to_string(a->getElevation());
        string latitude = isnan(a->getLatitude()) ? "" : to_string(a->getLatitude());
        string longitude = isnan(a->getLongitude()) ? "" : to_string(a->getLongitude());

        cout << INDENT << INDENT << right << setw(2) << count+1 << left << ". | "
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

    //Draw footer
    cout << endl << INDENT << "[Displaying " << count << " of " << airports.size()
         << " results]" << endl;
    
    //Pause
    awaitInput();
}

//Constructor and destructor
AirPortray::AirPortray(string dataFilePath){
    repository = new AirportRepository(dataFilePath);
}

AirPortray::~AirPortray(){
    delete(repository); //created with new so lasts out of scope
}

//Public methods
void AirPortray::openMainMenu(){
    awaitInput(); //allow user to read read info
    bool exit = false;
    while(!exit){ //main app loop
        string options[]{
            "Search Airports",
            "Sort Airports",
            "Analyse Airports",
            "Add Airport",
            "Save and Exit",
            "Exit Without Saving"
        };
        switch(openMenu("Main Menu", options, 6)){
            case 1: //Search Airports
                openSearchMenu();
                break;
            case 2: //Sort Airports
                openSortMenu();
                break;
            case 3: //Analyse Airports
                openAnalyseMenu();
                break;
            case 4: //Add Airport
                openAddAirportMenu();
                break;
            case 5: //Save and Exit
                try{
                    repository->save();
                    cout << "All changes succesfully saved!";
                    exit = true; //exit if save succeeds
                }catch(runtime_error& e){ //can't open file
                    cout << "Unable to save, " << e.what() << "\nAborting exit...\n";
                    awaitInput(); //wait for user to read before reset
                }
                break;
            case 0: //Exit without Saving
                exit = true;
                break;
        }
    }

    awaitInput(); //pause
}

void AirPortray::openAddAirportMenu(){
    //Draw title and instructions
    resetConsole();
    drawTitle("Add Airport");
    cout << INDENT << divider(35) << endl
         << INDENT << "Enter nothing for missing values.\n"
         << INDENT << "Airport Types:\n";
    int i = 0; //iteratively display types
    for(; i < NUM_AP_TYPES; i++){
        cout << INDENT << INDENT << i+1 << ". " << ((i==NUM_AP_TYPES-1) ? "Unknown" : Airport::typeToString(i)) << endl;
    }

    //Draw divider
    cout << INDENT << divider(35) << endl << endl;

    //Get inputs
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

    //Try to create airport
    int field = 0; //track which field fails
    try{
        Airport a;
        if(fields[field] != ""){ a.setType(static_cast<Airport::Type>(stoi(fields[field])-1)); } field++;
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
    }catch (invalid_argument& e){ //erroneous
        cout << endl << "Failed to add airport, invalid " << titles[field] << ": " << e.what() << "." << endl;
    }catch (out_of_range& e){ //too small/large
        cout << endl << "Failed to add airport, invalid " << titles[field] << ": value out of range." << endl;
    }

    //Pause
    awaitInput();
}

void AirPortray::openSearchMenu(){
    auto airports = repository->getAirports();
    string input; //used by nearly all options
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
        case 1: //Partial Name
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

        case 2: //Partial Municipality
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

        case 3: //Full IATA Code
            cout << INDENT << "Enter Full IATA Code: ";
            getline(cin, input);
            repository->filterByField(airports, [input](Airport* a){
                return (a->getIATACode() == input);
            });
            openAirportDisplayMenu(airports);
            break;

        case 4:{ //Type
            //Draw infomation box
            cout << INDENT << divider(25) << endl;
            cout << INDENT << "Airport Types:" << endl;
            int i = 0; //protected by case scope {}
            for(; i < NUM_AP_TYPES; i++){
                cout << INDENT << INDENT << i+1 << ". " << ((i==NUM_AP_TYPES-1) ? "Unknown" : Airport::typeToString(i)) << endl;
            }
            cout << INDENT << divider(25) << endl << endl;

            //Get input
            cout << INDENT << "Enter Type: ";
            getline(cin, input);

            //Try to process
            try{ //stoi fails on invalid input
                repository->filterByField(airports, [input](Airport* a){
                    return (a->getType() == static_cast<Airport::Type>(stoi(input)-1));
                });
                openAirportDisplayMenu(airports);
            }catch(invalid_argument& e){ //erroneous
                cout << endl << "Invalid Type, aborting search.\n";
                awaitInput();
            }catch(out_of_range& e){ //too small/large
                cout << endl << "Invalid Type, aborting search.\n";
                awaitInput();
            }
            break;
        }

        case 5: //Coordinates within Radius
            try{
                double latitude, longitude, radius;

                //Get input
                cout << INDENT << "Enter Latitude: ";
                getline(cin, input);
                latitude = stod(input);
                cout << INDENT << "Enter Longitude: ";
                getline(cin, input);
                longitude = stod(input);
                cout << INDENT << "Enter Radius (m): ";
                getline(cin, input);
                radius = stoi(input);

                //Filter and output
                repository->filterByDistanceFromCoordinates(airports, latitude, longitude, radius);
                repository->sortByDistanceFromCoordinates(airports, latitude, longitude);
                openAirportDisplayMenu(airports);

            }catch(invalid_argument& e){ //erroneous input
                cout << endl << "Invalid value, aborting search.\n";
                awaitInput();
            }catch(out_of_range& e){ //too small/large input
                cout << endl << "Invalid value, aborting search.\n";
                awaitInput();
            }
            break;

        case 6: //Full country code
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
    string input; //used by nearly all options
    string options[]{
        "Name",
        "Type",
        "Country Code",
        "Elevation",
        "Proximity to Coordinates",
        "Return to Main Menu"
    };
    switch(openMenu("Sort Airports", options, 6)){
        case 1: //Name
            repository->sortByField<string>(airports, [](Airport* a){return a->getName();});
            openAirportDisplayMenu(airports);
            break;
        case 2: //Type
            repository->sortByField<Airport::Type>(airports, [](Airport* a){return a->getType();});
            openAirportDisplayMenu(airports);
            break;
        case 3: //Country Code
            repository->sortByField<string>(airports, [](Airport* a){return a->getCountry();});
            openAirportDisplayMenu(airports);
            break;
        case 4: //Elevation
            repository->sortByField<short>(airports, [](Airport* a){return a->getElevation();});
            openAirportDisplayMenu(airports);
            break;
        case 5: //Proximity to Coordinates
            double latitude, longitude;
            try{
                //Get input
                cout << INDENT << "Enter Latitude: ";
                getline(cin, input);
                latitude = stod(input);
                cout << INDENT << "Enter Longitude: ";
                getline(cin, input);
                longitude = stod(input);

                //Sort and display
                repository->sortByDistanceFromCoordinates(airports, latitude, longitude);
                openAirportDisplayMenu(airports);
            }catch(invalid_argument& e){ //erroneous input
                cout << endl << "Invalid value, aborting search.\n";
                awaitInput();
            }catch(out_of_range& e){ //too small/large input
                cout << endl << "Invalid value, aborting search.\n";
                awaitInput();
            }
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
        case 1: //Highest and Lowest Elevation
            openHighestAndLowestElevationMenu();
            break;

        case 2:{ //Missing IATA Codes
            auto airports = repository->getAirports(); //protected by case scope
            repository->filterByField(airports, [](Airport* a){return a->getIATACode() == "";});
            openAirportDisplayMenu(airports);
            break;
        }

        case 3:{ //Distance
            openCalculateDistanceMenu();
            break;
        }

        case 4: //Count by Type
            openCountByTypeMenu();
            break;

    }
}

void AirPortray::openHighestAndLowestElevationMenu(){
    //Draw title
    resetConsole();
    drawTitle("Highest and Lowest Elevations");

    //Sort by elevation
    auto airports = repository->getAirports();
    repository->sortByField<short>(airports, [](Airport* a){return a->getElevation();});
    repository->filterByField(airports, [](Airport* a){return a->getElevation() != SHRT_NULL;});

    //Output first and last
    cout << INDENT << INDENT << "The highest airport is \"" << airports.back()->getName()
            << "\" which is " << airports.back()->getElevation() << "ft above sea-level." << endl;
    cout << INDENT << INDENT << "The lowest airport is \"" << airports.front()->getName()
            << "\" which is " << airports.front()->getElevation() << "ft above sea-level." << endl;

    //Pause
    awaitInput();
}

void AirPortray::openCalculateDistanceMenu(){
    //Draw title
    resetConsole();
    drawTitle("Highest and Lowest Elevations");

    //Get inputs
    string input;
    cout << INDENT << INDENT << "Enter First Airport IATA Code: ";
    getline(cin, input);
    Airport* a1 = repository->getAirportByIATA(input);
    cout << INDENT << INDENT << "Enter Second Airport IATA Code: ";
    getline(cin, input);
    Airport* a2 = repository->getAirportByIATA(input);

    //Try and calculate and output
    if(a1 == nullptr || a2 == nullptr){ //if either input is invalid
        cout << endl << "Invalid IATA Code, aborting search.\n";
    }else{
        cout << endl << INDENT << INDENT << "Distance: "
            << repository->calculateDistanceBetweenAirports(a1, a2) << " m" << endl;
    }
    
    //Pause
    awaitInput();
}

void AirPortray::openCountByTypeMenu(){
    //Draw title
    resetConsole();
    drawTitle("Airport Count By Type");

    //Output counts
    auto countByType = repository->calculateAirportCountByType();
    for(auto i: countByType){
        cout << INDENT << INDENT << left << setw(17)
                << ((Airport::typeToString(i.first) == "" ? "Unknown" : Airport::typeToString(i.first)) + ":")
                << i.second << endl;
    }

    //Pause
    awaitInput();
}