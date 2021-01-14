#ifndef DSTACK_H
#define DSTACK_H

template <typename T>
class Stack {
public:
	T* A;
	int capacity;
	int length;
	Stack() {
		A = new T[1];
		capacity = 1;
		length = 0;
	}
	~Stack() {
		delete[] A;
	}
	bool isEmpty() {
		return !length;
	}
	void push(T element) {
		if (capacity > length) {
			A[length] = element;
			length++;
		}
		else {
			T* x = new T[capacity * 2];
			capacity *= 2;
			for (int i = 0; i < length; i++) {
				x[i] = A[i];
			}
			x[length] = element;
			length++;
			delete[] A;
			A = x;
		}
	}
	T pop() {
		if (length != 0) {
			length--;
			return A[length];
		}
		exit(0);
	}
	T peek() {
		if (length != 0) {
			return A[length];
		}
		exit(0);
	}
};

#endif