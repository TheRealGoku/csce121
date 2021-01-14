#include <iostream>
#include <string>

using namespace std;

int getValueInRange(istream is, string prompt, int min, int max) {
	cout << prompt << endl;
	int num = 0;
	do {
		if (!is.good()) {
			is.clear(); // resets the state to good
			is.ignore(numeric_limits < streamsize>::max(), '\n'); //cleans out the buffer
		}
		is >> num;
	}while (num < min || num > max);
	return num;
}

int main() {
	int num = getValueInRange(cin, "Please enter a positive integer between 2 and 9: ", 2, 9);
	cout << "Number is " << num << endl;
}