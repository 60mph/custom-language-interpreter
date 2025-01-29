#include "LEXER.h"
#include <string>

LEXER::LEXER(string proga)
{
	this->proga = proga;
}

void LEXER::analyse()
{
	string lexem = "";
	enum ST { BEGIN, KEYWORD, ID, INT, REAL, SPLIT, ERR , OP };
	ST CURST = BEGIN;
	for (int i = 0; i < proga.size(); i++) {
		char ch = proga[i];
		switch (CURST) {
		case BEGIN: {
			////cout << ch << endl;
			if (isspace(ch)) {
				lexem = "";
				CURST = BEGIN;
			}
			else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || (proga[i] == ':' && proga[i + 1] == '='))
			{
				lexem += ch;
				CURST = OP;
			}
			else if (isalpha(ch)) {
				lexem += ch;
				CURST = KEYWORD;
			}
			else if (isdigit(ch))
			{
				lexem += ch;
				CURST = INT;
			}
			else if (ch == '(' || ch == ')' || ch == ',' || ch == ';' || ch == ':')
			{
				i--;
				lexem += ch;
				CURST = SPLIT;
			}
			break;
		}
		case KEYWORD: {
			if (!isspace(ch))
			{
				if (isalpha(ch))
					lexem += ch;
				else
				{
					if (ch != ',' && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '=')
					{
						i--;
						CURST = ERR;
					}
					else
					{
						i--;
						CURST = ID;
					}
				}
			}
			else {
				if (lexem == "procedure" || lexem == "integer" || lexem == "real" ||
					lexem == "begin" || lexem == "end" || lexem == "var" || lexem == "ITOR" || 
					lexem == "RTOI")
				{
					hash_t.insert(lexem, "KEYWORD");
					tokenList.push_back(make_pair(lexem, "KEYWORD"));
					//cout << lexem << "-KEY" << endl;
					CURST = BEGIN;
					lexem = "";
				}
				else CURST = ID;
			}
			break;
		}
		case ID: {
			hash_t.insert(lexem, "ID");
			tokenList.push_back(make_pair(lexem, "ID"));
			//cout << lexem << "-ID" << endl;
			lexem = "";
			//i--;
			if (ch == ',')
				CURST = SPLIT;
			else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=')
				CURST = OP;
			CURST = BEGIN;
		}
		case INT: {
			if (!isspace(ch) && isdigit(ch) || ch == '.')
			{
				if (ch == '.')
				{
					CURST = REAL;
				}
				lexem += ch;
			}
			else
			{
				i--;
				CURST = BEGIN;
				if (lexem != "")
				{
					hash_t.insert(lexem, "INT_NUM");
					tokenList.push_back(make_pair(lexem, "INT_NUM"));
					//cout << lexem << "-INT" << endl;
				}
				lexem = "";
			}
			break;
		}
		case REAL: {
			if (!isspace(ch))
				lexem += ch;
			else {
				hash_t.insert(lexem, "REAL");
				tokenList.push_back(make_pair(lexem, "REAL"));
				//cout << lexem << "-REAL" << endl;
				lexem = "";
				CURST = BEGIN;
				//i-=2;
			}
			break;
		}
		case SPLIT: {
			//if (ch == '(' || ch == ')' || ch == ',' || ch == ';')
			//{
				// lexem += ch;
			hash_t.insert(lexem, "SPLITTER");
				//cout << lexem << "-SPLITTER" << endl;
				tokenList.push_back(make_pair(lexem, "SPLITTER"));
				lexem = "";
				//i--;
				CURST = BEGIN;
			//}	
			//else
			//	CURST = BEGIN;
			break;
		}
		case OP: {
			
			if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=')
				lexem += ch;
			else 
			{
				hash_t.insert(lexem, "OPER");
				tokenList.push_back(make_pair(lexem, "OPER"));
				//cout << lexem << "-OPER" << endl;
				lexem = "";
				i--;
				//lexem += ch;
				CURST = BEGIN;
			}
		}
		case ERR: {
			//if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=')
				//CURST = OP;
			//else
			if (!isspace(ch))
				lexem += ch;
			else 
			{
				if (lexem != "")
				////cout << "ERR_ID:" << lexem << endl;
				lexem = "";
				CURST = BEGIN;
			}
			break;
		}
		}
	}
}

void LEXER::fileout()
{
	hash_t.fileout();
}

vector <pair<string,string>> LEXER::getTokenList() {
	return tokenList;
}
