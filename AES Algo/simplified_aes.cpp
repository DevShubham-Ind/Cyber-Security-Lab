#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <algorithm>
using namespace std;

string XORstring(string first, string second){
    string result = "";
    if(first.length() == second.length()){
        for(int i=0; i < first.length(); ++i) {
            if(first[i] == second[i]){
                result.push_back('0');
            }
            else{
                result.push_back('1');
            }
        }
    }
    else{
        cout << first << " & " << second << " differ in Len" << endl;
    }

    return result;
}

string SubNid(string bits, unordered_map<string, string> &sbox){
    string n0 = bits.substr(0, 4);
    string n1 = bits.substr(4, 4);

    string r1 = n0.substr(0, 2);
    string c1 = n0.substr(2, 2);
    string r2 = n1.substr(0, 2);
    string c2 = n1.substr(2, 2);

    string result = sbox[r1 + c1] + sbox[r2 + c2];
    return result;    
}

string RotNid(string str){
    string result = "";
    int half = str.length() /2;
    result = str.substr(half, half) + str.substr(0, half);
    return result;
}

vector<string> keyGen(string KEY, unordered_map<string, string> &sbox){
    string RCON1 = "10000000";
    string RCON2 = "00110000";

    // w0 = first half of key
    // w1 = second half of key
    string w0 = KEY.substr(0, 8);
    string w1 = KEY.substr(8, 8);

    // w2 = w0 XOR g(w1)
    // w2 = w0 XOR RCON1 XOR SubNid( RotNid( w1 ) )
    string w2 = XORstring(w0 , XORstring(RCON1, SubNid(RotNid(w1), sbox)));

    // w3 = w2 XOR w1
    string w3 = XORstring(w2, w1);

    // w4 = w2 XOR g(w3)
    // w4 = w2 XOR RCON1 XOR SubNid( RotNid( w3 ) )
    string w4 = XORstring(w2 , XORstring(RCON2, SubNid(RotNid(w3), sbox)));

    // w5 = w4 XOR w3
    string w5 = XORstring(w4, w3);

    vector<string> res = {w0, w1, w2, w3, w4, w5};

    return res;
}

string decToBinary(int num){
    string binary ="";

    while(num > 0){
        binary += to_string(num % 2);
        num = num /2;
    }

    while(binary.size() != 4) binary += '0';
    reverse(binary.begin(), binary.end());

    return binary;
}

int binaryToInt(string bits){
    int len = bits.size();
    int num =0;
    int pow = 1;
    reverse(bits.begin(), bits.end());
    
    for(int i= 0; i < len; i++){
        if(bits[i] == '1') num += (bits[i] - '0') * pow;
        pow = pow * 2;
    }
    return num;
}

int getRow(int n){
    if(n == 2) return 0;
    else if(n == 4) return 1;
    else return 2;
}

string encrypt(string text, vector<string> &keys, unordered_map<string, string> sbox, 
                vector<vector<string>> &gf_matrix){
    // text - XOR - key 0
    string res = XORstring(text, keys[0]);
    cout << "first XOR    : " << res << endl;

    // substitute niddle using SBOX
    string substituted = "";
    for(int i=0; i <13; i +=4){
        // substituted.push_back(sbox[res.substr(i, 4)]);
        substituted += sbox[res.substr(i, 4)];
    }
    cout << "substituted  : " << substituted << endl;

    // shift/ swap 2nd & 4th niddle
    string shiftNiddles = substituted;
    for(int i=4; i<8; i++){
        char ch = shiftNiddles[i];
        shiftNiddles[i] = shiftNiddles[i+8];
        shiftNiddles[i+8] = ch;
    }
    cout << "shift Niddle : " << shiftNiddles << endl;

    string s00 = shiftNiddles.substr(0, 4);
    string s10 = shiftNiddles.substr(4, 4);
    string s01 = shiftNiddles.substr(8, 4);
    string s11 = shiftNiddles.substr(12, 4);
    
    // Column Multiplication
    string sd00 = XORstring(s00 , gf_matrix[getRow(4)][binaryToInt(s10) -1]);
    string sd10 = XORstring(gf_matrix[getRow(4)][binaryToInt(s00) -1] , s10);
    string sd01 = XORstring(s01 , gf_matrix[getRow(4)][binaryToInt(s11) -1]);
    string sd11 = XORstring(gf_matrix[getRow(4)][binaryToInt(s01) -1] , s11);
    
    // cout << "sd00 : " << sd00 << endl;
    // cout << "sd10 : " << sd10 << endl;
    // cout << "sd01 : " << sd01 << endl;
    // cout << "sd11 : " << sd11 << endl;

    string round1_res = sd00 + sd10 + sd01 + sd11;
    cout << "Col mul      : " << round1_res << endl;
    // round1_res - XOR - key1
    round1_res = XORstring(round1_res, keys[1]);
    cout << "Round1_res   : " << round1_res << endl;

    cout << "---------------------------" << endl;
    // ------------ Round 2 ---------------
    
    string new_ip = round1_res;
    // substitute niddle using SBOX
    substituted = "";
    for(int i=0; i <13; i +=4){
        substituted += sbox[new_ip.substr(i, 4)];
    }
    cout << "substituted  : " << substituted << endl;
    
    // shift/ swap 2nd & 4th niddle
    shiftNiddles = substituted;
    for(int i=4; i<8; i++){
        char ch = shiftNiddles[i];
        shiftNiddles[i] = shiftNiddles[i+8];
        shiftNiddles[i+8] = ch;
    }
    cout << "shift Niddle : " << shiftNiddles << endl;
    
    // XOR with key 3
    string round2_res = XORstring(shiftNiddles, keys[2]);
    cout << "Round2 res   : " << round2_res << endl;
    cout << "---------------------------" << endl;

    return round2_res;
}

string decrypt(string encrypted, vector<string> &keys, unordered_map<string, string> sbox_inv, 
    vector<vector<string>> &gf_matrix) {
        // encrypted - XOR - key 3
        string res = XORstring(encrypted, keys[2]);
        cout << "res          : " << res << endl;

        // shift/ swap 2nd & 4th niddle
        string shiftNiddles = res;
        for(int i=4; i<8; i++){
            char ch = shiftNiddles[i];
            shiftNiddles[i] = shiftNiddles[i+8];
            shiftNiddles[i+8] = ch;
        }
        cout << "shift Niddle : " << shiftNiddles << endl;

        // reverse substitute niddle using SBOX Inv
        string substituted = "";
        for(int i=0; i <13; i +=4){
            substituted += sbox_inv[shiftNiddles.substr(i, 4)];
        }
        cout << "substituted  : " << substituted << endl;
        substituted = XORstring(substituted, keys[1]);
        cout << "sub XOR K1   : " << substituted << endl;

        string s00 = substituted.substr(0, 4);
        string s10 = substituted.substr(4, 4);
        string s01 = substituted.substr(8, 4);
        string s11 = substituted.substr(12, 4);
        
        // Inverse Column Multiplication
        string sd00 = XORstring(gf_matrix[getRow(9)][binaryToInt(s00) -1] , gf_matrix[getRow(2)][binaryToInt(s10) -1]);
        string sd10 = XORstring(gf_matrix[getRow(2)][binaryToInt(s00) -1] , gf_matrix[getRow(9)][binaryToInt(s10) -1]);
        string sd01 = XORstring(gf_matrix[getRow(9)][binaryToInt(s01) -1] , gf_matrix[getRow(2)][binaryToInt(s11) -1]);
        string sd11 = XORstring(gf_matrix[getRow(2)][binaryToInt(s01) -1] , gf_matrix[getRow(9)][binaryToInt(s11) -1]);

        string round1_res = sd00 + sd10 + sd01 + sd11;
        cout << "Col mul      : " << round1_res << endl;
        
        // Inverse Shift Row
        // shift/ swap 2nd & 4th niddle
        shiftNiddles = round1_res;
        for(int i=4; i<8; i++){
            char ch = shiftNiddles[i];
            shiftNiddles[i] = shiftNiddles[i+8];
            shiftNiddles[i+8] = ch;
        }
        cout << "shift Niddle : " << shiftNiddles << endl;

        // Inverse Nibble Substitution
        // reverse substitute niddle using SBOX Inv
        string inv_substituted = "";
        for(int i=0; i <13; i +=4){
            inv_substituted += sbox_inv[shiftNiddles.substr(i, 4)];
        }
        cout << "inv_substituted  : " << inv_substituted << endl;

        // inv_substituted - XOR - key 0
        string round2_res = XORstring(inv_substituted, keys[0]);
        cout << "Round2 res   : " << round2_res << endl;
        cout << "---------------------------" << endl;

        return round2_res;
}

int main(){
    cout << "Plain text        : ";
    string text ="";
    getline(cin, text);

    string KEY ="";
    cout << "Enter Key(16 bit) : ";
    getline(cin, KEY);
    cout << endl;

    unordered_map<string, string> sbox =
    {
        {"0000", "1001"}, {"1000", "0110"},
        {"0001", "0100"}, {"1001", "0010"},
        {"0010", "1010"}, {"1010", "0000"},
        {"0011", "1011"}, {"1011", "0011"},
        {"0100", "1101"}, {"1100", "1100"},
        {"0101", "0001"}, {"1101", "1110"},
        {"0110", "1000"}, {"1110", "1111"},
        {"0111", "0101"}, {"1111", "0111"}
    };

    unordered_map<string, string> sbox_inv =
    {
        {"1001", "0000"}, {"0110", "1000"},
        {"0100", "0001"}, {"0010", "1001"},
        {"1010", "0010"}, {"0000", "1010"},
        {"1011", "0011"}, {"0011", "1011"},
        {"1101", "0100"}, {"1100", "1100"},
        {"0001", "0101"}, {"1110", "1101"},
        {"1000", "0110"}, {"1111", "1110"},
        {"0101", "0111"}, {"0111", "1111"}
    };


    // vector<vector<string>> gf_matrix = {
    // { "0010", "0100", "0110", "1000", "1010", "1100", "1110", "0011", "0001", "0111", "0101", "1011", "1001", "1111", "1101" },
    // { "0100", "1000", "1100", "0011", "0111", "1011", "1111", "0110", "0010", "1110", "1010", "0101", "0001", "1101", "1001" },
    // { "1001", "0001", "1010", "0010", "1011", "0011", "1000", "0100", "1101", "0101", "1110", "0110", "1111", "0111", "1100" }
    // };

    vector<vector<string>> gf_matrix = {
    {"0010", "0100", "0110", "1000", "1010", "1100", "1110", "0011", "0001", "0111", "0101", "1011", "1001", "1111", "1101"}, 
    {"0100", "1000", "1100", "0011", "0111", "1011", "1111", "0110", "0010", "1110", "1010", "0101", "0001", "1101", "1001"}, 
    {"1001", "0001", "1000", "0010", "1011", "0011", "1010", "0100", "1101", "0101", "1100", "0110", "1111", "0111", "1110"}
    };

    vector<string> ws = keyGen(KEY, sbox);    

    for(int i=0; i<ws.size(); i++){
        cout << "W" << i << " : " << ws[i] << endl;
    }

    printf("\n==================================\n");

    vector<string> keys = {ws[0]+ws[1], ws[2]+ws[3], ws[4]+ws[5]};

    string encrypted = encrypt(text, keys, sbox, gf_matrix);
    cout << "Encrypted    : " << encrypted << endl;

    printf("\n==================================\n");
    
    string decrypted = decrypt(encrypted, keys, sbox_inv, gf_matrix);
    cout << "Decrypted    : " << decrypted << endl;
    
    printf("\n==================================\n");
    
    return 0;
}