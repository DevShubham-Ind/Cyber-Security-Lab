#include <iostream>
#include <string>
#include <vector>
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

    cout << "K    : " << k << endl;
    cout << "---------" << endl;

    string firstHalf = leftShift(k, 0, 4, 1);
    string secondHalf = leftShift(k, 5, 9, 1);
    string l1 = firstHalf + secondHalf;
    cout << "L1   : " << l1 << endl;


    string key1 ="";
    for(int i=0; i<8; ++i) {
        key1.push_back(l1[p8[i] -1]);
    }
    cout << "key1 : " << key1 << endl;
    cout << "---------" << endl;

    firstHalf = leftShift(l1, 0, 4, 2);
    secondHalf = leftShift(l1, 5, 9, 2);
    string l2 = firstHalf + secondHalf;
    cout << "L2   : " << l2 << endl;

    string key2 ="";
    for(int i=0; i<8; ++i) {
        key2.push_back(l2[p8[i] -1]);
    }
    cout << "key2 : " << key2 << endl;
    cout << "---------" << endl;

    return make_pair(key1, key2);
}

int main(){
    string key;
    cout << "Enter Key (10 bits)" << endl;
    cout << "Key  : ";
    getline(cin, key);

    pair<string, string> keys = generateKey(key);

    cout << "Key 1: " << keys.first << endl;
    cout << "Key 2: " << keys.second << endl;

    return 0;
}