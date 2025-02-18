#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

string leftShift(string str, int start, int end, int shiftBy){
    for(int i=0; i <shiftBy; ++i) {
        char first = str[start];
        for(int j=start; j <end; ++j) {
            str[j] = str[j+1];
        }
        str[end] = first;
    }

    return str.substr(start, end - start +1);
}

pair<string, string> generateKey(string key){
    vector<int> p10 = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    vector<int> p8 = {6, 3, 7, 4, 8, 5, 10, 9};

    string k = "";
    for(int i=0; i<10; ++i) {
        k.push_back(key[p10[i] -1]);
    }

    cout << "K    : " << k << endl << endl;
    // cout << "---------" << endl;

    string firstHalf = leftShift(k, 0, 4, 1);
    string secondHalf = leftShift(k, 5, 9, 1);
    string l1 = firstHalf + secondHalf;
    cout << "L1   : " << l1 << endl;


    string key1 ="";
    for(int i=0; i<8; ++i) {
        key1.push_back(l1[p8[i] -1]);
    }
    cout << "key1 : " << key1 << endl << endl;
    // cout << "---------" << endl;

    firstHalf = leftShift(l1, 0, 4, 2);
    secondHalf = leftShift(l1, 5, 9, 2);
    string l2 = firstHalf + secondHalf;
    cout << "L2   : " << l2 << endl;

    string key2 ="";
    for(int i=0; i<8; ++i) {
        key2.push_back(l2[p8[i] -1]);
    }
    cout << "key2 : " << key2 << endl << endl;
    // cout << "---------" << endl;

    return make_pair(key1, key2);
}

string XORstring(string first, string second){
    string res ="";
    if(first.length() == second.length()){
        for(int i=0; i<first.length(); ++i) {
            if(first[i] == second[i]) res.push_back('0');
            else res.push_back('1');
        }
    }
    else{
        cout << first << " & " << second << " : differ in LEN" << endl;
    }

    return res;
}

int stringToInt(string bits){
    int ans =0;
    reverse(bits.begin(), bits.end());
    for(int i=0; i < bits.length(); ++i){
        if(bits[i] == '1'){
            ans += round(pow(2, i));
        }
    }
    return ans;
}

string round1(string text, pair<string, string> &keys){
    vector<int> IP = {2, 6, 3, 1, 4, 8, 5, 7};
    string ip ="";
    for(int i=0; i<8; ++i) {
        ip.push_back(text[IP[i] -1]);
    }
    cout << "ip : " << ip << endl;
    string left_ip = ip.substr(0, 4);
    string right_ip = ip.substr(4, 4);

    vector<int> EP = {4, 1, 2, 3, 2, 3, 4, 1};
    string ep ="";
    for(int i=0; i<8; ++i) {
        ep.push_back(right_ip[EP[i] -1]);
    }
    cout << "ep : " << ep << endl;

    // ep - XOR - key1
    string res = XORstring(ep, keys.first);
    cout << "res  : " << res << endl << endl;

    vector<vector<string>> S0 { {"01", "00", "11", "10"},
                                {"11", "10", "01", "00"},
                                {"00", "10", "01", "11"},
                                {"11", "01", "11", "10"} };
    vector<vector<string>> S1 { {"00", "01", "10", "11"},
                                {"10", "00", "01", "11"},
                                {"11", "00", "01", "00"},
                                {"10", "01", "00", "11"} };

    string s0 = res.substr(0, 4);
    string s1 = res.substr(4, 4);

    cout << "s0 : " << s0 << " | " << "s1 : " << s1 << endl;

    int a = stringToInt(string(1, s0[0]) + string(1, s0[3]));
    int b = stringToInt(string(1, s0[1]) + string(1, s0[2]));
    int c = stringToInt(string(1, s1[0]) + string(1, s1[3]));
    int d = stringToInt(string(1, s1[1]) + string(1, s1[2]));

    printf("S0[%d][%d] & S1[%d][%d]\n", a, b, c, d);
    printf("      %s & %s\n", S0[a][b].c_str(), S1[c][d].c_str());
    string before_p4 = S0[a][b] + S1[c][d];
    cout << "before_p4 : " << before_p4 << endl << endl;

    vector<int> P4 = {2, 4, 3, 1};
    string p4 = "";
    for(int i=0; i<4; ++i) {
        p4.push_back(before_p4[P4[i] -1]);
    }

    string after_XOR_with_ip_left = XORstring(p4, left_ip);
    cout << "p4_after_XOR_with_ip_left : " << after_XOR_with_ip_left << endl;

    string round1_result = after_XOR_with_ip_left + right_ip;

    return round1_result;
}

string round2(string newIP, pair<string, string> &keys){
    string left_ip = newIP.substr(0, 4);
    string right_ip = newIP.substr(4, 4);

    vector<int> EP = {4, 1, 2, 3, 2, 3, 4, 1};
    string ep ="";
    for(int i=0; i<8; ++i) {
        ep.push_back(right_ip[EP[i] -1]);
    }
    cout << "ep : " << ep << endl;

    // ep - XOR - key2
    string res = XORstring(ep, keys.second);
    cout << "res  : " << res << endl << endl;

    vector<vector<string>> S0 { {"01", "00", "11", "10"},
                                {"11", "10", "01", "00"},
                                {"00", "10", "01", "11"},
                                {"11", "01", "11", "10"} };
    vector<vector<string>> S1 { {"00", "01", "10", "11"},
                                {"10", "00", "01", "11"},
                                {"11", "00", "01", "00"},
                                {"10", "01", "00", "11"} };

    string s0 = res.substr(0, 4);
    string s1 = res.substr(4, 4);

    cout << "s0 : " << s0 << " | " << "s1 : " << s1 << endl;

    int a = stringToInt(string(1, s0[0]) + string(1, s0[3]));
    int b = stringToInt(string(1, s0[1]) + string(1, s0[2]));
    int c = stringToInt(string(1, s1[0]) + string(1, s1[3]));
    int d = stringToInt(string(1, s1[1]) + string(1, s1[2]));

    printf("S0[%d][%d] & S1[%d][%d]\n", a, b, c, d);
    printf("      %s & %s\n", S0[a][b].c_str(), S1[c][d].c_str());
    string before_p4 = S0[a][b] + S1[c][d];
    cout << "before_p4 : " << before_p4 << endl << endl;

    vector<int> P4 = {2, 4, 3, 1};
    string p4 = "";
    for(int i=0; i<4; ++i) {
        p4.push_back(before_p4[P4[i] -1]);
    }

    string after_XOR_with_ip_left = XORstring(p4, left_ip);
    cout << "p4_after_XOR_with_ip_left : " << after_XOR_with_ip_left << endl;

    string res__rightIP = after_XOR_with_ip_left + right_ip;
    cout << "res__right_IP : " << res__rightIP << endl;

    vector<int> IP_inverse = {4, 1, 3, 5, 7, 2, 8, 6};
    string round2_result ="";
    for(int i=0; i<8; ++i){
        round2_result += res__rightIP[IP_inverse[i] -1];
    }

    return round2_result;
}

int main() {
    cout << "Plain text : ";
    string text ="";
    getline(cin, text);

    cout << "Enter key (10 bit) : ";
    string key ="";
    getline(cin, key);

    cout << "-------Generate Keys---------" << endl;
    pair<string, string> keys = generateKey(key);
    cout << "Key1 : " << keys.first << endl;
    cout << "Key2 : " << keys.second << endl << endl;

    cout << "-------Round 1---------" << endl;
    string r1 = round1(text, keys);
    cout << "R1   : " << r1 << endl << endl;

    cout << "-------Round 2---------" << endl;
    string newIP = r1.substr(4, 4) + r1.substr(0, 4);
    string r2 = round2(newIP, keys);
    cout << "R2   : " << r2 << endl;

    return 0;
}