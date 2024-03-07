#pragma once
#include "pair_key_value.h"

template <typename TKey, typename TValue>
hash_table<typename TKey, typename TValue>::my_pair::my_pair() : key(TKey()), value(TValue())
{

}

template <typename TKey, typename TValue>
inline hash_table<typename TKey, typename TValue>::my_pair::my_pair(TKey key, TValue value) : key(key), value(value)
{ }
template <typename TKey, typename TValue>
inline hash_table<typename TKey, typename TValue>::my_pair::my_pair(const my_pair& other) : key(other.key), value(other.value)
{
}

template <typename TKey, typename TValue>
bool hash_table<typename TKey, typename TValue>::my_pair::operator==(const my_pair& other) {
	return other.key == this->key;
}
