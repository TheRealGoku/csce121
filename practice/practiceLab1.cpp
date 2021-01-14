#include <iostream>
using namespace std;

int main() {
	cout << "Start entering number one at a time. Use 0 to terminate." << endl;
	int x;
	cin >> x;
	int min = x;
	if (x == 0) {
		cout << "empty" << endl;
	}
	else {
		while (x != 0) {
			if (x < min) {
				min = x;
			}
			cin >> x;
		}
		cout << min << endl;
	}
	return 0;
}