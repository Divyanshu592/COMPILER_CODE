#include <iostream>
#include <cstring>
using namespace std;

char stack[30];
int top = -1;

void push(char c) {
    top++;
    stack[top] = c;
}

char pop() {
    char c;
    if (top != -1) {
        c = stack[top];
        top--;
        return c;
    }
    return 'x';
}

void printstat() {
    cout << "\n\t\t\t $";
    for (int i = 0; i <= top; i++)
        cout << stack[i];
}

int main() {
    int i, l;
    char s1[20], s2[20], ch1, ch2, ch3;

    cout << "\n\n\t\t LR PARSING";
    cout << "\n\t\t ENTER THE EXPRESSION: ";
    cin >> s1;

    l = strlen(s1);
    cout << "\n\t\t $";
    for (i = 0; i < l; i++) {
        if (s1[i] == 'i' && s1[i + 1] == 'd') {
            s1[i] = ' ';
            s1[i + 1] = 'E';
            printstat();
            cout << "id";
            push('E');
            printstat();
        } else if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/' || s1[i] == 'd') {
            push(s1[i]);
            printstat();
        }
    }

    printstat();
    l = strlen(s2);
    while (l) {
        ch1 = pop();
        if (ch1 == 'x') {
            cout << "\n\t\t\t $";
            break;
        }
        if (ch1 == '+' || ch1 == '/' || ch1 == '*' || ch1 == '-') {
            ch3 = pop();
            if (ch3 != 'E') {
                cout << "errror";
                return 0;
            } else {
                push('E');
                printstat();
            }
        }
        ch2 = ch1;
    }
    return 0;
}
