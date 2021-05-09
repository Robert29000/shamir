//
// Created by Роберт Артур Меликян on 06/05/2021.
//

#ifndef SHAMIR_MODULARMATH_H
#define SHAMIR_MODULARMATH_H

#include <BigInteger.h>

BigInteger divmod(BigInteger num, const BigInteger& den, const BigInteger& p);
BigInteger mod_inverse(const BigInteger& a, const BigInteger& p);
BigInteger gcdExtended(const BigInteger& a, const BigInteger& b, BigInteger* x, BigInteger* y);
BigInteger positivemod(const BigInteger& a, const BigInteger& p);

#endif //SHAMIR_MODULARMATH_H
