#include <iostream>
#include <vector>

using namespace std;

int height;
vector<vector<int>> triangle;
vector<vector<int>> dp;

int getMaxValue(int y, int x) {
  if ( y == (height - 1) ) {
    return triangle[y][x];
  }

  int& cache = dp[y][x];
  if ( cache != -1 ) {
    return cache;
  }

  cache = triangle[y][x] + max(getMaxValue(y+1, x), getMaxValue(y+1, x+1));
  return cache;
}

void solution() {
  cin >> height;

  triangle.assign(height, vector<int>());
  dp.assign(height, vector<int>());
  int value;
  for ( int i = 1 ; i <= height ; i++ ) {
    for ( int j = 1 ; j <= i ; j++ ) {
      cin >> value;
      triangle[i-1].emplace_back(value);
      dp[i-1].emplace_back(-1);
    }
  }

  cout << getMaxValue(0, 0) << endl;
}

int main() {
  int case_count;
  std::cin >> case_count;

  for ( int c = 0 ; c < case_count ; c++ ) {
    solution();
  }
}
