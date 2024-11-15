#include <iostream>
#include <vector>
#include <stdexcept>
#include <ctime>

class nerfGun {
private:
    std::string model;
    int range;
    int capacity;
    int dartCount;

public:
    nerfGun(const std::string& model, int range, int capacity) : model(model), range(range), capacity(capacity) {
        if (capacity > 144) {
            throw std::invalid_argument("Capacity cannot be greater than 144.");
        }
        dartCount = capacity; // Fully loaded when created
    }

    std::string getModel() const {
        return model;
    }

    int getCapacity() const {
        return capacity;
    }

    int getDartCount() const {
        return dartCount;
    }

    void reload(int quantity) {
        if (dartCount + quantity > capacity) {
            throw std::overflow_error("Cannot reload. Capacity exceeded.");
        }
        dartCount += quantity;
    }

    void fire() {
        if (dartCount <= 0) {
            throw std::underflow_error("Cannot fire. Out of ammunition.");
        }
        dartCount--;
    }

    // Overloaded operators
    bool operator==(const nerfGun& other) const {
        return dartCount == other.dartCount;
    }

    bool operator<(const nerfGun& other) const {
        return dartCount < other.dartCount;
    }

    nerfGun& operator--() {
        // Prefix --
        fire();
        return *this;
    }

    nerfGun operator--(int) {
        // Postfix --
        nerfGun temp = *this;
        fire();
        return temp;
    }

    nerfGun& operator+=(int quantity) {
        reload(quantity);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const nerfGun& gun) {
        os << "Model: " << gun.model << "\nRange: " << gun.range << "\nCapacity: " << gun.capacity << "\nDart Count: " << gun.dartCount << "\n";
        return os;
    }
};

int main() {
    std::vector<nerfGun> guns;

    // Create 4 to 7 different guns
    guns.emplace_back("Gun1", 20, 50);
    guns.emplace_back("Gun2", 25, 100);
    guns.emplace_back("Gun3", 30, 75);
    guns.emplace_back("Gun4", 15, 120);

    // Display each gun's information
    for (const auto& gun : guns) {
        std::cout << gun << "\n";
    }

    // Compare guns and display the one with the most ammunition
    auto maxAmmoGun = std::max_element(guns.begin(), guns.end(), [](const nerfGun& a, const nerfGun& b) {
        return a < b;
    });

    std::cout << "Gun with the most ammunition:\n" << *maxAmmoGun << "\n";

    // Randomly fire and reload guns
    std::srand(std::time(0));

    try {
        for (int i = 0; i < 5; ++i) {
            int gunIndex = std::rand() % guns.size();
            int action = std::rand() % 2; // 0 for fire, 1 for reload

            if (action == 0) {
                std::cout << "Firing " << guns[gunIndex].getModel() << "...\n";
                guns[gunIndex]--;
            } else {
                int reloadAmount = std::rand() % 20 + 1; // Reload between 1 and 20 darts
                std::cout << "Reloading " << guns[gunIndex].getModel() << " with " << reloadAmount << " darts...\n";
                guns[gunIndex] += reloadAmount;
            }

            std::cout << guns[gunIndex] << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
