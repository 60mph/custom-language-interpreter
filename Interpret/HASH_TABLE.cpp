#include "HASH_TABLE.h"

void HASH_TABLE::fileout()
{
	ofstream fin("OUTPUT.txt", ios::trunc);
	for (int i = 0; i < vec.size(); ++i) {
		int sum = 0;
		for (int j = 0; j < vec[i].getId().size(); ++j)
		{
			sum += int(vec[i].getId()[j]);
		}
		fin << vec[i].getType() << "\t       " << vec[i].getId() << "\t       " << sum << "-" << vec[i].getPos() << endl;
	}
}

void HASH_TABLE::insert(string id, string type)
{
	pair <string, string> p;
	p.first = id;
	p.second = type;
	TOKEN vtoken(id, type, st.size());
	if (st.find(p) == st.end())
	{
		st.insert(p);
		vec.push_back(vtoken);
	}
}
