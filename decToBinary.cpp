#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
using namespace std;

void decToBinary(int num){
    string binary ="";
    int i=0;

    cout << "Bits: ";
    while(num > 0){
        cout << num % 2 << endl;
        binary += to_string(num % 2);
        num = num /2;
    }

    cout << "Binary : " << binary << endl;
    while(binary.size() != 4) binary += '0';
    reverse(binary.begin(), binary.end());
    cout << "Binary : " << binary << endl;
}

int binaryToInt(string bits){
    int len = bits.size();
    int num =0;
    reverse(bits.begin(), bits.end());
    
    cout << "reading bits: " << bits << endl;
    for(int i= 0; i < len; i++){
        cout << pow(2, i) << endl;
        if(bits[i] == '1') num += pow(2, i);
    }
    return num;
}

int main(){
    // decToBinary(4);
    cout << "binary: " << binaryToInt("0100") << endl;
    return 0;
}