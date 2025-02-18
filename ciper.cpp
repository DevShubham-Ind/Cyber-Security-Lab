#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string inputData;
    cout << "Enter Data: ";
    getline(cin, inputData);

    int n;
    cout << "Enter level: ";
    cin >> n;
    cout << endl;

    bool down = true;
    vector<string> ds(n, string(inputData.length(), ' '));
    int row =0;

    for(int i=0; i<inputData.length(); i++) {
        ds[row][i] = inputData[i];
        if(down){
            row++;
            if(row == n){
                down = false;
                row = n -2;
            }
        }
        else{
            row--;
            if(row < 0){
                down = true;
                row = 1;
            }
        }
    }

    cout << "Encrpt success" << endl << endl;
    for(int i=0; i<n; i++){
        cout << ds[i] << endl;
    }
    cout << endl; 

    string ciper ="";
    for(int i=0; i<n; i++) {
        for(int j=0; j<inputData.length(); j++){
            if(ds[i][j] != ' '){
                ciper += ds[i][j];
            }
        }
    }

    cout << "Ciper Text : " << ciper << endl;
    cout << "Ciper length : " << ciper.length() << endl;

    return 0;
}