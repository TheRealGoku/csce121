/*File: hello_world.cpp
 *Author: Aniket Patel
 *Date: 1/15/2020
 */



#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int a = 0, b = 0, c = 0;
	cout << "Please input the value for a, b, c " << endl;
	cin >> a;
	cin >> b;
	cin >> c;
	
	double inside = pow(b, 2) - 4 * a * c;
	double root = ((-1 * b) + sqrt(inside)) / (2 * a);
	double root1 = ((-1 * b) - sqrt(inside)) / (2 * a);
	if (inside > -1) {
		cout << "The root is " << root << ", " << root1 << endl;
	}
	else {
		cout << "No roots" << endl;
	}
	
	
	return 0;
}