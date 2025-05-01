#include <iostream>
#include <cmath>

using namespace std;

// compute (base^exp) % mod
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    long long p, g, a, b;

    // Input prime number and primitive root
    cout << "Enter a prime number (x): ";
    cin >> p;

    cout << "Enter a primitive root modulo x (g): ";
    cin >> g;

    // Input private keys
    cout << "Enter Alice's private key (Xa): ";
    cin >> a;

    cout << "Enter Bob's private key (Xb): ";
    cin >> b;

    // public keys
    long long A = modExp(g, a, p);
    long long B = modExp(g, b, p);

    // shared secret keys
    long long secretKeyA = modExp(B, a, p);
    long long secretKeyB = modExp(A, b, p);

    // Output results
    cout << "\n--- Diffie-Hellman Key Exchange ---" << endl;
    cout << "Alice's Public Key (A): " << A << endl;
    cout << "Bob's Public Key (B): " << B << endl;
    cout << "Shared Secret Key (calculated by Alice): " << secretKeyA << endl;
    cout << "Shared Secret Key (calculated by Bob):   " << secretKeyB << endl;

    return 0;
}
