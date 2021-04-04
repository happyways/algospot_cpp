#include <iostream>
#include <vector>

using namespace std;

int number_of_fence;
vector<int> fences_height;

int getMaxSizeFromTheMiddle(int left, int right, int mid) {
  int min_height = min(fences_height[mid], fences_height[mid+1]);
  int max_size = 2 * min_height;
  int lo = mid;
  int hi = mid+1;

  while ( left < lo || hi < right ) {
    //높이가 더 높은 쪽으로 확장
    if ( hi < right && ( lo == left || fences_height[lo-1] < fences_height[hi+1] )) {
      hi++;
      min_height = min(min_height, fences_height[hi]);
    }
    else {
      lo--;
      min_height = min(min_height, fences_height[lo]);
    }

    max_size = max(max_size, (hi-lo+1) * min_height);
  }

  return max_size;
}

//분할 정복으로 풀기
int solve(int left, int right) {
  if ( left == right ) {
    return fences_height[left];
  }

  int mid = left + (right-left)/2;
  int max_size = getMaxSizeFromTheMiddle(left, right, mid);

  return max(max(max_size, solve(left, mid)), solve(mid+1, right));
}

void solution() {
  std::cin >> number_of_fence;

  fences_height.clear();
  int height;
  for ( int i = 0 ; i < number_of_fence ; i++ ) {
    std::cin >> height;
    fences_height.emplace_back(height);
  }

  int max_size = solve(0, number_of_fence-1);
  std::cout << max_size << std::endl;
}

int main() {
  int case_count;
  std::cin >> case_count;

  for ( int c = 0 ; c < case_count ; c++ ) {
    solution();
  }
}
