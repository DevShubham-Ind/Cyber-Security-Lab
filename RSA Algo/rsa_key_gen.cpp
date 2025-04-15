#include <iostream>
#include <string>
#include <vector>
using namespace std;

int getGCD(int a, int b){

    int ch = a;
    a = b;
    b011
    while(b != 0){
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int p, q;
    cout << "Enter p: ";
    cin >> p;
    cout << "Enter q: ";
    cin >> q;

    int n = p * q;
    int m = (p -1) * (q -1);
    int e =0;

    cout << "n: " << n << endl;
    cout << "m: " << m << endl;

    for(int i=2; i<m; i++){
        // if(getGCD(i, m) == 1){
        if(isPrime(i)){
            e = i;
            break;
        }
    }

    cout << "e: " << e << endl;
    cout << "Public Key: (" << e << ", " << n << ")" << endl;

    return 0;
}