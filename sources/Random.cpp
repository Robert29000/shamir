//
// Created by Роберт Артур Меликян on 06/05/2021.
//

#include "Random.h"
#include <random>

BigInteger getBigRandom(){   // random number with 64 hex digits
    std::random_device gen;
    std::uniform_int_distribution<int> dis(0, 15);
    std::string rand = "0x";
    int first = 1 + dis(gen) % 15;
    rand += int_to_hex(first);
    for (auto i = 1; i < 64; i++){
        rand += int_to_hex(dis(gen));
    }
    return BigInteger(rand);
}

std::string int_to_hex(int a){
    if (a <= 9){
        return std::to_string(a);
    } else {
        switch (a) {
            case 10:
                return "a";
            case 11:
                return "b";
            case 12:
                return "c";
            case 13:
                return "d";
            case 14:
                return "e";
            case 15:
                return "f";
            default:
                break;
        }
    }
}