#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Scientists.h"
#include "Player.h"
#include "gameFeatures.h"
#include "animateText.h"
#define underline "\033[4m"
#define reset "\033[0m"
//#define underline "\033[24m"

// source for these include statements and their uses herein: https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
#include <chrono>
#include <thread>


using namespace std;


int main() {


    // Initialize Classes
    Player playerOne;
    Player playerTwo;
    characterSetUp setup("characters.txt");
    characterSetUp setup2("characters.txt");
    Features gf;
    /*
     */

    /* Game Introduction */
    cout << "" << endl;
    type_text("Welcome to your Journey Through the Genome!");
    cout << "" << endl;
    type_text("This is a mini-game in which two players play as DNA Scientists and roll a die to progress through their scientific journey...");
    cout << "" << endl;
    type_text("As you progress through the tiles on the board, you will face different challenges and different events that will impact your 'Discovery Points.'");
    cout << "" << endl;
    type_text("Successful events will result in gaining Discovery Points, while failed events will result in losing Discovery Points.");
    cout << "" << endl;
    type_text("You also have traits (Accuracy, Efficiency, and Insight) that will aid you in certain in-game events. Your experience level is used to gain or change an advisor.");
    cout << "" << endl;
    type_text("Once both players reach or pass the end of the board (the orange tile), whichever player has more Discovery Points wins and successfully presents their DNA findings at the Genome Conference.");
    cout << "" << endl;
    type_text("First, we will set up each player with a character and path.");
    cout << "" << endl;

    /* Uncomment console outputs if you want text to appear all at once instead of as if it were typed*/
    // cout << "Player 1! We're gonna start with you..." << endl;
    type_text("Player 1! We're gonna start with you... ");
    std::this_thread::sleep_for(std::chrono::seconds(1)); // wait one second before printing next line
    //cout << "What's your name?" << endl;    
    type_text("What's your name?");
    cout << "" << endl;

    /* setting player1name and object */
    string playerOneName;
    getline(cin, playerOneName);
    playerOne.setName(playerOneName);
    cout << "" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //cout << "Okay " << playerOneName << ", cool name I guess..." << endl;
    type_text("Okay ");
    cout << playerOneName;
    type_text(", cool name I guess...");
    cout << "" << endl;
    cout << "" << endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    
    setup.printScientists();
    string chosenCharacter = setup.selectCharacter();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    setup.setSelectedCharacter(chosenCharacter);

    // set player1 character
    playerOne.setCharacter(chosenCharacter);

    vector<string> playerStats = setup.logPlayerCharacterStats();
    setup.setplayerCharacterStats(playerStats);
    vector<string> allStats = setup.getplayerCharacterStats();

    playerOne.setAllStats(allStats);
    
    cout << ""<< endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    int chosenPath = setup.choosePath();
    setup.setSelectedPath(chosenPath);

    if (chosenPath == 1) {
        // Awarding stats based on path choice
        playerOne.setPath(1);
        playerOne.setAccuracy(playerOne.getAccuracy() + 500);
        playerOne.setEfficiency(playerOne.getEfficiency() + 500);
        playerOne.setInsight(playerOne.getInsight() + 1000);
        playerOne.setDiscoveryPoints(playerOne.getDiscoveryPoints() - 5000);

        int playerOneAdvisor = setup.chooseAdvisor();

        std::this_thread::sleep_for(std::chrono::seconds(1));
        switch (playerOneAdvisor) {
            case 1:
                playerOne.setAdvisor("Dr. Aliquot");
                playerOne.setAdvisorDesc("A master of the \"wet lab\", assisting in avoiding contamination");
                cout << "" << endl;
                break;
            
            case 2:
                playerOne.setAdvisor("Dr. Assembler");
                playerOne.setAdvisorDesc("An expert who helps improve efficiency and streamlines pipelines");
                cout << "" << endl;
                break;

            case 3:
                playerOne.setAdvisor("Dr. Pop-Gen");
                playerOne.setAdvisorDesc("A genetics specialist with insight for identifying rare genetic variants");
                cout << "" << endl;
                break;

            case 4:
                playerOne.setAdvisor("Dr. Bio-Script");
                playerOne.setAdvisorDesc("The genius behind the data analysis, helps debug code");
                cout << "" << endl;
                break;

            case 5:
                playerOne.setAdvisor("Dr. Loci");
                playerOne.setAdvisorDesc("Your biggest supporter assisting you in learning the equipment");
                cout << "" << endl;
                break;
        }

    } 
    else if (chosenPath == 2) {
        //Awarding stats based on path choice
        playerOne.setPath(2);
        playerOne.setAccuracy(playerOne.getAccuracy() + 200);
        playerOne.setEfficiency(playerOne.getEfficiency() + 200);
        playerOne.setInsight(playerOne.getInsight() + 200);
        playerOne.setDiscoveryPoints(playerOne.getDiscoveryPoints() + 5000);
        playerOne.setExp(playerOne.getExp() - playerOne.getExp() + 14);
    }
    
    



    cout << "" << endl;

    //cout << "Player 2! It's your turn now..." << endl;
    type_text("Player 2! It's your turn now... ");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //cout << "What's your name?" << endl;   
    type_text("What's your name?"); 
    
    cout << "" << endl;

    // setting player2name and object
    string playerTwoName;
    getline(cin, playerTwoName);
    playerTwo.setName(playerTwoName);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "" << endl;
    //cout << "Okay " << playerTwoName << ", now THAT'S a cool name!" << endl;
    type_text("Okay ");
    cout << playerTwoName;
    type_text(", now THAT'S a cool name!");
    cout << "" << endl;
    cout << "" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));


    setup2.printScientists();
    string chosenCharacter2 = setup2.selectCharacter();
    setup2.setSelectedCharacter(chosenCharacter2);

    // set player2 character
    playerTwo.setCharacter(chosenCharacter2);

    vector<string> playerStats2 = setup2.logPlayerCharacterStats();
    setup2.setplayerCharacterStats(playerStats2);
    vector<string> allStats2 = setup2.getplayerCharacterStats();

    playerTwo.setAllStats(allStats2);
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    int chosenPath2 = setup2.choosePath();
    setup2.setSelectedPath(chosenPath2);
    //Stats and advisors are assigned for second player
    if (chosenPath2 == 1) {
        playerTwo.setPath(1);
        playerTwo.setAccuracy(playerTwo.getAccuracy() + 500);
        playerTwo.setEfficiency(playerTwo.getEfficiency() + 500);
        playerTwo.setInsight(playerTwo.getInsight() + 1000);
        playerTwo.setDiscoveryPoints(playerTwo.getDiscoveryPoints() - 5000);

        cout << "" << endl;
        int playerTwoAdvisor = setup2.chooseAdvisor();

        std::this_thread::sleep_for(std::chrono::seconds(1));
        switch (playerTwoAdvisor) {
            case 1:
                playerTwo.setAdvisor("Dr. Aliquot");
                playerTwo.setAdvisorDesc("A master of the \"wet lab\", assisting in avoiding contamination");
                cout << "" << endl;
                break;
            
            case 2:
                playerTwo.setAdvisor("Dr. Assembler");
                playerTwo.setAdvisorDesc("An expert who helps improve efficiency and streamlines pipelines");
                cout << "" << endl;
                break;

            case 3:
                playerTwo.setAdvisor("Dr. Pop-Gen");
                playerTwo.setAdvisorDesc("A genetics specialist with insight for identifying rare genetic variants");
                cout << "" << endl;
                break;

            case 4:
                playerTwo.setAdvisor("Dr. Bio-Script");
                playerTwo.setAdvisorDesc("The genius behind the data analysis, helps debug code");
                cout << "" << endl;
                break;

            case 5:
                playerTwo.setAdvisor("Dr. Loci");
                playerTwo.setAdvisorDesc("Your biggest supporter assisting you in learning the equipment");
                cout << "" << endl;
                break;
        }
    } 
    else if (chosenPath2 == 2) {
        playerTwo.setPath(2);
        playerTwo.setAccuracy(playerTwo.getAccuracy() + 200);
        playerTwo.setEfficiency(playerTwo.getEfficiency() + 200);
        playerTwo.setInsight(playerTwo.getInsight() + 200);
        playerTwo.setDiscoveryPoints(playerTwo.getDiscoveryPoints() + 5000);
        playerTwo.setExp(playerTwo.getExp() - playerTwo.getExp() + 14);
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    //cout << "It's time to start the game..." << endl;

    type_text("It's time to start the game...");
    cout << "" << endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    srand(time(0)); // random seed for tile colors, otherwise will be same every time

    cout << "" << endl;
    cout << underline << "Game Board: " << reset << endl;

    int playerOnePath = chosenPath;
    int playerTwoPath = chosenPath2;

    Board gameBoard(playerOnePath, playerTwoPath); // Create board
    gameBoard.initializeBoard();
    gameBoard.displayBoard(); // Show initial board

    std::this_thread::sleep_for(std::chrono::seconds(1));

    //////////////////////////* TIME FOR THE GAMEPLAY LOOP *//////////////////////////
    
    bool gameOver = false;
    bool playerOneEnd = false;
    bool playerTwoEnd = false;
    bool useAdvisor = false;
    int currentPlayer = 0;
    // Main gameplay while loop, continues looping through players one and two until the game ends
    while (gameOver == false) {
        
        /* Player One's Turn */

        if (currentPlayer == 0 && !playerOneEnd) {
            cout << "" << endl;
            cout << playerOne.getName() << "'s turn" << endl;
            cout << "" << endl;


            /* The following choices are included here rather than in original function because these affect gameplay, they aren't merely informational */
            int playerChoice = 0;
        

            while (playerChoice != 5) {

                playerChoice = playerOne.displayMenu();

                if (playerChoice == 3) {
                    cout << "" << endl;
                    cout << underline << "Current Discovery Points" << reset << endl;
                    cout << playerOne.getName() << ": " << playerOne.getDiscoveryPoints() << endl;
                    cout << playerTwo.getName() << ": " << playerTwo.getDiscoveryPoints() << endl;
                    cout << "" << endl;
                }


            }

            gameBoard.savePreviousPosition(0);
            int roll = gf.rollDice();
            cout << "" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            //cout << "You rolled a " << roll << "!" << endl;
            type_text("You rolled a ");
            cout << roll;
            type_text("!");
            cout << "" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            for (int i = 0; i < roll; i++) {
                if (gameBoard.movePlayer(0)) {
                    //cout << "Player One has reached the end!" << endl;
                    type_text("Player One has reached the end!");
                    cout << "" << endl;
                    cout << "" << endl;
                    playerOneEnd = true;
                }
            }

            // Get current tile color
            char currentTileColor = gameBoard.getTileColor(0, gameBoard.getPlayerPosition(0));

            // Trigger event
            playerOne.setAllStats(gameBoard.tileTrigger(playerOne, currentTileColor, 0).getAllStats());
            
        }

        else if (currentPlayer == 1 && !playerTwoEnd) {
            cout << "" << endl;
            cout << playerTwo.getName() << "'s turn!" << endl;
            cout << "" << endl;

            /* The following choices are included here rather than in original function because these affect gameplay, they aren't merely informational */
            int playerChoice2 = 0;
            

            while (playerChoice2 != 5) {

                playerChoice2 = playerTwo.displayMenu();

                if (playerChoice2 == 3) {
                    cout << "" << endl;
                    cout << underline << "Current Discovery Points" << reset << endl;
                    cout << playerOne.getName() << ": " << playerOne.getDiscoveryPoints() << endl;
                    cout << playerTwo.getName() << ": " << playerTwo.getDiscoveryPoints() << endl;
                    cout << "" << endl;
                }

 
            }
            
            gameBoard.savePreviousPosition(1);

            int roll2 = gf.rollDice();

            cout << "" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            //cout << "You rolled a " << roll2 << "!" << endl;
            type_text("You rolled a ");
            cout << roll2;
            type_text("!");
            cout << "" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            for (int i = 0; i < roll2; i++) {
                if (gameBoard.movePlayer(1)) {
                    cout << "Player Two has reached the end!" << endl;
                    
                    cout << "" << endl;
                    playerTwoEnd = true;
                }
            }

            // Get current tile color
            char currentTileColor = gameBoard.getTileColor(1, gameBoard.getPlayerPosition(1));

            // Trigger event if green
            playerTwo.setAllStats(gameBoard.tileTrigger(playerTwo, currentTileColor, 1).getAllStats());

        }   
    
        cout << "" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        gameBoard.displayBoard();
        cout << "" << endl;

        currentPlayer = 1 - currentPlayer;

        if (playerOneEnd == true && playerTwoEnd == true) {
            gameOver = true;
            //Leaderboard updates
            gf.updateLeaderboard(playerOne.getName(), playerOne.getDiscoveryPoints());
            gf.updateLeaderboard(playerTwo.getName(), playerTwo.getDiscoveryPoints());
            
            cout << "" << endl;
            type_text("Both players have reached the end! Game over");
            cout << "" << endl;
            type_text("Leaderboard: ");

            cout << "" << endl;
            type_text(playerOne.getName());
            type_text(": ");
            type_text(to_string(playerOne.getDiscoveryPoints()));
            type_text(" Discovery Points");

            cout << "" << endl;
            type_text(playerTwo.getName());
            type_text(": ");
            type_text(to_string(playerTwo.getDiscoveryPoints()));
            type_text(" Discovery Points");
            cout << "" << endl;
            cout << "" << endl;

            if (playerOne.getDiscoveryPoints() > playerTwo.getDiscoveryPoints()) {
                type_text(playerOne.getName());
                type_text(" wins!");
                cout << "" << endl;
                type_text("You have successfully presented your research at the genome conference. Good job!");
                cout << "" << endl;
                cout << "" << endl;
                type_text("Thanks for playing! Goodbye");
            }

            else if (playerOne.getDiscoveryPoints() < playerTwo.getDiscoveryPoints()) {
                type_text(playerTwo.getName());
                type_text(" wins!");
                cout << "" << endl;
                type_text("You have successfully presented your research at the genome conference. Good job!");
                cout << "" << endl;
                cout << "" << endl;
                type_text("Thanks for playing! Goodbye");
            }

            else {
                type_text("Wow! A tie game! Both players successfuly present their research at the genome conference. Good job!");
                cout << "" << endl;
                cout << "" << endl;
                type_text("Thanks for playing! Goodbye");
            }
        }

    }
    

    return 0;
}