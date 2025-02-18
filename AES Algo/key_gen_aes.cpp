#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
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

int main(){
    string KEY ="";
    cout << "Enter Key(16 bit) : ";
    getline(cin, KEY);

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

    cout << "W0 : " << w0 << endl;
    cout << "W1 : " << w1 << endl;
    cout << "W2 : " << w2 << endl; 
    cout << "W3 : " << w3 << endl; 
    cout << "W4 : " << w4 << endl; 
    cout << "W5 : " << w5 << endl;

    return 0;
}