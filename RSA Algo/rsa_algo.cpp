#include <iostream>
#include <cmath>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int modInverse(int e, int phi) {
    for (int d = 1; d < phi; d++) {
        if ((e * d) % phi == 1) return d;
    }
    return -1;
}

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    // int p = 11;
    // int q = 17;
    int p, q;
    cout << "Enter p: " ;
    cin >> p;
    cout << "Enter q: " ;
    cin >> q;

    int n = p * q;

    int phi = (p - 1) * (q - 1);

    // e such that 1 < e < phi and gcd(e, phi) = 1
    // int e = 7;
    int e;
    cout << "Enter e: ";
    cin >> e;
    while (gcd(e, phi) != 1) e++;

    int d = modInverse(e, phi);

    cout << "Public Key: (" << e << ", " << n << ")\n";
    cout << "Private Key: (" << d << ", " << n << ")\n";

    // Encrypt a message
    int message;
    cout << "Enter a message (numeric): ";
    cin >> message;

    // Encryption: c = m^e mod n
    long long encrypted = modExp(message, e, n);
    cout << "Encrypted Message: " << encrypted << endl;

    // Decryption: m = c^d mod n
    long long decrypted = modExp(encrypted, d, n);
    cout << "Decrypted Message: " << decrypted << endl;

    return 0;
}
