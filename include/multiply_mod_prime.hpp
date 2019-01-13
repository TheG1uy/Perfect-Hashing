#ifndef HASHING_SCHEME_WITH_MOD
#define HASHING_SCHEME_WITH_MOD

#include <vector>
#include <random>
#include <string>
#include <ctime>

using uint = unsigned int;

template <typename Key>
class Multiply_Mod_Prime {
public: 
    Multiply_Mod_Prime() = delete;
    Multiply_Mod_Prime(size_t);
    void rebuild_hash();
    size_t hash(Key);
private:
    uint a;
    uint b;
    uint p;
    size_t m;
    static std::mt19937 gen;
    static std::uniform_int_distribution<uint> random;

};

template <typename Key>
std::mt19937 Multiply_Mod_Prime<Key>::gen(time(0));
template <typename Key>
std::uniform_int_distribution<uint> Multiply_Mod_Prime<Key>::random(0, UINT32_MAX);


template <typename Key>
Multiply_Mod_Prime<Key>::Multiply_Mod_Prime(size_t table_size) {
    m = table_size;
	m > 16 ? p = 1198754321 : p = 433494437;
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
    if (m == 1) return 0;
    return (a * key + b) % p % m;
}

template <>
size_t Multiply_Mod_Prime<std::string >::hash(std::string key) {
    if (m == 1) return 0;
    uint h = 1;
    for (auto it = key.begin(); it != key.end(); ++it)
        h = ((h*a) + *it) % p;
    return h % m;
}

#endif