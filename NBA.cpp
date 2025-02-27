#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;

void createTables(sqlite3 *db);
void insertData(sqlite3 *db);
void queryData(sqlite3 *db);
void viewTeamsInDivision(sqlite3 *db);
void addNewTeam(sqlite3 *db);
void addPlayer(sqlite3 *db);
void viewRoster(sqlite3 *db);
void viewGameInfo(sqlite3 *db);
void addGameInfo(sqlite3 *db);
void printMenu();

int main() {
    sqlite3 *db;
    int rc;

    // Open a connection to the database
    rc = sqlite3_open("nba.db", &db);
    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    } else {
        cout << "Opened database successfully" << endl;
    }

    // Create tables
    createTables(db);

    // Insert data
    insertData(db);

    int choice;
    do {
        printMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                viewTeamsInDivision(db);
                break;
            case 2:
                addNewTeam(db);
                break;
            case 3:
                addPlayer(db);
                break;
            case 4:
                viewRoster(db);
                break;
            case 5:
                viewGameInfo(db);
                break;
            case 6:
                addGameInfo(db);
                break;
            case 0:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}

void createTables(sqlite3 *db) {
    const char *sql = R"(
        -- Create the Conference table
        CREATE TABLE IF NOT EXISTS Conference (
            conference_id INTEGER PRIMARY KEY AUTOINCREMENT,
            conference_name TEXT NOT NULL
        );

        -- Create the Division table
        CREATE TABLE IF NOT EXISTS Division (
            division_id INTEGER PRIMARY KEY AUTOINCREMENT,
            division_name TEXT NOT NULL,
            conference_id INTEGER,
            FOREIGN KEY (conference_id) REFERENCES Conference(conference_id)
        );

        -- Create the Team table
        CREATE TABLE IF NOT EXISTS Team (
            team_id INTEGER PRIMARY KEY AUTOINCREMENT,
            team_name TEXT NOT NULL,
            mascot TEXT,
            city TEXT,
            state TEXT,
            arena TEXT,
            division_id INTEGER,
            FOREIGN KEY (division_id) REFERENCES Division(division_id)
        );

        -- Create the Player table
        CREATE TABLE IF NOT EXISTS Player (
            player_id INTEGER PRIMARY KEY AUTOINCREMENT,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            number INTEGER,
            team_id INTEGER,
            FOREIGN KEY (team_id) REFERENCES Team(team_id)
        );

        -- Create the Coach table
        CREATE TABLE IF NOT EXISTS Coach (
            coach_id INTEGER PRIMARY KEY AUTOINCREMENT,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            team_id INTEGER,
            FOREIGN KEY (team_id) REFERENCES Team(team_id)
        );

        -- Create the Game table
        CREATE TABLE IF NOT EXISTS Game (
            game_id INTEGER PRIMARY KEY AUTOINCREMENT,
            home_team_id INTEGER,
            away_team_id INTEGER,
            game_date DATETIME,
            home_team_score INTEGER,
            away_team_score INTEGER,
            arena TEXT,
            FOREIGN KEY (home_team_id) REFERENCES Team(team_id),
            FOREIGN KEY (away_team_id) REFERENCES Team(team_id)
        );
    )";

    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Tables created successfully" << endl;
    }
}

void insertData(sqlite3 *db) {
    const char *sql = R"(
        -- Insert data into the Conference table
        INSERT INTO Conference (conference_name) VALUES ('Eastern Conference');
        INSERT INTO Conference (conference_name) VALUES ('Western Conference');

        -- Insert data into the Division table
        INSERT INTO Division (division_name, conference_id) VALUES ('Atlantic', 1);
        INSERT INTO Division (division_name, conference_id) VALUES ('Central', 1);
        INSERT INTO Division (division_name, conference_id) VALUES ('Southeast', 1);
        INSERT INTO Division (division_name, conference_id) VALUES ('Northwest', 2);
        INSERT INTO Division (division_name, conference_id) VALUES ('Pacific', 2);
        INSERT INTO Division (division_name, conference_id) VALUES ('Southwest', 2);

        -- Insert data into the Team table
        INSERT INTO Team (team_name, mascot, city, state, arena, division_id) VALUES ('Boston Celtics', 'Celtics', 'Boston', 'MA', 'TD Garden', 1);
        INSERT INTO Team (team_name, mascot, city, state, arena, division_id) VALUES ('Brooklyn Nets', 'Nets', 'Brooklyn', 'NY', 'Barclays Center', 1);
        INSERT INTO Team (team_name, mascot, city, state, arena, division_id) VALUES ('Chicago Bulls', 'Bulls', 'Chicago', 'IL', 'United Center', 2);
        INSERT INTO Team (team_name, mascot, city, state, arena, division_id) VALUES ('Miami Heat', 'Heat', 'Miami', 'FL', 'FTX Arena', 3);
        INSERT INTO Team (team_name, mascot, city, state, arena, division_id) VALUES ('Denver Nuggets', 'Nuggets', 'Denver', 'CO', 'Ball Arena', 4);
        INSERT INTO Team (team_name, mascot, city, state, arena, division_id) VALUES ('Golden State Warriors', 'Warriors', 'San Francisco', 'CA', 'Chase Center', 5);
        INSERT INTO Team (team_name, mascot, city, state, arena, division_id) VALUES ('Los Angeles Lakers', 'Lakers', 'Los Angeles', 'CA', 'Staples Center', 5);
        INSERT INTO Team (team_name, mascot, city, state, arena, division_id) VALUES ('Dallas Mavericks', 'Mavericks', 'Dallas', 'TX', 'American Airlines Center', 6);

        -- Insert data into the Player table
        INSERT INTO Player (first_name, last_name, number, team_id) VALUES ('Jayson', 'Tatum', 0, 1);
        INSERT INTO Player (first_name, last_name, number, team_id) VALUES ('Kevin', 'Durant', 7, 2);
        INSERT INTO Player (first_name, last_name, number, team_id) VALUES ('Zach', 'LaVine', 8, 3);
        INSERT INTO Player (first_name, last_name, number, team_id) VALUES ('Jimmy', 'Butler', 22, 4);
        INSERT INTO Player (first_name, last_name, number, team_id) VALUES ('Nikola', 'Jokic', 15, 5);
        INSERT INTO Player (first_name, last_name, number, team_id) VALUES ('Stephen', 'Curry', 30, 6);
        INSERT INTO Player (first_name, last_name, number, team_id) VALUES ('LeBron', 'James', 23, 7);
        INSERT INTO Player (first_name, last_name, number, team_id) VALUES ('Luka', 'Doncic', 77, 8);

        -- Insert data into the Coach table
        INSERT INTO Coach (first_name, last_name, team_id) VALUES ('Ime', 'Udoka', 1);
        INSERT INTO Coach (first_name, last_name, team_id) VALUES ('Steve', 'Nash', 2);
        INSERT INTO Coach (first_name, last_name, team_id) VALUES ('Billy', 'Donovan', 3);
        INSERT INTO Coach (first_name, last_name, team_id) VALUES ('Erik', 'Spoelstra', 4);
        INSERT INTO Coach (first_name, last_name, team_id) VALUES ('Michael', 'Malone', 5);
        INSERT INTO Coach (first_name, last_name, team_id) VALUES ('Steve', 'Kerr', 6);
        INSERT INTO Coach (first_name, last_name, team_id) VALUES ('Frank', 'Vogel', 7);
        INSERT INTO Coach (first_name, last_name, team_id) VALUES ('Jason', 'Kidd', 8);

        -- Insert data into the Game table
        INSERT INTO Game (home_team_id, away_team_id, game_date, home_team_score, away_team_score, arena) VALUES (7, 1, '2025-02-26 19:00:00', 102, 99, 'Staples Center');
        INSERT INTO Game (home_team_id, away_team_id, game_date, home_team_score, away_team_score, arena) VALUES (8, 2, '2025-02-27 19:00:00', 110, 105, 'American Airlines Center');
    )";

    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Data inserted successfully" << endl;
    }
}

void queryData(sqlite3 *db) {
    const char *sql = "SELECT * FROM Player;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "Players:" << endl;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        cout << sqlite3_column_text(stmt, 1) << " " << sqlite3_column_text(stmt, 2) << " (Number: " << sqlite3_column_int(stmt, 3) << ", Team ID: " << sqlite3_column_int(stmt, 4) << ")" << endl;
    }

    if (rc != SQLITE_DONE) {
        cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
}

void viewTeamsInDivision(sqlite3 *db) {
    int division_id;
    cout << "Enter Division ID: ";
    cin >> division_id;

    string sql = "SELECT team_name FROM Team WHERE division_id = " + to_string(division_id) + ";";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "Teams in Division " << division_id << ":" << endl;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        cout << sqlite3_column_text(stmt, 0) << endl;
    }

    if (rc != SQLITE_DONE) {
        cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
}

void addNewTeam(sqlite3 *db) {
    string team_name, mascot, city, state, arena;
    int division_id;

    cout << "Enter team name: ";
    cin.ignore();
    getline(cin, team_name);
    cout << "Enter mascot: ";
    getline(cin, mascot);
    cout << "Enter city: ";
    getline(cin, city);
    cout << "Enter state: ";
    getline(cin, state);
    cout << "Enter arena: ";
    getline(cin, arena);
    cout << "Enter division ID: ";
    cin >> division_id;

    string sql = "INSERT INTO Team (team_name, mascot, city, state, arena, division_id) VALUES ('" + team_name + "', '" + mascot + "', '" + city + "', '" + state + "', '" + arena + "', " + to_string(division_id) + ");";
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Team added successfully" << endl;
    }
}

void addPlayer(sqlite3 *db) {
    string first_name, last_name;
    int number, team_id;

    cout << "Enter first name: ";
    cin.ignore();
    getline(cin, first_name);
    cout << "Enter last name: ";
    getline(cin, last_name);
    cout << "Enter number: ";
    cin >> number;
    cout << "Enter team ID: ";
    cin >> team_id;

    string sql = "INSERT INTO Player (first_name, last_name, number, team_id) VALUES ('" + first_name + "', '" + last_name + "', " + to_string(number) + ", " + to_string(team_id) + ");";
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Player added successfully" << endl;
    }
}

void viewRoster(sqlite3 *db) {
    int team_id;
    cout << "Enter Team ID: ";
    cin >> team_id;

    string sql = "SELECT first_name, last_name, number FROM Player WHERE team_id = " + to_string(team_id) + ";";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "Roster for Team " << team_id << ":" << endl;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        cout << sqlite3_column_text(stmt, 0) << " " << sqlite3_column_text(stmt, 1) << " (Number: " << sqlite3_column_int(stmt, 2) << ")" << endl;
    }

    if (rc != SQLITE_DONE) {
        cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
}

void viewGameInfo(sqlite3 *db) {
    int game_id;
    cout << "Enter Game ID: ";
    cin >> game_id;

    string sql = "SELECT home_team_id, away_team_id, game_date, home_team_score, away_team_score, arena FROM Game WHERE game_id = " + to_string(game_id) + ";";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        cout << "Home Team ID: " << sqlite3_column_int(stmt, 0) << endl;
        cout << "Away Team ID: " << sqlite3_column_int(stmt, 1) << endl;
        cout << "Game Date: " << sqlite3_column_text(stmt, 2) << endl;
        cout << "Home Team Score: " << sqlite3_column_int(stmt, 3) << endl;
        cout << "Away Team Score: " << sqlite3_column_int(stmt, 4) << endl;
        cout << "Arena: " << sqlite3_column_text(stmt, 5) << endl;
    } else {
        cerr << "No game found with ID " << game_id << endl;
    }

    if (rc != SQLITE_DONE) {
        cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
}

void addGameInfo(sqlite3 *db) {
    int home_team_id, away_team_id, home_team_score, away_team_score;
    string game_date, arena;

    cout << "Enter home team ID: ";
    cin >> home_team_id;
    cout << "Enter away team ID: ";
    cin >> away_team_id;
    cout << "Enter game date (YYYY-MM-DD HH:MM:SS): ";
    cin.ignore();
    getline(cin, game_date);
    cout << "Enter home team score: ";
    cin >> home_team_score;
    cout << "Enter away team score: ";
    cin >> away_team_score;
    cout << "Enter arena: ";
    cin.ignore();
    getline(cin, arena);

    string sql = "INSERT INTO Game (home_team_id, away_team_id, game_date, home_team_score, away_team_score, arena) VALUES (" + to_string(home_team_id) + ", " + to_string(away_team_id) + ", '" + game_date + "', " + to_string(home_team_score) + ", " + to_string(away_team_score) + ", '" + arena + "');";
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Game information added successfully" << endl;
    }
}

void printMenu() {
    cout << "\nMenu:" << endl;
    cout << "1. View teams in a division" << endl;
    cout << "2. Add a new team" << endl;
    cout << "3. Add a player" << endl;
    cout << "4. View roster for a team" << endl;
    cout << "5. View game information" << endl;
    cout << "6. Add game information" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}