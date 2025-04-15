#include <iostream>
using namespace std;

int getModInv(int temp2, int z){
    int inv = 1;
    while((temp2 * inv) % z != 1){
        inv++;
        cout << inv << " ";
    }
    cout << endl;
    return inv;
}

int main(){
    int a;
    cin >> a;
    int b;
    cin >> b;
    cout << "mod inv : " << getModInv(a, b) << endl;
    cout << "manual: " << (550 * 550) % 1769 << endl;
    return 0;
}