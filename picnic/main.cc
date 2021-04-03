#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

std::unordered_map<int, std::vector<int>> pair_map;
std::vector<std::pair<int, bool>> students;

bool isComplete(const std::vector<std::pair<int, bool>>& hasFriends) {
  return std::all_of(hasFriends.begin(), hasFriends.end(), [](auto p) {
        return p.second;
      });
}

int connectFriend(int has_friend_count) {
  if ( has_friend_count == students.size() ) {
    return 1;
  }

  auto iter = std::find_if(students.begin(), students.end(), [](const auto& p) -> bool {
        return ( p.second == false );
      });

  if ( iter != students.end() ) {
    int count = 0;
    iter->second = true;
    for ( auto& friend_num : pair_map[iter->first] ) {
      if ( students[friend_num].second == false ) {
        students[friend_num].second = true;
        count += connectFriend(has_friend_count + 2);
        students[friend_num].second = false;
      }
    }
    iter->second = false;

    return count;
  }
  else {
    return 0;
  }
}

void solution() {
  int student_count;
  int pair_count;

  //pair 입력 받기
  std::cin >> student_count >> pair_count;
  pair_map.clear();
  for ( int i = 0 ; i < pair_count ; i++ ) {
    int a, b;

    std::cin >> a >> b;
    if ( a > b ) {
      std::swap(a, b);
    }

    pair_map[a].emplace_back(b);
  }

  //친구 짝 지어주기
  students.clear();
  for ( int i = 0 ; i < student_count ; i++ ) {
    students.emplace_back(i, false);
  }

  int count = connectFriend(0);
  std::cout << count << std::endl;
}

int main() {
  int case_count;
  std::cin >> case_count;

  for ( int c = 0 ; c < case_count ; c++ ) {
    solution();
  }
}
