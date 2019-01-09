#ifndef HASHING_SCHEME_WITH_MOD
#define HASHING_SCHEME_WITH_MOD

#include <vector>
#include <random>
#include <string>
using uint = unsigned int;

template <typename Key>
class Multiply_Mod_Prime {
public: 
	Multiply_Mod_Prime() = delete;
    Multiply_Mod_Prime(size_t);
    void rebuild_hash();
    size_t hash(Key);
private:
    ulong a;
    ulong b;
    ulong p;
    size_t m;
    static std::mt19937 gen;
    static std::uniform_int_distribution<> random;

};

template <typename Key>
std::mt19937 Multiply_Mod_Prime<Key>::gen(time(0));
template <typename Key>
std::uniform_int_distribution<> Multiply_Mod_Prime<Key>::random(0, UINT32_MAX);


template <typename Key>
Multiply_Mod_Prime<Key>::Multiply_Mod_Prime(size_t table_size) {
    m = table_size;
    p = 4093082899;
    if (!(a = random(gen) % (p - 1))) ++a;
    b = random(gen) % (p - 1);
}

template <typename Key>
void Multiply_Mod_Prime<Key>::rebuild_hash() {
    if (!(a = random(gen) % (p - 1))) ++a;
    b = random(gen) % (p - 1);
}

template <typename Key>
size_t Multiply_Mod_Prime<Key>::hash(Key key) {
    return (a * key + b) % p % m;
}

template <>
size_t Multiply_Mod_Prime<std::string >::hash(std::string key) {
    uint h = 1;
    for (auto it = key.begin(); it != key.end(); ++it)
        h = ((h*a) + *it) % p;
    return h % m;
}

#endif