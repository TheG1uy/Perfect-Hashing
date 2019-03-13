#ifndef FIRST_LEVEL_HASH
#define FIRST_LEVEL_HASH

#include <vector>
#include <second_level_hash_table.hpp>
#include "multiply_mod_prime.hpp"
#include "multiply_shift.hpp"

template <typename Key, typename Hash_Func>
struct first_lvl_size {
    size_t get(size_t size) {
        return size;
    }
};

template <typename Key>
struct first_lvl_size<Key, Multiply_Shift> {
    size_t get(size_t size) {
        return 1 << (int)ceil(log2(size));
    }
};

template <typename Key, typename Value, typename Hash_Func>
class First_LvL_Hash_Table {
public:
    First_LvL_Hash_Table(size_t);
    size_t length();
    void operator() (std::vector<std::pair<Key, Value>>&, size_t);
	Value& find(Key key) {
		return tables[hfunc->hash(key)]->find(key);
	}
private:
    std::vector<Second_LvL_Hash_Table<Key, Value, Hash_Func>*> tables;
    Hash_Func* hfunc;
};

template <typename Key, typename Value, typename Hash_Func>
First_LvL_Hash_Table<Key, Value, Hash_Func>::First_LvL_Hash_Table(size_t size) {
	first_lvl_size<Key, Hash_Func> size_calculator;
    tables.resize(size_calculator.get(size));
    hfunc = new Hash_Func(tables.size());
}

template <typename Key, typename Value, typename Hash_Func>
void  First_LvL_Hash_Table<Key, Value, Hash_Func>::operator() (
      std::vector<std::pair<Key, Value>>& data, size_t param) {
    for (;;) {
        std::vector<std::vector<std::pair<Key, Value>>> hash_res(tables.size());
        for (const auto& rec : data)
            hash_res[hfunc->hash(rec.first)].emplace_back(rec);
        for (int i = 0; i < tables.size(); ++i)
            if (hash_res[i].size()) {
                tables[i] = new Second_LvL_Hash_Table<Key,
                    Value, Hash_Func>(hash_res[i].size());
                (*tables[i])(hash_res[i]);
            }
        if (!(length() <= data.size() * param))
            hfunc->rebuild_hash();
        else break;
    }
}

template <typename Key, typename Value, typename Hash_Func>
size_t First_LvL_Hash_Table<Key, Value, Hash_Func>::length() {
    int sum_lenght = 0;
    for (int i = 0; i < tables.size(); ++i)
        if (tables[i]) sum_lenght += tables[i]->length();
    return sum_lenght;
}
#endif