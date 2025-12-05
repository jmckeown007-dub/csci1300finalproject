#include <string>
#include <vector>

#pragma once
using namespace std;

class characterSetUp {

    private:
        vector<vector<string>> characterStats;
        int selectedPath;
        string selectedCharacter;
        string filename;
        vector<string> playerCharacterStats;

    public:
        // Constructor
        characterSetUp(string file);


        vector<vector<string>> getCharacterStats();
        string getSelectedCharacter();
        int getSelectedPath();
        vector<string> getplayerCharacterStats();


        void setSelectedCharacter(string character);
        void setSelectedPath(int path);
        void setplayerCharacterStats(vector<string> stats);


        vector<vector<string>> readCharacterStats();
        void printScientists();
        string selectCharacter();
        int choosePath();
        vector<string> logPlayerCharacterStats();
        string chooseAdvisor();
};