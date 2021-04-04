#include <iostream>
#include <string>

using namespace std;

string reverseQuadtree(string::iterator& iter) {
  char head = *iter;
  iter++;

  if ( head == 'b' || head == 'w' ) {
    return string(1, head);
  }

  string ul = reverseQuadtree(iter);
  string ur = reverseQuadtree(iter);
  string ll = reverseQuadtree(iter);
  string lr = reverseQuadtree(iter);

  return string("x") + ll + lr + ul + ur;
}

void solution() {
  string quadtree;
  cin >> quadtree;

  auto iter = quadtree.begin();
  string reversed_quadtree = reverseQuadtree(iter);

  cout << reversed_quadtree << endl;
}

int main() {
  int case_count;
  cin >> case_count;

  for ( int c = 0 ; c < case_count ; c++ ) {
    solution();
  }
}
