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

// Function to perform modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)  // If exp is odd
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    // Step 1: Choose two prime numbers (small ones for simplicity)
    int p = 11;
    int q = 17;

    // Step 2: Compute n = p * q
    int n = p * q;

    // Step 3: Compute phi(n)
    int phi = (p - 1) * (q - 1);

    // Step 4: Choose e such that 1 < e < phi and gcd(e, phi) = 1
    int e = 7; // Commonly used value
    while (gcd(e, phi) != 1) e++;

    // Step 5: Compute d (modular inverse of e)
    int d = modInverse(e, phi);

    // Display keys
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
