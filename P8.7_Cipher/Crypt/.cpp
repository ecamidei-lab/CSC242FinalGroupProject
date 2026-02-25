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
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// Author: 
// Check if character exists in string
bool containsChar(const string& s, char c)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == c)
            return true;
    }
    return false;
}

// Author: 
// Remove duplicate letters and convert to uppercase
string removeDuplicates(const string& keyword)
{
    string result = "";

    for (int i = 0; i < keyword.length(); i++)
    {
        char c = toupper(keyword[i]);

        if (c >= 'A' && c <= 'Z')
        {
            if (!containsChar(result, c))
            {
                result += c;
            }
        }
    }

    return result;
}

// Author: 
// Build cipher alphabet
string buildCipherAlphabet(const string& cleanedKey)
{
    string cipher = cleanedKey;

    for (char c = 'Z'; c >= 'A'; c--)
    {
        if (!containsChar(cipher, c))
        {
            cipher += c;
        }
    }

    return cipher;
}

// Author: 
// Encrypt one letter
char encryptLetter(char c, const string& cipher)
{
    int index = toupper(c) - 'A';
    char encrypted = cipher[index];

    if (islower(c))
        encrypted = tolower(encrypted);

    return encrypted;
}

// Author: 
// Decrypt one letter
char decryptLetter(char c, const string& cipher)
{
    char upper = toupper(c);

    for (int i = 0; i < cipher.length(); i++)
    {
        if (cipher[i] == upper)
        {
            char decrypted = 'A' + i;

            if (islower(c))
                decrypted = tolower(decrypted);

            return decrypted;
        }
    }

    return c;
}

// Author: 
// Encrypt or decrypt file
void transformFile(string inputFile, string outputFile, string cipher, bool decryptMode)
{
    ifstream fin(inputFile);
    ofstream fout(outputFile);

    if (!fin)
    {
        cout << "Could not open input file.\n";
        return;
    }

    if (!fout)
    {
        cout << "Could not open output file.\n";
        return;
    }

    char c;

    while (fin.get(c))
    {
        if (isalpha(c))
        {
            if (decryptMode)
                fout << decryptLetter(c, cipher);
            else
                fout << encryptLetter(c, cipher);
        }
        else
        {
            fout << c;
        }
    }

    fin.close();
    fout.close();
}

// Author: 
// Main function
int main(int argc, char* argv[])
{
    if (argc != 4 && argc != 5)
    {
        cout << "Usage:\n";
        cout << "Encrypt: crypt -kKEY input.txt output.txt\n";
        cout << "Decrypt: crypt -d -kKEY input.txt output.txt\n";
        return 1;
    }

    bool decryptMode = false;
    string keyArg;
    string inputFile;
    string outputFile;

    if (argc == 4)
    {
        keyArg = argv[1];
        inputFile = argv[2];
        outputFile = argv[3];
    }
    else
    {
        decryptMode = true;
        keyArg = argv[2];
        inputFile = argv[3];
        outputFile = argv[4];
    }

    if (keyArg.substr(0, 2) != "-k")
    {
        cout << "Keyword must start with -k\n";
        return 1;
    }

    string keyword = keyArg.substr(2);

    string cleanedKey = removeDuplicates(keyword);

    string cipher = buildCipherAlphabet(cleanedKey);

    transformFile(inputFile, outputFile, cipher, decryptMode);

    return 0;
}