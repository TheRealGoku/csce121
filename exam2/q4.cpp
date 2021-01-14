#include <iostream>
// not other includes are allowed

using std::cin, std::cout, std::endl;

unsigned foo(unsigned a, unsigned b) {
  if (a == b) {
    return 1;
  }
  else if (b > a) {
    return 0;
  }
  else if (a == 0 || b == 0) {
    return 1;
  }
  else {
    return foo(a - 1, b - 1) + foo(a - 1, b);
  }
}

int main() {
  // write your own tests here
  if (foo(1,3) != 0) {
    cout << "[FAIL] expected foo(1,3) to be 0" << endl;
  }
}