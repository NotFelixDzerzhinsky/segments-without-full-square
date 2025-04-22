#include "testlib.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

map<string, string> params;

long long get(string name, long long def = 0) {
    if (params.count(name)) {
        return stoll(params[name]);
    } else {
        return def;
    }
}

bool full_square_check (int x) {
    int sx = sqrt(x);
    for (int k = max(0, sx - 2); k <= sx + 2; ++k) {
        if (k * k == x) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);

    for (int i = 1; i < argc; ++i) {
        string s = string(argv[i]);
        if (s.find("=") != string::npos) {
            auto pos = s.find("=");
            params[s.substr(0, pos)] = s.substr(pos + 1);
        } else {
            params[s] = "";
        }
    }

    int n = get("n", 100000);
    int c = get("c", 100000); // a_i <= c

    cout << n << '\n';
    // TODO: create smart generator
    for (int i = 0; i < n; ++i) {
        int v = rnd.next(2, c);
        if (full_square_check(v)) {
            if (rnd.next(0, 1) || v == c) {
                cout << v - 1;
            } else {
                cout << v + 1;
            }
        } else {
            cout << v;
        }
        if (i != n - 1) {
            cout << ' ';
        }
    }
    cout << '\n';
}

