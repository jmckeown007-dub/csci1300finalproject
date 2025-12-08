// Recognized as "include guards"
// Prevent the board header file from being used more than once
#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include "Player.h"

class Board {
    private:
        // Static in this context: Belongs to the class, not each object
        static const int _BOARD_SIZE = 52;
        static const int _MAX_PLAYERS = 2;

        // Composition!
        Tile _tiles[2][_BOARD_SIZE];

        int _player_count;
        int _player_position[_MAX_PLAYERS];
        int _previous_position[_MAX_PLAYERS];
        int _player_paths[2];

        void initializeTiles(int player_index, int player_path);
        bool isPlayerOnTile(int player_index, int pos);
        void displayTile(int player_index, int pos);

    public:
        // Default Constructor
        Board(int playerOnePath, int playerTwoPath);

        void initializeBoard();
        void displayTrack(int player_index);
        void displayBoard();
        void savePreviousPosition(int player_index);
        void moveBackPosition(int player_index);
        bool movePlayer(int player_index);
        // Recall we can use const for getter functions
        int getPlayerPosition(int player_index) const;
        char getTileColor(int player_index, int pos);
        Player tileTrigger(Player player, char tileColor, int player_index);
};

#endif