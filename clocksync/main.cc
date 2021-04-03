#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

constexpr int CLOCK_COUNT = 16;
int min_switch_count;
std::vector<int> clocks;
std::vector<std::string> switchs =
//0~15
{"xxx.............",
 "...x...x.x.x....",
 "....x.....x...xx",
 "x...xxxx........",
 "......xxx.x.x...",
 "x.x...........xx",
 "...x..........xx",
 "....xx.x......xx",
 ".xxxxx..........",
 "...xxx...x...x.."};

bool isComplete() {
  return std::all_of(clocks.begin(), clocks.end(), [](int t) {
      return ( t == 12 );
      });
}

void pressSwitch(int switch_number) {
  auto& current_switch = switchs[switch_number];
  for ( int i = 0 ; i < current_switch.size() ; i++ ) {
    if ( current_switch[i] == 'x' ) {
      clocks[i] = clocks[i] == 12 ? 3 : clocks[i] + 3;
    }
  }
}

void solve(int current_switch, int switch_press_count) {
  //누를 수 있는 스위치 개수를 넘어가면 중단
  if ( current_switch >= switchs.size() ) {
    if ( isComplete() ) {
      min_switch_count = std::min(min_switch_count, switch_press_count);
    }
    return;
  }

  //현재 스위치 0번 누른 후
  solve(current_switch+1, switch_press_count);
  //1~3번 누른 후 계산
  for ( int i = 0 ; i < 3 ; i++ ) {
    pressSwitch(current_switch);
    switch_press_count++;
    solve(current_switch+1, switch_press_count);
  }

  //다시 원상태로 복구하기 위해 4번째 press
  pressSwitch(current_switch);
}

//스위치의 최소 수 리턴
void solution() {
  clocks.clear();
  min_switch_count = std::numeric_limits<int>::max();

  for ( int i = 0 ; i < CLOCK_COUNT ; i++ ) {
    int clock;
    std::cin >> clock;
    clocks.emplace_back(clock);
  }

  solve(0, 0);

  if ( min_switch_count == std::numeric_limits<int>::max() ) {
    std::cout << -1 << std::endl;
  }
  else {
    std::cout << min_switch_count << std::endl;
  }
}

int main() {
  int case_count;
  std::cin >> case_count;

  for ( int c = 0 ; c < case_count ; c++ ) {
    solution();
  }
}
