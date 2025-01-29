#include "TOKEN.h"

string TOKEN::getId()
{
	return id;
}

string TOKEN::getType()
{
	return type;
}

int TOKEN::getPos()
{
	return pos;
}

TOKEN::TOKEN(string id, string type, int pos)
{
	this->id = id;
	this->type = type;
	this->pos = pos;
}

