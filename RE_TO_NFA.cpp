#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char reg[20];
    int q[20][3] = {0}, i = 0, j = 1, len, a, b;
    cout<<"ENTER THE EXPRESSION:";
    cin >> reg;
    cout << "Given regular expression: " << reg << endl;
    len = strlen(reg);
    
    while (i < len) {
        if (reg[i] == 'a' && reg[i + 1] != '|' && reg[i + 1] != '*') {
            q[j][0] = j + 1;
            j++;
        }
        if (reg[i] == 'b' && reg[i + 1] != '|' && reg[i + 1] != '*') {
            q[j][1] = j + 1;
            j++;
        }
        if (reg[i] == 'e' && reg[i + 1] != '|' && reg[i + 1] != '*') {
            q[j][2] = j + 1;
            j++;
        }
        if (reg[i] == 'a' && reg[i + 1] == '|' && reg[i + 2] == 'b') {
            q[j][2] = (j + 1) * 10 + (j + 3);
            j++;
            q[j][0] = j + 1;
            j++;
            q[j][2] = j + 3;
            j++;
            q[j][1] = j + 1;
            j++;
            q[j][2] = j + 1;
            j++;
            i += 2;
        }
        if (reg[i] == 'b' && reg[i + 1] == '|' && reg[i + 2] == 'a') {
            q[j][2] = (j + 1) * 10 + (j + 3);
            j++;
            q[j][1] = j + 1;
            j++;
            q[j][2] = j + 3;
            j++;
            q[j][0] = j + 1;
            j++;
            q[j][2] = j + 1;
            j++;
            i += 2;
        }
        if (reg[i] == 'a' && reg[i + 1] == '*') {
            q[j][2] = (j + 1) * 10 + (j + 3);
            j++;
            q[j][0] = j + 1;
            j++;
            q[j][2] = (j + 1) * 10 + (j - 1);
            j++;
        }
        if (reg[i] == 'b' && reg[i + 1] == '*') {
            q[j][2] = (j + 1) * 10 + (j + 3);
            j++;
            q[j][1] = j + 1;
            j++;
            q[j][2] = (j + 1) * 10 + (j - 1);
            j++;
        }
        if (reg[i] == ')' && reg[i + 1] == '*') {
            q[0][2] = (j + 1) * 10 + 1;
            q[j][2] = (j + 1) * 10 + 1;
            j++;
        }
        i++;
    }
    
    cout << "\n\tTransition Table \n";
    cout << "_____________________________________\n";
    cout << "Current State |\tInput |\tNext State";
    cout << "\n_____________________________________\n";
    
    for (i = 0; i <= j; i++) {
        if (q[i][0] != 0) cout << "\n  q[" << i << "]\t      |   a   |  q[" << q[i][0] << "]";
        if (q[i][1] != 0) cout << "\n  q[" << i << "]\t      |   b   |  q[" << q[i][1] << "]";
        if (q[i][2] != 0) {
            if (q[i][2] < 10) cout << "\n  q[" << i << "]\t      |   e   |  q[" << q[i][2] << "]";
            else cout << "\n  q[" << i << "]\t      |   e   |  q[" << q[i][2] / 10 << "] , q[" << q[i][2] % 10 << "]";
        }
    }
    
    cout << "\n_____________________________________\n";
    return 0;
}