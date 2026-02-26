/*
CSC242 – Final Group Project
Project: P8.7 Random Monoalphabetic Cipher
File Name: crypt.cpp

Description:
This program encrypts or decrypts a text file using a keyword cipher.
The program removes duplicate letters from the keyword, builds a cipher alphabet,
and uses it to transform the input file. The result is written to an output file.

Inputs:
- Keyword supplied using -k option
- Input text file
- Encrypt or decrypt mode (-d for decrypt)

Outputs:
- New text file containing encrypted or decrypted text

Team Members:
- Eric Amidei
- Kevin Ferry
- Jose Lopez-Arredondo
*/

#include <iostream>
#include <fstream>      // For file output
#include <string>
#include <unordered_set>
#include <cctype>

using namespace std;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Author: Kevin Ferry
string generateCipherAlphabet(const string& keyword) {
    string result;
    unordered_set<char> used;

    // Add keyword letters (remove duplicates)
    for (char c : keyword) {
        if (isalpha(c)) {
            c = toupper(c);
            if (!used.count(c)) {
                result += c;
                used.insert(c);
            }
        }
    }

    // Append remaining letters in reverse order
    for (int i = 25; i >= 0; --i) {
        char c = ALPHABET[i];
        if (!used.count(c)) {
            result += c;
        }
    }

    return result;
}

int main() {
    string keyword;

    cout << "Enter keyword: ";
    cin >> keyword;

    string cipherAlphabet = generateCipherAlphabet(keyword);

    cout << "Generated cipher alphabet:\n";
    cout << cipherAlphabet << endl;

    // Write output to file
    ofstream outFile("cipher_output.txt");
    if (outFile.is_open()) {
        outFile << "Keyword: " << keyword << "\n";
        outFile << "Generated cipher alphabet: " << cipherAlphabet << "\n";
        outFile.close();
        cout << "Cipher alphabet written to cipher_output.txt" << endl;
    }
    else {
        cerr << "Error: Could not open file for writing." << endl;
    }

    return 0;
}
