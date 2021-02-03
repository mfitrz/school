//
//  application.cpp
//  Author: Michal Fitrzyk
//  TODO(mfitrz2): Nothing
//  DNA Profiling app that matches a given dna strand to a person by counting
//  how many specific strings of DNA were present in the input and comparing
//  them to people in a database file.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "dna.h"

using namespace std;

// Given a database file, the file is looped trough. Each line is extracted
// which holds a name and counts of a DNA string. The name and the counts are
// stored in a vector. This vector is then stored in another vector. This
// creates a vector that bascially holds each person's information in each index
void loadData(vector<vector<string>> &allPersons, string &filename) {
    vector<string> eachPerson;
    fstream inFile(filename);
    string line;
    // Loops through the file and adds each persons information as a element
    // into the eachPerson vector. This vector is then pushed back into the
    // allPersons vector.
    while (inFile >> line) {
        // Loops through each line of the file and extracts that person's data
        while (line.find(',') != std::string::npos){
            // Finds the first comma
            size_t pos = line.find(',');
            // Extracts the information before the comma
            string temp = line.substr(0, pos);
            eachPerson.push_back(temp);
            // Deletes the extracted data and the comma from the line
            line = line.substr(pos + 1, line.size() - temp.size() - 1);
        }
        eachPerson.push_back(line);
        allPersons.push_back(eachPerson);
        // Clears the eachPerson vector in order to use the same vector
        // for different people
        eachPerson.clear();
    }
}
// Given a DNA file that contains a strand of DNA, that strand is stored as a
// string and then an object is created that is equivalent to that string.
// That dna object is then spliced target DNA strings that are present in the
// database. If the DNA strand contains the same nubmer of certian DNA strings
// present in the database, then it matches an individual.
void locateDna(string &filename, string &person,
               vector<vector<string>> &allPersons) {
    fstream inFile(filename);
    string dnastr;
    int foundIndex, indexBefore = 0;
    bool foundBefore = false;
    inFile >> dnastr;  // Gets the DNA strand into the string
    // Checks all of the given DNA strings that are in the based against the DNA
    // strand.
    for (int i = 1; i < (int)allPersons[0].size(); i++) {
        bool found = false;
        dna d(dnastr);
        int count = 0;
        string search = allPersons[0][i];
        dna searchDNA(search);  // Creates a dna object that holds the DNA
                                // strand (linked list)
        // Splices the current target DNA string until the DNA strand
        // does not contain it anymore. This counts how many times
        // that certain target string existed in the DNA strand.
        while (d.splice(searchDNA) != false) {
            count++;
        }
        // Goes through the database data which is stored in the vector,
        // allPersons, and checks if the number of DNA strings present
        // in the DNA strand matches anyone else's data.
        for (int j = 1; j < (int)allPersons.size(); j++) {
            if (stoi(allPersons[j][i]) == count) {
                found = true;
                // All the strings have to match a person, so if the previous
                // doesn't match, then it can not be that person's DNA.
                if (foundBefore && indexBefore == j) {
                    foundIndex = j;  // j stores the matched person's data
                }
                foundBefore = true;
                indexBefore = j;
                break;
            }
            found = false;
        }
        // If at any point the data in the database does not match the DNA
        // strand, then the there is no person that matches and thus returns
        if (!found){
            return;
        }
    }
    // The person that matches is updated in a string
    person = allPersons[foundIndex][0];
}

int main() {
    vector<vector<string>> allPersons;
    string database, dnaFile, person = "";
    cout << "Welcome to the DNA Profiling App!" << endl
         << "Enter database file: ";
    cin >> database;
    cout << "Enter dna file: ";
    cin >> dnaFile;
    cout << endl << "Searching database..." << endl;
    // Loads the database data into the allPersons vector
    loadData(allPersons, database);
    // Tries to match the given DNA strand to a person
    locateDna(dnaFile, person, allPersons);
    // the DNA matched someone's data
    if (person != "") {
        cout << "DNA match: " << person << endl;
        // The DNA did not match anyone in the given database
    } else {
        cout << "No match." << endl;
    }
    return 0;
}
