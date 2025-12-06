#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <vector>
using namespace std;

int displayRiddle(){
    ifstream inFile;
    inFile.open ("riddles.txt");
    string line;
    vector<string> riddles(25);
    vector<string> answers (25);
    for(int i = 0; i < 25; i++){
        getline (inFile, line, '|');
        riddles[i] = line;
        getline (inFile, line);
        answers [i] = line;
    }
    srand(time(0));
    int id = rand()%24;
    cout << riddles[id] << endl;
    return id;
}

bool answerRiddle(int id, string answer){
    ifstream inFile;
    inFile.open ("riddles.txt");
    string line;
    vector<string> riddles(25);
    vector<string> answers (25);
    for(int i = 0; i < 25; i++){
        getline (inFile, line, '|');
        riddles[i] = line;
        getline (inFile, line);
        answers [i] = line;
    }
    if(answer == answers[id]){
        cout << "That's Correct!" << endl;
        return true;
    }
    else{
        cout << "That's Incorrect" << endl;
        return false;
    }
}

int main(){
    int id = displayRiddle();
    string answer;
    cin >> answer;
    answerRiddle(id, answer);
    return 0;
}