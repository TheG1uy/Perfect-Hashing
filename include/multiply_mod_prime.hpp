#ifndef HASHING_SCHEME_WITH_MOD
#define HASHING_SCHEME_WITH_MOD

#include <random>
#include <ctime>

using uint = unsigned int;

class Multiply_Mod_Prime {
public: 
    Multiply_Mod_Prime() = delete;
    Multiply_Mod_Prime(size_t);
    void rebuild_hash();
    size_t hash(int);
private:
    uint first_factor;
    uint second_factor;
    uint prime_number;
    size_t table_size;
    static std::mt19937 gen;
    static std::uniform_int_distribution<uint> random;
};

std::mt19937 Multiply_Mod_Prime::gen(time(0));
std::uniform_int_distribution<uint> Multiply_Mod_Prime::random(0, UINT32_MAX);

Multiply_Mod_Prime::Multiply_Mod_Prime(size_t _table_size) {
	table_size = _table_size;
	table_size > 16 ? prime_number = 1198754321 : prime_number = 433494437;
	first_factor = random(gen) % (prime_number - 1);
    if (first_factor == 0) ++first_factor;
	second_factor = random(gen) % (prime_number - 1);
}

void Multiply_Mod_Prime::rebuild_hash() {
	first_factor = random(gen) % (prime_number - 1);
	if (first_factor == 0) ++first_factor;
	second_factor = random(gen) % (prime_number - 1);
}

size_t Multiply_Mod_Prime::hash(int key) {
    if (table_size == 1) return 0;
    return (first_factor * key + second_factor) % prime_number % table_size;
}

#endif