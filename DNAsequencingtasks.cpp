#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
// DNA Sequencing Task 1: Strand Similarity (Equal Length)
double strandSimilarity (string strand1, string strand2){
int matches = 0;
int size = strand1.length();
for (int i = 0; i < size; i++){
    if (strand1[i] == strand2[i])
    matches++;
}
double similarity = (double)matches/size;
return similarity;
}
// DNA Sequencing Task 2: Strand Similarity (Unequal Length)
int bestStrandMatch (string input_strand, string target_strand){
    int matches = 0;
    int bestMatches = 0;
    int bestPosition;
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
    cout << input_strand << " " << target_strand << endl;
    int lengthDiff = inputLength - targetLength;
    for (int j = 0; j <= lengthDiff; j++){
        for (int i = 0; i < targetLength; i++){
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
    double similarityScore = (double)bestMatches/targetLength;
    cout << "Best Similarity Score: " << similarityScore << endl;

    //cout << input_strand << " " << target_strand << endl;
    return bestPosition;

}
//DNA Sequencing Task 3: Mutation Identification
void identifyMutations(string input_strand, string target_strand){
    // Re-use of code for finding the best position before identifying mutations
    int matches = 0;
    int bestMatches = 0;
    int bestPosition;
    int inLength = input_strand.length();
    int tgtLength = target_strand.length();
    int lengthDiff = abs(inLength - tgtLength);
    
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
            cout << "Deletion at position " << i + 1 << ": "<< input_strand[i] << " is deleted in target strand" << endl;
        }
        for (int i = bestPosition + tgtLength; i < inLength; i++){
            cout << "Deletion at position " << i + 1 << ": "<< input_strand[i] << " is deleted in target strand" << endl;
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
            cout << "Insertion at position " << i + 1 << ": "<< input_strand[i] << " is inserted in input strand" << endl;
        }
        for (int i = bestPosition + tgtLength; i < inLength; i++){
            cout << "Insertion at position " << i + 1 << ": "<< input_strand[i] << " is inserted in input strand" << endl;
        }
    }
    // Printing Mutations within aligned positions
    for (int i = bestPosition; i < bestPosition + tgtLength; i++){
        if (target_strand[i] != input_strand[i+bestPosition]){
            cout << "Substitution at position " << i+1 << ": " << input_strand[i] << " -> " << target_strand[i+bestPosition] << endl;
        }
        else{
            cout << "Position " << i+1 << " is correct" << endl;
        }
    }
    cout << "Best Position: "<< bestPosition << endl;
    
}
// DNA Sequencing Task 4: Transcribe DNA to RNA
void transcribeDNAtoRNA (string strand){
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
        }
        else{
            cout << strand[i] << " ";
        }
    }
    cout << endl;
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
int main (){
    //cout << "Task 1 Test:" << endl;
    //cout << "Strand Similarity: " << strandSimilarity ("ACTG", "ACCG") << endl;

    //cout << "Task 2 Test:" << endl;
    //bestStrandMatch ("ACTG", "ACTGACTG");

    //cout << "Task 3 Test:" << endl;
    //identifyMutations("ACTG", "ACCGACTG");

    //cout << "Task 4 Test:" << endl;
    //transcribeDNAtoRNA ("ACTG");

    cout << "DNA Gerneration Test:" << endl;
    cout << randomDNAGenerator(4) << endl;

    return 0;
}