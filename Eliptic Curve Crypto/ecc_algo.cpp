#include <iostream>
#include <cstdlib>
using namespace std;

// Returns a mod b (handles negative a)
int mod(int a, int b) {
    return (a % b + b) % b;
}

// Extended Euclidean Algorithm for modular inverse
int modInverse(int a, int p) {
    a = mod(a, p);
    if (a == 0) return -1;
    int t = 0, newT = 1;
    int r = p, newR = a;

    while (newR != 0) {
        int q = r / newR;
        t -= q * newT;  r -= q * newR;
        swap(t, newT);
        swap(r, newR);
    }
    if (r > 1) return -1;     // no inverse
    if (t < 0) t += p;
    return t;
}

// Double a point on the curve
pair<int, int> doublePoint(int x, int y, int p, int a) {
    // slope = (3x^2 + a) / (2y)  mod p
    int inv = modInverse(2 * y, p);
    if (inv < 0) return {-1, -1};  // point at infinity
    int slope = mod((3 * x * x + a) * inv, p);

    int x3 = mod(slope * slope - 2 * x, p);
    int y3 = mod(slope * (x - x3) - y, p);
    return {x3, y3};
}

// Add two points (covers general, doubling, inverses, infinity)
pair<int, int> addPoints(int x1, int y1, int x2, int y2, int p, int a) {
    // identity cases
    if (x1 == -1 && y1 == -1) return {x2, y2};
    if (x2 == -1 && y2 == -1) return {x1, y1};

    // same point → doubling
    if (x1 == x2 && y1 == y2) {
        return doublePoint(x1, y1, p, a);
    }
    // vertical line → inverse points → infinity
    if (x1 == x2) {
        return {-1, -1};
    }

    // slope = (y2 - y1) / (x2 - x1)  mod p
    int inv = modInverse(x2 - x1, p);
    if (inv < 0) return {-1, -1};
    int slope = mod((y2 - y1) * inv, p);

    int x3 = mod(slope * slope - x1 - x2, p);
    int y3 = mod(slope * (x1 - x3) - y1, p);
    return {x3, y3};
}

// Scalar multiplication by repeated addition
pair<int, int> repeatedAdd(int k, int x, int y, int p, int a) {
    pair<int, int> result = {-1, -1};  // start with point at infinity
    pair<int, int> base = {x, y};

    for (int i = 0; i < k; ++i) {
        result = addPoints(result.first, result.second,
                           base.first,  base.second,
                           p, a);
    }
    return result;
}

// Generate public key Q = d·G
pair<int, int> generatePublicKey(int privKey, int p, int a, int Gx, int Gy) {
    return repeatedAdd(privKey, Gx, Gy, p, a);
}

// ECC ElGamal encryption
pair<pair<int, int>, pair<int, int>>
encrypt(int Mx, int My,
        int r,
        pair<int, int> pubKey,
        int p, int a,
        int Gx, int Gy)
{
    auto C1 = repeatedAdd(r, Gx, Gy, p, a);
    auto R  = repeatedAdd(r, pubKey.first, pubKey.second, p, a);
    auto C2 = addPoints(Mx, My, R.first, R.second, p, a);
    return {C1, C2};
}

// ECC ElGamal decryption
pair<int, int> decrypt(pair<pair<int, int>, pair<int, int>> ct,
                       int privKey,
                       int p, int a)
{
    auto C1 = ct.first;
    auto C2 = ct.second;

    // shared secret = d*C1
    auto S = repeatedAdd(privKey, C1.first, C1.second, p, a);
    // negate S
    auto negS = make_pair(S.first, mod(-S.second, p));
    // M = C2 + (–S)
    return addPoints(C2.first, C2.second, negS.first, negS.second, p, a);
}

int main() {
    // curve y^2 = x^3 + 2x + 2 over F17
    // int p = 17, a = 2, b = 2;
    // int Gx = 5, Gy = 1;
    int p, a, b, Gx, Gy, Mx, My;
    cout << "Enter P: ";
    cin >> p;
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    cout << "Enter Gx: ";
    cin >> Gx;
    cout << "Enter Gy: ";
    cin >> Gy;
    cout << "Enter Message --" << endl;
    cout << "Enter M(x, y): ";
    cin >> Mx >> My;

    int privateKey = 5;
    cout << endl;
    cout << "Private Key: " << privateKey << "\n";

    auto publicKey = generatePublicKey(privateKey, p, a, Gx, Gy);
    cout << "Public Key : (" << publicKey.first << ", " << publicKey.second << ")\n";

    // plaintext point
    // int Mx = 6, My = 3;
    int r  = 3;  // random nonce
    cout << "Encrypting M(" << Mx << ", " << My << ") with r = " << r << "\n";

    auto ciphertext = encrypt(Mx, My, r, publicKey, p, a, Gx, Gy);
    cout << "Ciphertext:\n"
         << "  C1(" << ciphertext.first.first  << ", " << ciphertext.first.second  << ")\n"
         << "  C2(" << ciphertext.second.first << ", " << ciphertext.second.second << ")\n";

    auto decrypted = decrypt(ciphertext, privateKey, p, a);
    cout << "Decrypted Message: ("
         << decrypted.first << ", "
         << decrypted.second
         << ")\n";

    return 0;
}
