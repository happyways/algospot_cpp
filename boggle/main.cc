#include <bits/stdc++.h>
constexpr int n = 5; //row & col count

int dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
std::vector<std::string> boards;

bool isInBoard(int y, int x) {
  return ( 0 <= y && y < n && 0 <= x && x < n );
}

bool findWord(int y, int x, const std::string& word) {
  if ( boards[y][x] != word[0] ) {
    return false;
  }

  if ( word.size() == 1 && boards[y][x] == word[0] ) {
    return true;
  }

  //char c = boards[y][x];
  //boards[y][x] = ' ';
  //std::cout << "find : " << c << "(" << y << ", " << x << ")" << std::endl;

  //주변 탐색
  for ( int i = 0 ; i < 8 ; i++ ) {
    int ny = y + dy[i];
    int nx = x + dx[i];

    if ( isInBoard(ny, nx) ) {
      bool find_result = findWord(ny, nx, word.substr(1));

      if ( find_result ) {
        //boards[y][x] = c;
        return true;
      }
    }
  }

  //boards[y][x] = c;
  return false;
}

void solution() {
  std::vector<std::string> words;

  std::string row;
  boards.clear();
  for ( int i = 0 ; i < n ; i++ ) {
    std::cin >> row;
    boards.emplace_back(row);
  }

  int word_count;
  std::cin >> word_count;
  std::string word;
  for ( int i = 0 ; i < word_count ; i++ ) {
    std::cin >> word;
    words.emplace_back(word);
  }

  for ( const auto& word : words ) {
    std::cout << word << " ";
    bool find_result = false;
    for ( int y = 0 ; y < n ; y++ ) {
      for ( int x = 0 ; x < n ; x++ ) {
        if ( findWord(y, x, word) ) {
          find_result = true;
          break;
        }
      }

      if ( find_result ) {
        break;
      }
    }

    if ( find_result ) {
      std::cout << "YES" << std::endl;
    }
    else {
      std::cout << "NO" << std::endl;
    }
  }
}

int main() {
  int case_count;
  std::cin >> case_count;

  for ( int c = 0 ; c < case_count ; c++ ) {
    solution();
  }
}
