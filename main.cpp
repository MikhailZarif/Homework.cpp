#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

string encrypt(int xor_code) {
    string cypher{};
    unsigned char letter1, letter2;
    if (xor_code < (pow(2.0, 14))) {
        xor_code = xor_code << 2;
        letter1 = xor_code & 255;
        letter2 = (xor_code - (xor_code & 255)) >> 8;
        xor_code = 0;
    }
    if ((xor_code >= (pow(2.0, 14))) && (xor_code < (pow(2.0, 15)))) {
        xor_code -= (pow(2.0, 14));
        xor_code = (xor_code << 2) + 1;
        letter1 = xor_code & 255;
        letter2 = (xor_code - (xor_code & 255)) >> 8;
        xor_code = 0;
    }
    if ((xor_code >= (pow(2.0, 15))) && (xor_code < ((pow(2.0, 15)) + (pow(2.0, 14))))) {
        xor_code -= (pow(2.0, 15));
        xor_code = (xor_code << 2) + 2;
        letter1 = xor_code & 255;
        letter2 = (xor_code - (xor_code & 255)) >> 8;
        xor_code = 0;
    }
    if (xor_code >= ((pow(2.0, 15)) + (pow(2.0, 14)))) {
        xor_code -= ((pow(2.0, 15)) + (pow(2.0, 14)));
        xor_code = (xor_code << 2) + 3;
        letter1 = xor_code & 255;
        letter2 = (xor_code - (xor_code & 255)) >> 8;
        xor_code = 0;
    }
    cypher += letter2;
    cypher += letter1;
    return cypher;
}

int decrypt(int code) {
    int result = 0;
    if (code % 4 == 0) {
        result = code >> 2;
    }
    if (code % 4 == 1) {
        result = (code >> 2) + pow(2.0, 14);
    }
    if (code % 4 == 2) {
        result = (code >> 2) + pow(2.0, 15);
    }
    if (code % 4 == 3) {
        result = (code >> 2) + pow(2.0, 14) + pow(2.0, 15);
    }
    return result;
}

int main() {
    string mode, name, cypher, message, symbols;
    int block1, block2, block, key, gamma, code1, code2, code;
    unsigned char letter1, letter2;
    cout << "Welcome to Basic String Encoder!" << endl;
    cout << "For Encryption you need an empty file, a key and Your english message." << endl;
    cout << "For Decryption you need an encrypted file and the right key." << endl;
    cout << "Enjoy!" << endl;
    cout << "Enter mode: Encrypt or Decrypt" << endl;
    cin >> mode;
    if ((mode != "Encrypt") && (mode != "Decrypt")) {
        cout << "Error, wrong mode, mind Your typing." << endl;
    }
    if ((mode == "Encrypt") || (mode == "Decrypt")) {
        cout << "Enter file name" << endl;
        cin >> name;
    }
    if (mode == "Encrypt") {
        unsigned int n, i;
        cout << "Enter message" << endl;
        cin.ignore(32767, '\n');
        getline(cin, message);
        n = message.length();
        int flag = n % 2;
        cout << "Enter key" << endl;
        cin >> key;
        srand(key);
        for (i = 0; i < (n - 1); i += 2) {
            block1 = message[i];
            block2 = message[i + 1];
            block1 = block1 << 8;
            block = block1 | block2;
            gamma = (rand());
            code = block ^ gamma;
            cypher += encrypt(code);
        }
        if (flag == 1) {
            block1 = *(message.end() - 1);
            block = block1 << 8;
            gamma = rand();
            code = block ^ gamma;
            cypher += encrypt(code);
        }
        fstream out;
        out.open(name);
        out << cypher;
        cout << "Task completed successfully, thank you for using our program!" << endl;
    }
    if (mode == "Decrypt") {
        int n, i;
        fstream in;
        in.open(name);
        in >> message;
        cout << "Enter key" << endl;
        cin >> key;
        srand(key);
        n = message.length();
        for (i = 0; i < (n - 1); i += 2) {
            letter1 = message[i];
            letter2 = message[i + 1];
            code1 = letter1;
            code2 = letter2;
            code1 = code1 << 8;
            code = code1 | code2;
            gamma = (rand());
            block = (decrypt(code)) ^ gamma;
            int copy = block;
            block1 = block & 255;
            block2 = (copy - block1) >> 8;
            letter1 = block1;
            letter2 = block2;
            cypher += letter2;
            cypher += letter1;
        }
        if (*(cypher.end() - 1) == 0) {
            cypher.pop_back();
        }
        cout << cypher << endl;
        cout << "Task completed successfully, thank you for using our program!" << endl;
    }
    return 0;
}