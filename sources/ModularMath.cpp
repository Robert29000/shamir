//
// Created by Роберт Артур Меликян on 06/05/2021.
//

#include "ModularMath.h"

BigInteger divmod(BigInteger num, const BigInteger& den, const BigInteger& p) {
    num = num % p;
    auto inv = mod_inverse(den, p);
    if (inv == -1) {
        throw std::runtime_error{"Den and p are not coprime"};
    }
    return (inv * num) % p;
}

BigInteger mod_inverse(const BigInteger& a, const BigInteger& m) {
    BigInteger x, y;
    auto g = gcdExtended(a, m, &x, &y);

    if (g != 1)
        return -1;

    return (x % m + m) % m;
}

BigInteger gcdExtended(const BigInteger& a, const BigInteger& b, BigInteger* x, BigInteger* y){
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    BigInteger x1, y1;
    auto gcd = gcdExtended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

BigInteger positivemod(const BigInteger& a, const BigInteger& p) {
    auto temp = a;
    while (temp < 0) {
        temp += p;
    }
    return temp;
}