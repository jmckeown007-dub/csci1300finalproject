#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Scientists.h"
#include "Player.h"

using namespace std;

int main() {


    //

    /*
     */
    cout << "" << endl;

    cout << "Player 1! We're gonna start with you..." << endl;
    cout << "What's your name?" << endl;    

    // setting player1name and object
    Player playerOne;
    string playerOneName;
    getline(cin, playerOneName);
    playerOne.setName(playerOneName);
    cout << "Okay " << playerOneName << ", cool name I guess..." << endl;
    cout << "" << endl;


    characterSetUp setup("characters.txt");
    setup.printScientists();
    string chosenCharacter = setup.selectCharacter();
    setup.setSelectedCharacter(chosenCharacter);

    // set player1 character
    playerOne.setCharacter(chosenCharacter);

    vector<string> playerStats = setup.logPlayerCharacterStats();
    setup.setplayerCharacterStats(playerStats);
    vector<string> allStats = setup.getplayerCharacterStats();

    playerOne.setAllStats(allStats);
    

    int chosenPath = setup.choosePath();
    setup.setSelectedPath(chosenPath);

    if (chosenPath == 1) {
        playerOne.setAccuracy(playerOne.getAccuracy() + 500);
        playerOne.setEfficiency(playerOne.getEfficiency() + 500);
        playerOne.setInsight(playerOne.getInsight() + 1000);
        playerOne.setDiscoveryPoints(playerOne.getDiscoveryPoints() - 5000);
    } 
    else if (chosenPath == 2) {
        playerOne.setAccuracy(playerOne.getAccuracy() + 200);
        playerOne.setEfficiency(playerOne.getEfficiency() + 200);
        playerOne.setInsight(playerOne.getInsight() + 200);
        playerOne.setDiscoveryPoints(playerOne.getDiscoveryPoints() + 5000);
    }
    //
    // test menu
    //
    //playerOne.displayMenu();
    



    cout << "" << endl;

    cout << "Player 2! It's your turn now..." << endl;
    cout << "What's your name?" << endl;    

    // setting player2name and object
    Player playerTwo;
    string playerTwoName;
    getline(cin, playerTwoName);
    playerTwo.setName(playerTwoName);
    cout << "Okay " << playerTwoName << ", now THAT'S a cool name!" << endl;
    cout << "" << endl;


    characterSetUp setup2("characters.txt");
    setup2.printScientists();
    string chosenCharacter2 = setup2.selectCharacter();
    setup2.setSelectedCharacter(chosenCharacter2);

    // set player2 character
    playerTwo.setCharacter(chosenCharacter);

    vector<string> playerStats2 = setup2.logPlayerCharacterStats();
    setup2.setplayerCharacterStats(playerStats2);
    vector<string> allStats2 = setup2.getplayerCharacterStats();

    playerTwo.setAllStats(allStats2);
    

    int chosenPath2 = setup2.choosePath();
    setup2.setSelectedPath(chosenPath2);

    if (chosenPath2 == 1) {
        playerTwo.setAccuracy(playerTwo.getAccuracy() + 500);
        playerTwo.setEfficiency(playerTwo.getEfficiency() + 500);
        playerTwo.setInsight(playerTwo.getInsight() + 1000);
        playerTwo.setDiscoveryPoints(playerTwo.getDiscoveryPoints() - 5000);
    } 
    else if (chosenPath2 == 2) {
        playerTwo.setAccuracy(playerTwo.getAccuracy() + 200);
        playerTwo.setEfficiency(playerTwo.getEfficiency() + 200);
        playerTwo.setInsight(playerTwo.getInsight() + 200);
        playerTwo.setDiscoveryPoints(playerTwo.getDiscoveryPoints() + 5000);
    }

    srand(time(0)); // Seed random numbers for tile colors

    Board gameBoard; // Create the board
    gameBoard.initializeBoard();
    gameBoard.displayBoard(); // Show initial board

    return 0;
}