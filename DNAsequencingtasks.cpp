#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
// DNA Sequencing Task 1: Strand Similarity (Equal Length)
bool strandSimilarity (string strand1, string strand2, int answer){
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
bool bestStrandMatch (string input_strand, string target_strand, int answer){
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
            vector <int> bestPosition;
            bestPosition.push_back(j+1);
        }
        if (matches == bestMatches){
            bestPosition.push_back(j+1);
        }
        matches = 0;
    }
    double similarityScore = (double)bestMatches/targetLength;
    cout << "Best Similarity Score: " << similarityScore << endl;
    for (int i = 0; i < bestPosition.size(); i++){
    if (answer == bestPosition[i]){
        return true;
    }
    }
    return false;

}
//DNA Sequencing Task 3: Mutation Identification
bool identifyMutations(string input_strand, string target_strand, int answer){
    // Re-use of code for finding the best position before identifying mutations
    int matches = 0;
    int bestMatches = 0;
    int bestPosition;
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
    if (answer == substitutions + lengthDiff){
        return true;
    }
    else{
        return false;
    }
}
// DNA Sequencing Task 4: Transcribe DNA to RNA
bool transcribeDNAtoRNA (string strand, string answer){
    string RNA = " ";
    int length = strand.length();
    //Outputting Original DNA Strand
    cout << "Original DNA Strand" << endl;
    for (int i = 0; i < length; i++){
        cout << strand[i] << " ";
    }
    cout << endl;
    //Outputting Transcribed RNA Strand
    cout << "Transcribed RNA Strand" << endl;
    for (int i = 0; i < length; i++){
        if (strand[i] == 'T'){
            cout << 'U' << " "; 
            RNA = RNA + "U";
        }
        else{
            cout << strand[i] << " ";
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
string randomDNAGenerator(int length){
    string DNA = " ";
    srand(time(0));
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