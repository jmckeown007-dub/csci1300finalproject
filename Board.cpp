// Source file calling the header file
#include "Board.h"
// Recall we use this preprocessor directive for rand() and srand()
#include <cstdlib>
// Similarly, we use this one for time() (The seed for random)
#include <ctime>
#include <iostream>
#include <string>
#include <cmath>
#include "Scientists.h"
#include "Player.h"
#include "gameFeatures.h"
#include "animateText.h"
#define underline "\033[4m"
#define reset "\033[0m"
//#define underline "\033[24m"


// Each of the following defines a macro
// Essentially nicenames to use instead of the corresponding escape sequence ('\') 
#define ORANGE "\033[48;2;230;115;0m"
#define GREY "\033[48;2;128;128;128m"
#define GREEN "\033[48;2;34;139;34m"
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define RED "\033[48;2;230;10;10m"
#define PURPLE "\033[48;2;128;0;128m"
#define RESET "\033[0m"

using namespace std;


// =========================== Constructor ===========================

Board::Board(int playerOnePath, int playerTwoPath) {
    // Creates two players
    _player_count = _MAX_PLAYERS;

    // Initialize player's position
    for (int i = 0; i < _player_count; i++) {
        _player_position[i] = 0;
        _previous_position[i] = 0;
    }

    _player_paths[0] = playerOnePath;
    _player_paths[1] = playerTwoPath;

    // Fill both lanes
    initializeBoard();
}

// =========================== Private Member Functions ===========================

void Board::initializeTiles(int player_index, int player_path) {
    Tile tile;
    int green_count = 0;
    // Recall 52 from header file
    int total_tiles = _BOARD_SIZE;

    for (int i = 0; i < total_tiles; i++) {
        // Set the last tile as Orange for the finish line
        if (i == total_tiles - 1) {
            tile.color = 'O';
        } 
        // Set the first tile as Grey for the starting line
        else if (i == 0) {
            tile.color = 'Y';
        } 
        // Hard-coded target of 30 green tiles
        // Probablisitic method to spread out the green tiles randomly
        else if (player_path == 1 && green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count)) {
            tile.color = 'G';
            green_count++;
        }

        else if (player_path == 2 && green_count < 20 && (rand() % (total_tiles - i) < 20 - green_count)) {
            tile.color = 'G';
            green_count++;
        }

        // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
        else {
            int color_choice = rand() % 5;
            switch (color_choice) {
                case 0:
                    tile.color = 'B'; // Blue
                    break;
                case 1:
                    tile.color = 'P'; // Pink
                    break;
                case 2:
                    tile.color = 'T'; // Brown
                    break;
                case 3:
                    tile.color = 'R'; // Red
                    break;
                case 4:
                    tile.color = 'U'; // Purple
                    break;
            }
        }

        // Assign the tile to the board for the specified lane/player 1 or 2
        // Recall i refers to tile 0 to 51
        _tiles[player_index][i] = tile;
    }
}

bool Board::isPlayerOnTile(int player_index, int pos) {
    if (_player_position[player_index] == pos) {
        return true;
    }
    return false;
}

void Board::displayTile(int player_index, int pos) {
    string color = "";
    int player = isPlayerOnTile(player_index, pos);

    // Using the defined nicenames above
    switch(_tiles[player_index][pos].color) {
        case 'O': color = ORANGE; break;
        case 'Y': color = GREY; break;
        case 'G': color = GREEN; break;
        case 'B': color = BLUE; break;
        case 'P': color = PINK; break;
        case 'T': color = BROWN; break;
        case 'R': color = RED; break;
        case 'U': color = PURPLE; break;
    }

    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>
    if (player == true) {
        cout << color << "|" << (player_index + 1) << "|" << RESET;
    }
    else {
        cout << color << "| |" << RESET;
    }
}

// =========================== Public Member Functions ===========================

void Board::initializeBoard() {
    for (int i = 0; i < 2; i++) {
        // This ensures each lane (or each player) has a unique tile distribution
        initializeTiles(i, _player_paths[i]);
    }
}

void Board::displayTrack(int player_index) {
    for (int i = 0; i < _BOARD_SIZE; i++) {
        displayTile(player_index, i);
    }
    cout << endl;
}

void Board::displayBoard() {
    for (int i = 0; i < 2; i++) {
        displayTrack(i);
        if (i == 0) {
            cout << endl; // Add an extra line between the two lanes
        }
    }
}

bool Board::movePlayer(int player_index) {
    // Increment player position by 1
    _player_position[player_index]++;

    // Player reached last tile
    if (_player_position[player_index] == _BOARD_SIZE - 1) {
        return true;
    }

    return false;
}

int Board::getPlayerPosition(int player_index) const {
    if (player_index >= 0 && player_index <= _player_count) {
        return _player_position[player_index];
    }
    return -1;
}

char Board::getTileColor(int player_index, int pos) {
    return _tiles[player_index][pos].color;
}
// Tile Trigger Function activates events based on the color of tile the player lands on. 
Player Board::tileTrigger(Player player, char tileColor, int player_index) {

    switch(tileColor) {
        // Green Tile Events
        case 'G': {

            /*Debugging below because there was an issue with paths */
            //cout << "Debug: tileTrigger called with tileColor = " << tileColor << endl;
            //cout << "Debug: Player path value = " << player.getPath() << endl;
            if (rand() % 2 == 0) {
                Features greenFeatures;

                vector<vector<string>> greenEvents = greenFeatures.greenString("random_events_new.txt");

                int rand_num = rand() % greenEvents.size();

                cout << "" << endl;
                cout << "Green Tile Event Time!" << endl;
                cout << greenEvents[rand_num][0] << endl; // pick a random event from vector of events

                int accuracy = 0;
                int efficiency = 1; // initialize variables to compare to player's trait to calculate total discovery points change
                int insight = 2;

                int none = 0;
                int aliquot = 1; // initialize variables to compare to player's advisor
                int assembler = 2;
                int popgen = 3;
                int bioscript = 4;
                int loci = 5;

                // Player stats determine outcomes of random events: high stats can increase points earned from events and prevent losses from others
                if (player.getPath() == 2) {
                    // Accuracy based events
                    if (stoi(greenEvents[rand_num][4]) == accuracy) {

                        if (player.getAccuracy() >= abs(stoi(greenEvents[rand_num][3]))) {
                            if (stoi(greenEvents[rand_num][3]) < 0) {
                                cout << "" << endl;
                                cout << "Your accuracy was high enough to prevent any loss of discovery points!" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                return player;
                            }
                            else if (stoi(greenEvents[rand_num][3]) > 0) {
                                cout << "" << endl;
                                cout << "Your accuracy was high enough to gain double discovery points!" << endl;
                                cout << "You have gained: " << 2 * stoi(greenEvents[rand_num][3]) << " Discovery Points" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + (2 * stoi(greenEvents[rand_num][3])));
                                return player;
                            }
                        }

                        else {
                            if (stoi(greenEvents[rand_num][3]) < 0) {
                                cout << "" << endl;
                                cout << "You have lost: " << greenEvents[rand_num][3] << " Discovery Points" << endl;
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + stoi(greenEvents[rand_num][3]));
                                return player;
                            }
                            else if (stoi(greenEvents[rand_num][3]) > 0) {
                                cout << "" << endl;
                                cout << "You have gained: " << greenEvents[rand_num][3] << " Discovery Points" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + (stoi(greenEvents[rand_num][3])));
                                return player;
                            }
                        }
                    }
                    // Efficiency based events
                    else if (stoi(greenEvents[rand_num][4]) == efficiency) {

                        if (player.getEfficiency() >= abs(stoi(greenEvents[rand_num][3]))) {
                            if (stoi(greenEvents[rand_num][3]) < 0) {
                                cout << "" << endl;
                                cout << "Your efficiency was high enough to prevent any loss of discovery points!" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                return player;
                            }
                            else if (stoi(greenEvents[rand_num][3]) > 0) {
                                cout << "" << endl;
                                cout << "Your efficiency was high enough to gain double discovery points!" << endl;
                                cout << "You have gained: " << 2 * stoi(greenEvents[rand_num][3]) << " Discovery Points" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + (2 * stoi(greenEvents[rand_num][3])));
                                return player;
                            }
                        }

                        else {
                            if (stoi(greenEvents[rand_num][3]) < 0) {
                                cout << "" << endl;
                                cout << "You have lost: " << greenEvents[rand_num][3] << " Discovery Points" << endl;
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + stoi(greenEvents[rand_num][3]));
                                return player;
                            }
                            else if (stoi(greenEvents[rand_num][3]) > 0) {
                                cout << "" << endl;
                                cout << "You have gained: " << greenEvents[rand_num][3] << " Discovery Points" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + (stoi(greenEvents[rand_num][3])));
                                return player;
                            }
                        }
                    }
                    // Insight Based Events
                    else if (stoi(greenEvents[rand_num][4]) == insight) {

                        if (player.getInsight() >= abs(stoi(greenEvents[rand_num][3]))) {
                            if (stoi(greenEvents[rand_num][3]) < 0) {
                                cout << "" << endl;
                                cout << "Your insight was high enough to prevent any loss of discovery points!" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                return player;
                            }
                            else if (stoi(greenEvents[rand_num][3]) > 0) {
                                cout << "" << endl;
                                cout << "Your insight was high enough to gain double discovery points!" << endl;
                                cout << "You have gained: " << 2 * stoi(greenEvents[rand_num][3]) << " Discovery Points" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + (2 * stoi(greenEvents[rand_num][3])));
                                return player;
                            }
                        }

                        else {
                            if (stoi(greenEvents[rand_num][3]) < 0) {
                                cout << "" << endl;
                                cout << "You have lost: " << greenEvents[rand_num][3] << " Discovery Points" << endl;
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + stoi(greenEvents[rand_num][3]));
                                return player;
                            }
                            else if (stoi(greenEvents[rand_num][3]) > 0) {
                                cout << "" << endl;
                                cout << "You have gained: " << greenEvents[rand_num][3] << " Discovery Points" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + (stoi(greenEvents[rand_num][3])));
                                return player;
                            }
                        }
                    }
                    
                }

                else if (player.getPath() == 1) {
                    // Advisors Preventing discovery point loss from events
                    if (stoi(greenEvents[rand_num][2]) == 1 && player.getAdvisor() == "Dr. Aliquot") {
                        if (stoi(greenEvents[rand_num][3]) < 0) {
                            cout << "" << endl;
                            cout << "Your advisor has prevented you from losing any Discovery Points" << endl;
                            cout << "+1 Exp" << endl;
                            player.setExp(player.getExp() + 1);
                            cout << "" << endl;
                            return player;
                        }           

                        else {return player;}
                    }

                    else if (stoi(greenEvents[rand_num][2]) == 2 && player.getAdvisor() == "Dr. Assembler") {
                        if (stoi(greenEvents[rand_num][3]) < 0) {
                            cout << "" << endl;
                            cout << "Your advisor has prevented you from losing any Discovery Points" << endl;
                            cout << "+1 Exp" << endl;
                            player.setExp(player.getExp() + 1);
                            cout << "" << endl;
                            return player;
                        }    
                        else {return player;}       
                    }

                    else if (stoi(greenEvents[rand_num][2]) == 3 && player.getAdvisor() == "Dr. Pop-Gen") {
                        if (stoi(greenEvents[rand_num][3]) < 0) {
                            cout << "" << endl;
                            cout << "Your advisor has prevented you from losing any Discovery Points" << endl;
                            cout << "+1 Exp" << endl;
                            player.setExp(player.getExp() + 1);
                            cout << "" << endl;
                            return player;
                        }    
                        else {return player;}       
                    }

                    else if (stoi(greenEvents[rand_num][2]) == 4 && player.getAdvisor() == "Dr. Bio-Script") {
                        if (stoi(greenEvents[rand_num][3]) < 0) {
                            cout << "" << endl;
                            cout << "Your advisor has prevented you from losing any Discovery Points" << endl;
                            cout << "+1 Exp" << endl;
                            player.setExp(player.getExp() + 1);
                            cout << "" << endl;
                            return player;
                        }    
                        else {return player;}       
                    }

                    else if (stoi(greenEvents[rand_num][2]) == 5 && player.getAdvisor() == "Dr. Loci") {
                        if (stoi(greenEvents[rand_num][3]) < 0) {
                            cout << "" << endl;
                            cout << "Your advisor has prevented you from losing any Discovery Points" << endl;
                            cout << "+1 Exp" << endl;
                            player.setExp(player.getExp() + 1);
                            cout << "" << endl;
                            return player;
                        }    
                        else {return player;}       
                    }

                    else if (stoi(greenEvents[rand_num][4]) == accuracy) {

                        if (player.getAccuracy() >= abs(stoi(greenEvents[rand_num][3]))) {
                            if (stoi(greenEvents[rand_num][3]) < 0) {
                                cout << "" << endl;
                                cout << "Your accuracy was high enough to prevent any loss of discovery points!" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                return player;
                            }
                            else if (stoi(greenEvents[rand_num][3]) > 0) {
                                cout << "" << endl;
                                cout << "Your accuracy was high enough to gain double discovery points!" << endl;
                                cout << "You have gained: " << 2 * stoi(greenEvents[rand_num][3]) << " Discovery Points" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + (2 * stoi(greenEvents[rand_num][3])));
                                return player;
                            }
                        }

                        else {
                            if (stoi(greenEvents[rand_num][3]) < 0) {
                                cout << "" << endl;
                                cout << "You have lost: " << greenEvents[rand_num][3] << " Discovery Points" << endl;
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + stoi(greenEvents[rand_num][3]));
                                return player;
                            }
                            else if (stoi(greenEvents[rand_num][3]) > 0) {
                                cout << "" << endl;
                                cout << "You have gained: " << greenEvents[rand_num][3] << " Discovery Points" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + (2 * stoi(greenEvents[rand_num][3])));
                                return player;
                            }
                        }
                    }
                    

                    else if (stoi(greenEvents[rand_num][4]) == efficiency) {

                        if (player.getEfficiency() >= abs(stoi(greenEvents[rand_num][3]))) {
                            if (stoi(greenEvents[rand_num][3]) < 0) {
                                cout << "" << endl;
                                cout << "Your efficiency was high enough to prevent any loss of discovery points!" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                return player;
                            }
                            else if (stoi(greenEvents[rand_num][3]) > 0) {
                                cout << "" << endl;
                                cout << "Your efficiency was high enough to gain double discovery points!" << endl;
                                cout << "You have gained: " << 2 * stoi(greenEvents[rand_num][3]) << " Discovery Points" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + (2 * stoi(greenEvents[rand_num][3])));
                                return player;
                            }
                        }

                        else {
                            if (stoi(greenEvents[rand_num][3]) < 0) {
                                cout << "" << endl;
                                cout << "You have lost: " << greenEvents[rand_num][3] << " Discovery Points" << endl;
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + stoi(greenEvents[rand_num][3]));
                                return player;
                            }
                            else if (stoi(greenEvents[rand_num][3]) > 0) {
                                cout << "" << endl;
                                cout << "You have gained: " << greenEvents[rand_num][3] << " Discovery Points" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + (2 * stoi(greenEvents[rand_num][3])));
                                return player;
                            }
                        }
                    }

                    else if (stoi(greenEvents[rand_num][4]) == insight) {

                        if (player.getInsight() >= abs(stoi(greenEvents[rand_num][3]))) {
                            if (stoi(greenEvents[rand_num][3]) < 0) {
                                cout << "" << endl;
                                cout << "Your insight was high enough to prevent any loss of discovery points!" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                return player;
                            }
                            else if (stoi(greenEvents[rand_num][3]) > 0) {
                                cout << "" << endl;
                                cout << "Your insight was high enough to gain double discovery points!" << endl;
                                cout << "You have gained: " << 2 * stoi(greenEvents[rand_num][3]) << " Discovery Points" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + (2 * stoi(greenEvents[rand_num][3])));
                                return player;
                            }
                        }

                        else {
                            if (stoi(greenEvents[rand_num][3]) < 0) {
                                cout << "" << endl;
                                cout << "You have lost: " << greenEvents[rand_num][3] << " Discovery Points" << endl;
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + stoi(greenEvents[rand_num][3]));
                                return player;
                            }
                            else if (stoi(greenEvents[rand_num][3]) > 0) {
                                cout << "" << endl;
                                cout << "You have gained: " << greenEvents[rand_num][3] << " Discovery Points" << endl;
                                cout << "+1 Exp" << endl;
                                player.setExp(player.getExp() + 1);
                                cout << "" << endl;
                                player.setDiscoveryPoints(player.getDiscoveryPoints() + (2 * stoi(greenEvents[rand_num][3])));
                                return player;
                            }
                        }
                    }
                }



            }
            //Chance for nothing to occur on green tiles
            else {
                cout << "Nothing seems to happen... this time" << endl;
                cout << "" << endl;
            }
        break;
        }
        // Blue Tile Event Triggers
        case 'B': {

            Features blueFeatures;
            // Player player; no need to reinitialize
            cout << "" << endl;
            cout << "Blue Tile Event Time!" << endl;
            cout << "" << endl;

            int dnaLength = rand() % 9 + 4;
            string strand1 = blueFeatures.randomDNAGenerator(dnaLength);
            string strand2 = blueFeatures.randomDNAGenerator(dnaLength); // variables for parameters for first DNA sequence function and task

            if (strand2 > strand1) {     // make sure that strand 1 is always longer so there is no issue when it's passed as a parameter
                string temp;
                temp = strand1;
                strand1 = strand2;
                strand2 = temp;
            }
            int user_answer;

            cout << "For this easy task, you must provide the total number of positions that are identical between two different strand halves of equal length." << endl;
            cout << "" << endl;
            cout << "DNA Strand One: " << strand1 << endl;
            cout << "DNA Strand Two: " << strand2 << endl;
            cout << "How many positions are identical between both strands?" << endl;
            cin >> user_answer;
            cin.ignore();
            cout << "" << endl;

            if (blueFeatures.strandSimilarity(strand1, strand2, user_answer)) {
                cout << "Correct! You have gained 200 Discovery Points" << endl;
                cout << "+1 Exp" << endl;
                player.setExp(player.getExp() + 1);
                cout << "" << endl;
                player.setDiscoveryPoints(player.getDiscoveryPoints() + 200);
                return player;
            }

            else {
                cout << "Incorrect! You have lost 200 Discovery Points and went back to your previous position" << endl;
                moveBackPosition(player_index);
                cout << "" << endl;
                player.setDiscoveryPoints(player.getDiscoveryPoints() - 200);
                return player;
            }



            break;
        }

        // Pink tile event triggers
        case 'P': {

            Features pinkFeatures;
            // Player player; no need to reinitialize
            cout << "" << endl;
            cout << "Pink Tile Event Time!" << endl;
            cout << "" << endl;

            int dnaOneLength = rand() % 9 + 4;
            int dnaTwoLength = rand() % 9 + 4;
            string strand1 = pinkFeatures.randomDNAGenerator(dnaOneLength);
            string strand2 = pinkFeatures.randomDNAGenerator(dnaTwoLength); // variables for parameters for second DNA sequence function and task

            while (strand1.length() == strand2.length()) {
                dnaOneLength = rand() % 9 + 4;
                dnaTwoLength = rand() % 9 + 4;
                strand1 = pinkFeatures.randomDNAGenerator(dnaOneLength);
                strand2 = pinkFeatures.randomDNAGenerator(dnaTwoLength);
            }
            if (strand2 > strand1) {
                string temp;
                temp = strand1;
                strand1 = strand2;
                strand2 = temp;
            }
            int user_answer;

            cout << "For this task, you will be provided two DNA strand halves. You must find the position (integral value 1, 2, etc.) on the longer strand where the shorter strand has the closest similarity score." << endl;
            cout << "Remember, the shorter DNA piece must fit completely onto the longer one. No overhangs allowed!";
            cout << "" << endl;
            cout << "DNA Strand: " << strand1 << endl;
            cout << "DNA Strand: " << strand2 << endl;
            cout << "" << endl;
            cout << "At what position (integral value) on the longer strand, does the shorter strand have the best similarity score? " << endl;
            cout << "Remember, there could be multiple right answers, just pick one." << endl;
            cin >> user_answer;
            cin.ignore();
            cout << "" << endl;

            if (pinkFeatures.bestStrandMatch(strand1, strand2, user_answer)) {
                cout << "Correct! You have gained 400 Discovery Points" << endl;
                cout << "+1 Exp" << endl;
                player.setExp(player.getExp() + 1);
                cout << "" << endl;
                player.setDiscoveryPoints(player.getDiscoveryPoints() + 400);
                return player;
            }

            else {
                cout << "Incorrect! You have lost 400 Discovery Points and went back to your previous position" << endl;
                moveBackPosition(player_index);
                cout << "" << endl;
                player.setDiscoveryPoints(player.getDiscoveryPoints() - 400);
                return player;
            }

        break;
        }
        // Red tile event Triggers
        case 'R': {

            Features redFeatures;
            cout << "" << endl;
            cout << "Red Tile Event Time!" << endl;
            cout << "" << endl;

            int dnaOneLength = rand() % 9 + 4;
            int dnaTwoLength = rand() % 9 + 4;
            string strand1 = redFeatures.randomDNAGenerator(dnaOneLength);
            string strand2 = redFeatures.randomDNAGenerator(dnaTwoLength); // variables for parameters for second DNA sequence function and task
            if (strand2 > strand1) {
                string temp;
                temp = strand1;
                strand1 = strand2;
                strand2 = temp;
            }
            int user_answer;

            cout << "For this difficult task, you will be provided with two DNA strand halves. You must calculate the total number of substitutions wherever the two strand halves have the greatest similarity." << endl;
            cout << "Remember, if length differs when looking for similarity, the shorter DNA piece must fit completely onto the longer one. No overhangs allowed!";
            cout << "" << endl;
            cout << "DNA Strand: " << strand1 << endl;
            cout << "DNA Strand: " << strand2 << endl;
            cout << "" << endl;
            cout << "At the position of greatest similarity (integral value), how many substitutions are there?" << endl;
            cin >> user_answer;
            cin.ignore();
            cout << "" << endl;
            
            if (redFeatures.identifyMutations(strand1, strand2, user_answer)) {
                cout << "Correct! You have gained 800 Discovery Points" << endl;
                cout << "+1 Exp" << endl;
                player.setDiscoveryPoints(player.getDiscoveryPoints() + 800);
                player.setExp(player.getExp() + 1);
                cout << "" << endl;
                return player;
            }

            else {
                cout << "Incorrect! You have lost 800 Discovery Points and went back to your previous position" << endl;
                moveBackPosition(player_index);
                cout << "" << endl;
                player.setDiscoveryPoints(player.getDiscoveryPoints() - 800);
                return player;
            }

        break;
        }
        // Brown Tile Event Trigger
        case 'T': {

            Features brownFeatures;
            // Player player; no need to reinitialize
            cout << "" << endl;
            cout << "Brown Tile Event Time!" << endl;
            cout << "" << endl;

            int dnaLength = rand() % 9 + 4;
            string strand = brownFeatures.randomDNAGenerator(dnaLength); // variables for parameters for fourth DNA sequence function and task
            string user_answer;

            cout << "For this task, you will be given a DNA strand half, and you must provide the corresponding RNA strand. (Hint, T = U)" << endl;
            cout << "" << endl;
            cout << "DNA Strand: " << strand << endl;
            cout << "What would be the corresponding RNA Strand?" << endl;
            cin >> user_answer;
            cin.ignore();
            cout << "" << endl;

            if (brownFeatures.transcribeDNAtoRNA(strand, user_answer)) {
                cout << "Correct! You have gained 600 Discovery Points!" << endl;
                cout << "+1 Exp" << endl;
                player.setExp(player.getExp() + 1);
                cout << "" << endl;
                player.setDiscoveryPoints(player.getDiscoveryPoints() + 600);
                return player;
            }

            else {
                cout << "Incorrect! You have lost 600 Discovery Points and went back to your previous position" << endl;
                moveBackPosition(player_index);
                cout << "" << endl;
                player.setDiscoveryPoints(player.getDiscoveryPoints() - 600);
                return player;
            }

        break;
        }
        // Purple Tile Event Triggers
        case 'U':
        Features purpleFeatures;
        // Player player; no need to reinitialize
        cout << "" << endl;
        cout << "Purple Tile Event Time!" << endl;
        cout << "" << endl;
        cout << "It's time to answer a riddle..." << endl;

        int riddle_int = purpleFeatures.displayRiddle();
        string user_answer;
        cin >> user_answer;
        cin.ignore();
        cout << "" << endl;

        if (purpleFeatures.answerRiddle(riddle_int, user_answer)) {
            cout << "That's correct! You have gained 500 Insight Points and 100 Discovery Points" << endl;
            cout << "+1 Exp" << endl;
            player.setExp(player.getExp() + 1);
            cout << "" << endl;
            player.setInsight(player.getInsight() + 500);
            player.setDiscoveryPoints(player.getDiscoveryPoints() + 100);
            return player;
        }

        else {
            cout << "That's incorrect! You have lost 100 Discovery Points and went back to your previous position" << endl;
            moveBackPosition(player_index);
            cout << "" << endl;
            player.setDiscoveryPoints(player.getDiscoveryPoints() - 100);
            return player;
        }

        break;
    }
    return player;

}
// Saves previous board position to potentially move backwards one step
void Board::savePreviousPosition(int player_index) {
        _previous_position[player_index] = _player_position[player_index];
}
// Activates moving back one step when players get answers wrong
void Board::moveBackPosition(int player_index) {
        _player_position[player_index] = _previous_position[player_index];
}