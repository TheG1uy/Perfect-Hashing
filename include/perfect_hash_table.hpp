#ifndef PERFECT_HASH
#define PERFECT_HASH

#include "first_level_hash_table.hpp"

template <typename Key, typename Value, typename Hash_Func>
class Perfect_Hash_Table {
public:
	Perfect_Hash_Table() = delete;
	Perfect_Hash_Table(std::vector<std::pair<Key, Value>>& data, size_t param) : main_table(data.size()) {
		main_table(data, param);
	}
	Value& find(Key key) {
		return main_table.find(key);
	}
private:
	First_LvL_Hash_Table<Key, Value, Hash_Func> main_table;
};

#endif
