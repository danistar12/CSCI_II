/////////////////////////////////////////////////////////////
//#  Program name: M04_Program_2.cpp                      //
//#  Author: Danielle Lloyd                              //
//#  Date last updated: 11/14/2024                      // 
//#  Purpose: NerfGun Fun                              //
////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class NerfGun {
private:
    std::string model;
    int range;
    int capacity;
    int darts;

public:
    // Constructor
    NerfGun(std::string mdl, int rng, int cap)
        : model(mdl), range(rng), capacity(cap), darts(cap) {
        if (capacity > 144) {
            throw std::invalid_argument("Capacity cannot exceed 144.");
        }
    }

    // Member functions
    std::string getModel() const { return model; }
    int getCapacity() const { return capacity; }
    int getDartCount() const { return darts; }

    void fire() {
        if (darts <= 0) {
            throw std::underflow_error("No darts left to fire!");
        }
        darts--;
    }
    void reload(int quantity) {
        if (darts + quantity > capacity) {
            throw std::overflow_error("Exceeding dart capacity!");
        }
        darts += quantity;
    }
    // Overloaded operators
    bool operator==(const NerfGun& other) const {
        return darts == other.darts;
    }
    bool operator<(const NerfGun& other) const {
        return darts < other.darts;
    }
    // Prefix decrement
    NerfGun& operator--() {
        fire();
        return *this;
    }
    // Postfix decrement
    NerfGun operator--(int) {
        NerfGun temp = *this;
        fire();
        return temp;
    }
    NerfGun& operator+=(int quantity) {
        reload(quantity);
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const NerfGun& gun) {
        os << "Model: " << gun.model << ", Range: " << gun.range << "m, Capacity: " << gun.capacity << ", Darts: " << gun.darts;
        return os;
    }
};

// Main function
int main() {
    std::vector<NerfGun> nerfGuns;

    try {
        nerfGuns.emplace_back("AlphaStrike", 27, 110);
        nerfGuns.emplace_back("EliteDisruptor", 21, 90);
        nerfGuns.emplace_back("UltraOne", 36, 134);
        nerfGuns.emplace_back("MegaCycloneShock", 25, 70);

        // Display each gun’s information
        for (const auto& gun : nerfGuns) {
            std::cout << gun << std::endl;
        }
        // Compare the guns using the overloaded operator
        NerfGun* mostAmmoGun = &nerfGuns[0];
        for (size_t i = 1; i < nerfGuns.size(); ++i) {
            if (*mostAmmoGun < nerfGuns[i]) {
                mostAmmoGun = &nerfGuns[i];
            }
        }
        std::cout << "Gun with the most ammunition: " << *mostAmmoGun << std::endl;
        // Use the overloaded operators to fire and reload the guns
        nerfGuns[0].fire();
        nerfGuns[1]--;
        // Safely reload the gun without exceeding its capacity
        if (nerfGuns[2].getDartCount() + 10 <= nerfGuns[2].getCapacity()) {
            nerfGuns[2] += 10;
        }
        // Display each gun’s information again
        for (const auto& gun : nerfGuns) {
            std::cout << gun << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}

