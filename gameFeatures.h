#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Scientists.h"
#include "Player.h"
#include <sstream>
#include <fstream>

#ifndef GAMEFEATURES_H
#define GAMEFEATURES_H

using namespace std;

class Features {
    private:
        string greenValue;
        int blueValue;
        int pinkValue;
        int redValue;
        string brownValue;
        string purpleValue;
    public:
        int rollDice();

        Features();

        //getters
        string getGreenValue();
        int getBlueValue();
        int getPinkValue();
        int getRedValue();
        string getBrownValue();
        string getPurpleValue();

        //setters
        void setGreenValue(string value);
        void setBlueValue(int value);
        void setPinkValue(int value);
        void setRedValue(int value);
        void setBrownValue(string value);
        void setPurpleValue(string value);


        // read file for random string for green tiles
        vector<vector<string>> greenString(string filename);

        // rest of tile types
        bool strandSimilarity (string strand1, string strand2, int answer);
        bool bestStrandMatch (string input_strand, string target_strand, int answer);
        bool identifyMutations(string input_strand, string target_strand, int answer);
        bool transcribeDNAtoRNA (string strand, string answer);
        string randomDNAGenerator(int length);
        int displayRiddle();
        bool answerRiddle(int id, string answer);
        void printLeaderboard();
        void updateLeaderboard(string newname, int newscore);
};

#endif