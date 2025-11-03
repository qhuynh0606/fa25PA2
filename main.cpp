
//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};
    buildFrequencyTable(freq, "input.txt");
    int nextFree = createLeafNodes(freq);
    int root = buildEncodingTree(nextFree);
    string codes[26];
    generateCodes(root, codes);
    encodeMessage("input.txt", codes);
    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
// 1. Create a MinHeap object.
// 2. Pushes all leaf node indices into the heap.
// 3. While the heap size is greater than 1:
//      - Pop two smallest nodes
//      - Create a new parent node with combined weight
//      - Set left/right pointers
//      - Push new parent index back into the heap
// 4. Return the index of the last remaining node (root)

int buildEncodingTree(int nextFree) {

    MinHeap h;

    for (int i = 0; i < nextFree; ++i) {
        h.push(i, weightArr);
    }
    // next free slot for new parent nodes
    int nextIndex = nextFree;
    while (h.size > 1) {
        int pop1 = h.pop(weightArr); // popped smallest
        int pop2 = h.pop(weightArr); // popped second smallest

        charArr[nextIndex] = '\0';  // internal node
        weightArr[nextIndex] = weightArr[pop1] + weightArr[pop2];

        leftArr[nextIndex] = pop1;
        rightArr[nextIndex] = pop2;

        h.push(nextIndex, weightArr);
        nextIndex++;
    }
    int root = (h.size == 1) ? h.pop(weightArr) : -1;
    return root;
}

// Step 4: Use an STL stack to generate codes
// Uses stack<pair<int, string>> to simulate DFS traversal.
// Left edge adds '0', right edge adds '1'.
// Record code when a leaf node is reached.
void generateCodes(int root, string codes[]) {
    // empty codes
    for (int i = 0; i < 26; ++i) {
        codes[i] = "";
    }

    if (root < 0) {
        return;
    }

    stack<pair<int, string>> stk;
    stk.push(make_pair(root, "")); // start root with empty code

    while (!stk.empty()) {
        pair<int, string> curr = stk.top();
        stk.pop();

        int node = curr.first;
        string code = curr.second;

        // check if leaf
        if (leftArr[node] != -1 && rightArr[node] != -1) {
            char ch = charArr[node];
            if (ch >= 'A' && ch <= 'Z') {
                codes[ch - 'a'] = code;
            }
        } else {
            // go right -> left
            if (rightArr[node] != -1) {
                stk.push(make_pair(rightArr[node], code + '1'));
            }
            if (leftArr[node] != -1) {
                stk.push(make_pair(leftArr[node], code + '2'));
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}