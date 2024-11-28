#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <fstream>
#include <locale>
#include <cmath>

using namespace std;

struct Node {
    wchar_t character;
    int frequency;
    Node *left, *right;

    Node(wchar_t character, int frequency) {
        left = right = nullptr;
        this->character = character;
        this->frequency = frequency;
    }
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

void generateHuffmanCodes(Node* root, wstring code, map<wchar_t, wstring>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->character] = code;
    }

    generateHuffmanCodes(root->left, code + L"0", huffmanCodes);
    generateHuffmanCodes(root->right, code + L"1", huffmanCodes);
}

map<wchar_t, wstring> buildHuffmanTree(const wstring& text) {

    map<wchar_t, int> frequencyMap;
    for (wchar_t ch : text) {
        frequencyMap[ch]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (auto pair : frequencyMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() != 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        int sum = left->frequency + right->frequency;
        Node* newNode = new Node(L'\0', sum);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }

    map<wchar_t, wstring> huffmanCodes;
    generateHuffmanCodes(minHeap.top(), L"", huffmanCodes);

    return huffmanCodes;
}

wstring encodeText(const wstring& text, map<wchar_t, wstring>& huffmanCodes) {
    wstring encodedText = L"";
    for (wchar_t ch : text) {
        encodedText += huffmanCodes[ch];
    }
    return encodedText;
}

wstring decodeText(const wstring& encodedText, map<wstring, wchar_t>& reverseHuffmanCodes) {
    wstring decodedText = L"";
    wstring codeBuffer = L"";
    for (wchar_t bit : encodedText) {
        codeBuffer += bit;
        if (reverseHuffmanCodes.find(codeBuffer) != reverseHuffmanCodes.end()) {
            decodedText += reverseHuffmanCodes[codeBuffer];
            codeBuffer.clear();
        }
    }
    return decodedText;
}

double calculateAverageCodeLength(const map<wchar_t, wstring>& huffmanCodes, const map<wchar_t, int>& frequencyMap, int totalSymbols) {
    double sumCodeLengths = 0.0;

    for (const auto& pair : huffmanCodes) {
        wchar_t symbol = pair.first;
        int codeLength = pair.second.length();
        int frequency = frequencyMap.at(symbol);

        sumCodeLengths += codeLength * frequency;
    }

    return sumCodeLengths / totalSymbols;
}

double calculateVariance(const map<wchar_t, wstring>& huffmanCodes, const map<wchar_t, int>& frequencyMap, int totalSymbols, double averageLength) {
    double squaredDifferenceSum = 0.0;

    for (const auto& pair : huffmanCodes) {
        wchar_t symbol = pair.first;
        int codeLength = pair.second.length();
        int frequency = frequencyMap.at(symbol);

        double difference = codeLength - averageLength;
        squaredDifferenceSum += frequency * pow(difference, 2);
    }

    return squaredDifferenceSum / totalSymbols;
}


int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    wstring inputText;

    wifstream inputFile(L"input.txt");
    if (!inputFile.is_open()) {
        wcerr << L"Error openning file." << endl;
        return 1;
    }
    
    wstring line;
    getline(inputFile, inputText, L'\0');
    inputFile.close();

    map<wchar_t, wstring> huffmanCodes = buildHuffmanTree(inputText);

    // wcout << L"Huffman codes for each symbol:\n";
    // for (auto pair : huffmanCodes) {
    //     wstring characterRepresentation;

    //     if (pair.first == L'\n') {
    //         characterRepresentation = L"\\n"; 
    //     } else {
    //         characterRepresentation = wstring(1, pair.first);  
    //     }

    //     // Выводим символ и его код
    //     wcout << L"\'" << characterRepresentation << L"\': " << pair.second << endl;
    // }

    wstring encodedText = encodeText(inputText, huffmanCodes);

    wofstream encodedFile("encoded.txt");
    encodedFile << encodedText;
    encodedFile.close();


    map<wstring, wchar_t> reverseHuffmanCodes;
    for (const auto& pair: huffmanCodes) {
        reverseHuffmanCodes[pair.second] = pair.first;
    }

    wstring decodedText = decodeText(encodedText, reverseHuffmanCodes);

    wofstream decodedFile("decoded.txt");
    decodedFile << decodedText;
    decodedFile.close();


    map<wchar_t, int> frequencyMap;
    for (wchar_t ch : inputText) {
        frequencyMap[ch]++;
    }

    int totalSymbols = inputText.length();

    double averageCodeLength = calculateAverageCodeLength(huffmanCodes, frequencyMap, totalSymbols);
    cout << "Average code length: " << averageCodeLength << endl;

    double variance = calculateVariance(huffmanCodes, frequencyMap, totalSymbols, averageCodeLength);
    cout << "Variance: " << variance << endl;

    size_t originalSize = inputText.length() * 8;
    size_t compressedSize = encodedText.length();
    cout << "Original size: " << originalSize << " bytes" << endl;
    cout << "Compressed size: " << compressedSize << " bytes" << endl;
    cout << "Compression ratio: " << static_cast<double>(originalSize) / compressedSize << endl;

    wcout << L"Frequency of each character:\n";
    for (const auto& pair : frequencyMap) {
    wstring characterRepresentation;

    if (pair.first == L'\n') {
        characterRepresentation = L"\\n"; // Обозначение для символа новой строки
    } else {
        characterRepresentation = wstring(1, pair.first); // Символ
    }

    wcout << L"\'" << characterRepresentation << L"\': " << pair.second << endl;
}
}