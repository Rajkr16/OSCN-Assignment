#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Function to calculate required number of redundant bits
int calculateRedundantBits(int m) {
    int r = 0;
    while (pow(2, r) < (m + r + 1)) {
        r++;
    }
    return r;
}

// Function to generate Hamming Code
vector<int> generateHammingCode(vector<int> data) {
    int m = data.size();
    int r = calculateRedundantBits(m);

    int total = m + r;
    vector<int> hamming(total + 1); // 1-based indexing

    // Insert data bits into non-power-of-2 positions
    int j = 0;
    for (int i = 1; i <= total; i++) {
        if ((i & (i - 1)) == 0) {
            hamming[i] = 0;  // placeholder for parity bit
        } else {
            hamming[i] = data[j++];
        }
    }

    // Calculate parity using even parity
    for (int i = 0; i < r; i++) {
        int pos = pow(2, i);
        int parity = 0;
        for (int k = pos; k <= total; k++) {
            if (k & pos)
                parity ^= hamming[k];
        }
        hamming[pos] = parity;
    }

    return hamming;
}

// Receiver side: detect and correct error
void detectError(vector<int>& hamming) {
    int total = hamming.size() - 1;
    int r = 0;

    while (pow(2, r) <= total) r++;

    int errorPos = 0;

    for (int i = 0; i < r; i++) {
        int pos = pow(2, i);
        int parity = 0;
        for (int k = pos; k <= total; k++) {
            if (k & pos)
                parity ^= hamming[k];
        }
        if (parity != 0)
            errorPos += pos;
    }

    if (errorPos == 0) {
        cout << "\nNo error detected. Correct data packet received.\n";
    } else {
        cout << "\nError detected at bit position: " << errorPos << endl;
        cout << "Correcting the bit...\n";
        hamming[errorPos] ^= 1;
        cout << "Corrected data: ";
        for (int i = 1; i <= total; i++) cout << hamming[i] << " ";
        cout << endl;
    }
}

int main() {
    string input;
    cout << "Enter binary data: ";
    cin >> input;

    vector<int> data;
    for (char c : input)
        data.push_back(c - '0');

    // Generate Hamming code
    vector<int> hamming = generateHammingCode(data);

    cout << "\nThe data packet to be sent is: ";
    for (int i = 1; i < hamming.size(); i++)
        cout << hamming[i] << " ";

    // Simulate receiving (optionally introduce error)
    vector<int> received = hamming;

    char ch;
    cout << "\n\nDo you want to introduce an error? (y/n): ";
    cin >> ch;

    if (ch == 'y') {
        int pos;
        cout << "Enter bit position to flip (1 to " << received.size() - 1 << "): ";
        cin >> pos;
        received[pos] ^= 1;
    }

    cout << "\nReceived data: ";
    for (int i = 1; i < received.size(); i++)
        cout << received[i] << " ";

    cout << endl;

    // Detect and fix error
    detectError(received);

    return 0;
}
