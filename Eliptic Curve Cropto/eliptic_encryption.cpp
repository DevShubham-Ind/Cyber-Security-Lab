#include <iostream>
#include <string>
#include <vector>
using namespace std;

int getMod(int a, int b){
    if(a == 0) return 0;
    else if(a > 0){
        return a % b;
    }
    else{
        return b - (abs(a) % b);
    }
}

int getModInv(int temp2, int z){
    int inv = 1;
    while((temp2 * inv) % z != 1){
        inv++;
    }
    return inv;
}

pair<int, int> getDoubledPoint(int x, int y, int z) {
    // find lambda
    int lambda = 0;
    int a =1;
    int temp1 = (3 * (x * x) + a);
    int temp2 = (2 * y);
    cout << "temp1: " << temp1 << endl;
    cout << "temp2: " << temp2 << endl;
    if(temp1 % temp2 == 0){
        cout << "Divisible" << endl;
        lambda = getMod((temp1 / temp2), z);
    }
    else{
        cout << "Not Divisible" << endl;
        int modInv = getModInv(temp2, z);
        cout << "Mod Inv: " << modInv << endl;
        lambda = getMod((temp1 * modInv), z);
    }

    cout << "Lambda: " << lambda << endl << endl;

    int x3 = getMod(((lambda * lambda) - x - x), z);
    int y3 = getMod((lambda * (x - x3) - y), z);

    return {x3, y3};
}

pair<int, int> add_Two_Points_On_Curve(int x1, int y1, int x2, int y2, int z){
    // find lambda
    int lambda = 0;
    int temp = (y2 - y1) / (x2 - x1);
    if(temp > 0){
        cout << "temp is +ve : " << temp << endl;
        lambda = getMod(temp, z);
    }
    else if(temp < 0){
        cout << "temp is -ve : " << temp << endl;
        temp *= -1;
        lambda = getMod(temp, z);
    }
    else{
        cout << "temp is 0 : " << temp << endl;
    }

    cout << "Lambda : " << lambda << endl;

    int x3 = getMod((lambda * lambda) - x1 - x2, z);
    int y3 = getMod(lambda * (x1 - x3) - y1, z);

    return {x3, y3};
}

int main() {
    int m1, m2, g1, g2, a, b;
    cout << "Enter Plain Text (x, y): ";
    cin >> m1;
    cin >> m2;

    cout << "Enter G(x, y): ";
    cin >> g1;
    cin >> g2;

    cout << "Enter (a, b): ";
    cin >> a;
    cin >> b;

    // select private key between 1 to p-1
    int p =11;
    
    // find public key
    pair<int, int> public = getDoubledPoint(g1, g2, 11);

    
}