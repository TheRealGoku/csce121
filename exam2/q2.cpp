#include <iostream>
// not other include files are allowed

using std::cin, std::cout, std::endl;

// PUT YOUR FUNCTION HERE
template <typename T>
T* rotate(T arr[], int n, int r) {
  T *copy = new T[n];
  r = r % n;
  if (r > 0) {
    for (int i = 0; i < n; i++) {
      copy[i] = arr[(i - r + n) % n];
    }
  }
  else if (r < 0) {
    r = r + n;
    for (int i = 0; i < n; i++) {
      copy[i] = arr[(i - r + n) % n];
    }
  }
  else {
    for (int i = 0; i < n; i++) {
      copy[i] = arr[i];
    }
  }
  return copy;
}
// [1, 2, 3, 4]

int main() {
  // write your own tests here
  {
    int A[] = {1, 2, 3, 4, 5};
    int expected[] = {4, 5, 1, 2, 3};
    int* actual = rotate(A, 5, 2);
    for (size_t i = 0; i < 5; ++i) {
      if (actual[i] != expected[i]) {
        cout << "[FAIL] expected actual["<<i<<"] to be " << expected[i] << endl;
      }
    }
  }
  return 0;
}