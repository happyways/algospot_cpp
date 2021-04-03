#include <tuple>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

constexpr int SHAPE_TYPE_COUNT = 4;
constexpr int SHAPE_SIZE_COUNT = 3;
int height, width;
std::vector<std::string> board;
int blank_count;

int shape[SHAPE_TYPE_COUNT][SHAPE_SIZE_COUNT][2] = {{{0,0}, {0,1}, {1,1}}, //'ㄱ'
                                {{0,0}, {0,1}, {1,0}}, //'ㄱ' 반대
                                {{0,0}, {1,0}, {1,1}}, //'ㄴ'
                                {{0,0}, {1,0}, {1,-1}}}; //'ㄴ' 반대

bool isInBoard(int y, int x) {
  return ( 0 <= y && y < height && 0 <= x && x < width );
}

bool canCoverShape(int y, int x, int shape_type) {
  for ( int i = 0 ; i < SHAPE_SIZE_COUNT ; i++ ) {
    const int ny = y + shape[shape_type][i][0];
    const int nx = x + shape[shape_type][i][1];
    if ( not isInBoard(ny, nx) || board[ny][nx] != '.' ) {
      return false;
    }
  }
  return true;
}

void coverShape(int y, int x, int shape_type, bool cover) {
  for ( int i = 0 ; i < SHAPE_SIZE_COUNT ; i++ ) {
    const int ny = y + shape[shape_type][i][0];
    const int nx = x + shape[shape_type][i][1];
    board[ny][nx] = cover ? '#' : '.';
  }
}

std::tuple<int, int> findFirstBlank() {
  for ( int y = 0 ; y < height ; y++ ) {
    for ( int x = 0 ; x < width ; x++ ) {
      if ( board[y][x] == '.' ) {
        return std::make_tuple(y, x);
      }
    }
  }
  return std::make_tuple(-1, -1);
}

int coverBoard(int cover_count) {
  int y, x;
  std::tie(y, x) = findFirstBlank();

  //모두 덮었으면 종료
  if ( cover_count == blank_count ) {
    return 1;
  }

  //y, x좌표에 덮을 수 있는 방법으로 덮은 후 다음 단계 진행
  int count = 0;
  for ( int shape_type = 0 ; shape_type < SHAPE_TYPE_COUNT ; shape_type++ ) {
    if ( canCoverShape(y, x, shape_type) ) {
      coverShape(y, x, shape_type, true);
      count += coverBoard(cover_count + 3);
      coverShape(y, x, shape_type, false);
    }
  }
  return count;
}

void solution() {
  std::cin >> height >> width;

  board.clear();
  blank_count = 0;

  for ( int i = 0 ; i < height ; i++ ) {
    std::string row;
    std::cin >> row;
    board.emplace_back(row);

    blank_count += std::count(row.begin(), row.end(), '.');
  }

  //공백 개수가 3의 배수가 아닐 경우, 완성 불가능
  if (blank_count % 3 != 0) {
    std::cout << 0 << std::endl;
  }
  else {
    std::cout << coverBoard(0) << std::endl;
  }
}

int main() {
  int case_count = 0;
  std::cin >> case_count;

  for ( int c = 0 ; c < case_count ; c++ ) {
    solution();
  }
}
