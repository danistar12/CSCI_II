//# Program name: M01_Lab_part_1.cpp           //
//# Author: Danielle Lloyd                     //
//# Date last updated: 10/23/2024              // 
//# Purpose: Manipulate data involving the Cube//
/////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <limits>
using namespace std;
//Cube class definitions//
class Cube 
{
private: 
    int length;
    int width;
    int height;
    string color;

public:
    //create constructor//
    Cube(int l, int w, int h, const string &c) : length(l), width(w), height(h), color(c) {}   //copilot helped here

    //accessor methods//
    int get_length() const {return length;}
    int get_width()  const {return width;}
    int get_height() const {return height;}
    string get_color() const {return color;}

    //mutator methods//
    void set_length(int l){length=l;}
    void set_width(int w){width=w;}
    void set_height(int h){height=h;}
    void set_color (const string &c){color=c;}

    //calculateVolume method//
    int calculate_volume() const {return length*width*height;}
};
// Function prototypes to vaildate user input // copilot helped here //
int get_validated_int(const string &prompt);
string get_validated_str(const string &prompt);

//main program//
int main()
{
    int length, width, height;
    string color;

    //prompts user for input//
    length = get_validated_int("What is the length of your Cube?? ");
    width = get_validated_int("What is the width of your Cube?? ");
    height = get_validated_int("What is the height of your Cube?? ");
    color = get_validated_str("What color is your Cube?!? ");

    //create the Cube object//
    Cube my_cube(length, width, height, color);

    char update;
    do {
        //display the cubes details//
        cout << "Your Cube's dimensions:"<< endl;
        cout << "Length: " << my_cube.get_length() << endl;
        cout << "Width: " << my_cube.get_width() <<endl;
        cout << "Height: " << my_cube.get_height()<<endl;
        cout << "Color: " << my_cube.get_color()<<endl;
        cout << "Volume: " << my_cube.calculate_volume()<<endl;

        cout << "\nWould you like to update the Cube's attributes? (y/n): ";
        cin >> update;
        if (update=='y' || update == 'Y'){
            cout << "Update your Cube's attributes: "<< endl;
            my_cube.set_length(get_validated_int("Length: "));
            my_cube.set_width(get_validated_int("Width: "));
            my_cube.set_height(get_validated_int("Height: "));
            my_cube.set_color(get_validated_str("Color: "));
        }
    } while (update == 'y' || update == 'Y');
        cout << "Your Cube's Final Dimensions: " << endl;
        cout << "Length: "<< my_cube.get_length() << endl;
        cout << "Width: " << my_cube.get_width() << endl;
        cout << "Height: " << my_cube.get_height() << endl;
        cout << "Color: " << my_cube.get_color() << endl;
        cout << "volume: " << my_cube.calculate_volume() << endl;
    return 0;
}
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
