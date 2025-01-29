#pragma once
#include <iostream>
#include "HASH_TABLE.h"
#include "TOKEN.h"
using namespace std;
class LEXER
{
	string proga;
	HASH_TABLE hash_t;
	vector < pair < string, string > > tokenList;
public:
	LEXER() { proga = ""; }
	LEXER(string lexem);
	void analyse();
	void fileout();
	vector < pair < string, string > > getTokenList();
};

