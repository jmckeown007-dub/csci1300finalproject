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
for (int j = 0; j < 5; j++){
   inFile >> word >> score;
   cout << word << " " << score;
cout << endl;
}
}
void updateLeaderboard(string newname, int newscore){
    string name;
    int score;
    int newposition;
    vector<string> names(5);
    vector<int> scores(5);
    ifstream inFile;
    inFile.open ("leaderboard.txt");
    for (int i = 0; i < 5; i++){
        inFile >> name >> score;
        names[i] = name;
        scores[i] = score;
    }
    for(int i = 4; i >= 0; i--){
        if (newscore > scores.at(i)){
            newposition = i;
        }
    }
    for (int i = 4; i > newposition; i--){
        scores[i] = scores[i-1];
        names[i] = names[i-1];
    }
    scores[newposition] = newscore;
    names[newposition] = newname;
    inFile.close();
    ofstream outFile;
    outFile.open("leaderboard.txt");
    for(int i = 0; i < 5; i++){
        outFile << names[i] << " " << scores[i] << endl;
    }
}