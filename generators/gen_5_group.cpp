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
    int c_1 = get("c_1", 100000); // a_i <= c
    int spec_seg_len_1 = get("spec_seg_len_1", 1000);
    int spec_seg_cnt_1 = get("spec_seg_cnt_1", 1);
    int c_2 = get("c_2", 100000); // a_i <= c
    int spec_seg_len_2 = get("spec_seg_len_2", 1000);
    int spec_seg_cnt_2 = get("spec_seg_cnt_2", 1);
    vector<int> a (n);
    int last = 1;

    assert(7 * (spec_seg_len_1 * spec_seg_cnt_1 + spec_seg_cnt_2 * spec_seg_cnt_2) <= n);

    {
        vector<int> spec_seg_positions;
        for (int i = 0; i < spec_seg_cnt_1; ++i) {
            if (!i) {
                spec_seg_positions.push_back(rnd.next(1, spec_seg_len_1));
                continue;
            }
            int next = spec_seg_positions.back() + 2 * spec_seg_len_1 + 2;
            spec_seg_positions.push_back(next + rnd.next(0, spec_seg_len_1));
        }

        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(2, c_1);
            if (full_square_check(a[i])) {
                if (rnd.next(0, 1) || a[i] == c_1) {
                    --a[i];
                } else {
                    ++a[i];
                }
            }
        }

        for (auto left : spec_seg_positions) {
            int right = left + spec_seg_len_1;
            a[left - 1] = a[left];
            for (int x = left + spec_seg_len_1; x < right + spec_seg_len_1; ++x) {
                a[x] = a[x - spec_seg_len_1];
            }
        }
        last = spec_seg_positions.back() + spec_seg_len_1 + 9;
    }

    {
        vector<int> spec_seg_positions;
        for (int i = 0; i < spec_seg_cnt_2; ++i) {
            if (!i) {
                spec_seg_positions.push_back(rnd.next(last, last + spec_seg_len_2));
                continue;
            }
            int next = spec_seg_positions.back() + 2 * spec_seg_len_2 + 2;
            spec_seg_positions.push_back(next + rnd.next(0, spec_seg_len_2));
        }

        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(2, c_2);
            if (full_square_check(a[i])) {
                if (rnd.next(0, 1) || a[i] == c_2) {
                    --a[i];
                } else {
                    ++a[i];
                }
            }
        }

        for (auto left : spec_seg_positions) {
            int right = left + spec_seg_len_2;
            a[left - 1] = a[left];
            for (int x = left + spec_seg_len_2; x < right + spec_seg_len_2; ++x) {
                a[x] = a[x - spec_seg_len_2];
            }
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

