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
#include <cctype>

using namespace std;

// Generate cipher alphabet from keyword
string generateCipherAlphabet(const string& keyword) {
    string result;
    string used;

    for (char c : keyword) {
        if (isalpha(c)) {
            c = toupper(c);
            if (used.find(c) == string::npos) {
                result += c;
                used += c;
            }
        }
    }

    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 25; i >= 0; --i) {
        char c = ALPHABET[i];
        if (used.find(c) == string::npos) {
            result += c;
        }
    }

    return result;
}

// Encrypt a keyword (returns cipher alphabet)
string encryptKeyword(const string& keyword) {
    return generateCipherAlphabet(keyword);
}

// Decipher using cipher alphabet to get only the original keyword
string decipherToKeyword(const string& cipherAlphabet, int keywordLength) {
    // Take only the first N letters from cipher alphabet, N = keyword length
    string result;
    for (int i = 0; i < keywordLength; ++i) {
        result += tolower(cipherAlphabet[i]);
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
        int keywordLength;
        cout << "Enter word in cipher alphabet format: ";
        cin >> cipherWord;
        cout << "Enter length of original keyword: ";
        cin >> keywordLength;

        string originalKeyword = decipherToKeyword(cipherWord, keywordLength);

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
