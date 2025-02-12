/////////////////////////////////////////////////////////////
//#  Program name: Facts.cpp                              //
//#  Author: Danielle Lloyd                              //
//#  Date last updated: 2/12/2025                       // 
//#  Purpose: Opens connection to the facts db         //
////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sqlite3.h>
using namespace std;

// Callback function to print the results of the select query
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    cout << endl;
    return 0;
}

int main() {
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    // Open a connection to the database
    rc = sqlite3_open("factdb.db", &db);

    if (rc) {
        // If the connection fails, print an error message and end the program
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return(1);
    } else {
        // If the connection is successful, print a success message
        cout << "Opened database successfully" << endl;
    }

    // Execute a select query and use the callback function to print the results
    const char* sql = "SELECT * FROM facts;";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        // If the query execution fails, print an error message
        cerr << "SQL error: " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
    } else {
        // If the query execution is successful, print a success message
        cout << "Query executed successfully" << endl;
    }

    // Close the database connection
    sqlite3_close(db);

    return 0;
}

