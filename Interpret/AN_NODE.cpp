#include "AN_NODE.h"

void AN_NODE::add_child(AN_NODE* child)
{
    children.push_back(child);
}

string AN_NODE::get_lex()
{
    return lexem;
}

string AN_NODE::get_type()
{
    return type;
}

vector<AN_NODE*> AN_NODE::get_children()
{
    return children;
}

void AN_NODE::print_node(int level) const
{
    for (int i = 0; i < level; ++i) {
        cout << "      ";
    }

    cout << lexem << (type != "" ? (" (Type: " + type + ")") : "") << endl;

    for (int i = 0; i < children.size(); i++) {
        children[i]->print_node(level + 1);
    }
}
ofstream fout(string("NodeOut.txt"), ios::trunc);
void AN_NODE::fileprint_node(int level) const
{
    
    for (int i = 0; i < level; ++i) {
        fout << "      ";
    }

    fout << lexem << (type != "" ? (" (Type: " + type + ")") : "") << endl;

    for (int i = 0; i < children.size(); i++) {
        children[i]->fileprint_node(level + 1);
    }
}
