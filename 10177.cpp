#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename A, typename B>
ostream &operator<<(ostream &out, const pair<A, B> &a) {
  out << "(" << a.first << "," << a.second << ")";
  return out;
}
template <typename T, size_t N>
ostream &operator<<(ostream &out, const array<T, N> &a) {
  out << "[";
  bool first = true;
  for (auto &v : a) {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}
template <typename T>
ostream &operator<<(ostream &out, const vector<T> &a) {
  out << "[";
  bool first = true;
  for (auto &v : a) {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}
template <typename T, class Cmp>
ostream &operator<<(ostream &out, const set<T, Cmp> &a) {
  out << "{";
  bool first = true;
  for (auto &v : a) {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "}";
  return out;
}
template <typename U, typename T, class Cmp>
ostream &operator<<(ostream &out, const map<U, T, Cmp> &a) {
  out << "{";
  bool first = true;
  for (auto &p : a) {
    out << (first ? "" : ", ");
    out << p.first << ":" << p.second;
    first = 0;
  }
  out << "}";
  return out;
}
#ifdef LOCAL
#define trace(...)                   \
  cerr << "@" << __LINE__ << " -> "; \
  __f(#__VA_ARGS__, __VA_ARGS__)
#define nl() cerr << endl;
#else
#define trace(...)
#define nl()
#endif
template <typename Arg1>
void __f(const char *name, Arg1 &&arg1) {
  cerr << name << ": " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char *names, Arg1 &&arg1, Args &&... args) {
  const char *comma = strchr(names + 1, ',');
  cerr.write(names, comma - names) << ": " << arg1 << " |";
  __f(comma + 1, args...);
}

struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;

#define ll long long
#define sz(x) (ll)((x).size())
#define all(x) (x).begin(), (x).end()

ll n;

void solve() {
  ll sq = 0, total = 0, sq3d = 0, total3d = 0, sq4d = 0, total4d = 0;
  vector<ll> squares2d(n + 1);
  vector<ll> squares3d(n + 1);
  for (ll row = 0; row < n; row++) {
    for (ll col = 0; col < n; col++) {
      for (ll upper_right = col + 1; upper_right <= n; upper_right++) {
        for (ll lower_left = row + 1; lower_left <= n; lower_left++) {
          total++;
          if ((upper_right - col) == (lower_left - row)) {
            sq++;
            squares2d[upper_right - col]++;
          }
        }
      }
    }
  }

  for (ll ds = 0; ds < n; ds++) {
    for (ll de = ds + 1; de <= n; de++) {
      total3d += total;
      sq3d += squares2d[de - ds];
      squares3d[de - ds] += squares2d[de - ds];
    }
  }

  for (ll d4s = 0; d4s < n; d4s++) {
    for (ll d4e = d4s + 1; d4e <= n; d4e++) {
      total4d += total3d;
      sq4d += squares3d[d4e - d4s];
    }
  }

  // ll d4sq = 0, d4total = 0;
  // for (ll row = 0; row < n; row++) {
  //   for (ll col = 0; col < n; col++) {
  //     for (ll upper_right = col + 1; upper_right <= n; upper_right++) {
  //       for (ll lower_left = row + 1; lower_left <= n; lower_left++) {
  //         for (ll ds = 0; ds < n; ds++) {
  //           for (ll de = ds + 1; de <= n; de++) {
  //             for (ll d4s = 0; d4s < n; d4s++) {
  //               for (ll d4e = d4s + 1; d4e <= n; d4e++) {
  //                 d4total++;
  //                 if ((upper_right - col) == (lower_left - row) &&
  //                     (lower_left - row) == (de - ds) &&
  //                     (lower_left - row) == (d4e - d4s))
  //                   d4sq++;
  //               }
  //             }
  //           }
  //         }
  //       }
  //     }
  //   }
  // }

  // added answers to an array and printed the array
  vector<ll> ans{sq, total - sq, sq3d, total3d - sq3d, sq4d, total4d - sq4d};
  for (ll i = 0; i < 6; i++) {
    cout << ans[i];
    if (i < 5) cout << ' ';
  }
  cout << '\n';
}

signed main() {
  while (cin >> n) solve();
}