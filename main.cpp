#include "Header.h"
#include <iostream>
#include <ctime>
using namespace std;

vector<int> generate_vector(size_t size, int range) {
	srand((int)time(0));

	vector<int> vec;
	while (size--)
		vec.push_back(rand() % range);
	return vec;
}

int main()
{
	int range = 100;
	size_t size = 20;
	hash_table<string, int> table;

	int value = 25;

	string key = "apple";
	string key1 = "tomato";
	string key2 = "cucumber";
	string key3 = "pasta";
	string key4 = "meat";

	table.add(key, value);
	table.add(key1, value);
	table.add(key2, value);
	table.add(key3, value);
	

	hash_table<string, int> table1 = table;
	table.add(key4, value);
	cout << (table1 == table);





}

