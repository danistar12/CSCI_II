/////////////////////////////////////////////////////////////
//#  Program name: M03_Program1A.cpp                       //
//#  Author: Danielle Lloyd                              //
//#  Date last updated: 11/06/2024                      // 
//#  Purpose: Manipulate data involving StereoReceiver //
////////////////////////////////////////////////////////

#include <iostream>
#include <array>
#include <numeric>
#include <algorithm>
using namespace std;

const int numModules = 16;

//While loop to secure user enters correct score between 0-15
void getData(array<int, numModules>& scores) {
    for (int i = 0; i < numModules; ++i) {
        int score;
        while (true) {
            cout << "Enter score for Module " << i + 1 << " (0-15): ";
            cin >> score;
            if (score >= 0 && score <= 15) {
                scores[i] = score;
                break;
            } else {
                cout << "Invalid score. Please enter a number between 0 and 15." << endl;
            }
        }
    }
}
int highScore(const array<int, numModules>& scores){
    return max_element(scores.begin(), scores.end())-scores.begin();
}
int lowScore(const array<int, numModules>& scores){
    return min_element(scores.begin(), scores.end())- scores.begin();
}

int main() {
    array<int, numModules> scores;
    getData(scores);

    int highest = highScore(scores);
    int lowest = lowScore(scores);
    double average = accumulate(scores.begin(), scores.end(), 0.0) / numModules;

    cout << "Fall 2024 Quiz Grades:\n";
    for (int i = 0; i < numModules; ++i) {
        cout << "Module " << i + 1 << ": " << scores[i] << endl;
    }

    cout << "Average Grade: " << average << endl;
    cout << "Your lowest score was in Module " << lowest + 1 << " with " << scores[lowest] << "." << endl;
    cout << "Your highest score was in Module " << highest + 1 << " with " << scores[highest] << "." << endl;

    return 0;
}