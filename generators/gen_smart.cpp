#include "testlib.h"

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

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
    int prime_gen = get("prime_gen", 0);
    int spec_seg_len = get("spec_seg_len", 1000);
    int spec_seg_cnt = get("spec_seg_cnt", 1);

    vector<int> primes;
    if (prime_gen) {
        vector<int> prime (c + 1);
        prime[0] = prime[1] = 1;
        for (int i = 2; i <= c; ++i) {
            if (prime[i] == 0) {
                for (int j = i * 2; j <= c; j += i) {
                    prime[j] = 1;
                }
            }
        }
        for (int i = 1; i <= c; ++i) {
            if (!prime[i]) {
                primes.push_back(i);
            }
        }
    }


    assert(7 * spec_seg_len * spec_seg_cnt <= n);

    vector<int> spec_seg_positions;
    for (int i = 0; i < spec_seg_cnt; ++i) {
        if (!i) {
            spec_seg_positions.push_back(rnd.next(1, spec_seg_len));
            continue;
        }
        int last = spec_seg_positions.back() + 2 * spec_seg_len + 2;
        spec_seg_positions.push_back(last + rnd.next(0, spec_seg_len));
    }

    vector<int> a (n);
    for (int i = 0; i < n; ++i) {
        if (prime_gen) {
            int ind = rnd.next(0, (int)primes.size() - 1);
            a[i] = primes[ind];
        } else {
            a[i] = rnd.next(2, c);
            if (full_square_check(a[i])) {
                if (rnd.next(0, 1) || a[i] == c) {
                    --a[i];
                } else {
                    ++a[i];
                }
            }
        }
    }

    for (auto left : spec_seg_positions) {
        int right = left + spec_seg_len;
        a[left - 1] = a[left];
        for (int x = left + spec_seg_len; x < right + spec_seg_len; ++x) {
            a[x] = a[x - spec_seg_len];
        }
    }

    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        cout << a[i];
        if (i != n - 1) {
            cout << ' ';
        }
    }
    cout << '\n';
}

