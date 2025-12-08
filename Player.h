#include <iostream>
#include <string>
#include "Scientists.h"

#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class Player {
    private:
        string name;
        string character;
        int exp;
        int accuracy;
        int efficiency;
        int insight;
        int discoveryPoints;
        int path;
        string advisor;
        string advisorDesc;
    
    public:
        Player(); //default constructor
        Player(string playerName, string chosenCharacter, int xp, int acc, int eff, int ins, int dp, int playerPath); //parameter constructor

        // getters
        string getName();
        string getCharacter();
        int getExp();
        int getAccuracy();
        int getEfficiency();
        int getInsight();
        int getDiscoveryPoints();
        int getPath();
        string getAdvisor();
        string getAdvisorDesc();


        // setters
        void setName(string playerName);
        void setCharacter(string playerCharacter);
        void setExp(int experience);
        void setAccuracy(int acc);
        void setEfficiency(int eff);
        void setInsight(int ins);
        void setDiscoveryPoints(int dp);
        void setPath(int playerPath);
        void setAdvisor(string playerAdvisor);
        void setAdvisorDesc(string playerAdvisorDesc);

        // get player stats
        vector<string> getAllStats();

        // set player stats
        void setAllStats(vector<string> stats);

        // display menu
        int displayMenu();

};

#endif