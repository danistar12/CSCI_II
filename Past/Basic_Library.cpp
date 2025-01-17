/////////////////////////////////////////////////////////////
//#  Program name: Basic_Library.cpp                      //
//#  Author: Danielle Lloyd                              //
//#  Date last updated: 12/12/2024                      // 
//#  Purpose: This is a basic Library Console Application//
////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

//Tis will constitute as both user and staff
class User {
private:
    std::string name;
    int userId;

public:
    User(const std::string &n, int id) : name(n), userId(id) {}

    std::string getName() const { return name; }
    int getUserId() const { return userId; }
};

class Staff : public User {
public:
    Staff(const std::string &n, int id) : User(n, id) {}
};
//Library item is the base class for all the items in the library
class LibraryItem {
private:
    std::string title;
    std::string description;
    std::string genre;
    double price;
    bool checkedOut;
    int checkedOutBy; // User ID of the person who checked out the item

public:
    LibraryItem(const std::string &t, const std::string &d, const std::string &g, double p)
        : title(t), description(d), genre(g), price(p), checkedOut(false), checkedOutBy(-1) {}

    std::string getTitle() const { return title; }
    std::string getDescription() const { return description; }
    std::string getGenre() const { return genre; }
    double getPrice() const { return price; }
    bool isCheckedOut() const { return checkedOut; }
    int getCheckedOutBy() const { return checkedOutBy; }

    void checkOut(int userId) {
        if (!checkedOut) {
            checkedOut = true;
            checkedOutBy = userId;
        }
    }

    void checkIn() {
        if (checkedOut) {
            checkedOut = false;
            checkedOutBy = -1;
        }
    }
};
//Book class is derived from the library item class
class Book : public LibraryItem {
private:
    std::string isbn;
    std::string author;
    std::string publisher;

public:
    Book(const std::string &t, const std::string &d, const std::string &g, double p, const std::string &i, const std::string &a, const std::string &pub)
        : LibraryItem(t, d, g, p), isbn(i), author(a), publisher(pub) {}

    std::string getIsbn() const { return isbn; }
    std::string getAuthor() const { return author; }
    std::string getPublisher() const { return publisher; }
};
//Music class is derived from the library item class
class Music : public LibraryItem {
private:
    std::string artist;
    std::string album;
    int releaseYear;

public:
    Music(const std::string &t, const std::string &d, const std::string &g, double p, const std::string &art, const std::string &alb, int year)
        : LibraryItem(t, d, g, p), artist(art), album(alb), releaseYear(year) {}

    std::string getArtist() const { return artist; }
    std::string getAlbum() const { return album; }
    int getReleaseYear() const { return releaseYear; }
};
//Movie class is derived from the library item class
class Movie : public LibraryItem {
private:
    std::string director;
    int duration; // in minutes
    int releaseYear;   

public:
    Movie(const std::string &t, const std::string &d, const std::string &g, double p, const std::string &dir, int dur, int year)
        : LibraryItem(t, d, g, p), director(dir), duration(dur), releaseYear(year) {}

    std::string getDirector() const { return director; }
    int getDuration() const { return duration; }
    int getReleaseYear() const { return releaseYear; }
};
//Library class is the main class which will have all the items, users and staff
class Library {
private:
    std::vector<LibraryItem*> items;
    std::vector<User> users;
    std::vector<Staff> staff;

public:
    void addItem(LibraryItem* item) {
        items.push_back(item);
    }

    void addUser(const User &user) {
        users.push_back(user);
    }

    void addStaff(const Staff &staffMember) {
        staff.push_back(staffMember);
    }

    LibraryItem* findItem(const std::string &title) {
        for (auto item : items) {
            if (item->getTitle() == title) {
                return item;
            }
        }
        return nullptr;
    }

    User* findUser(int userId) {
        for (auto &user : users) {
            if (user.getUserId() == userId) {
                return &user;
            }
        }
        return nullptr;
    }

    void checkOutItem(const std::string &title, int userId) {
        LibraryItem* item = findItem(title);
        if (item && !item->isCheckedOut()) {
            item->checkOut(userId);
        }
    }

    void checkInItem(const std::string &title) {
        LibraryItem* item = findItem(title);
        if (item && item->isCheckedOut()) {
            item->checkIn();
        }
    }
};
//Functions to get the input from the user//error handling
bool getIntInput(int &input) {
    std::cin >> input;
    if (std::cin.fail()) {
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard any extra input
    return true;
}
bool getStringInput(std::string &input) {
    std::getline(std::cin, input);
    if (input.empty()) {
        return false;
    }
    return true;
}
bool getDoubleInput(double &input) {
    std::cin >> input;
    if (std::cin.fail()) {
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard any extra input
    return true;
}
//Display menu function
void displayMenu() {
    std::cout << "Library Menu:\n";
    std::cout << "1. Check out item\n";
    std::cout << "2. Check in item\n";
    std::cout << "3. Add user\n";
    std::cout << "4. Add staff\n";
    std::cout << "5. Add book\n";
    std::cout << "6. Add music\n";
    std::cout << "7. Add movie\n";
    std::cout << "8. Exit\n";
    std::cout << "Enter your choice: ";
}
//Add book information function
void addBook(Library &library) {
    std::string title, description, genre, isbn, author, publisher;
    double price;

    std::cout << "Enter book title: ";
    if (!getStringInput(title)) {
        std::cout << "Invalid input. Please enter a valid title.\n";
        return;
    }
    std::cout << "Enter book description: ";
    if (!getStringInput(description)) {
        std::cout << "Invalid input. Please enter a valid description.\n";
        return;
    }
    std::cout << "Enter book genre: ";
    if (!getStringInput(genre)) {
        std::cout << "Invalid input. Please enter a valid genre.\n";
        return;
    }
    std::cout << "Enter book price: ";
    if (!getDoubleInput(price)) {
        std::cout << "Invalid input. Please enter a valid price.\n";
        return;
    }
    std::cout << "Enter book ISBN: ";
    if (!getStringInput(isbn)) {
        std::cout << "Invalid input. Please enter a valid ISBN.\n";
        return;
    }
    std::cout << "Enter book author: ";
    if (!getStringInput(author)) {
        std::cout << "Invalid input. Please enter a valid author.\n";
        return;
    }
    std::cout << "Enter book publisher: ";
    if (!getStringInput(publisher)) {
        std::cout << "Invalid input. Please enter a valid publisher.\n";
        return;
    }

    library.addItem(new Book(title, description, genre, price, isbn, author, publisher));
    std::cout << "Book added successfully.\n";
}
//Add music information function
void addMusic(Library &library) {
    std::string title, description, genre, artist, album;
    double price;
    int releaseYear;

    std::cout << "Enter music title: ";
    if (!getStringInput(title)) {
        std::cout << "Invalid input. Please enter a valid title.\n";
        return;
    }
    std::cout << "Enter music description: ";
    if (!getStringInput(description)) {
        std::cout << "Invalid input. Please enter a valid description.\n";
        return;
    }
    std::cout << "Enter music genre: ";
    if (!getStringInput(genre)) {
        std::cout << "Invalid input. Please enter a valid genre.\n";
        return;
    }
    std::cout << "Enter music price: ";
    if (!getDoubleInput(price)) {
        std::cout << "Invalid input. Please enter a valid price.\n";
        return;
    }
    std::cout << "Enter music artist: ";
    if (!getStringInput(artist)) {
        std::cout << "Invalid input. Please enter a valid artist.\n";
        return;
    }
    std::cout << "Enter music album: ";
    if (!getStringInput(album)) {
        std::cout << "Invalid input. Please enter a valid album.\n";
        return;
    }
    std::cout << "Enter music release year: ";
    if (!getIntInput(releaseYear)) {
        std::cout << "Invalid input. Please enter a valid year.\n";
        return;
    }

    library.addItem(new Music(title, description, genre, price, artist, album, releaseYear));
    std::cout << "Music added successfully.\n";
}
//Add movie information function
void addMovie(Library &library) {
    std::string title, description, genre, director;
    double price;
    int duration, releaseYear;

    std::cout << "Enter movie title: ";
    if (!getStringInput(title)) {
        std::cout << "Invalid input. Please enter a valid title.\n";
        return;
    }
    std::cout << "Enter movie description: ";
    if (!getStringInput(description)) {
        std::cout << "Invalid input. Please enter a valid description.\n";
        return;
    }
    std::cout << "Enter movie genre: ";
    if (!getStringInput(genre)) {
        std::cout << "Invalid input. Please enter a valid genre.\n";
        return;
    }
    std::cout << "Enter movie price: ";
    if (!getDoubleInput(price)) {
        std::cout << "Invalid input. Please enter a valid price.\n";
        return;
    }
    std::cout << "Enter movie director: ";
    if (!getStringInput(director)) {
        std::cout << "Invalid input. Please enter a valid director.\n";
        return;
    }
    std::cout << "Enter movie duration (in minutes): ";
    if (!getIntInput(duration)) {
        std::cout << "Invalid input. Please enter a valid duration.\n";
        return;
    }
    std::cout << "Enter movie release year: ";
    if (!getIntInput(releaseYear)) {
        std::cout << "Invalid input. Please enter a valid year.\n";
        return;
    }

    library.addItem(new Movie(title, description, genre, price, director, duration, releaseYear));
    std::cout << "Movie added successfully.\n";
}
//main function
int main() {
    Library library;

    // Add some initial data
    library.addUser(User("Alice", 1));
    library.addUser(User("Bob", 2));
    library.addStaff(Staff("Charlie", 3));
    //Adding some items to the library
    library.addItem(new Book("The Great Gatsby", "A novel by F. Scott Fitzgerald", "Fiction", 10.99, "1234567890", "F. Scott Fitzgerald", "Scribner"));
    library.addItem(new Music("Thriller", "An album by Michael Jackson", "Pop", 9.99, "Michael Jackson", "Thriller", 1982));
    library.addItem(new Movie("Inception", "A film by Christopher Nolan", "Sci-Fi", 14.99, "Christopher Nolan", 148, 2010));
        //Menu to display the options
        while (true) {
        displayMenu();
        int choice;
        if (!getIntInput(choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        //Switch case to handle the user input
        if (choice == 1) {
            std::string title;
            int userId;
            std::cout << "Enter item title: ";
            if (!getStringInput(title)) {
                std::cout << "Invalid input. Please enter a valid title.\n";
                continue;
            }
            std::cout << "Enter user ID: ";
            if (!getIntInput(userId)) {
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            library.checkOutItem(title, userId);
        } else if (choice == 2) {
            std::string title;
            std::cout << "Enter item title: ";
            if (!getStringInput(title)) {
                std::cout << "Invalid input. Please enter a valid title.\n";
                continue;
            }
            library.checkInItem(title);
        } else if (choice == 3) {
            std::string name;
            int userId;
            std::cout << "Enter user name: ";
            if (!getStringInput(name)) {
                std::cout << "Invalid input. Please enter a valid name.\n";
                continue;
            }
            std::cout << "Enter user ID: ";
            if (!getIntInput(userId)) {
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            library.addUser(User(name, userId));
        } else if (choice == 4) {
            std::string name;
            int userId;
            std::cout << "Enter staff name: ";
            if (!getStringInput(name)) {
                std::cout << "Invalid input. Please enter a valid name.\n";
                continue;
            }
            std::cout << "Enter staff ID: ";
            if (!getIntInput(userId)) {
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            library.addStaff(Staff(name, userId));
        } else if (choice == 5) {
            addBook(library);
        } else if (choice == 6) {
            addMusic(library);
        } else if (choice == 7) {
            addMovie(library);
        } else if (choice == 8) {
            break;
        } else {
            std::cout << "Invalid choice. Please enter a number between 1 and 8.\n"; //Error handling
        }
    }

    return 0;
}