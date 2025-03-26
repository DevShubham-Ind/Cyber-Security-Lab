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
        a *= -1;
        return b - (a % b);
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

int main() {
    int x1, y1;
    cout << "Enter x1: ";
    cin >> x1;
    cout << "Enter y1: ";
    cin >> y1;

    int z;
    cout << "Enter z: ";
    cin >> z;

    printf("Points: P(%d, %d)\n\n", x1, y1);

    pair<int, int> result = getDoubledPoint(x1, y1, z);
    printf("Result: (%d, %d)", result.first, result.second);

    return 0;
}