/////////////////////////////////////////////////////////////
//#  Program name: M05_Programming.cpp                    //
//#  Author: Danielle Lloyd                              //
//#  Date last updated: 11/21/2024                      // 
//#  Purpose: Hierarchy of beverages and print details //
////////////////////////////////////////////////////////

#include <iostream>
#include <string>
using namespace std;

class Beverage {
protected:
    string name;
    string description;
    double servingSize; // in ounces
    int calories;
    double price;
public:
    Beverage(string n, string d, double s, int c, double p)
        : name(n), description(d), servingSize(s), calories(c), price(p) {}

    virtual ~Beverage() {}

    // Setters and Getters
    void setName(string n) { name = n; }
    string getName() const { return name; }

    void setDescription(string d) { description = d; }
    string getDescription() const { return description; }

    void setServingSize(double s) { servingSize = s; }
    double getServingSize() const { return servingSize; }

    void setCalories(int c) { calories = c; }
    int getCalories() const { return calories; }

    void setPrice(double p) { price = p; }
    double getPrice() const { return price; }

    // toString method
    virtual string toString() const {
        return "Name: " + name + "\nDescription: " + description + "\nServing Size: " + to_string(servingSize) + " oz\nCalories: " + to_string(calories) + "\nPrice: $" + to_string(price);
    }
};
class Coffee : public Beverage {
private:
    bool hot;
    bool caffeinated;
    string roastType;
    string strength;
    string creamer;
    string sweetener;

public:
    Coffee(string n, string d, double s, int c, double p, bool h, bool caf, string r, string st, string cr, string sw)
        : Beverage(n, d, s, c, p), hot(h), caffeinated(caf), roastType(r), strength(st), creamer(cr), sweetener(sw) {}

    string toString() const override {
        return Beverage::toString() + "\nHot: " + (hot ? "Yes" : "No") + "\nCaffeinated: " + (caffeinated ? "Yes" : "No") + "\nRoast Type: " + roastType + "\nStrength: " + strength + "\nCreamer: " + creamer + "\nSweetener: " + sweetener;
    }
};
class Tea : public Beverage {
private:
    string type;
    bool hot;
    string creamer;
    string sweetener;
    bool lemon;

public:
    Tea(string n, string d, double s, int c, double p, string t, bool h, string cr, string sw, bool l)
        : Beverage(n, d, s, c, p), type(t), hot(h), creamer(cr), sweetener(sw), lemon(l) {}

    string toString() const override {
        return Beverage::toString() + "\nType: " + type + "\nHot: " + (hot ? "Yes" : "No") + "\nCreamer: " + creamer + "\nSweetener: " + sweetener + "\nLemon: " + (lemon ? "Yes" : "No");
    }
};
class Soda : public Beverage {
private:
    string brand;
    string type;
    bool diet;

public:
    Soda(string n, string d, double s, int c, double p, string b, string t, bool isDiet)
        : Beverage(n, d, s, c, p), brand(b), type(t), diet(isDiet) {}

    string toString() const override {
        return Beverage::toString() + "\nBrand: " + brand + "\nType: " + type + "\nDiet: " + (diet ? "Yes" : "No");
    }
};
class EnergyDrink : public Beverage {
private:
    string brand;
    string stimulant;
    string sweetener;

public:
    EnergyDrink(string n, string d, double s, int c, double p, string b, string st, string sw)
        : Beverage(n, d, s, c, p), brand(b), stimulant(st), sweetener(sw) {}

    string toString() const override {
        return Beverage::toString() + "\nBrand: " + brand + "\nStimulant: " + stimulant + "\nSweetener: " + sweetener;
    }
};
int main() {
    Coffee coffee("Coffee", "Coffee w/ cream", 12.0, 5, 2.50, true, true, "Medium", "Strong", "Regular", "Sugar");
    Tea tea("Tea", "Green tea", 8.0, 2, 1.75, "Green", true, "None", "Honey", true);
    Soda soda("Soda", "Sprite", 16.0, 150, 1.00, "Sprite", "Lemon", false);
    EnergyDrink energyDrink("Energy Drink", "Energy drink with caffeine", 8.0, 110, 2.00, "Monster", "Caffeine", "Sugar");

    cout << "Beverage Details:\n\n";
    cout << coffee.toString() << "\n\n";
    cout << tea.toString() << "\n\n";
    cout << soda.toString() << "\n\n";
    cout << energyDrink.toString() << "\n";

    return 0;
}
