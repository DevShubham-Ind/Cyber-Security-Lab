#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <algorithm>
using namespace std;

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

int main(){
    string bin = "1101";
    cout << "binary : 1101 | int : " << binaryToInt(bin);
    return 0;
}