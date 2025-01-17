/////////////////////////////////////////////////////////////
//#  Program name: Pet_Rescue_App                         //
//#  Author: Danielle Lloyd                              //
//#  Date last updated: 1/15/2025                       // 
//#  Purpose: Pet Rescue Menu Driven Program           //
////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void addPet();
void viewPets();
void displayMenu(); // Creates a menu for the user to choose from

int main() {
    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addPet();
                break;
            case 2:
                viewPets();
                break;
            case 3:
                running = false;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}

void displayMenu() {
    cout << "1. Add a pet" << endl;
    cout << "2. View pets" << endl;
    cout << "3. Quit" << endl;
    cout << "Enter your choice: ";
}

void addPet() {
    string name, species, breed, color;

    cout << "Enter pet's name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter pet's species: ";
    getline(cin, species);
    cout << "Enter pet's breed: ";
    getline(cin, breed);
    cout << "Enter pet's color: ";
    getline(cin, color);

    ofstream outFile("pets.txt", ios::app);
    // ios::app is used to append to the file instead of overwriting it
    if (outFile.is_open()) {
        outFile << "Name: " << name << ", Species: " << species << ", Breed: " << breed << ", Color: " << color << endl;
        outFile.close();
        cout << "Pet added successfully!" << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
}

void viewPets() {
    string line;
    ifstream inFile("pets.txt");
    // ios::in is used to read from the file
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "Unable to open file." << endl;
    }
}
