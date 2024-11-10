/////////////////////////////////////////////////////////////
//#  Program name: M02_Program_1.cpp                      //
//#  Author: Danielle Lloyd                              //
//#  Date last updated: 10/31/2024                      // 
//#  Purpose: Manipulate data involving date           //
////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <stdexcept>

using namespace std;

class Date {
private:
    int month;
    int day;
    int year;

public:
    // Constructor
    Date(int month, int day, int year) {
        setMonth(month);
        setDay(day);
        setYear(year);
    }

    // Mutator methods
    void setMonth(int month) {
        if (month < 1 || month > 12) {
            throw invalid_argument("Invalid Value!! The month must be a valid month (1-12).");
        }
        this->month = month;
    }

    void setDay(int day) {
        if (day < 1 || (month == 2 && day > 28) || (monthHas30Days() && day > 30) || day > 31) {
            throw invalid_argument("Invalid Value!! The day must be in the appropriate range for that month.");
        }
        this->day = day;
    }

    void setYear(int year) {
        if (year < 1900 || year > 2020) {
            throw invalid_argument("Invalid Value!! The year must be between 1900 and 2024.");
        }
        this->year = year;
    }

    // Helper method to check if month has 30 days
    bool monthHas30Days() {
        return month == 4 || month == 6 || month == 9 || month == 11;
    }

    string toString() {
        map<int, string> monthNames = {
            {1, "January"}, {2, "February"}, {3, "March"}, {4, "April"}, {5, "May"}, {6, "June"},
            {7, "July"}, {8, "August"}, {9, "September"}, {10, "October"}, {11, "November"}, {12, "December"}
        };
        return monthNames[month] + " " + to_string(day) + ", " + to_string(year);
    }
};

// Function to get a validated integer input
int getValidatedInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input! Please enter an integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return value;
}

// Function to validate and set date
void setDate(Date& date, int& month, int& day, int& year) {
    while (true) {
        try {
            month = getValidatedInt("Enter month (1-12) or 0 to quit: ");
            if (month == 0) return; // Quit the loop
            date.setMonth(month);
            
            day = getValidatedInt("Enter day (1-31): ");
            date.setDay(day);
            
            year = getValidatedInt("Enter year (1900-2024): ");
            date.setYear(year);

            break;
        } catch (const invalid_argument& e) {
            cerr << e.what() << endl;
        }
    }
}

int main() {
    int month, day, year;

    Date date(1, 1, 1900); // Default date initialization ??

    while (true) {
        cout << "\nYour current date: " << date.toString() << endl;
        setDate(date, month, day, year);

        // Check if user chose to quit ??
        if (month == 0) break;

        cout << "Your updated date: " << date.toString() << endl;
    }

    cout << "Thanks for using the Date Loop Converter, Later!" << endl;
    return 0;
}