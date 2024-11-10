/////////////////////////////////////////////////////////////////////////////////
//#  Program name: M03_Program_2A.cpp                                         //
//#  Author: Danielle Lloyd                                                  //
//#  Date last updated: 11/10/2024                                          // 
//#  Purpose: Reads words from text file and displays non-duplicate words  //
////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <set>
#include <fstream>

using namespace std;

int main (){
    ifstream inputFile("words.txt");
    set<string> uniqueWords;
    string word;
    if(!inputFile){
        cerr<<"Error: Unable to open file!"<< endl;
        return 1;
    }
    
    while (inputFile >> word){
        uniqueWords.insert(word);
    }

    inputFile.close();

    cout<<"Here are the unique words in ascending order: "<< endl;
    for(const auto& w : uniqueWords){
        cout<< w << endl;
    }
    return 0; 
};















