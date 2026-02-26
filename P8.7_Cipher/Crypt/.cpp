/*
CSC242 – Final Group Project
Project: P8.7 Random Monoalphabetic Cipher
File Name: crypt.cpp

Description:
This program encrypts or decrypts a text file using a keyword cipher.
The program removes duplicate letters from the keyword, builds a cipher alphabet,
and uses it to transform the input file. The result is written to an output file.

Usage Examples:
Encrypt: crypt -kFEATHER input.txt output.txt
Decrypt: crypt -d -kFEATHER input.txt output.txt

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
#include <string>
#include <unordered_set>
#include <cctype>

using namespace std;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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

    return 0;
}
