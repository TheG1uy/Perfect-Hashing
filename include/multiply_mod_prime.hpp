#ifndef HASHING_SCHEME_WITH_MOD
#define HASHING_SCHEME_WITH_MOD

#include <vector>
#include <random>
using ulong = unsigned long long;

template <typename Key, typename Value>
class Multiply_Mod_Prime {
public: 
    Multiply_Mod_Prime(int);
    void rebild_hash();
    int hash(Key);
private:
    ulong a;
    ulong b;
    ulong p;
    size_t m; //table size
    static std::mt19937 gen;
    static std::uniform_int_distribution<ulong> random;
};

template <typename Key, typename Value>
std::mt19937 Multiply_Mod_Prime<Key, Value>::gen(time(0));
template <typename Key, typename Value>
std::uniform_int_distribution<ulong> Multiply_Mod_Prime<Key, Value>::random(0, ULLONG_MAX);
#endif