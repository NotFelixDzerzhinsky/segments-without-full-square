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

    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        int v = rnd.next(2, 3);
        cout << v;
        if (i != n - 1) {
            cout << ' ';
        }
    }
    cout << '\n';
}

