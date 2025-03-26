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
    int x1, y1, x2, y2;
    cout << "Enter x1: ";
    cin >> x1;
    cout << "Enter y1: ";
    cin >> y1;
    cout << "Enter x2: ";
    cin >> x2;
    cout << "Enter y2: ";
    cin >> y2;

    int z;
    cout << "Enter z: ";
    cin >> z;

    printf("Points: P(%d, %d), Q(%d, %d)", x1, y1, x2, y2);

    pair<int, int> result = add_Two_Points_On_Curve(x1, y1, x2, y2, z);
    printf("Result: (%d, %d)", result.first, result.second);

    return 0;
}