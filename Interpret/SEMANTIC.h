#pragma once
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
//#include <iostream>
#include <fstream>
using namespace std;
class SEMANTIC
{
	vector <string> expression;
	vector <string> postfix;
public:
	SEMANTIC(vector <string> expression) {
		this->expression = expression;
	}
	void ToPostfix();
	void Print();
	void FilePrint();
};

