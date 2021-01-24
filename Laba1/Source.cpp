#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <clocale>
#include <vector>


using namespace std;

const int keySize = 10;
const int keyPosition[keySize] = { 2, 5, 4, 1, 3, 0, 6, 8, 7, 9 };
const int keySource[keySize] = { 5, 3, 0, 4, 2, 1, 6, 8, 7, 9 };

void init() {
    setlocale(LC_ALL, "ru");
}


vector<char> readText(const string& filename) {

    ifstream fin(filename, ios::binary);
    vector<char> text((istreambuf_iterator<char>(fin)),
        istreambuf_iterator<char>());
    fin.close();

    return text;
}

void writeText(const string& filename, const vector<char>& text) {
    ofstream fout("inputShifr.txt", ios::binary);
    for (int i = 0; i < text.size(); i++)
        fout << text[i];
    fout.close();
}


void encodeBlock(const  vector<char>& source, vector<char>& destination, int start) {
    for (int i = 0; i < keySize; i++) {
        destination[start + keyPosition[i]] = source[start + i];
    }
}

vector<char> encodeString(const vector<char>& source) {
    vector<char> encoded = source;
    for (int i = 0; i + keySize < source.size(); i += keySize) {
        encodeBlock(source, encoded, i);
    }
    return encoded;
}

void decodeBlock(const vector<char>& source, vector<char>& destination, int start) {
    for (int i = 0; i < keySize; i++) {
        destination[start + keySource[i]] = source[start + i];
    }
}

vector<char> decodeString(const vector<char>& source) {
    vector<char> decoded = source;
    for (int i = 0; i + keySize < source.size(); i += keySize) {
        decodeBlock(source, decoded, i);
    }
    ofstream fout("output.txt", ios::binary);
    for (int i = 0; i < decoded.size(); i++)
        fout << decoded[i];
    fout.close();
    return decoded;
}


int main() {
    init();

    vector<char> text = readText("vc142.pdb");
    //for (int i = 0; i < text.size(); i++){
    //        cout << text[i];
    //}

    vector<char> encrypted = encodeString(text);
    writeText("inputShifr.txt", encrypted);

    vector<char> encryptedText = readText("inputShifr.txt");
    //for (int i = 0; i < text.size(); i++) {
    //        cout << encryptedText[i];        
    //}

    vector<char> decodedText = decodeString(encryptedText);
    //for (int i = 0; i < text.size(); i++) {
    //        cout << decodedText[i]; 
    //}

    if (decodedText != text)
        cout << "Unsuccessful decoding\n";
    else
        cout << "Successful decoding\n";
    return 0;
}