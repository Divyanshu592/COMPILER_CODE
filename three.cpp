#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

// Structure to represent a TAC instruction
struct TAC {
    string result;
    string arg1;
    string op;
    string arg2;
};

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to check precedence of operators
int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

// Function to convert infix expression to postfix
string infixToPostfix(const string& infix) {
    stack<char> s;
    string postfix;
    for (char c : infix) {
        if (isdigit(c) || isalpha(c)) {
            postfix += c;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        } else if (isOperator(c)) {
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

// Function to generate three-address code from postfix expression
vector<TAC> generateTAC(const string& postfix) {
    stack<string> s;
    vector<TAC> code;
    int tempVarCount = 1;

    for (char c : postfix) {
        if (isdigit(c) || isalpha(c)) {
            s.push(string(1, c));
        } else if (isOperator(c)) {
            string arg2 = s.top(); s.pop();
            string arg1 = s.top(); s.pop();
            string tempVar = "t" + to_string(tempVarCount++);
            code.push_back({tempVar, arg1, string(1, c), arg2});
            s.push(tempVar);
        }
    }
    return code;
}

int main() {
    string expression;
    cout << "Enter a valid infix expression: ";
    cin >> expression;

    // Remove whitespace from the input expression
    expression.erase(remove_if(expression.begin(), expression.end(), ::isspace), expression.end());

    string postfix = infixToPostfix(expression);
    vector<TAC> tacCode = generateTAC(postfix);

    cout << "\nThree Address Code:\n";
    for (const TAC& tac : tacCode) {
        cout << tac.result << " = " << tac.arg1 << " " << tac.op << " " << tac.arg2 << endl;
    }

    return 0;
}