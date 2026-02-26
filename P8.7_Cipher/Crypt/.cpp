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
#include <fstream>
#include <string>
#include <unordered_set>
#include <cctype>

using namespace std;

// Generate cipher alphabet from keyword
string generateCipherAlphabet(const string& keyword) {
    string result;
    unordered_set<char> used;

    for (char c : keyword) {
        if (isalpha(c)) {
            c = toupper(c);
            if (!used.count(c)) {
                result += c;
                used.insert(c);
            }
        }
    }

    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 25; i >= 0; --i) {
        char c = ALPHABET[i];
        if (!used.count(c)) {
            result += c;
        }
    }

    return result;
}

// Encrypt a keyword (just returns its cipher alphabet)
string encryptKeyword(const string& keyword) {
    return generateCipherAlphabet(keyword);
}

// Decipher a word in cipher alphabet format to recover original keyword
string decipherToKeyword(const string& cipherWord) {
    string result;
    unordered_set<char> added;

    // Only take letters until all unique letters are collected
    for (char c : cipherWord) {
        char upperC = toupper(c);
        if (!added.count(upperC)) {
            result += tolower(upperC);
            added.insert(upperC);
        }
        else {
            break; // stop once duplicates begin
        }
    }

    return result;
}

int main() {
    int choice;
    cout << "Select an option:\n";
    cout << "1. Encrypt a keyword (generate cipher alphabet)\n";
    cout << "2. Decipher a word in cipher alphabet format to get the keyword\n";
    cout << "Enter 1 or 2: ";
    cin >> choice;
    cin.ignore(); // clear newline

    ofstream outFile("cipher_output.txt");
    if (!outFile.is_open()) {
        cerr << "Error: Could not open file for writing.\n";
        return 1;
    }

    if (choice == 1) {
        string keyword;
        cout << "Enter keyword to encrypt: ";
        cin >> keyword;

        string cipherAlphabet = encryptKeyword(keyword);

        cout << "Cipher alphabet generated: " << cipherAlphabet << endl;

        outFile << "=== Cipher Process ===\n";
        outFile << "Keyword entered: " << keyword << "\n";
        outFile << "Cipher alphabet generated: " << cipherAlphabet << "\n";
        outFile << "=====================\n";

    }
    else if (choice == 2) {
        string cipherWord;
        cout << "Enter word in cipher alphabet format: ";
        cin >> cipherWord;

        string originalKeyword = decipherToKeyword(cipherWord);

        cout << "Recovered keyword: " << originalKeyword << endl;

        outFile << "=== Cipher Process ===\n";
        outFile << "Cipher word entered: " << cipherWord << "\n";
        outFile << "Recovered keyword: " << originalKeyword << "\n";
        outFile << "=====================\n";

    }
    else {
        cout << "Invalid choice.\n";
    }

    outFile.close();
    cout << "Process written to cipher_output.txt" << endl;

    return 0;
}
