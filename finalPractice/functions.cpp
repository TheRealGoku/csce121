#include "functions.h"
#include <iostream>
#include <string.h>
using namespace std;

template<class T, int n>
constexpr int size(T (&)[n])
{ return n; }

bool IsEvenGeneric(char *x, char *y) {
	int cnt = 0;
	for (int i = 0; i < strlen(x); i++) {
		for (int j = 0; j < strlen(y); j++) {
			if (x[i] == y[j]) {
				cnt++;
			}
		}
	}
	cout << cnt << endl;
	return ((cnt % 2) == 0);
}

int main() {
	char s[] = "aeiou";
	cout << IsEvenGeneric(s, "aeiou") << endl;
}