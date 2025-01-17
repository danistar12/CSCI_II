#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Player {
public:
    Player(const std::string &name, int playerID) : name(name), playerID(playerID) {}
    virtual ~Player() = default;

    std::string getName() const { return name; }
    int getPlayerID() const { return playerID; }

    virtual std::string getPlayerPosition() const = 0;
    virtual void play() const = 0;
    virtual std::string toString() const = 0;

protected:
    std::string name;
    int playerID;
};
// Offensive Players//Derived class
class QuarterBack : public Player {
public:
    QuarterBack(const std::string &name, int playerID) : Player(name, playerID) {}

    std::string getPlayerPosition() const override { return "QuarterBack"; }
    void play() const override { std::cout << getName() << " throws the ball." << std::endl; }
    std::string toString() const override { return getName() + " (" + std::to_string(getPlayerID()) + ") - QuarterBack"; }
};
class WideReceiver : public Player {
public:
    WideReceiver(const std::string &name, int playerID) : Player(name, playerID) {}

    std::string getPlayerPosition() const override { return "WideReceiver"; }
    void play() const override { std::cout << getName() << " catches the ball." << std::endl; }
    std::string toString() const override { return getName() + " (" + std::to_string(getPlayerID()) + ") - WideReceiver"; }
};
class RunningBack : public Player {
public:
    RunningBack(const std::string &name, int playerID) : Player(name, playerID) {}

    std::string getPlayerPosition() const override { return "RunningBack"; }
    void play() const override { std::cout << getName() << " runs with the ball." << std::endl; }
    std::string toString() const override { return getName() + " (" + std::to_string(getPlayerID()) + ") - RunningBack"; }
};
class OffensiveLineman : public Player {
public:
    OffensiveLineman(const std::string &name, int playerID) : Player(name, playerID) {}

    std::string getPlayerPosition() const override { return "OffensiveLineman"; }
    void play() const override { std::cout << getName() << " blocks the defense." << std::endl; }
    std::string toString() const override { return getName() + " (" + std::to_string(getPlayerID()) + ") - OffensiveLineman"; }
};
class TightEnd : public Player {
public:
    TightEnd(const std::string &name, int playerID) : Player(name, playerID) {}

    std::string getPlayerPosition() const override { return "TightEnd"; }
    void play() const override { std::cout << getName() << " catches the ball and runs with it." << std::endl; }
    std::string toString() const override { return getName() + " (" + std::to_string(getPlayerID()) + ") - TightEnd"; }
};
//Defensive Players // Derived class
class DefensiveLineman : public Player {
public:
    DefensiveLineman(const std::string &name, int playerID) : Player(name, playerID) {}

    std::string getPlayerPosition() const override { return "DefensiveLineman"; }
    void play() const override { std::cout << getName() << " tackles the ball carrier." << std::endl; }
    std::string toString() const override { return getName() + " (" + std::to_string(getPlayerID()) + ") - DefensiveLineman"; }
};
class LineBacker : public Player {
public:
    LineBacker(const std::string &name, int playerID) : Player(name, playerID) {}

    std::string getPlayerPosition() const override { return "LineBacker"; }
    void play() const override { std::cout << getName() << " blitzes the QuarterBack." << std::endl; }
    std::string toString() const override { return getName() + " (" + std::to_string(getPlayerID()) + ") - LineBacker"; }
};
class DefensiveBack : public Player {
public:
    DefensiveBack(const std::string &name, int playerID) : Player(name, playerID) {}

    std::string getPlayerPosition() const override { return "DefensiveBack"; }
    void play() const override { std::cout << getName() << " intercepts the ball." << std::endl; }
    std::string toString() const override { return getName() + " (" + std::to_string(getPlayerID()) + ") - DefensiveBack"; }
};
//Special Teams Players // Derived class
class Kicker : public Player {
public:
    Kicker(const std::string &name, int playerID) : Player(name, playerID) {}

    std::string getPlayerPosition() const override { return "Kicker"; }
    void play() const override { std::cout << getName() << " kicks the ball." << std::endl; }
    std::string toString() const override { return getName() + " (" + std::to_string(getPlayerID()) + ") - Kicker"; }
};
class Holder : public Player {
public:
    Holder(const std::string &name, int playerID) : Player(name, playerID) {}

    std::string getPlayerPosition() const override { return "Holder"; }
    void play() const override { std::cout << getName() << " holds the ball for the kicker." << std::endl; }
    std::string toString() const override { return getName() + " (" + std::to_string(getPlayerID()) + ") - Holder"; }
};
class Punter : public Player {
public:
    Punter(const std::string &name, int playerID) : Player(name, playerID) {}

    std::string getPlayerPosition() const override { return "Punter"; }
    void play() const override { std::cout << getName() << " punts the ball." << std::endl; }
    std::string toString() const override { return getName() + " (" + std::to_string(getPlayerID()) + ") - Punter"; }
};
class Returner : public Player {
public:
    Returner(const std::string &name, int playerID) : Player(name, playerID) {}

    std::string getPlayerPosition() const override { return "Returner"; }
    void play() const override { std::cout << getName() << " returns the ball." << std::endl; }
    std::string toString() const override { return getName() + " (" + std::to_string(getPlayerID()) + ") - Returner"; }
};
//Methods and Functions
void addPlayer(std::vector<std::shared_ptr<Player>> &team, std::shared_ptr<Player> player) {
    team.push_back(player);
}

void printTeam(const std::vector<std::shared_ptr<Player>> &team) {
    for (const auto &player : team) {
        std::cout << player->toString() << std::endl;
    }
    std::cout << "Total players on the team: " << team.size() << std::endl;
}

std::shared_ptr<Player> createPlayer(int playerType) {
    std::string name;
    int playerID;
    std::cout << "Enter player name: ";
    std::cin.ignore(); // To clear the newline character left in the buffer
    std::getline(std::cin, name);
    std::cout << "Enter player ID: ";
    std::cin >> playerID;

    switch (playerType) {
        case 1:
            return std::make_shared<QuarterBack>(name, playerID);
        case 2:
            return std::make_shared<WideReceiver>(name, playerID);
        case 3:
            return std::make_shared<TightEnd>(name, playerID);
        case 4:
            return std::make_shared<RunningBack>(name, playerID);
        case 5:
            return std::make_shared<OffensiveLineman>(name, playerID);
        case 6:
            return std::make_shared<DefensiveLineman>(name, playerID);
        case 7:
            return std::make_shared<LineBacker>(name, playerID);
        case 8:
            return std::make_shared<DefensiveBack>(name, playerID);
        case 9:
            return std::make_shared<Kicker>(name, playerID);
        case 10:
            return std::make_shared<Holder>(name, playerID);
        case 11:
            return std::make_shared<Punter>(name, playerID);
        case 12:
            return std::make_shared<Returner>(name, playerID);
        default:
            return nullptr;
    }
}

int main() {
    std::vector<std::shared_ptr<Player>> team;
    bool running = true;

    while (running) {
        std::cout << "Menu:\n";
        std::cout << "1. Add QuarterBack\n";
        std::cout << "2. Add WideReceiver\n";
        std::cout << "3. Add TightEnd\n";
        std::cout << "4. Add RunningBack\n";
        std::cout << "5. Add OffensiveLineman\n";
        std::cout << "6. Add DefensiveLineman\n";
        std::cout << "7. Add Linebacker\n";
        std::cout << "8. Add DefensiveBack\n";
        std::cout << "9. Add Kicker\n";
        std::cout << "10. Add Holder\n";
        std::cout << "11. Add Punter\n";
        std::cout << "12. Add Returner\n";
        std::cout << "13. Print Team\n";
        std::cout << "14. Exit\n";
        std::cout << "Choose an option: ";
        
        int choice;
        std::cin >> choice;
        
        if (choice >= 1 && choice <= 12) {
            auto player = createPlayer(choice);
            if (player) {
                addPlayer(team, player);
            } else {
                std::cout << "Invalid player type selected." << std::endl;
            }
        } else if (choice == 13) {
            printTeam(team);
        } else if (choice == 14) {
            running = false;
        } else {
            std::cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
