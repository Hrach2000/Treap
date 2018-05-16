#include "tree.hpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int main() {
  srand(time(NULL));
  ll n;
  cin >> n;
  Tree mtree;
  for (ll i = 0; i < n; ++i) {
    mtree.insert(rand());
  }
  cout << mtree.height() << endl;
  return 0;
}
