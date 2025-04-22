#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

const int BUBEN = 15;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto& x : a) cin >> x;

  vector<vector<int>> prime_divs(n);
  for (int i = 0; i < n; i++) {
    for (int j = 2; j * j <= a[i]; j++) {
      if (a[i] % j == 0) {
        int cur = 0;
        while (a[i] % j == 0) {
          a[i] /= j;
          cur ^= 1;
        }
        if (cur) {
          prime_divs[i].push_back(j);
        }
      }
    }
    if (a[i] != 1) {
      prime_divs[i].push_back(a[i]);
    }
  }

  vector<int> dp(n, n);
  for (int i = 0; i < n; i++) {
    for (int j = i; j >= max(0, i - BUBEN); j--) {
      bool ok = true;
      set<int> st;
      for (int k = j; k <= i; k++) {
        for (const auto& div : prime_divs[k]) {
          if (st.contains(div)) {
            st.erase(div);
          } else {
            st.insert(div);
          }
        }

        if (st.empty()) {
          ok = false;
          break;
        }
      }

      if (ok) {
        dp[i] = min(dp[i], 1 + (j == 0 ? 0 : dp[j - 1]));
      } else {
        break;
      }
    }
  }

  cout << dp.back() << '\n';
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  solve();
  return 0;
}

