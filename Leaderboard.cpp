#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void printLeaderboard(){
ifstream inFile ("leaderboard.txt");
string word;
int score;
cout << "Leaderboard: " << endl;
cout << "Name:   Score:" << endl;
// Reading in and outputting each pair of name and score line by line
for (int j = 0; j < 5; j++){
   inFile >> word >> score;
   cout << word << " " << score;
cout << endl;
}
}
void updateLeaderboard(string newname, int newscore){
    string name;
    int score;
    int newposition = 6;
    vector<string> names(5);
    vector<int> scores(5);
    ifstream inFile;
    inFile.open ("leaderboard.txt");
    // Reading names and scores into seperate vectors and storing them
    for (int i = 0; i < 5; i++){
        inFile >> name >> score;
        names[i] = name;
        scores[i] = score;
    }
    // Finding the position of a new score on the leaderboard
    for(int i = 4; i >= 0; i--){
        if (newscore > scores.at(i)){
            newposition = i;
        }
    }
    // Moving scores below the new score into lower positions to make room for the new score
    for (int i = 4; i > newposition; i--){
        scores[i] = scores[i-1];
        names[i] = names[i-1];
    }
    // Adding the new score into the position made.
    scores[newposition] = newscore;
    names[newposition] = newname;
    inFile.close();
    ofstream outFile;
    outFile.open("leaderboard.txt");
    // Writing new data into the leaderboard file to store permanently
    for(int i = 0; i < 5; i++){
        outFile << names[i] << " " << scores[i] << endl;
    }
}