#include <iostream>
using namespace std;

int main() {
	// makes two variables for dollars and cents and asks for input to assign
	// to those varibles.
	int dollar;
	int cent;
	cout << "Enter dollars: ";
	cin >> dollar;
	cout << "Enter cents: ";
	cin >> cent;
	
	// makes four variables for each coin type with the variable name 
	// corresponding with the first letter of each coin.
	int q = 0;
	int d = 0;
	int n = 0;
	int p = 0;
	
	// calculates the number of each coin
	q += (dollar * 4); 
	if (cent / 25 != 0) {
		q += (cent / 25);
		cent = (cent % 25);
	}
	if (cent / 10 != 0) {
		d += (cent / 10);
		cent = (cent % 10);
	}
	if (cent / 5 != 0) {
		n += (cent / 5);
		cent = (cent % 5);
	}
	p += cent;
		
	// prints out the number of each coin and the total number of coins in 
	// format.
	cout << "Pennies: " << p << "\nNickels: " << n << "\nDimes: " << d 
	<< "\nQuarters: " << q << "\n\nTotal coins used: " << p + n + d + q 
	<< endl;
	
}