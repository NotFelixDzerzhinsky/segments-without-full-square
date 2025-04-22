#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int MAXN = 1e5;
const int MAXC = 1e5; // a_i <= MAXC

bool full_square_check (int x) {
    int sx = sqrt(x);
    for (int k = max(0, sx - 2); k <= sx + 2; ++k) {
        if (k * k == x) {
            return true;
        }
    }
    return false;
}

bool prime_check(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

const int N[7] = {MAXN, 10, 10, MAXN, MAXN, MAXN, MAXN};
const int A[7] = {MAXC, 10, MAXC, 3, MAXC, 200, MAXC};

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int g = atoi(validator.group().c_str());
    
    int n = inf.readInt(1, N[g], "n");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        int num = inf.readInt(2, A[g], "a_i");
        ensuref(!full_square_check(num), "number is square");
        if (g == 4) {
            ensuref(prime_check(num), "number is not prime in group 4");
        }
        if (i != n - 1) {
            inf.readSpace();
        }
    }
    inf.readEoln();
    inf.readEof();
}

