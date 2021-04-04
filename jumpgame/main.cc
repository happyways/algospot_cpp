#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> board;
vector<vector<int>> dp;

bool solve(int y, int x) {
  if ( !(y < n && x < n) ) {
    return false;
  }

  if ( y == (n-1) && x == (n-1) ) {
    return true;
  }

  int& cache = dp[y][x];
  if ( cache != -1 ) {
    return cache;
  }

  int jump_distance = board[y][x];
  cache = solve(y + jump_distance, x) || solve(y, x + jump_distance);
  return cache;
}

void solution() {
  cin >> n;

  board.assign(n, vector<int>(n, 0));

  //계산 아직 안됨, 못가는 곳, 갈 수 있는 곳
  //-1, 0, 1
  dp.assign(n, vector<int>(n, -1));

  int jump_distance;
  for ( int i = 0 ; i < n ; i++ ) {
    for ( int j = 0 ; j < n ; j++ ) {
      cin >> jump_distance;
      board[i][j] = jump_distance;
    }
  }

  if ( solve(0, 0) ) {
    cout << "YES" << endl;
  }
  else {
    cout << "NO" << endl;
  }
}

int main() {
  int case_count;
  cin >> case_count;

  for ( int c = 0 ; c < case_count ; c++ ) {
    solution();
  }
}
