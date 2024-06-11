#include <iostream>
#include <vector>

using namespace std;

int main() {
    int nfa[5][2] = {{0, 0}, {12, 1}, {0, 3}, {0, 4}, {0, 0}};
    vector<vector<int>> dfa(10, vector<int>(2, 0));
    vector<int> dstate(10, 0);
    int i = 1, n, j, k, flag = 0, m, q, r;
    dstate[i++] = 1;
    n = i;
    dfa[1][0] = nfa[1][0];
    dfa[1][1] = nfa[1][1];

    cout << "\nf(" << dstate[1] << ",a)=" << dfa[1][0];
    cout << "\nf(" << dstate[1] << ",b)=" << dfa[1][1];

    for (j = 1; j < n; j++) {
        if (dfa[1][0] != dstate[j]) flag++;
    }
    if (flag == n - 1) dstate[i++] = dfa[1][0], n++;
    flag = 0;
    for (j = 1; j < n; j++) {
        if (dfa[1][1] != dstate[j]) flag++;
    }
    if (flag == n - 1) dstate[i++] = dfa[1][1], n++;

    k = 2;
    while (dstate[k] != 0) {
        m = dstate[k];
        if (m > 10) {
            q = m / 10;
            r = m % 10;
        }
        if (nfa[r][0] != 0)
            dfa[k][0] = nfa[q][0] * 10 + nfa[r][0];
        else
            dfa[k][0] = nfa[q][0];
        if (nfa[r][1] != 0)
            dfa[k][1] = nfa[q][1] * 10 + nfa[r][1];
        else
            dfa[k][1] = nfa[q][1];

        cout << "\nf(" << dstate[k] << ",a)=" << dfa[k][0];
        cout << "\nf(" << dstate[k] << ",b)=" << dfa[k][1];

        flag = 0;
        for (j = 1; j < n; j++) {
            if (dfa[k][0] != dstate[j]) flag++;
        }
        if (flag == n - 1) dstate[i++] = dfa[k][0], n++;
        flag = 0;
        for (j = 1; j < n; j++) {
            if (dfa[k][1] != dstate[j]) flag++;
        }
        if (flag == n - 1) dstate[i++] = dfa[k][1], n++;
        k++;
    }
    return 0;
}
