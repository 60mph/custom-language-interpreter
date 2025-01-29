#pragma once
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "AN_NODE.h"
#include "SEMANTIC.h"
using namespace std;
class SYNTAX
{
	vector < pair < string, string > > tokenList;
	void Procedure(size_t&index);
	void proc(size_t&index);
	void proc_name(size_t&index);
	void semicolon(size_t&index);
	void Begin(size_t&index);
	void begin(size_t& index);
	void Descriptions(size_t&index);
	void var(size_t& index);
	void DescrList(size_t& index);
	void Descr(size_t& index);
	void VarList(size_t& index);
	void Type(size_t& index);
	void Operators(size_t&index);
	void Op(size_t& index);
	void SimpleExpr(size_t& index);
	void Expr(size_t& index);
	void End(size_t&index);
	void ID(size_t&index);
	void Letter(size_t&index);
	map <string, string> id_types;
	vector <string> toSemantic;
	vector <AN_NODE*> Letters;
	AN_NODE Node;

public:
	SYNTAX(vector < pair < string, string > > tokenList) {
		this->tokenList = tokenList;
	}
	void Parse();
	void Print_Node();
	void Print_Node_ToFile();
};