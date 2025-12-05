#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Scientists.h"
#include "Player.h"
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
    void Player::displayMenu() {

        int playerInput = 0;

        while (playerInput != 5) {

        cout << underline << "Menu" << reset << endl;
        cout << "(1) Check Player Progress" << endl;
        cout << "(2) Review Character" << endl;
        cout << "(3) Check Position" << endl;
        cout << "(4) Review Advisor" << endl;
        cout << "(5) Move Forward" << endl;

        cin >> playerInput;


        switch(playerInput) {
            case 1:
                cout << "(1) Review Discovery Points or (2) Review Trait stats" << endl;
                int playerSubChoice;
                cin >> playerSubChoice;
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
        }
        }
    }
