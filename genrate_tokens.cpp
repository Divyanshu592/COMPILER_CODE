#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

bool isDelimiter(char ch) {
    return (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
            ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
            ch == '[' || ch == ']' || ch == '{' || ch == '}');
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '>' || ch == '<' || ch == '=');
}

bool validIdentifier(char* str) {
    return !(str[0] >= '0' && str[0] <= '9' || isDelimiter(str[0]));
}

bool isKeyword(char* str) {
    const char* keywords[] = {"if", "else", "while", "do", "break", "continue",
                              "int", "double", "float", "return", "char", "case",
                              "sizeof", "long", "short", "typedef", "switch",
                              "unsigned", "void", "static", "struct", "goto"};
    for (const char* keyword : keywords)
        if (!strcmp(str, keyword))
            return true;
    return false;
}

bool isInteger(char* str) {
    for (int i = 0; i < strlen(str); i++)
        if (!(str[i] >= '0' && str[i] <= '9') || (str[i] == '-' && i > 0))
            return false;
    return true;
}

bool isRealNumber(char* str) {
    bool hasDecimal = false;
    for (int i = 0; i < strlen(str); i++) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.' || (str[i] == '-' && i > 0))
            return false;
        if (str[i] == '.')
            hasDecimal = true;
    }
    return hasDecimal;
}

char* subString(char* str, int left, int right) {
    char* subStr = (char*)malloc(right - left + 2);
    for (int i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return subStr;
}

void parse(char* str) {
    int left = 0, right = 0;
    int len = strlen(str);
    while (right <= len && left <= right) {
        if (!isDelimiter(str[right]))
            right++;
        if (isDelimiter(str[right]) && left == right) {
            if (isOperator(str[right]))
                cout << "'" << str[right] << "' IS AN OPERATOR\n";
            right++;
            left = right;
        } else if ((isDelimiter(str[right]) && left != right) || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);
            if (isKeyword(subStr))
                cout << "'" << subStr << "' IS A KEYWORD\n";
            else if (isInteger(subStr))
                cout << "'" << subStr << "' IS AN INTEGER\n";
            else if (isRealNumber(subStr))
                cout << "'" << subStr << "' IS A REAL NUMBER\n";
            else if (validIdentifier(subStr) && !isDelimiter(str[right - 1]))
                cout << "'" << subStr << "' IS A VALID IDENTIFIER\n";
            else
                cout << "'" << subStr << "' IS NOT A VALID IDENTIFIER\n";
            left = right;
        }
    }
}

int main() {
    char str[100];
    cout << "Enter a string: ";
    cin.getline(str, 100);
    parse(str);
    return 0;
}
