#ifndef SECOND_LEVEL_HASH
#define SECOND_LEVEL_HASH

#include <vector>
#include <set>
#include "multiply_mod_prime.hpp"
#include "multiply_shift.hpp"

template <typename Key, typename Hash_Func>
struct s_size {
    size_t operator() (size_t size) {
        return size * size;
    }
};

template <typename Key>
struct s_size<Key, Multiply_Shift<Key>> {
    size_t operator() (size_t size) {
        return 1 << (int)ceil(log2(size * size));
    }
};

template <typename Key, typename Value, typename Hash_Func>
class Second_LvL_Hash_Table {
public:
    Second_LvL_Hash_Table() = delete;
    inline Second_LvL_Hash_Table(size_t);
    inline size_t length();
    void operator() (std::vector<std::pair<Key, Value>>&);
	Value& find(Key key) {
		return table[hfunc->hash(key)];
	}
private:
    std::vector<Value> table;
    Hash_Func* hfunc;
};

template <typename Key, typename Value, typename Hash_Func>
Second_LvL_Hash_Table<Key, Value, Hash_Func>::Second_LvL_Hash_Table(size_t size) {
    table.resize(s_size<Key, Hash_Func>()(size));
    hfunc = new Hash_Func(table.size());
}

template <typename Key, typename Value, typename Hash_Func>
void Second_LvL_Hash_Table<Key, Value, Hash_Func>::operator() (
    std::vector<std::pair<Key, Value>>& data) {
    std::set<Key> hash_values;
    while (hash_values.size() != data.size()){
        hash_values.clear();
        for (const auto rec : data)
            if (!hash_values.insert(hfunc->hash(rec.first)).second){
                hfunc->rebuild_hash();
                break;
            }
    }
    for (const auto rec : data)
        table[hfunc->hash(rec.first)] = (rec.second);
}
template <typename Key, typename Value, typename Hash_Func>
size_t Second_LvL_Hash_Table<Key, Value, Hash_Func>::length() {
    return table.size();
}


#endif