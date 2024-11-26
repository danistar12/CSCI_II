#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Base class for library items
class LibraryItem {
protected:
    std::string title;
    std::string description;
    std::string genre;
    double price;

public:
    LibraryItem(const std::string &t, const std::string &d, const std::string &g, double p)
        : title(t), description(d), genre(g), price(p) {}

    virtual std::string toString() const {
        std::ostringstream oss;
        oss << "Title: " << title << "\nDescription: " << description << "\nGenre: " << genre << "\nPrice: $" << price;
        return oss.str();
    }

    virtual ~LibraryItem() {}
};

// Derived class for books
class Book : public LibraryItem {
private:
    std::string ISBN;
    std::string author;
    std::string publisher;

public:
    Book(const std::string &t, const std::string &d, const std::string &g, double p,
         const std::string &isbn, const std::string &a, const std::string &pub)
        : LibraryItem(t, d, g, p), ISBN(isbn), author(a), publisher(pub) {}

    std::string toString() const override {
        std::ostringstream oss;
        oss << LibraryItem::toString() << "\nISBN: " << ISBN << "\nAuthor: " << author << "\nPublisher: " << publisher;
        return oss.str();
    }
};

// Derived class for music
class Music : public LibraryItem {
private:
    std::string artist;
    std::string album;
    int releaseYear;

public:
    Music(const std::string &t, const std::string &d, const std::string &g, double p,
          const std::string &a, const std::string &al, int ry)
        : LibraryItem(t, d, g, p), artist(a), album(al), releaseYear(ry) {}

    std::string toString() const override {
        std::ostringstream oss;
        oss << LibraryItem::toString() << "\nArtist: " << artist << "\nAlbum: " << album << "\nRelease Year: " << releaseYear;
        return oss.str();
    }
};

// Derived class for movies
class Movie : public LibraryItem {
private:
    std::string director;
    int duration; // in minutes
    int releaseYear;

public:
    Movie(const std::string &t, const std::string &d, const std::string &g, double p,
          const std::string &dir, int dur, int ry)
        : LibraryItem(t, d, g, p), director(dir), duration(dur), releaseYear(ry) {}

    std::string toString() const override {
        std::ostringstream oss;
        oss << LibraryItem::toString() << "\nDirector: " << director << "\nDuration: " << duration << " minutes\nRelease Year: " << releaseYear;
        return oss.str();
    }
};

// Base class for people
class Person {
protected:
    std::string name;
    int ID;
    std::string contactInfo;

public:
    Person(const std::string &n, int id, const std::string &ci)
        : name(n), ID(id), contactInfo(ci) {}

    virtual std::string toString() const {
        std::ostringstream oss;
        oss << "Name: " << name << "\nID: " << ID << "\nContact Info: " << contactInfo;
        return oss.str();
    }

    virtual ~Person() {}
};

// Derived class for users
class User : public Person {
private:
    std::string membershipLevel;

public:
    User(const std::string &n, int id, const std::string &ci, const std::string &ml)
        : Person(n, id, ci), membershipLevel(ml) {}

    std::string toString() const override {
        std::ostringstream oss;
        oss << Person::toString() << "\nMembership Level: " << membershipLevel;
        return oss.str();
    }
};

// Derived class for staff
class Staff : public Person {
private:
    std::string position;
    double salary;

public:
    Staff(const std::string &n, int id, const std::string &ci, const std::string &pos, double sal)
        : Person(n, id, ci), position(pos), salary(sal) {}

    std::string toString() const override {
        std::ostringstream oss;
        oss << Person::toString() << "\nPosition: " << position << "\nSalary: $" << salary;
        return oss.str();
    }
};

// Library class
class Library {
private:
    std::vector<LibraryItem *> items;
    std::vector<Person *> users;

public:
    void addItem(LibraryItem *item) {
        items.push_back(item);
    }

    void addUser(Person *user) {
        users.push_back(user);
    }

    std::string listItems() const {
        std::ostringstream oss;
        for (const auto &item : items) {
            oss << item->toString() << "\n\n";
        }
        return oss.str();
    }

    std::string listUsers() const {
        std::ostringstream oss;
        for (const auto &user : users) {
            oss << user->toString() << "\n\n";
        }
        return oss.str();
    }

    ~Library() {
        for (auto &item : items) {
            delete item;
        }
        for (auto &user : users) {
            delete user;
        }
    }
};

// Main function
int main() {
    Library myLibrary;

    // Add some items
    Book *book1 = new Book("C++ Programming", "A comprehensive guide", "Programming", 29.99, "1234567890", "Bjarne Stroustrup", "Addison-Wesley");
    Music *music1 = new Music("The Wall", "Iconic rock album", "Rock", 19.99, "Pink Floyd", "The Wall", 1979);
    Movie *movie1 = new Movie("Inception", "A mind-bending thriller", "Sci-Fi", 14.99, "Christopher Nolan", 148, 2010);

    myLibrary.addItem(book1);
    myLibrary.addItem(music1);
    myLibrary.addItem(movie1);

    // Add some users
    User *user1 = new User("John Doe", 1, "john.doe@example.com", "Gold");
    Staff *staff1 = new Staff("Jane Smith", 2, "jane.smith@example.com", "Librarian", 50000);

    myLibrary.addUser(user1);
    myLibrary.addUser(staff1);

    // List items and users
    std::cout << "Library Items:\n" << myLibrary.listItems() << std::endl;
    std::cout << "Library Users:\n" << myLibrary.listUsers() << std::endl;

    return 0;
}
