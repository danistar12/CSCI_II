/////////////////////////////////////////////////////////////
//#  Program name: M03_Program_1B.cpp                     //
//#  Author: Danielle Lloyd                              //
//#  Date last updated: 11/06/2024                      // 
//#  Purpose: Tracking personal Computer Inventory     //
////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class PersonalComputer {
private:
    string manufacturer;
    string formFactor;
    string serialNumber;
    string processor;
    int ram;
    string storageType;
    int storageSize;

public:
    //constructor//
    PersonalComputer(string man, string form, string serial, string proc, int r, string storageT, int storageS) 
        : manufacturer(man), formFactor(form), serialNumber(serial), processor(proc), ram(r), storageType(storageT), storageSize(storageS) {
        if (r <= 0 || storageS <= 0) {
            throw invalid_argument("Invalid RAM or storage size");
        }
    }
    //Methods//
    string getManufacturer() const { return manufacturer; }
    string getFormFactor() const { return formFactor; }
    string getSerialNumber() const { return serialNumber; }
    string getProcessor() const { return processor; }
    int getRAM() const { return ram; }
    string getStorageType() const { return storageType; }
    int getStorageSize() const { return storageSize; }     

    void setRAM(int newRam){
        if (newRam > 0 & newRam <= 64 ){
            ram = newRam;
        }else {
            throw invalid_argument("Invalid RAM size");
        }
    }

    void setStorage(string newStorageType, int newStorageSize){
        if (newStorageSize > 0 & newStorageSize <= 512){
            storageType = newStorageType;
            storageSize = newStorageSize;
        } else {
            throw invalid_argument("Invalid storage size");
        }
    }
    string toString() const {
        return "Manufacturer: " + manufacturer + ", Form Factor: " + formFactor + ", Serial Number: " + serialNumber + 
               ", Processor: " + processor + ", RAM: " + to_string(ram) + "GB, Storage: " + storageType + " " + to_string(storageSize) + "GB";
    }
};

int main() {
    vector<PersonalComputer> inventory;
    char choice;

    do {
        string manufacturer, formFactor, serialNumber, processor, storageType;
        int ram, storageSize;
        // use getline to account if there are spaces added //
        cout << "Enter Manufacturer: ";
        cin.ignore(); 
        getline(cin, manufacturer);

        cout << "Enter Form Factor (laptop/desktop): ";
        getline(cin, formFactor);

        cout << "Enter Serial Number: ";
        getline(cin, serialNumber);

        cout << "Enter Processor: ";
        getline(cin, processor);

        cout << "Enter RAM (GB): ";
        cin >> ram;

        cout << "Enter Storage Type (UFS/SDD/HDD): ";
        cin.ignore(); 
        getline(cin, storageType);

        cout << "Enter Storage Size (GB/TB): ";
        cin >> storageSize;

        try {
            PersonalComputer pc(manufacturer, formFactor, serialNumber, processor, ram, storageType, storageSize);
            inventory.push_back(pc);
            cout << "Added: " << pc.toString() << endl;
            cout << "Total PCs in inventory: " << inventory.size() << endl;
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
        }

        cout << "Do you want to update RAM or storage for any PC in the inventory? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "Enter the index of the PC to update (starting from 0): ";
            int index;
            cin >> index;
            //Use of methods to update storage, ram etc //
            if (index >= 0 && index < inventory.size()) {
                cout << "Enter new RAM (GB): ";
                int newRam;
                cin >> newRam;
                cout << "Enter new Storage Type (UFS/SDD/HDD): ";
                string newStorageType;
                cin.ignore(); 
                getline(cin, newStorageType);
                cout << "Enter new Storage Size (GB/TB): ";
                int newStorageSize;
                cin >> newStorageSize;
                try {
                    inventory[index].setRAM(newRam);
                    inventory[index].setStorage(newStorageType, newStorageSize);
                    cout << "Updated: " << inventory[index].toString() << endl;
                } catch (const invalid_argument& e) {
                    cerr << "Error: " << e.what() << endl;
                }
            } else {
                cout << "Invalid index." << endl;
            }
        }

        cout << "Do you want to add another PC? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    //Prints Current Inventory List??
    cout << "\nInventory List:\n";
    for (const auto& pc : inventory) {
        cout << pc.toString() << endl;
    }

    return 0;
}