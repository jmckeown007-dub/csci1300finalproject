#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Scientists.h"
#include "Player.h"
#include "Board.h"
#define underline "\033[4m"
#define reset "\033[0m"
//#define underline "\033[24m"
using namespace std;

// Constructors
Player::Player() {
    name = "";
    character = "";
    exp = 0;
    accuracy = 0;
    efficiency = 0;
    insight = 0;
    discoveryPoints = 0;
    advisor = "";
    advisorDesc = "";
}

Player::Player(string playerName, string chosenCharacter, int xp, int acc, int eff, int ins, int dp, int playerPath) {
    name = playerName;
    character = chosenCharacter;
    exp = xp;
    accuracy = acc;
    efficiency = eff;
    insight = ins;
    discoveryPoints = dp;
    path = playerPath;
}


// getters
    string Player::getName() {
        return name;
    }
    string Player::getCharacter() {
        return character;
    }
    int Player::getExp() {
        return exp;
    }
    int Player::getAccuracy() {
        return accuracy;
    }
    int Player::getEfficiency() {
        return efficiency;
    }
    int Player::getInsight() {
        return insight;
    }
    int Player::getDiscoveryPoints() {
        return discoveryPoints;
    }
    int Player::getPath() {
        return path;
    }
    string Player::getAdvisor() {
        return advisor;
    }
    string Player::getAdvisorDesc() {
        return advisorDesc;
    }


    // setters
    void Player::setName(string playerName) {
        name = playerName;
    }
    void Player::setCharacter(string playerCharacter) {
        character = playerCharacter;
    }
    void Player::setExp(int experience) {
        exp = experience;
    }
    void Player::setAccuracy(int acc) {
        accuracy = acc;
    }
    void Player::setEfficiency(int eff) {
        efficiency = eff;
    }
    void Player::setInsight(int ins) {
        insight = ins;
    }
    void Player::setDiscoveryPoints(int dp) {
        discoveryPoints = dp;
    }
    void Player::setPath(int playerPath) {
        path = playerPath;
    }
    void Player::setAdvisor(string playerAdvisor) {
        advisor = playerAdvisor;
    }
    void Player::setAdvisorDesc(string playerAdvisorDesc) {
        advisorDesc = playerAdvisorDesc;
    }

    // get player stats
    vector<string> Player::getAllStats() {
        vector<string> stats;

        stats.push_back(to_string(getExp()));
        stats.push_back(to_string(getAccuracy()));
        stats.push_back(to_string(getEfficiency()));
        stats.push_back(to_string(getInsight()));
        stats.push_back(to_string(getDiscoveryPoints()));

        return stats;
    }

    // set player stats
    void Player::setAllStats(vector<string> stats) {
        vector<string> statsToSet = stats;

        setExp(stoi(statsToSet[0]));
        setAccuracy(stoi(statsToSet[1]));
        setEfficiency(stoi(statsToSet[2]));
        setInsight(stoi(statsToSet[3]));
        setDiscoveryPoints(stoi(statsToSet[4]));
    }


    // display menu
    int Player::displayMenu() {

        int playerInput = 0;

        while (playerInput != 5) {

        cout << underline << "Menu" << reset << endl;
        cout << "(1) Check Player Progress" << endl;
        cout << "(2) Review Character" << endl;
        cout << "(3) Check Current Leaderboard" << endl;
        cout << "(4) Review Advisor" << endl;
        cout << "(5) Move Forward" << endl;

        cin >> playerInput;
        cin.ignore();
        cout << "" << endl;

        switch(playerInput) {
            case 1:
                cout << "(1) Review Discovery Points or (2) Review Trait stats" << endl;
                int playerSubChoice;
                cin >> playerSubChoice;
                if (playerSubChoice != 1 && playerSubChoice != 2) {
                    cout << "Invalid Selection" << endl;
                    break;
                    }
                cin.ignore();
                cout << "" << endl;
                switch(playerSubChoice) {
                    case 1: {
                        int displayDP = getDiscoveryPoints();
                        cout << "Discovery Points: " << displayDP << endl;
                        cout << "" << endl;
                        break;
                    }
                    case 2: {
                        int displayEXP = getExp();
                        int displayAccuracy = getAccuracy();
                        int displayEfficiency = getEfficiency();
                        int displayInsight = getInsight();

                        cout << "Experience: " << displayEXP << endl;
                        cout << "Accuracy: " << displayAccuracy << endl;
                        cout << "Efficiency: " << displayEfficiency << endl;
                        cout << "Insight: " << displayInsight << endl;

                        cout << "" << endl;

                        break;
                    }
                    
                }
                break;
            case 2: {
                cout << "Character: " << getCharacter() << endl;
                cout << "Experience Points: " << getExp() << endl;
                cout << "" << endl;
                break;
            }
            case 3: {
                    return 3;
                }
            case 4: {

                if (getPath() == 2) {
                    cout << "" << endl;
                    cout << "You don't have an advisor" << endl;
                    cout << "Would you like one? (Y or N) (-20 Exp)" << endl;
                    char user_input;
                    cin >> user_input;
                    if (tolower(user_input) != 'y' && tolower(user_input) != 'n') {
                        cout << "Invalid Selection" << endl;
                        break;
                    }
                    cin.ignore();

                    if (tolower(user_input) == 'y' && getExp() >= 20) {
                        characterSetUp chooseAdvisor;
                        int newAdvisor = chooseAdvisor.chooseAdvisor();
                        switch(newAdvisor) {
                            case 1:
                                setAdvisor("Dr. Aliquot");
                                setAdvisorDesc("A master of the \"wet lab\", assisting in avoiding contamination");
                                break;
                            case 2:
                                setAdvisor("Dr. Assembler");
                                setAdvisorDesc("An expert who helps improve efficiency and streamlines pipelines");
                                break;
                            case 3:
                                setAdvisor("Dr. Pop-Gen");
                                setAdvisorDesc("A genetics specialist with insight for identifying rare genetic variants");
                                break;
                            case 4:
                                setAdvisor("Dr. Bio-Script");
                                setAdvisorDesc("The genius behind the data analysis, helps debug code");
                                break;
                            case 5:
                                setAdvisor("Dr. Loci");
                                setAdvisorDesc("Your biggest supporter assisting you in learning the equipment");
                                break;
                        }

                        cout << "Your new advisor is: " << getAdvisor() << endl;
                        cout << "-20 Exp" << endl;
                        setExp(getExp() - 20);
                    }

                    else if (tolower(user_input) == 'y' && getExp() < 20) {
                        cout << "You don't have enough experience points to get an advisor yet" << endl;
                        break;
                    }

                    else {break;}

                    break;
                }

                else {
                    cout << "(1) Review Advisor Abilities or (2) Change Advisor (-10 Exp)" << endl;
                    int playerSubChoice;
                    cin >> playerSubChoice;
                    if (playerSubChoice != 1 && playerSubChoice != 2) {
                        cout << "Invalid Selection" << endl;
                        break;
                    }
                    cin.ignore();
                    cout << "" << endl;
                    switch(playerSubChoice) {
                        case 1: {   
                            cout << "" << endl;
                            cout << underline << "Details About Your Advisor" << reset << endl;
                            cout << getAdvisor() << ": " << endl;
                            cout << getAdvisorDesc() << endl;
                            cout << "" << endl;
                            break;
                        }
                        case 2: {
                            characterSetUp chooseAdvisor;
                            string currentAdvisor = getAdvisor();

                            if (getExp() < 10) {
                                cout << "You don't have enough Exp for a new advisor" << endl;
                                break;
                            }
                            
                            int newAdvisor = chooseAdvisor.chooseAdvisor();
                        
                            switch(newAdvisor) {
                                case 1:
                                    setAdvisor("Dr. Aliquot");
                                    setAdvisorDesc("A master of the \"wet lab\", assisting in avoiding contamination");
                                    break;
                                case 2:
                                    setAdvisor("Dr. Assembler");
                                    setAdvisorDesc("An expert who helps improve efficiency and streamlines pipelines");
                                    break;
                                case 3:
                                    setAdvisor("Dr. Pop-Gen");
                                    setAdvisorDesc("A genetics specialist with insight for identifying rare genetic variants");
                                    break;
                                case 4:
                                    setAdvisor("Dr. Bio-Script");
                                    setAdvisorDesc("The genius behind the data analysis, helps debug code");
                                    break;
                                case 5:
                                    setAdvisor("Dr. Loci");
                                    setAdvisorDesc("Your biggest supporter assisting you in learning the equipment");
                                    break;
                            }

                            if (currentAdvisor == getAdvisor()) {
                                cout << "" << endl;
                                cout << "You already have this advisor!" << endl;
                                break;
                            }
                            
                            else {
                                cout << "Your new advisor is: " << getAdvisor() << endl;
                                cout << "-10 Exp" << endl;
                                setExp(getExp() - 10);
                                break;
                            }
                        }
                    }
                    break;
                }
                }
            case 5: {
                    return 5;
            }
        }
        }

    return 0;
    }
