#include <iostream>
using namespace std;

int main() {
	int input;
	cout << "Please give an integer: " << endl;
	cin >> input;
	
	int sum = 0;
	while (input > 0) {
		sum += input % 10;
		input /= 10;
	}
	
	cout << sum << endl;
	return 0;
}