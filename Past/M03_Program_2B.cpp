/////////////////////////////////////////////////////////////////////////////////
//#  Program name: M03_Program_2A.cpp                                         //
//#  Author: Danielle Lloyd                                                  //
//#  Date last updated: 11/10/2024                                          // 
//#  Purpose: To Store State Information and Query by Abbreviation         //
////////////////////////////////////////////////////////////////////////////

#include <iostream> 
#include <fstream> 
#include <map> 
#include <string> 

using namespace std;
//create s truct to store information
struct StateInfo {
    string fullName;
    string governor;
    string stateFlower;
};

int main (){
    ifstream inputFile("states.txt");
    map<string, StateInfo> stateMap;       //createmap//
    string abbreviation, fullName, governor, stateFlower;

    //throw error for bad file read //
    if (!inputFile){
        cerr << "Error: Unable to open file!"<< endl;
        return 1;
    }
    while (inputFile >> abbreviation >> fullName >> governor >> stateFlower){
        StateInfo info = {fullName, governor, stateFlower};
        stateMap[abbreviation] = info;
    }
    inputFile.close();
    // create user input //
    
    string userInput;
    cout << "Enter the state abbreviation (or 'EXIT' to quit): ";
    while (true) {
        getline(cin, userInput);
        if (userInput == "EXIT"|| userInput == "exit"){
            break;                  //create a break out for 'exit'
        }
        auto it = stateMap.find(userInput);
        if (it != stateMap.end()){
            cout << "State: " << it->second.fullName << endl;
            cout << "Governor: " << it->second.governor << endl;
            cout << "State Flower: " << it->second.stateFlower << endl;
        } else {
            cout<< "Invalid State abbreviation! "<< endl;
        }
        cout << "\nEnter state abbreviation (or 'EXIT' to quit): ";
    }  
    return 0; 
}