#include "SEMANTIC.h"
ofstream cout("PostFix.txt", ios::trunc);
bool isOperator(const string& token) {
    static unordered_map<string, int> precedence{
        {"+", 3}, {"-", 3},
        {"*", 4}, {"/", 4},
        {"RTOI", 5}, {"ITOR", 5},
        {"=", 1}, {";", 1}
    };
    return precedence.find(token) != precedence.end();
}

bool hasHigherPrecedence(const string& op1, const string& op2) {
    static unordered_map<string, int> precedence{
        {"+", 3}, {"-", 3},
        {"*", 4}, {"/", 4},
        {"RTOI", 5}, {"ITOR", 5},
        {"=", 1}, {";", 1}
    };
    return precedence[op1] >= precedence[op2];
}

void SEMANTIC::ToPostfix()
{
    stack<string> operators;

    for (const string& token : expression) {
        if (isOperator(token)) {
            while (!operators.empty() && operators.top() != "(" && hasHigherPrecedence(operators.top(), token)) {
                postfix.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
        else if (token == "(") {
            operators.push(token);
        }
        else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                postfix.push_back(operators.top());
                operators.pop();
            }
            if (!operators.empty() && operators.top() == "(") {
                operators.pop();
            }
        }
        else {
            postfix.push_back(token);
        }
    }

    while (!operators.empty()) {
        postfix.push_back(operators.top());
        operators.pop();
    }
}

void SEMANTIC::Print()
{
    for (int i = 0; i < postfix.size(); i++) {
        cout << postfix[i] << " ";
    }
    cout << endl;
}
