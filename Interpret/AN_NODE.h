#include <iostream>
#include <vector>
#include <fstream>

#pragma once

using namespace std;
class AN_NODE
{
	
	string lexem;
	string type;
	vector <AN_NODE*> children;
public:
	AN_NODE() {
		lexem = {};
		type = {};
		children = vector <AN_NODE*>(0);
	}
	AN_NODE(string lexem, string type) {
		this->lexem = lexem;
		this->type = type;
	}
	void add_child(AN_NODE *child);
	string get_lex();
	string get_type();
	vector <AN_NODE*> get_children();
	void print_node(int level = 0) const;
	void fileprint_node(int level = 0) const;
};

