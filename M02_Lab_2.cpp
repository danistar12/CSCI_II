/////////////////////////////////////////////////////////////
//#  Program name: M01_Lab_2.cpp                          //
//#  Author: Danielle Lloyd                              //
//#  Date last updated: 10/24/2024                      // 
//#  Purpose: Manipulate data involving StereoReceiver //
////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <limits>

using namespace std;

class StereoReceiver {
    private:
        string manufacturer;
        string model;
        string serial_number;
        int wattage;
        int channels;
        string band;
        double frequency;
        int volume;
        bool power;
        string color;         //own attributes added of color
        int quantity;        // and quantity 
    public:
        //constructor// co pilot helped here //
        StereoReceiver(const string& mfg, const string& mdl, const string& sn, int w, int ch, const string& clr, int q):
            manufacturer(mfg), model(mdl), serial_number(sn), wattage(w), channels(ch), 
            band("FM"), frequency(0.0), volume(5), power(false),
            color(clr), quantity(q){}

        // Accessor methods//
        string get_manufacturer() const {return manufacturer;}
        string get_model() const {return model;}
        string get_serial_number() const {return serial_number;}
        int get_wattage() const {return wattage;}
        int get_channels() const {return channels;}
        string get_band() const {return band;}
        double get_frequency() const {return frequency;}
        int get_volume() const {return volume;}
        bool get_power() const {return power;}
        string get_color() const {return color;}
        int get_quantity() const {return quantity;}

        //mutator methods//
        void set_power(bool pwr){power=pwr;}
        void set_volume(int vol){volume = (vol >= 0 && vol <= 10) ? vol : volume; }
        void set_band(const string& b) { band = (b == "AM" || b == "FM") ? b : band; }
        void set_frequency(double freq) { frequency = freq; }
        void set_color(const string& clr){color =clr;}
        void set_quantity(int q){quantity=q;}
};

//function to get a validated integer input//
int get_validated_int (const string &prompt){
    int value;
    cout << prompt;
    while (!(cin >> value)){
        cout << "Invalid input. Please enter an integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

//function to get a validated string input//
string get_validated_str(const string &prompt){
    string value;
    cout << prompt;
    cin.ignore();
    getline(cin, value);
    return value;
}

//main program//
int main(){

    //user prompts//
    string manufacturer = get_validated_str("Enter the Manufacturer: ");
    string model = get_validated_str("Enter the Model: ");
    string serial_number = get_validated_str("Enter the Serial Number: ");
    int wattage = get_validated_int("Enter the wattage: ");
    int channels = get_validated_int("Enter the number of channels: ");
    string color = get_validated_str("Enter the Color: ");
    int quantity = get_validated_int("Enter the amount in stock: ");

    //stereo object created//
    StereoReceiver stereo(manufacturer, model, serial_number, wattage, channels, color, quantity);

    //Display stereo information//
    cout << "\n|| Stereo Reciever's Information "<< endl;
    cout << "|| Manufacturer: " << stereo.get_manufacturer() << endl;
    cout << "|| Model: " << stereo.get_model() << endl;
    cout << "|| Serial Number: " << stereo.get_serial_number() << endl;
    cout << "|| Wattage: " << stereo.get_wattage() << endl;
    cout << "|| Number of Channels: " << stereo.get_channels() << endl;
    cout << "|| Band: " << stereo.get_band() << endl;
    cout << "|| Frequency: " << stereo.get_frequency() << endl;
    cout << "|| Volume: " << stereo.get_volume() << endl;
    cout << "|| Power: " << stereo.get_power() << endl;
    cout << "|| Color: " << stereo.get_color() << endl;
    cout << "|| Quantity: " << stereo.get_quantity() << endl;
    //Turn on Stereo//
    stereo.set_power(true);

    //Change attributes if needed//
    char update;
    do {
        cout << "Would you like to update the stereo settings? (y/n): ";
        cin >> update;
        if (update =='y' || update == 'Y'){
            int choice;
            cout << "\nPlease choose which setting to update" << endl;
            cout << "1. Change Band " << endl;
            cout << "2. Set Frequency " << endl;
            cout << "3. Change Volume " << endl;
            cout << "4. Turn Stereo off " << endl;
            cout << "5. Update Quantity " << endl;
            cout << "6. Exit " << endl;
            choice = get_validated_int("Enter your choice: ");
            if (choice == 1) {
                string band = get_validated_str("\nEnter the band (AM/FM) ");
                stereo.set_band(band);
            } else if (choice == 2) {
                double frequency;
                cout << "\nEnter the frequency: ";
                cin >> frequency;
                stereo.set_frequency(frequency);
            } else if (choice == 3) {
                int volume = get_validated_int("\nEnter the volume (0-10): ");
                stereo.set_volume(volume);
            } else if (choice == 4) {
                stereo.set_power(false);
                cout << "\nThe stereo is now off ";
            } else if (choice == 5) {
                int quantity = get_validated_int("\nEnter the new quantity available: ");
                stereo.set_quantity(quantity);
            } else if (choice == 6) {
                break;
            } else {
                cout << "Invalid choice. Please try again. "<< endl;
            }
            cout << "\nUpdated Stereo Settings: "<< endl;
            cout << "Power: " << (stereo.get_power()? "On" : "Off") << endl;
            cout << "Band: " << stereo.get_band() << endl;
            cout << "Frequency: " << stereo.get_frequency() << endl;
            cout << "Volume: " << stereo.get_volume() << endl;
            cout << "Quantity: " << stereo.get_quantity() << endl;
        }
    } while (update == 'y' || update == 'Y');
    //Turn off Stereo
    stereo.set_power(false);
    cout << "Stereo is now off! Goodbye." << endl;
};