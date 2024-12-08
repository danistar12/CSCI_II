#include <iostream>
#include <string>
#include <vector>
#include <sstream>

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
int main() {
    Library library;

    // Add some initial data
    library.addUser(User("Alice", 1));
    library.addUser(User("Bob", 2));
    library.addStaff(Staff("Charlie", 3));

    library.addItem(new Book("The Great Gatsby", "A novel by F. Scott Fitzgerald", "Fiction", 10.99, "1234567890", "F. Scott Fitzgerald", "Scribner"));
    library.addItem(new Music("Thriller", "An album by Michael Jackson", "Pop", 9.99, "Michael Jackson", "Thriller", 1982));
    library.addItem(new Movie("Inception", "A film by Christopher Nolan", "Sci-Fi", 14.99, "Christopher Nolan", 148, 2010));

    while (true) {
        std::cout << "Library Menu:\n";
        std::cout << "1. Check out item\n";
        std::cout << "2. Check in item\n";
        std::cout << "3. Add user\n";
        std::cout << "4. Add staff\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string title;
            int userId;
            std::cout << "Enter item title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            std::cout << "Enter user ID: ";
            std::cin >> userId;
            library.checkOutItem(title, userId);
        } else if (choice == 2) {
            std::string title;
            std::cout << "Enter item title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            library.checkInItem(title);
        } else if (choice == 3) {
            std::string name;
            int userId;
            std::cout << "Enter user name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter user ID: ";
            std::cin >> userId;
            library.addUser(User(name, userId));
        } else if (choice == 4) {
            std::string name;
            int userId;
            std::cout << "Enter staff name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter staff ID: ";
            std::cin >> userId;
            library.addStaff(Staff(name, userId));
        } else if (choice == 5) {
            break;
        }
    }

    return 0;
}