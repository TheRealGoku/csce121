#include <iostream>
using namespace std;

int main() {
	
	int n;
	cout << "Please input the total amount of numbers: " << endl;
	cin >> n;
	
	int cnt = 0;
	
	for (int i = 0; i < n;  i++) {
		int x;
		cout << "Enter a number: " << endl;
		cin >> x;
		if (x % 2 == 0){
			cnt++;
		}
	}
	cout << "There are " << cnt << " even number(s).";
	
	return 0;
}