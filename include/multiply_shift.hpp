#ifndef HASHING_SCHEME_WITHOUT_MOD
#define HASHING_SCHEME_WITHOUT_MOD

#include <vector>
#include <random>
#include <ctime>

using ullong = unsigned long long;

template <typename Key>
class Multiply_Shift {
public:
    Multiply_Shift() = delete;
    Multiply_Shift(size_t);
    void rebuild_hash();
    size_t hash(Key);
private:
    ullong a;
    ullong b;
    ullong one;
    size_t w;
    size_t m;
    static std::mt19937 gen;
    static std::uniform_int_distribution<ullong> random;
};

template <typename Key>
std::mt19937 Multiply_Shift<Key>::gen(time(0));
template <typename Key>
std::uniform_int_distribution<ullong> Multiply_Shift<Key>::random(0, ULLONG_MAX);


template <typename Key>
Multiply_Shift<Key>::Multiply_Shift(size_t table_size) : 
         m(std::log2(table_size)), w(64), one(1) {
    a = random(gen) % (one << w - 1);
    if (!(a % 2)) ++a;
    b = random(gen) % (one << w - m - 1);
}

template <typename Key>
void Multiply_Shift<Key>::rebuild_hash() {
    a = random(gen) % (one << w - 1);
    if (!(a % 2)) ++a;
    b = random(gen) % (one << w - m - 1);
}

template <typename Key>
size_t Multiply_Shift<Key>::hash(Key key) {
    if (!m) return 0;
    return (a * key + b) >> (w - m);
}

#endif