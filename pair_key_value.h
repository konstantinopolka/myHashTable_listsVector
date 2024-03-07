#pragma once
#include "hash_table.h"


template <typename TKey, typename TValue>
class hash_table<typename TKey, typename TValue>::my_pair {
public:
	my_pair();
	my_pair(TKey key, TValue value);
	my_pair(const my_pair& other);
	bool operator==(const my_pair& other);
	TKey key;
	TValue value;
};

