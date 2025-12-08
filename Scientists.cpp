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



    

    

    // Constructor
    characterSetUp::characterSetUp() {
        characterStats = {};
        int selectedPath = 0;
        string selectedCharacter = "";
        string filename = "";
        playerCharacterStats = {};
    }

    characterSetUp::characterSetUp(string file) {
        filename = file;
        characterStats = readCharacterStats();
    }

    // getters
    vector<vector<string>> characterSetUp::getCharacterStats() {
        return characterStats;
    }

    string characterSetUp::getSelectedCharacter() {
        return selectedCharacter;
    }

    int characterSetUp::getSelectedPath() {
        return selectedPath;
    }

    vector<string> characterSetUp::getplayerCharacterStats() {
        return playerCharacterStats;
    }

    // setters
    void characterSetUp::setSelectedCharacter(string character) {
        selectedCharacter = character;
    }

    void characterSetUp::setSelectedPath(int path) {
        selectedPath = path;
    }

    void characterSetUp::setplayerCharacterStats(vector<string> stats) {
        playerCharacterStats = stats;
    }


    //
    // Read the file
    //
    vector<vector<string>> characterSetUp::readCharacterStats() {
        // open file
        ifstream ReadFile(filename);
        // check if file opened
        if (!ReadFile) {
            cout << "Error opening character list";
            return {};
        }

        // read each line of file
        string line;
        
        // arrays to loop through later to print the contents of each line
        vector<vector<string>> stats;

        while (getline (ReadFile, line)) {

            // read each word of line
            stringstream ss(line);

            string word;

            vector<string> row;


            while(getline (ss, word, '|')) {

                if (word.back() == '\r') {
                    word.pop_back();            // avoid carriage returns so that last part of line is properly read
                }
                row.push_back(word);
            }

            stats.push_back(row);

        }

        return stats;
    }


    //
    // Print Character Stats
    //
    void characterSetUp::printScientists() {

        // read file to a vector
        vector<vector<string>> stats = characterStats;


        vector<string> header = stats[0];

        cout << "" << endl;
        cout << "Choose your character! " << endl;
        cout << "---------------------" << endl;
        cout << "" << endl;

        // print out character descriptions
        for (int k = 1; k < stats.size(); k++) {
            for (int j = 0; j < 6; j++) {
                cout << header[j] << ": " << stats[k][j] << endl;
            }

            cout << " ------------- " << endl;
        }

        cout << "" << endl;
        
    }

    //
    // Character Selection
    //
    string characterSetUp::selectCharacter() {
        vector<vector<string>> stats = characterStats;

        /*
        for (size_t i = 1; i < stats.size(); i++) {
            cout << "(" << i << ") " << stats[i][0] << endl;
        }
        cout << "" << endl;
        */

        vector<string> characters;

        for (size_t i = 1; i < stats.size(); i++) {
            characters.push_back(stats[i][0]);
        }

        int user_choice = -1;
        //cin >> user_choice;

        while (user_choice < 1 || user_choice > characters.size()) {
            cout << "Make your choice..." << endl;
            cout << "" << endl;
            for (size_t i = 0; i < characters.size(); i++) {
                cout << "(" << i + 1 << ") " << characters[i] << endl;
            }

            cin >> user_choice;
            cin.ignore();

            if (user_choice < 1 || user_choice > characters.size()) {
                cout << "Invalid choice, please select a provided number" << endl;
            }
        }
        
        cout << "" << endl;
        cout << "You have chosen " << characters[user_choice - 1] << endl;

        setSelectedCharacter(characters[user_choice - 1]);
        return characters[user_choice - 1];
    }


    //
    // Path Selection
    //
    int characterSetUp::choosePath() {
        cout << "It's time to choose your path..." << endl;

        cout << "" << endl;

        cout << underline << "Training Fellowship" << reset << endl;
        cout << "This path grants you a variety of trait boosts and an advisor that will help you in select challenges. " << 
        "However, it requires an initial investment of 5,000 Discovery Points." << endl;
        cout << "+500 Accuracy Points" << endl;
        cout << "+500 Efficiency Points" << endl;
        cout << "+1,000 Insight Points" << endl;
        cout << "-5,000 Discovery Points" << endl;

        cout << "----------------------------------" << endl;

        cout << underline << "Direct Lab Assignment" << reset << endl;
        cout << "This path grants you an instant boost of 5,000 Discovery Points. " << 
        "However, you will receive fewer trait boosts and no initial advisor." << endl;
        cout << "+200 Accuracy Points" << endl;
        cout << "+200 Efficiency Points" << endl;
        cout << "+200 Insight Points" << endl;
        cout << "+5,000 Discovery Points" << endl;

        cout << "----------------------------------" << endl;

        int user_choice = 0;
        while (user_choice < 1 || user_choice > 2) {
            cout << "Make your choice..." << endl;
            
            cout << "" << endl;

            cout << "(1) Training Fellowship" << endl;
            cout << "(2) Direct Lab Assignment" << endl;

            cout << "" << endl;

            cin >> user_choice;
            cin.ignore();
            cout << "" << endl;

            if (user_choice < 1 || user_choice > 2) {
                cout << "Invalid choice, please select a provided number" << endl;
                cout << "" << endl;
            }
        }

        Player player;

        switch(user_choice) {
            case 1:
                cout << "You have selected Training Fellowship" << endl;
                cout << "" << endl;
                return 1;
            case 2:
                cout << "You have selected Direct Lab Assignment" << endl;
                cout << "" << endl;
                return 2;
        }

        return 0;
    }

    vector<string> characterSetUp::logPlayerCharacterStats() {
        vector<vector<string>> stats = characterStats;
        string characterName = getSelectedCharacter();
        vector<string> playerCharacterStats;
        for (int i = 0; i < stats.size(); i++) {
            if (stats[i][0] == characterName) {
                for (int j = 1; j < stats[i].size(); j++) {
                    playerCharacterStats.push_back(stats[i][j]);
                }
            }
        }

        return playerCharacterStats;

        
        
    }

    int characterSetUp::chooseAdvisor() {

        
        
        cout << underline << "Choose your advisor: " << reset << endl;
        cout << "(1) Dr. Aliquot -- A master of the \"wet lab\", assisting in avoiding contamination" << endl;
        cout << "(2) Dr. Assembler -- An expert who helps improve efficiency and streamlines pipelines" << endl;
        cout << "(3) Dr. Pop-Gen -- A genetics specialist with insight for identifying rare genetic variants" << endl;
        cout << "(4) Dr. Bio-Script -- The genius behind the data analysis, helps debug code" << endl;
        cout << "(5) Dr. Loci -- Your biggest supporter assisting you in learning the equipment" << endl;

        int user_choice;

        cin >> user_choice;
        cin.ignore();
        while (user_choice != 1 && user_choice != 2 && user_choice != 3 && user_choice != 4 && user_choice != 5) {
            cout << "Invalid Selection, please choose again:" << endl;
            cout << "(1) Dr. Aliquot -- A master of the \"wet lab\", assisting in avoiding contamination" << endl;
            cout << "(2) Dr. Assembler -- An expert who helps improve efficiency and streamlines pipelines" << endl;
            cout << "(3) Dr. Pop-Gen -- A genetics specialist with insight for identifying rare genetic variants" << endl;
            cout << "(4) Dr. Bio-Script -- The genius behind the data analysis, helps debug code" << endl;
            cout << "(5) Dr. Loci -- Your biggest supporter assisting you in learning the equipment" << endl;

            cin >> user_choice;
            cin.ignore();
        }
        

        return user_choice;

    }

