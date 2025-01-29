#include <iostream>
#include <fstream>
#include "LEXER.h"
#include "SYNTAX.h"
#include "AN_NODE.h"
#include "SEMANTIC.h"
using namespace std;
int main() {
	ifstream fin("input.txt", ios::in);
	string proga = "";
	while (!fin.eof()) {
		string temp;
		fin >> temp;
		proga += temp + " ";
	}
	vector <string> vec = { "a", "=", "v", "*", "(", "b", "+", "c", ")"};
	proga += " ";
	LEXER lex(proga);
	lex.analyse();
	lex.fileout();
	SYNTAX SY(lex.getTokenList());
	SY.Parse();
	//SY.Print_Node();
	SY.Print_Node_ToFile();
	//SEMANTIC sem(vec);
	//sem.ToPostfix();
	//sem.Print();
}