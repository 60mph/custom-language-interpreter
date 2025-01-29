#pragma once
#include <iostream>

using namespace std;
class TOKEN
{
	private:
		string id;
		string type;
		int pos;
	public:
		TOKEN(string id, string type, int pos);
		TOKEN() { id = ""; type = ""; pos = 0; };
		string getId();
		string getType();
		int getPos();
		void setId(string);
		void setType(string);
		void setPos(int);
};

