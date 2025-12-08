#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Scientists.h"
#include "Player.h"
#include "gameFeatures.h"
#include <sstream>
#include <fstream>

using namespace std;




int Features::rollDice() {
            return rand() % 6 + 1;
        }



Features::Features() {
    greenValue = "";
    blueValue = 0;
    pinkValue = 0;
    redValue = 0;
    brownValue = "";
    purpleValue = "";
};

//getters
string Features::getGreenValue() {
    return greenValue;
}
int Features::getBlueValue() {
    return blueValue;
}
int Features::getPinkValue() {
    return pinkValue;
}
int Features::getRedValue() {
    return redValue;
}
string Features::getBrownValue() {
    return brownValue;
}
string Features::getPurpleValue() {
    return purpleValue;
}

//setters
void Features::setGreenValue(string value) {
    greenValue = value;
}
void Features::setBlueValue(int value) {
    blueValue = value;
}
void Features::setPinkValue(int value) {
    pinkValue = value;
}
void Features::setRedValue(int value) {
    redValue = value;
}
void Features::setBrownValue(string value) {
    brownValue = value;
}
void Features::setPurpleValue(string value) {
    purpleValue = value;
}


// read file for random string for green tiles
vector<vector<string>> Features::greenString(string filename) {
    ifstream greenFile(filename);

    if (!greenFile) {
        cout << "Cannot open file." << endl;
        return {};
    }
    string line;
    getline(greenFile, line); // read the header line first to get rid of it

    vector<vector<string>> eventsVector;

    while (getline (greenFile, line)) {

        if (line.rfind("/", 0) == 0 || line.empty()) { // source: https://stackoverflow.com/questions/1878001/how-do-i-check-if-a-c-stdstring-starts-with-a-certain-string-and-convert-a
            continue;
        }

        stringstream ss(line);
        string part;
        vector<string> row;

        while (getline (ss, part, '|')) {
            row.push_back(part);
        }

        eventsVector.push_back(row);
    }

    return eventsVector;

}


// DNA Sequencing Task 1: Strand Similarity (Equal Length)
bool Features::strandSimilarity (string strand1, string strand2, int answer){
int matches = 0;
int size = strand1.length();
for (int i = 0; i < size; i++){
    if (strand1[i] == strand2[i])
    matches++;
}
double similarity = (double)matches/size;
if (matches == answer){
    return true;
}
else{
    return false;
}

}
// DNA Sequencing Task 2: Strand Similarity (Unequal Length)
bool Features::bestStrandMatch (string input_strand, string target_strand, int answer){
    int matches = 0;
    int bestMatches = 0;
    vector <int> bestPosition;
    int inputLength = input_strand.length();
    int targetLength = target_strand.length();
    if (inputLength < targetLength){
        string temp = input_strand;
        input_strand = target_strand;
        target_strand = temp;
        int tempint = inputLength;
        inputLength = targetLength;
        targetLength = tempint;
    }
    int lengthDiff = inputLength - targetLength;
    for (int j = 0; j <= lengthDiff; j++){
        for (int i = 0; i < targetLength; i++){
            if (target_strand[i] == input_strand[i+j]){
                matches++;
            }
        }
        if (matches > bestMatches){
            bestMatches = matches;
            bestPosition.clear();
            bestPosition.push_back(j+1);
        }
        else if (matches == bestMatches){
            bestPosition.push_back(j+1);
        }
        matches = 0;
    }
    double similarityScore = (double)bestMatches/targetLength;
    //cout << "Best Similarity Score: " << similarityScore << endl;
    for (int i = 0; i < bestPosition.size(); i++){
    if (answer == bestPosition[i]){
        return true;
    }
    }
    return false;

}

//DNA Sequencing Task 3: Mutation Identification
bool Features::identifyMutations(string input_strand, string target_strand, int answer){
    // Re-use of code for finding the best position before identifying mutations
    int matches = 0;
    int bestMatches = 0;
    int bestPosition = 0;
    int inLength = input_strand.length();
    int tgtLength = target_strand.length();
    int lengthDiff = abs(inLength - tgtLength);
    int substitutions = 0;
    
    // If the input strand is longer than the target strand
    if (inLength >= tgtLength){
        for (int j = 0; j < lengthDiff; j++){
            for (int i = 0; i < tgtLength; i++){
                if (target_strand[i] == input_strand[i+j]){
                    matches++;
                }
            }
            if (matches > bestMatches){
                bestMatches = matches;
                bestPosition = j;
            }
            matches = 0;
        }
        // Printing deletions before and after target strand
        for (int i = 0; i < bestPosition; i++){
            //cout << "Deletion at position " << i + 1 << ": "<< input_strand[i] << " is deleted in target strand" << endl;
        }
        for (int i = bestPosition + tgtLength; i < inLength; i++){
            //cout << "Deletion at position " << i + 1 << ": "<< input_strand[i] << " is deleted in target strand" << endl;
        }
    }
    // If the target strand is Longer than the input strand
    if (tgtLength > inLength){
        for (int j = 0; j < lengthDiff; j++){
            for (int i = 0; i < inLength; i++){
                if (target_strand[i+j] == input_strand[i]){
                    matches++;
                }
            }
            if (matches > bestMatches){
                bestMatches = matches;
                bestPosition = j;
            }
            matches = 0;
        }
        // Printing insertions before and after target strand
        for (int i = 0; i < bestPosition; i++){
            //cout << "Insertion at position " << i + 1 << ": "<< input_strand[i] << " is inserted in input strand" << endl;
        }
        for (int i = bestPosition + tgtLength; i < inLength; i++){
            //cout << "Insertion at position " << i + 1 << ": "<< input_strand[i] << " is inserted in input strand" << endl;
        }
    }
    // Printing Mutations within aligned positions
    for (int i = bestPosition; i < bestPosition + tgtLength; i++){
        if (target_strand[i] != input_strand[i+bestPosition]){
            //cout << "Substitution at position " << i+1 << ": " << input_strand[i] << " -> " << target_strand[i+bestPosition] << endl;
            substitutions++;
        }
        else{
            //cout << "Position " << i+1 << " is correct" << endl;
        }
    }
    //cout << "Best Position: "<< bestPosition << endl;
    if (answer == substitutions) { // + lengthDiff){ commented this out to make it easier for the user
        return true;
    }
    else{
        return false;
    }
}
// DNA Sequencing Task 4: Transcribe DNA to RNA
bool Features::transcribeDNAtoRNA (string strand, string answer){
    string RNA = "";
    int length = strand.length();
    //Outputting Original DNA Strand
    //cout << "Original DNA Strand" << endl; 
    /*for (int i = 0; i < length; i++){
        cout << strand[i]; // << " ";
    }*/
    cout << endl;
    //Outputting Transcribed RNA Strand     uncomment if you want to see results, but i am omitting them for the purposes of gameplay
    //cout << "Transcribed RNA Strand" << endl;
    for (int i = 0; i < length; i++){
        if (strand[i] == 'T'){
            //cout << 'U'; // << " "; 
            RNA = RNA + "U";
        }
        else{
            //cout << strand[i]; // << " ";
            RNA = RNA + strand[i];
        }
    }
    cout << endl;
    if (answer == RNA){
        return true;
    }
    else{
        return false;
    }
}
string Features::randomDNAGenerator(int length){
    string DNA = "";
    for(int i = 0; i < length; i++){
        int randint = rand()%4;
        switch (randint){
            case 0:
            DNA = DNA + "A";
            break;
            case 1:
            DNA = DNA + "C";
            break;
            case 2:
            DNA = DNA + "T";
            break;
            case 3:
            DNA = DNA + "G";
            break;
        }
    }
    return DNA;
}

int Features::displayRiddle(){
    ifstream inFile;
    inFile.open ("riddles.txt");
    string line;
    vector<string> riddles(25);
    vector<string> answers (25);
    getline(inFile, line); // skip header line
    for(int i = 0; i < 25; i++){
        getline (inFile, line, '|');
        riddles[i] = line;
        getline (inFile, line);

        if (line.back() == '\r') {
            line.pop_back();            // remove carriage return
        }

        answers [i] = line;
    }
    int id = rand()%25;
    cout << riddles[id] << endl;
    return id;
}

bool Features::answerRiddle(int id, string answer){
    ifstream inFile;
    inFile.open ("riddles.txt");
    string line;
    vector<string> riddles(25);
    vector<string> answers (25);
    getline(inFile, line); // skip header line
    for(int i = 0; i < 25; i++){
        getline (inFile, line, '|');
        riddles[i] = line;
        getline (inFile, line);

        if (line.back() == '\r') {
            line.pop_back();            // remove carriage return
        }

        answers [i] = line;
    }
    if(answer == answers[id]){
        //cout << "That's Correct!" << endl;   include this in call, not in function
        return true;
    }
    else{
        //cout << "That's Incorrect" << endl;  ditto
        return false;
    }
}

void Features::printLeaderboard(){
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

void Features::updateLeaderboard(string newname, int newscore){
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