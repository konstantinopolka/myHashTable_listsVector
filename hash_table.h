#pragma once
#include <vector>
#include <deque>
#include <string>
#include <type_traits>
#include <iostream>
#include <memory>
#include <sstream>

// an own class must have an overloaded toString to be able to get hash
using namespace std;

template <typename TKey, typename TValue>
class hash_table
{
public:

	hash_table(); // OK
	~hash_table(); // OK

	hash_table(const hash_table& other); // OK
	bool operator==(const hash_table& other); // OK
	bool operator!=(const hash_table& other); // OK
	hash_table& operator=(const hash_table& other); // OK
	void clear();

	static void swap(hash_table& table1, hash_table& table2); // OK

	TValue& operator[](TKey key); // OK
	void add(TKey key, TValue value); // OK
	bool erase(const TKey& key); // OK

	static size_t size(); // OK
	bool empty(); // OK

	bool contains(const TKey& key); // OK
private:
	class my_pair;
	static const size_t sizes_count = 29;
	static const size_t sizes[sizes_count];
	int size_index;
	size_t actual_size;
	shared_ptr<vector <deque <my_pair> >> pairs;
	size_t count;
	TValue* search(const TKey&);


	const double MAX_FULLNESS = 0.75;

	size_t get_index(const TKey&); // OK
	void rehash(bool more_less); // OK
	bool too_much(); // OK
	bool too_few(); // OK
	static size_t  get_hash(TKey key); // OK
	

};

#include "pair_key_value.h"
#include "hash_table_impl.h"
#include "pair_key_value_impl.h"