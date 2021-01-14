#include <iostream>
using namespace std;

int main() {
	int sum = 0;
	int input;
	cout << "Enter one number at a time to calculate sum. Enter 0 to terminate." << endl;
	cin >> input;
	while (input != 0){
		sum += input;
		cin >> input;
	}
	cout << "The sum is " << sum;
	return 0;
}