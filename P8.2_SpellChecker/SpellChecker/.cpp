/*
CSC242 – Final Group Project
Project: P8.2 Spell Check

Description:
Write a program that checks the spelling of all words in a file.

Team Members:
- Eric Amidei (EA)
- Kevin Ferry (KF)
- Jose Lopez-Arredondo (JL)
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> // for std::find
#include <cctype>    // for std::ispunct

// (KF) Function to remove punctuation from a word
std::string cleanWord(const std::string &word) {
    std::string cleaned;
    for (char c : word) {
        if (!std::ispunct(c))
            cleaned += c;
    }
    return cleaned;
}

//(KF) Pull from file location
int main() {
    std::ifstream dictFile("words.txt");//EA changed the dictionary file location
    if (!dictFile) {
        std::cerr << "Could not open dictionary file.\n";
        return 1;
    }

    std::vector<std::string> words;
    std::string word;

    // (KF) Read dictionary words into vector
    while (dictFile >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        //EA added line to check for both case words from dictionary
        words.push_back(word);
    }
    dictFile.close();

    std::ifstream checkFile("input.txt");//EA changed the file containing test words to input
    if (!checkFile) {
        std::cerr << "Could not open file to check.\n";
        return 1;
    }

    // (JL) Check each word in the file
    while (checkFile >> word) {
        std::string cleaned = cleanWord(word);

        // Convert to lowercase for case-insensitive comparison
        std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(), ::tolower);

        if (std::find(words.begin(), words.end(), cleaned) == words.end()) {
            std::cout << cleaned << "\n";
        }
    }

    checkFile.close();
    return 0;
}

