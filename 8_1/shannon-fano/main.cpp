#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <bitset>

using namespace std;

struct Symbol {
    char character;
    double probability;
    string code;

    Symbol(char ch, double prob, const string& c) : character(ch), probability(prob), code(c) {}
};

bool compareByProbability(const Symbol& a, const Symbol& b) {
    return a.probability > b.probability;
}

void shannonFanoCode(vector<Symbol>& symbols, int start, int end) {
    if (start >= end) return;

    int splitIndex = start;
    double totalProbLeft = 0, totalProbRight = 0;

    for (int i = start; i <= end; i++) {
        totalProbRight += symbols[i].probability;
    }

    double diff = totalProbRight;
    for (int i = start; i <= end; i++) {
        totalProbLeft += symbols[i].probability;
        totalProbRight -= symbols[i].probability;

        if (abs(totalProbLeft - totalProbRight) < diff) {
            diff = abs(totalProbLeft - totalProbRight);
            splitIndex = i;
        }
    }
    
    for (int i = start; i <= splitIndex; i++) {
        symbols[i].code += "0";
    }
    for (int i = splitIndex + 1; i <= end; i++) {
        symbols[i].code += "1";
    }

    shannonFanoCode(symbols, start, splitIndex);
    shannonFanoCode(symbols, splitIndex + 1, end);
}

string encodeText(string& text, map<char, string>& encodingMap) {
    string encodedText;
    for (char ch : text) {
        encodedText += encodingMap.at(ch);
    }
    return encodedText;
}

string decodeText(const string& encodedText, map<string, char>& decodingMap) {
    string decodedText;
    string temp;
    for (char bit : encodedText) {
        temp += bit;
        if (decodingMap.find(temp) != decodingMap.end()) {
            decodedText += decodingMap.at(temp);
            temp.clear();
        }
    }
    return decodedText;
}


int main() {
    string inputText;
    ifstream inputFile("input.txt");

    if (inputFile.is_open()) {
        getline(inputFile, inputText, '\0');
        inputFile.close();
    } else {
        cout << "Error openning file." << endl;
        return 1;
    }

    map<char, int> frequencyMap;
    for (char ch : inputText) {
        frequencyMap[ch]++;
    }

    vector<Symbol> symbols;
    for (const auto& pair : frequencyMap) {
        symbols.emplace_back(pair.first, static_cast<double>(pair.second) / inputText.size(), "");
    }

    sort(symbols.begin(), symbols.end(), compareByProbability);

    shannonFanoCode(symbols, 0, symbols.size() - 1);

    map<char, string> encodingMap;
    map<string, char> decodingMap;
    for (const auto& symbol : symbols) {
        encodingMap[symbol.character] = symbol.code;
        decodingMap[symbol.code] = symbol.character;
    }

    string encodedText = encodeText(inputText, encodingMap);

    string decodedText = decodeText(encodedText, decodingMap);

    ofstream encodedFile("encoded.txt");
    encodedFile << encodedText;
    encodedFile.close();

    ofstream decodedFile("decoded.txt");
    decodedFile << decodedText;
    decodedFile.close();


    return 0;
}