#include <iostream>
#include <vector>

using namespace std;

void normalize(vector<int>& num) {
  //자리수가 늘어날 수 있기 때문에
  //0을 맨 앞자리 위치에 추가
  num.push_back(0);

  //제일 낮은 자리수 부터, (제일 높은자리-1)까지 carry계산
  for ( int i = 0 ; i+1 < num.size() ; i++ ) {
    if ( num[i] < 0 ) {
      int borrow = (abs(num[i]) + 9) / 10;
      num[i+1] -= borrow;
      num[i] += borrow * 10;
    }
    else {
      //10이 넘는 값은 carry값 전달
      num[i+1] += num[i] / 10;
      num[i] %= 10;
    }
  }

  //사용하지 않는 높은 자리수 0들 제거
  //ex ) 00123 -> 123
  while ( num.size() > 1 && num.back() == 0 ) {
    num.pop_back();
  }
}

//곱한 결과의 역순이 리턴됨
//ex ) 123 * 456 = 56088 = {8, 8, 0, 6, 5}
vector<int> multiply(const vector<int>& a,
                     const vector<int>& b) {
  vector<int> c(a.size() + b.size() + 1, 0);
  for ( int i = 0 ; i < a.size() ; i++ ) {
    for ( int j = 0 ; j < b.size() ; j++ ) {
      c[i+j] += a[i] * b[j];
    }
  }
  normalize(c);
  return c;
}

//a += b * 10^k
void addTo(vector<int>& a, const vector<int>& b, int k) {
  //a의 자릿수가 더 작아 공간이 부족할 경우 resize
	if(a.size() < b.size() + k) {
		a.resize(b.size() + k);
  }

  //k만큼 자릿수를 shift하고 저장
	for(int i = 0; i < b.size(); i++) {
    a[i+k] += b[i];
  }
	normalize(a);
}

//a가 b보다 큰 값일 경우를 가정
void subFrom(vector<int>& a, const vector<int>& b) {
	for(int i = 0; i < b.size(); i++) {
    a[i] -= b[i];
  }
	normalize(a);
}

//숫자가 높은 값일수록 높은 자릿수를 뜻함
vector<int> karatsuba(const vector<int>& a,
                      const vector<int>& b) {
  int a_size = a.size();
  int b_size = b.size();

  if ( a_size < b_size ) {
    return karatsuba(b, a);
  }

  //a의 자릿수가 더 클때 계산됨
  if ( a_size == 0 || b_size == 0 ) {
    return vector<int>();
  }

  if ( a.size() <= 50 ) {
    return multiply(a, b);
  }

  int half = a_size / 2;

  //a1 : 높은자릿수 반, a0 : 낮은 자리수 반
  vector<int> a0(a.begin(), a.begin() + half);
  vector<int> a1(a.begin() + half, a.end());

  //b1 : 높은자릿수 반, b0 : 낮은 자리수 반
  vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
  vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

  vector<int> z2 = karatsuba(a1, b1);
  vector<int> z0 = karatsuba(a0, b0);

  addTo(a0, a1, 0);
  addTo(b0, b1, 0);
  vector<int> z1 = karatsuba(a0, b0);

  subFrom(z1, z0);
  subFrom(z1, z2);

  vector<int> ret;
  addTo(ret, z0, 0);
  addTo(ret, z1, half);
  addTo(ret, z2, half + half);
  return ret;
}

int main() {
  vector<int> result = karatsuba({5,5}, {5,5});

  for ( int value : result ) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}
