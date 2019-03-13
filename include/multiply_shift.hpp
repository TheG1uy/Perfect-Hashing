#ifndef HASHING_SCHEME_system_capacityITHOUT_MOD
#define HASHING_SCHEME_system_capacityITHOUT_MOD

#include <random>
#include <ctime>

using ullong = unsigned long long;

class Multiply_Shift {
public:
    Multiply_Shift() = delete;
    Multiply_Shift(size_t);
    void rebuild_hash();
    size_t hash(ullong);
private:
    ullong first_factor;
    ullong second_factor;
    ullong one;
    size_t system_capacity; //w
    size_t logarithm_table_size; //M
    static std::mt19937 gen;
    static std::uniform_int_distribution<ullong> random;
};

std::mt19937 Multiply_Shift::gen(time(0));
std::uniform_int_distribution<ullong> Multiply_Shift::random(0, ULLONG_MAX);

Multiply_Shift::Multiply_Shift(size_t table_size) : 
	logarithm_table_size(std::log2(table_size)), system_capacity(64), one(1) {
	first_factor = random(gen) % (one << system_capacity - 1);
    if ((first_factor % 2) == 0) ++first_factor;
	second_factor = random(gen) % (one << system_capacity - logarithm_table_size - 1);
}

void Multiply_Shift::rebuild_hash() {
	first_factor = random(gen) % (one << system_capacity - 1);
    if ((first_factor % 2) == 0) ++first_factor;
	second_factor = random(gen) % (one << system_capacity - logarithm_table_size - 1);
}

size_t Multiply_Shift::hash(ullong key) {
    if (logarithm_table_size == 0) return 0;
    return (first_factor * key + second_factor) >> (system_capacity - logarithm_table_size);
}

#endif