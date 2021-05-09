#include <iostream>
#include <vector>
#include <fstream>
#include <BigInteger.h>
#include <Random.h>
#include <ModularMath.h>

struct Share {
    int x;
    BigInteger y;
};

const BigInteger p = BigInteger::pow(2, 521) - 1; // prime number bigger than 2^256. Prime is needed for modular division

std::vector<Share> proceed_split_mode();
BigInteger proceed_recover_mode();
BigInteger poly(int x, std::vector<BigInteger> coefs);
void write_to_file(int t);

int main(int argc, char *argv[]) {
    std::string mode;
    if (argc == 2) {
        mode = argv[1];
        if (mode == "split") {
            auto shares = proceed_split_mode();
            for (const auto& share: shares){
                std::string key = std::to_string(share.x);
                key += share.y.to0xHexString();
                std::cout << key << std::endl;
            }
        } else {
            auto secret = proceed_recover_mode();
            std::cout << secret.to0xHexString() << std::endl;
        }
    } else {
        throw std::runtime_error{"Incorrect number of arguments"};
    }
    return 0;
}

std::vector<Share> proceed_split_mode() {
    std::string key;
    int n, t;
    std::cin >> key >> n >> t;
    write_to_file(t);
    BigInteger num_key(key);

    std::vector<Share> shares;

    std::vector<BigInteger> coefs;
    coefs.reserve(t);
    for (auto i = 0; i < t - 1; i ++){
        coefs.push_back(getBigRandom());
    }
    coefs.push_back(num_key);

    for (auto i = 1; i <= n; i++) {
        shares.push_back({i, poly(i, coefs)});
    }

    return shares;
}

BigInteger proceed_recover_mode() {
    int required_t, t;
    std::ifstream f("data.txt");
    f >> required_t;
    f.close();
    std::cin >> t;
    if (t >= required_t) {
        std::vector<Share> shares;
        shares.reserve(required_t);

        for (auto i = 0; i < t; i++){
            std::string part;
            std::cin >> part;
            if (i < required_t) {
                auto pos = std::find(part.begin(), part.end(), 'x');
                std::string x_coord(part.begin(), pos - 1);
                std::string y_coord(pos - 1, part.end());
                shares.push_back({std::stoi(x_coord), BigInteger(y_coord)});
            }
        }

        std::vector<BigInteger> nums;
        nums.reserve(required_t);
        std::vector<BigInteger> dens;
        dens.reserve(required_t);

        for (auto i = 0; i < required_t; i++) {
            BigInteger num = 1;
            BigInteger den = 1;
            for (auto j = 0; j < required_t; j++) {
                if (i != j) {
                    num *= -shares[j].x;
                    den *= (shares[i].x - shares[j].x);
                }
            }
            nums.push_back(num);
            dens.push_back(den);
        }

        BigInteger den = 1;
        for (const auto& el: dens) {
            den *= el;
        }

        den = positivemod(den, p);

        BigInteger res = 0;

        for (auto i = 0; i < required_t; i++) {
            BigInteger num = nums[i] * den * shares[i].y;
            num = positivemod(num, p);
            BigInteger den_i = dens[i];
            den_i = positivemod(den_i, p);
            res += divmod(num % p, den_i, p);
        }

        res = (divmod(res, den, p) + p) % p;
        return res % p;

    } else {
        throw std::runtime_error{"Can not construct secret"};
    }
}

BigInteger poly(int x, std::vector<BigInteger> coefs){
    auto degree = coefs.size();
    BigInteger value;
    for (auto i = 0; i < degree; i++){
        value += (coefs[i] * BigInteger::pow(x, degree - i - 1)) % p;
    }
    return value % p;
}


void write_to_file(int t){
    std::ofstream f("data.txt");
    f << t;
    f.close();
}

