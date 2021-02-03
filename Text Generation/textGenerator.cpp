/*
 * File: textGenerator.cpp
 * Author: Michal Fitrzyk
 * Description: Program that takes in a .txt file and creates sentences based
 * on any group of N words together and each word after that group of words
 * TODO(mfitrz2): Nothing
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "myrandom.h"

using namespace std;

// Function prototypes
void buildMap(map<vector<string>, vector<string>> &map, string &fileName,
              int &nValue);
void printMap(map<vector<string>, vector<string>> &map);
void generateText(map<vector<string>, vector<string>> &map, int &sentLength);
bool fileGood(string &fileName);

int main() {
    int nValue, sentLength;
    string fileName;
    char option;
    map<vector<string>, vector<string>> map;

    cout << "Welcome to the Text Generator." << endl
         << "This program makes random text based on a document." << endl
         << "Input file name?  ";
    cin >> fileName;
    // Loops until a valid file is given
    while (!fileGood(fileName)) {
        cout << "Invalid file, try again: ";
        cin >> fileName;
    }
    cout << "Value of N?  ";
    cin >> nValue;
    // Loops until a valid nValue is given
    while (nValue < 2) {
        cout << "N must be > 1, try again: ";
        cin >> nValue;
    }
    cout << "Total words you'd like to generate?  ";
    cin >> sentLength;
    // Loops until a valid sentLength is given
    while (sentLength < nValue) {
        cout << "Total words must be at least N, try again: ";
        cin >> sentLength;
    }
    // Main loop that runs all the functions and executes given options
    do {
        cout << "Type b-build map, p-print map, g-generate text, s-start over, "
                "x-to exit: ";
        cin >> option;
        cout << endl;
        // Builds the map with given fileName and nValue
        if (option == 'b') {
            buildMap(map, fileName, nValue);
            cout << "...Building map: " << fileName << "..." << endl;
        }
        // Prints out an already build map
        if (option == 'p') {
            printMap(map);
        }
        // Generates a sentence from the given map and sentLength
        if (option == 'g') {
            generateText(map, sentLength);
        }
        // Starts the program over; getting rid of the current map
        if (option == 's') {
            map.clear();  // Empties the entire map in order to build a new one
            cout << "Welcome to the Text Generator." << endl
                 << "This program makes random text based on a document."
                 << endl
                 << "Input file name?  ";
            cin >> fileName;
            // Loops until a valid fileName is given
            while (!fileGood(fileName)) {
                cout << "Invalid file, try again: ";
                cin >> fileName;
            }
            cout << "Value of N?  ";
            cin >> nValue;
            // Loops until a valid nValue is given
            while (nValue < 2) {
                cout << "N must be > 1, try again: ";
                cin >> nValue;
            }
            cout << "Total words you'd like to generate?  ";
            cin >> sentLength;
            // Loops until a valid sentLength is given
            while (sentLength < nValue) {
                cout << "Total words must be at least N, try again: ";
                cin >> sentLength;
            }
        }
        // Ends the loop and the program
        if (option == 'x') {
            return 0;
        }
        cout << endl;
    } while (true);
    return 0;
}
// Function that reads in given .txt file and generates groups of words (based
// on N) and the word that comes after the group.
// The map named map is passed as a reference as we will only be building it
// once. I also need to pass in the file (fileName) and how many words in a
// group (N).
void buildMap(map<vector<string>, vector<string>> &map, string &fileName,
               int &nValue) {
    vector<string> key, value, temp, nFirstWords;
    ifstream inFile(fileName);
    string word;
    // While the end of the file is not reached, a group of words denoted by N
    // is mapped to a suffixes into a map.
    while (!inFile.eof()) {
        inFile >> word;
        if (!inFile.fail()) {
            // Reads in the first couple of words denoted by the N value
            // and stores it into a vecor for later use in N - 1 iterations
            // to map the words at the beginning of the file to the words at the
            // end of the file.
            if ((int)nFirstWords.size() != (nValue - 1)) {
                nFirstWords.push_back(word);
            }
            // If the key vector holds enough words for a N gram, map is updated
            // with the key vector as its key, and the next word in the file is
            // added as a value to that key.
            if (((int)key.size() == (nValue - 1))) {
                // Key already exits in the map
                if (map.count(key) > 0) {
                    // Creates a temporary vector which holds the value vector.
                    // This is in order to add another word into value vector.
                    temp = map.at(key);
                    temp.push_back(word);
                    map[key] = temp;
                    temp.clear();
                } else {  // Key doesn't exist in the map
                    value.push_back(word);
                    map[key] = value;
                }
                key.erase(key.begin());  // Erases the first element in key
                key.push_back(word);  // Adds the next word into key vector
                value.clear();
            } else {
                key.push_back(word);
            }
        }
    }
    // Iterates N - 1 times in order to map the first couple of words
    // into the map because the last words cannot be mapped to words at the
    // beginning of the file inside the while loop above.
    for (int i = 0; i < (int)nFirstWords.size(); i++) {
        if (((int)key.size() == (nValue - 1))) {
            // Key already exits in the map
            if (map.count(key) > 0) {
                // Creates a temporary vector which holds the value vector.
                // This is in order to add another word into value vector.
                temp = map.at(key);
                temp.push_back(nFirstWords[i]);
                map[key] = temp;
                temp.clear();
            } else {  // Key doesn't exist in the map
                value.push_back(nFirstWords[i]);
                map[key] = value;
            }
            key.erase(key.begin());  // Erases the first element in key vector
            key.push_back(nFirstWords[i]);  // Adds next word into key
            value.clear();
        } else {
            key.push_back(nFirstWords[i]);
        }
    }
}
// Function that prints out each key and associated value in given map
// in ascending order.
void printMap(map<vector<string>, vector<string>> &map) {
    // Loops through the map in ascending order using a for each loop
    // in order to print out each key and associated value.
    for (auto &e : map) {
        cout << "{";
        // Loops through the key which is a vector and prints out its
        // contents.
        for (int i = 0; i < (int)e.first.size(); i++) {
            if (i != (int)e.first.size() - 1) {
                cout << e.first[i] << " ";
            } else {
                cout << e.first[i];
            }
        }
        cout << "} -> {";
        // Loops through the associated value vector and prits out its
        // contents.
        for (int j = 0; j < (int)e.second.size(); j++) {
            if (j != (int)e.second.size() - 1) {
                cout << e.second[j] << " ";
            } else {
                cout << e.second[j];
            }
        }
        cout << "}" << endl;
    }
}
// Function that creates a sentence randomly using the given map.
// This is done by first selecting a random number and looping through the map
// until that valued is reached. This is the first key and value pair that will
// be used in the sentence. Then, the last word in key and the randomly selected
// value is then used the next key. This is repeated until the sentLength is
// reached.
void generateText(map<vector<string>, vector<string>> &map, int &sentLength) {
    // The window vector is used to keep track of the current key that will be
    // used to select a random value to add into the sentence.
    vector<string> window, sentence, temp;
    int randomOne = randomInteger(0, (int)map.size() - 1), randomTwo, c = 0;
    cout << "...";
    // Loops through the map in order to randomly select the first key and
    // value pair for the words in the sentence.
    for (auto &e : map) {
        if (c == randomOne) {
            // Appends all the words in the first key into the sentence vector
            for (auto &i : e.first) {
                sentence.push_back(i);
            }
            window = e.first;
            window.erase(window.begin());  // Erases the first element in window
            randomTwo = randomInteger(0, (int)e.second.size() - 1);
            window.push_back(e.second[randomTwo]);  // Appends a random word in
                                                    // the value vector into the
                                                    // current "window"
            sentence.push_back(e.second[randomTwo]);  // Appends the same random
                                                      // word into the sentence
            break;
        }
        c++;
    }
    // Instead of looping through the map each time to the current window,
    // every iteration uses the .find()->second function of the map to get the
    // associated value. A random value is then chosen in the value vector
    // which is added to the sentence vector and to the window.
    while ((int)sentence.size() < sentLength) {
        temp = window;
        window.erase(window.begin());  // Deletes the first element in window
        randomTwo = randomInteger(0, (int)map.find(temp)->second.size() - 1);
        // Adds a random value from the old window into the new window,
        // and adds the same value into the sentence vector.
        window.push_back(map.find(temp)->second[randomTwo]);
        sentence.push_back(map.find(temp)->second[randomTwo]);
    }
    // Loops that prints out the sentence to the terminal
    for (int i = 0; i < (int)sentence.size(); i++) {
        if (i != (int)sentence.size() - 1) {
            cout << sentence[i] << " ";
        } else {
            cout << sentence[i];
        }
    }
    cout << "..." << endl;
}
// Function that checks if a given file name is good and returns true if the
// file is good, and false if the file cannot be opened.
bool fileGood(string &fileName) {
    ifstream inFile(fileName);
    return inFile.good();
}



















