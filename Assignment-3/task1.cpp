// A bit stream 1101011011 is transmitted using the standard CRC method. The generator polynomial is x4+x+1. What is the actual bit string transmitted?

#include <iostream>
#include <string>
using namespace std;

// Function to perform XOR between two binary strings
string xor1(string a, string b) {
    string result = "";
    for (int i = 1; i < b.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

// Function to perform Mod-2 division
string mod2div(string dividend, string divisor) {
    int pick = divisor.length();
    string tmp = dividend.substr(0, pick);

    int n = dividend.length();

    while (pick < n) {
        if (tmp[0] == '1')
            tmp = xor1(divisor, tmp) + dividend[pick];
        else
            tmp = xor1(string(pick, '0'), tmp) + dividend[pick];
        pick++;
    }

    // For last n bits
    if (tmp[0] == '1')
        tmp = xor1(divisor, tmp);
    else
        tmp = xor1(string(pick, '0'), tmp);

    return tmp;
}

int main() {
    string data = "1101011011";
    string divisor = "10011";  // x^4 + x + 1

    int m = divisor.length();
    string appended_data = data + string(m - 1, '0');

    string remainder = mod2div(appended_data, divisor);
    string codeword = data + remainder;

    cout << "Original Data:      " << data << endl;
    cout << "Generator:          " << divisor << endl;
    cout << "Appended Data:      " << appended_data << endl;
    cout << "CRC Remainder:      " << remainder << endl;
    cout << "Transmitted Code:   " << codeword << endl;

    return 0;
}
