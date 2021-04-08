#include <iostream>
#include <vector>

using namespace std;

vector<int> dp;
const int MOD = 1000000007;

int tiling(int n) {
  int& cache = dp[n];

  if ( cache != -1 ) {
    return cache;
  }

  if ( n <= 1 ) {
    return cache = 1;
  }

  return cache = (tiling(n-1) + tiling(n-2)) % MOD;
}

void solution() {
  int n;
  cin >> n;

  dp.assign(n+1, -1);
  cout << tiling(n) << endl;
}

int main() {
  int case_count;
  std::cin >> case_count;

  for ( int c = 0 ; c < case_count ; c++ ) {
    solution();
  }
}
