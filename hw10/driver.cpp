#include <iostream>
#include "Node.h"
#include "DoublyLinkedList.h"

using namespace std;

int main() {
	DoublyLinkedList<int> x = DoublyLinkedList<int>(1);
	x.push_back(3);
	cout << x.to_str() << endl;
	x.push_front(0);
	cout << x.to_str() << endl;
	x.insert(2, 2);
	cout << x.to_str() << endl;
	x.pop_back();
	cout << x.to_str() << endl;
	x.pop_front();
	cout << x.to_str() << endl;
	x.erase(1);
	cout << x.to_str() << endl;
	x.push_back(20);
	cout << x.to_str() << endl;
	DoublyLinkedList<int> y = DoublyLinkedList<int>(x);
	cout << y.to_str() << endl;
    return 0;
}