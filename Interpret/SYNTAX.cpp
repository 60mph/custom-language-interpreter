#include "SYNTAX.h"
size_t index = 0;
size_t descrindex, dindex = 0, lastVarList = 0, operatorsindex = 0, opindex = 0, exprindex = 0, sexprindex = 0, procindex = 0, desrclistundex = 0;
string expected_type = "";

ofstream erout(string("SemanticErrors.txt"), ios::trunc);

void SYNTAX::Parse()
{
	Procedure(index);
}

void SYNTAX::Procedure(size_t &index) {
	Letters.push_back(new AN_NODE("Procedure", ""));
	Begin(index);
	Descriptions(index);
	Operators(index);
	End(index);
}

void SYNTAX::Begin(size_t &index)
{
	Letters.push_back(new AN_NODE("Begin", ""));
	Letters[0]->add_child(Letters[Letters.size() - 1]);
	proc(index);
	proc_name(index);
	semicolon(index);
	begin(index);
}

void SYNTAX::begin(size_t & index)
{
	Letters.push_back(new AN_NODE("begin", ""));
	if (tokenList[index].first == "begin")
	{
		Letters[1]->add_child(Letters[Letters.size() - 1]);
		index++;
	}
	else { 
		cout << "Expected \"begin\"!" << endl;
		exit(1);
	}
}

void SYNTAX::proc(size_t &index)
{
	size_t tosem = index;
	while (tokenList[tosem].first != ";") {
		if (tokenList[tosem].first != ":" && tokenList[tosem].first != ",")
			toSemantic.push_back(tokenList[tosem].first);
		tosem++;
	}
	SEMANTIC sem(toSemantic);
	sem.ToPostfix();
	sem.Print();
	toSemantic = vector <string>();
	Letters.push_back(new AN_NODE("procedure", ""));
	if (tokenList[index].first == "procedure")
	{
		Letters[Letters.size() - 2]->add_child(Letters[Letters.size() - 1]);
		index++;
	}
	else {
		cout << "Expected \"procedure\"!" << endl;
		exit(1);
	}
}

void SYNTAX::proc_name(size_t &index)
{
	if (index == tokenList.size())
	{
		cout << "Expected \"ProcedureName\"!" << endl;
		exit(1);
	}
	Letters.push_back(new AN_NODE("ProcedureName", ""));
	Letters[Letters.size() - 3]->add_child(Letters[Letters.size() - 1]);
	ID(index);
}

void SYNTAX::semicolon(size_t &index)
{
	if (index == tokenList.size())
	{
		cout << "Expected \";\"!" << endl;
		exit(1);
	}
	Letters.push_back(new AN_NODE(";", ""));
	if (tokenList[index].first == ";")
	{
		Letters[1]->add_child(Letters[Letters.size() - 1]);
		index++;
	}
	else {
		cout << "Expected \";\"!" << endl;
		exit(1);
	}
}

AN_NODE Descriptionsw("Descriptions", "");

void SYNTAX::Descriptions(size_t &index)
{
	Letters.push_back(new AN_NODE("Descriptions", ""));
	Letters[0]->add_child(Letters[Letters.size() - 1]);
	descrindex = Letters.size() - 1;
	var(index);
	if (index == tokenList.size())
	{
		cout << "Expected \"ID\"!" << endl;
		exit(1);
	}
	DescrList(index);
	if (index == tokenList.size())
	{
		cout << "Expected \"ID\"!" << endl;
		exit(1);
	}
}

void SYNTAX::var(size_t& index)
{
	if (index == tokenList.size())
	{
		cout << "Expected \";\"!" << endl;
		exit(1);
	}
	if (tokenList[index].first == "var") {
		Letters.push_back(new AN_NODE("var", ""));
		Letters[descrindex]->add_child(Letters[Letters.size() - 1]);
		index++;
	}
	else {
		cout << "Expected \"var\"!" << endl;
		exit(1);
	}
}

void SYNTAX::DescrList(size_t& index)
{
	if (index == tokenList.size())
	{
		cout << "Expected \";\"!" << endl;
		exit(1);
	}
	Letters.push_back(new AN_NODE("DescrList", ""));
	if (desrclistundex == 0)
	{
		desrclistundex = descrindex;
	}
	Letters[desrclistundex]->add_child(Letters[Letters.size() - 1]);
	desrclistundex = Letters.size() - 1;
	Descr(index);
	if (index == tokenList.size())
	{
		cout << "Expected \";\"!" << endl;
		exit(1);
	}
	size_t olddescrindex = descrindex;
	bool f = 0;
	if (tokenList[index + 1].first == "," || tokenList[index + 1].first == ":")
	{
		lastVarList = 0;
		f = 1;
	}
	if (f) {
		DescrList(index);
	}
	descrindex = olddescrindex;
}

void SYNTAX::Descr(size_t& index)
{
	Letters.push_back(new AN_NODE("Descr", ""));
	Letters[desrclistundex]->add_child(Letters[Letters.size() - 1]);
	dindex = Letters.size() - 1;
	size_t tosem = index;
	while (tokenList[tosem].first != ";") {
		if(tokenList[tosem].first != ":" && tokenList[tosem].first != ",")
		toSemantic.push_back(tokenList[tosem].first);
		tosem++;
	}
	SEMANTIC sem(toSemantic);
	sem.ToPostfix();
	sem.Print();
	toSemantic = vector <string>();
	if (tokenList[index].second == "ID") {
		VarList(index);
	}
}

void SYNTAX::VarList(size_t& index)
{
	if (index == tokenList.size())
	{
		cout << "Expected \";\"!" << endl;
		exit(1);
	}
	id_types[tokenList[index].first] = "0";
	if (lastVarList == 0)
		lastVarList = dindex;
	Letters.push_back(new AN_NODE("VarList", ""));
	Letters[lastVarList]->add_child(Letters[Letters.size() - 1]);
	ID(index);
	if (index == tokenList.size())
	{
		cout << "Expected \",\" or \":\"!" << endl;
		exit(1);
	}
	if (tokenList[index].first == ",")
	{
		Letters.push_back(new AN_NODE(",", "SPLITTER"));
		Letters[Letters.size() - 5]->add_child(Letters[Letters.size() - 1]);
		lastVarList = Letters.size() - 5;
		index++;
		VarList(index);
	}
	else if (tokenList[index].first == ":")
	{
		lastVarList = 0;
		Letters.push_back(new AN_NODE(":", ""));
		Letters[dindex]->add_child(Letters[Letters.size() - 1]);
		index++;
		Type(index);
	}
	else {
		cout << "Expected \",\" or \":\"" << endl;
		exit(1);
	}
}

void SYNTAX::Type(size_t& index)
{
	Letters.push_back(new AN_NODE("Type", ""));
	Letters[dindex]->add_child(Letters[Letters.size() - 1]);
	if (index == tokenList.size())
	{
		cout << "Expected \";\"!" << endl;
		exit(1);
	}
	if (tokenList[index].first == "integer")
	{
		Letters.push_back(new AN_NODE("integer", ""));
		Letters[Letters.size() - 2]->add_child(Letters[Letters.size() - 1]);
		for (auto it = id_types.begin(); it != id_types.end(); it++)
		{
			if (it->second == "0")
				it->second = "integer";
		}
	}
	else if (tokenList[index].first == "real")
	{
		Letters.push_back(new AN_NODE("real", ""));
		Letters[Letters.size() - 2]->add_child(Letters[Letters.size() - 1]);
		for (auto it = id_types.begin(); it != id_types.end(); it++)
		{
			if (it->second == "0")
				it->second = "real";
		}
	}
	else
	{
		cout << "Expected Type!" << endl;
		exit(1);
	}
	index++;
	if (index == tokenList.size())
	{
		cout << "Expected \";\"!" << endl;
		exit(1);
	}
	if (tokenList[index].first == ";")
	{
		Letters.push_back(new AN_NODE(";", ""));
		Letters[dindex]->add_child(Letters[Letters.size() - 1]);
		index++;
	}
	else {
		cout << "Expected \";\"!" << endl;
		exit(1);
	}
	if (index == tokenList.size())
	{
		cout << "Expected \";\"!" << endl;
		exit(1);
	}
	
}

void SYNTAX::Operators(size_t &index)
{
	if (index >= tokenList.size() - 1)
	{
		cout << "Expected \"ID\"!" << endl;
		exit(1);
	}
	Letters.push_back(new AN_NODE("Operators", ""));
	Letters[procindex]->add_child(Letters[Letters.size() - 1]);
	operatorsindex = Letters.size() - 1;
	Op(index);
}

void SYNTAX::Op(size_t& index)
{
	size_t tosem = index;
	while (tokenList[tosem].first != ";") {
		toSemantic.push_back(tokenList[tosem].first);
		tosem++;
	}
	string first = *toSemantic.begin();
	toSemantic.erase(toSemantic.begin());
	string second = *toSemantic.begin();
	toSemantic.push_back(second);
	toSemantic.push_back(first);
	toSemantic.erase(toSemantic.begin());
	SEMANTIC sem(toSemantic);
	sem.ToPostfix();
	sem.Print();
	toSemantic = vector <string>();
	Letters.push_back(new AN_NODE("Op", ""));
	Letters[operatorsindex]->add_child(Letters[Letters.size() - 1]);
	if (index >= tokenList.size())
	{
		cout << "Expected \"ID\"!" << endl;
		exit(1);
	}
	opindex = Letters.size() - 1;
	if (id_types[tokenList[index].first] == "")
	{
		erout << "The variable has not been declared: " << "\"" << tokenList[index].first << "\". " << "\n";
		expected_type = "Unknown type";
	}
	else {
		expected_type = id_types[tokenList[index].first];
	}
	ID(index);
	if (index == tokenList.size())
	{
		cout << "Expected \"=\"!" << endl;
		exit(1);
	}
	if (tokenList[index].first == "=")
	{
		Letters.push_back(new AN_NODE("=", "OPER"));
		Letters[opindex]->add_child(Letters[Letters.size() - 1]);
		index++;
	}
	else {
		cout << "Expected \"=\"!" << endl;
		exit(1);
	}
	Expr(index);
	if (index == tokenList.size())
	{
		cout << "Expected \";\"!" << endl;
		exit(1);
	}
	if (tokenList[index].first == ";")
	{
		Letters.push_back(new AN_NODE(";", ""));
		Letters[opindex]->add_child(Letters[Letters.size() - 1]);
		index++;
	}
	else {
		cout << "Expected \";\"!" << endl;
		exit(1);
	}
	if (index == tokenList.size())
	{
		cout << "Expected \"end\"!" << endl;
		exit(1);
	}
	if (tokenList[index].second == "ID")
	{
		size_t oldoperatorsindex = operatorsindex;
		size_t oldopindex = opindex;
		procindex = operatorsindex;
		
		Operators(index);
		operatorsindex = oldoperatorsindex;
		opindex = oldopindex;
	}
	else {
			if (tokenList[index].first != "end")
			{
				cout << "Expected \"ID\"!" << endl;
				exit(1);
			}
	}
}

void SYNTAX::Expr(size_t& index)
{
	if (index == tokenList.size())
	{
		cout << "Expected \"Expr\"!" << endl;
		exit(1);
	}
	Letters.push_back(new AN_NODE("Expr", ""));
	Letters[opindex]->add_child(Letters[Letters.size() - 1]);
	exprindex = Letters.size() - 1;
	SimpleExpr(index);
	if (index == tokenList.size())
	{
		cout << "Expected \";\"!" << endl;
		exit(1);
	}
	if (tokenList[index].first == "+" || tokenList[index].first == "-") {
		Letters[exprindex]->add_child(new AN_NODE(tokenList[index].first, ""));
		size_t oldopindex = opindex;
		size_t oldexprindex = exprindex;
		opindex = exprindex;
		index++;
		Expr(index);
		opindex = oldopindex;
		exprindex = oldexprindex;
	}
}

void SYNTAX::SimpleExpr(size_t& index)
{
	Letters.push_back(new AN_NODE("SimpleExpr", ""));
	Letters[exprindex]->add_child(Letters[Letters.size() - 1]);
	sexprindex = Letters.size() - 1;
	if (tokenList[index].second == "ID")
	{
		if (id_types[tokenList[index].first] == "")
		{
			erout << "The variable has not been declared: " << "\"" << tokenList[index].first << "\". ";
			erout << "Expected: " << expected_type << "\n";
		}
		else if (expected_type != id_types[tokenList[index].first])
		{
			erout << "Invalid variable type detected! " << "Type of \"" << tokenList[index].first << "\" detected: " << id_types[tokenList[index].first] << ". ";
			erout << "Expected: " << expected_type << "\n";
		}

		ID(index);
	}
	else if (tokenList[index].second == "INT_NUM" || tokenList[index].second == "REAL") {
		if (tokenList[index].second == "INT_NUM" && expected_type != "integer") {
			erout << "Invalid number type detected! " << "Type of \"" << tokenList[index].first << "\" detected: " << "integer. ";
			erout << "Expected: " << expected_type << "\n";
		}
		if (tokenList[index].second == "REAL" && expected_type != "real") {
			erout << "Invalid number type detected! " << "Type of \"" << tokenList[index].first << "\" detected: " << "real. ";
			erout << "Expected: " << expected_type << "\n";
		}
		Letters.push_back(new AN_NODE(tokenList[index].second, ""));
		Letters[sexprindex]->add_child(Letters[Letters.size() - 1]);
		Letters[Letters.size() - 1]->add_child(new AN_NODE(tokenList[index].first, ""));
		index++;
	}
	else if (tokenList[index].first == "(") {
		Letters[sexprindex]->add_child(new AN_NODE("(", ""));
		index++;
		size_t oldopindex = opindex;
		size_t oldsexprindex = sexprindex;
		opindex = sexprindex;
		Expr(index);
		opindex = oldopindex;
		if (tokenList[index].first == ")")
			Letters[oldsexprindex]->add_child(new AN_NODE(")", "")), index++;
		else {
			cout << "Expected \")\"!" << endl;
			exit(1);
		}
	}
	else if (tokenList[index].first == "RTOI" || tokenList[index].first == "ITOR") {
		if (tokenList[index].first == "RTOI")
		{
			if (expected_type != "integer")
			{
				erout << "Invalid RTOI operation! The type of the variable on the left side is " 
					<< "\"" << expected_type << "\"" << "\n";
			}
		}
		else
		{
			if (expected_type != "real")
			{
				erout << "Invalid ITOR operation! The type of the variable on the left side is " << "\"" << expected_type << "\"" << "\n";
			}
		}
		Letters[sexprindex]->add_child(new AN_NODE(tokenList[index].first, ""));
		index++;
		if (tokenList[index].first == "(")
			Letters[sexprindex]->add_child(new AN_NODE("(", ""));
		else {
			cout << "Expected \"(\"!" << endl;
			exit(1);
		}
		index++;
		size_t oldopindex = opindex;
		size_t oldsexprindex = sexprindex;
		opindex = sexprindex;
		string oldexptype = expected_type;
		expected_type = tokenList[index - 2].first == "RTOI" ? "real" : "integer";
		Expr(index);
		expected_type = oldexptype;
		opindex = oldopindex;
		if (tokenList[index].first == ")")
			Letters[oldsexprindex]->add_child(new AN_NODE(")", "")), index++;
		else {
			cout << "Expected \")\"!" << endl;
			exit(1);
		}
	}
	else {
		cout << "Expected SimpleExpr!" << endl;
		exit(1);
	}
}

void SYNTAX::End(size_t &index)
{
	
	Letters.push_back(new AN_NODE("End", ""));
	if (tokenList[index].first == "end")
	{
		Letters[0]->add_child(Letters[Letters.size() - 1]);
		Letters[Letters.size() - 1]->add_child(new AN_NODE("end", ""));
	}
	else
	{
		cout << "Expected \"end\"!" << endl;
		exit(1);
	}
}

void SYNTAX::ID(size_t &index)
{
	Letters.push_back(new AN_NODE("ID", ""));
	Letters[Letters.size() - 2]->add_child(Letters[Letters.size() - 1]);
	Letter(index);
}
void SYNTAX::Letter(size_t &index) {
	Letters.push_back(new AN_NODE("Letter", ""));
	if (tokenList[index].second == "ID")
	{
		Letters.push_back(new AN_NODE(tokenList[index].first, tokenList[index].second));
		index++;
		Letters[Letters.size() - 3]->add_child(Letters[Letters.size() - 1]);
	}
	else {
		cout << "Expected \"ID\"!" << endl;
		exit(1);
	}
}

void SYNTAX::Print_Node()
{
	Letters[0]->print_node();
}

void SYNTAX::Print_Node_ToFile()
{
	Letters[0]->fileprint_node();
}
