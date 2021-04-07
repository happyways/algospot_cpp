#include <iostream>
#include <vector>

using namespace std;

int length;
vector<int> nums;
vector<int> dp;

int getMaxLength(int x) {
  int& cache = dp[x];
  if ( cache != -1 ) {
    return cache;
  }

  int max_length = 1;
  for ( int i = x+1 ; i < length ; i++ ) {
    if ( nums[x] < nums[i] ) {
      max_length = max(max_length, 1 + getMaxLength(i));
    }
  }
  return cache = max_length;
}

void solution() {
  cin >> length;

  int value;
  nums.clear();
  dp.assign(length, -1);
  for ( int i = 0 ; i < length ; i++ ) {
    cin >> value;
    nums.emplace_back(value);
  }

  int max_length = 0;
  for ( int i = 0 ; i < length ; i++ ) {
    max_length = max(max_length, getMaxLength(i));
  }

  cout << max_length << endl;
}

int main() {
  int case_count;
  std::cin >> case_count;

  for ( int c = 0 ; c < case_count ; c++ ) {
    solution();
  }
}
