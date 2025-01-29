#pragma once
#include "TOKEN.h"
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
using namespace std;
class HASH_TABLE
{
	set <pair<string,string>> st;
	vector <TOKEN> vec;
public:
	HASH_TABLE() {};
	void fileout();
	void insert(string id, string type);
};

