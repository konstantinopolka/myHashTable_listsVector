#pragma once
#include "hash_table.h"


template <typename TKey, typename TValue>
const size_t hash_table<TKey, TValue>::sizes[hash_table<TKey, TValue>::sizes_count] = {
	5, 11, 23, 97, 193, 389, 769, 1543, 3072, 3079, 12289, 24593,
	49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
	50331653, 100663319, 201326611, 402653189, 805306457, 1610612736, 2147483629
};

template <typename TKey, typename TValue>
hash_table<typename TKey, typename TValue>::hash_table() :
size_index(0), actual_size(sizes[size_index]), pairs(make_shared<vector <deque <my_pair> >>(actual_size)), count(0)
{
}


template <typename TKey, typename TValue>
hash_table<typename TKey, typename TValue>::~hash_table()
{
}

template<typename TKey, typename TValue>
inline hash_table<TKey, TValue>::hash_table(const hash_table& other) :
	size_index(other.size_index),
	actual_size(other.actual_size),
	pairs(make_shared<vector<deque<my_pair>>>(actual_size)),
	count(other.count)
{
	for (auto i = other.pairs->begin(); i != other.pairs->end(); i++) {
		for (auto j = i->begin(); j != i->end(); j++) {
			size_t index = get_index(j->key);
			pairs->at(index).push_back(*j);
		}
	}

}

template<typename TKey, typename TValue>
inline bool hash_table<TKey, TValue>::operator==(const hash_table& other)
{

	if (this->count != other.count || this->pairs->size() != other.pairs->size())
		return false;

	for (size_t i = 0; i < pairs->size(); i++) {
		if (this->pairs->at(i).size() != other.pairs->at(i).size())
			return false;
		for (size_t j = 0; j < pairs->at(i).size(); j++)
			if (this->pairs->at(i)[j].key != other.pairs->at(i)[j].key || 
				this->pairs->at(i)[j].value != other.pairs->at(i)[j].value)
				return false;
	}
	return true;
}

template<typename TKey, typename TValue>
inline bool hash_table<TKey, TValue>::operator!=(const hash_table& other)
{
	return !operator==(other);
}

template<typename TKey, typename TValue>
inline hash_table<TKey, TValue>& hash_table<TKey, TValue>::operator=(const hash_table<TKey, TValue>& other)
{
	clear();
	size_index = other.size_index;
	actual_size = other.actual_size;
	count = other.count;
	pairs = make_shared<vector<deque<my_pair>>>(actual_size);
	for (size_t i = 0; i < other.pairs->size(); i++) {
		for (auto j : other.pairs->operator[](i)) {
			size_t index = get_index(j.key);
			pairs->at(index).push_back(j);
		}
	}

	return *this;
}

template<typename TKey, typename TValue>
inline void hash_table<TKey, TValue>::clear()
{
	count = 0;
	size_index = 0;
	actual_size = sizes[size_index];
	pairs = make_shared<vector<deque<my_pair>>>(actual_size);
}


template <typename TKey, typename TValue>
size_t hash_table<typename TKey, typename TValue>::get_index(const TKey& value) {
	return get_hash(value) % actual_size;
}

template<typename TKey, typename TValue>
inline TValue& hash_table<TKey, TValue>::operator[](TKey key)
{
	if (!contains(key))
		add(key, TValue());
	return *search(key);
}

template <typename TKey, typename TValue>
void hash_table<typename TKey, typename TValue>::add(TKey key, TValue value) {
	size_t index_to_insert = get_index(key);
	pairs->operator[](index_to_insert).push_back(my_pair(key, value));
	count++;
	if (too_much())
		rehash(true);
}
template <typename TKey, typename TValue>
bool hash_table<typename TKey, typename TValue>::too_much() {
	return (double)count / actual_size >= MAX_FULLNESS;
}


template <typename TKey, typename TValue>
bool hash_table<typename TKey, typename TValue>::too_few() {
	if (size_index >= 1) {
		if ((double)count / sizes[size_index - 1] < MAX_FULLNESS)
			return true;
	}
	return false;
}

template <typename TKey, typename TValue>
void hash_table<typename TKey, typename TValue>::rehash(bool more_less) {
	if (more_less)
		actual_size = sizes[++size_index];
	else
		actual_size = sizes[--size_index];

	shared_ptr<vector <deque <my_pair> >> new_pairs = make_shared<vector <deque <my_pair> >>(actual_size);

	for (size_t i = 0; i < pairs->size(); i++) {
		for (auto j : pairs->operator[](i)) {
			my_pair toInsert = j;
			size_t index = get_index(toInsert.key);
			new_pairs->operator[](index).push_back(toInsert);
		}
	}

	pairs = new_pairs;
}


template <typename TKey, typename TValue>
size_t hash_table<typename TKey, typename TValue>::size() {
	return count;
}
template <typename TKey, typename TValue>
bool hash_table<typename TKey, typename TValue>::empty() {
	return count == 0;
}

template <typename TKey, typename TValue>
bool hash_table<typename TKey, typename TValue>::contains(const TKey& key) {
	size_t index = get_index(key);
	for (auto i : pairs->operator[](index))
		if (i.key == key)
			return true;
	return false;
}


template <typename TKey, typename TValue>
TValue* hash_table<typename TKey, typename TValue>::search(const TKey& key) {
	size_t index = get_index(key);
	for (auto i : pairs->operator[](index))
		if (i.key == key)
			return &i.value;
	//return TValue();
}

template <typename TKey, typename TValue>
bool hash_table<typename TKey, typename TValue>::erase(const TKey& key) {

	size_t index = get_index(key);
	for (auto i = pairs->operator[](index).begin(); i != pairs->operator[](index).end(); i++) {
		if (i->key == key) {
			pairs->operator[](index).erase(i);
			count--;
			if (too_few())
				rehash(false);
			return true;
		}
	}

	return false;
}
template <typename TKey, typename TValue>
size_t  hash_table<typename TKey, typename TValue>::get_hash(TKey key)
{
	// to_string is avialible only for default types and string
	// and for the classes which have an overloaded toString()

	string string_key;
	std::ostringstream oss;
	oss << key;
	string_key = oss.str();


	size_t hash_value = hash<string>{}(string_key);
	return hash_value;
}


template <typename TKey, typename TValue>
void hash_table<typename TKey, typename TValue>::swap(hash_table& table1, hash_table& table2)
{
	using std::swap;
	swap(table1.size_index, table2.size_index);
	swap(table1.count, table2.count);
	swap(table1.actual_size, table2.actual_size);
	swap(table1.pairs, table2.pairs);
}
