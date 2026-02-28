/*
CSC242 – Final Group Project
Project: P8.7 Random Monoalphabetic Cipher
File Name: crypt.cpp

Description:
This program encrypts or decrypts a text file using a keyword cipher.
It removes duplicate letters from the keyword, builds a cipher alphabet,
then reads an input file and writes an output file with letters mixed up.

How to run:
1) Put your input file (plain.txt) in the SAME folder as this project (.vcxproj).
2) Click Run.
3) Choose Encrypt (1) or Decrypt (2).
4) Enter keyword, input filename, output filename.
5) Repeat steps to decrypt input (encrypted.txt) to output (encrypted.txt)

Team Members:
- Eric Amidei (EA)
- Kevin Ferry (KF)
- Jose Lopez-Arredondo (JL)

*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// (KF) Generate cipher alphabet from keyword
string generateCipherAlphabet(const string& keyword) {
    string result;
    string used;

    for (char c : keyword) {
        if (isalpha((unsigned char)c)) {
            c = (char)toupper((unsigned char)c);
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

    return result; // 26 letters
}

// (KF) Encrypt a keyword
string encryptKeyword(const string& keyword) {
    return generateCipherAlphabet(keyword);
}

// decipherToKeyword function does not work with duplicated letters (JL)

// (EA) Encrypt one character using cipher alphabet
char encryptChar(char ch, const string& cipherAlphabet) {
    if (!isalpha((unsigned char)ch)) return ch;

    bool wasLower = islower((unsigned char)ch);
    char upper = (char)toupper((unsigned char)ch);

    int index = upper - 'A';               // A=0, B=1, ...
    char mapped = cipherAlphabet[index];   // plain -> cipher

    if (wasLower) mapped = (char)tolower((unsigned char)mapped);
    return mapped;
}

// (EA) Decrypt one character using cipher alphabet
char decryptChar(char ch, const string& cipherAlphabet) {
    if (!isalpha((unsigned char)ch)) return ch;

    bool wasLower = islower((unsigned char)ch);
    char upper = (char)toupper((unsigned char)ch);

    // cipher -> plain by finding the cipher letter position
    size_t pos = cipherAlphabet.find(upper);
    if (pos == string::npos) return ch;

    char mapped = (char)('A' + (int)pos);
    if (wasLower) mapped = (char)tolower((unsigned char)mapped);
    return mapped;
}

// (EA) Encrypt or decrypt a file using the cipher alphabet
bool transformFile(const string& inputName,
    const string& outputName,
    const string& cipherAlphabet,
    bool decryptMode) {
    ifstream fin(inputName);
    ofstream fout(outputName);

    if (!fin.is_open()) {
        cerr << "Error: Could not open input file: " << inputName << "\n";
        return false;
    }
    if (!fout.is_open()) {
        cerr << "Error: Could not open output file: " << outputName << "\n";
        return false;
    }

    char ch;
    while (fin.get(ch)) {
        if (decryptMode) {
            fout.put(decryptChar(ch, cipherAlphabet));
        }
        else {
            fout.put(encryptChar(ch, cipherAlphabet));
        }
    }

    fin.close();
    fout.close();
    return true;
}


// (EA) Uses a simple menu so it runs in Visual Studio without command arguments.
int main() {
    cout << "Select an option:\n";
    cout << "1. Encrypt a file\n";
    cout << "2. Decrypt a file\n";
    cout << "Enter 1 or 2: ";

    int choice;
    cin >> choice;

    if (choice != 1 && choice != 2) {
        cout << "Invalid choice.\n";
        return 1;
    }

    string keyword;
    cout << "Enter keyword (required): ";
    cin >> keyword;

    if (keyword.empty()) {
        cout << "Error: keyword is required.\n";
        return 1;
    }

    string inputName;
    cout << "Enter input filename: ";
    cin >> inputName;

    string outputName;
    cout << "Enter output filename: ";
    cin >> outputName;

    // (KF) Build cipher alphabet from keyword
    string cipherAlphabet = encryptKeyword(keyword);

    // (EA) choice==2 means decrypt mode
    bool decryptMode = (choice == 2);

    // (EA) Transform the file and report results
    bool ok = transformFile(inputName, outputName, cipherAlphabet, decryptMode);

    if (ok) {
        cout << "Cipher alphabet: " << cipherAlphabet << "\n";
        cout << "Done. Output written to: " << outputName << "\n";
        return 0;
    }
    else {
        cout << "File transform failed.\n";
        return 1;
    }
}
