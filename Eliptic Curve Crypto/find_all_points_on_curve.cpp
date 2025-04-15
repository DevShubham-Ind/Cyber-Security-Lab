#include <iostream>
#include <vector>
using namespace std;

int main(){
    int p, a, b, n;
    cout << "Enter p: ";
    cin >> p;
    cout << "Enter const a: ";
    cin >> a;
    cout << "Enter const b: ";
    cin >> b;
    cout << "Enter value n: ";
    cin >> n;
    n++;

    vector<int> x_val(n, 0);
    vector<int> y_val(n, 0);

    // (y^2) mod p = (x^3 + ax + b) mod p
    printf("\ni_val|  left| right|\n");
    cout << "--------------------" << endl;
    for(int i = 0; i < n; ++i) {
        x_val[i] = ((i * i * i) + a * i + b) % p;
        y_val[i] = (i * i) % p;
        printf(" %2d  |  %2d  |  %2d  |\n", i, y_val[i], x_val[i]);
    }

    cout << "-------------------" << endl << endl;;
    cout << "Points lie on curve: " << endl;
    int count =0;
    for(int i=0; i < n; ++i){
        for(int j=0; j < n; ++j){
            if(x_val[i] == y_val[j]){
                printf("{%2d, %2d}, ", i, j);
                count++;
                if(count % 5 == 0) cout << endl;
            }
        }
    }
    cout << endl;

    return 0;    
}