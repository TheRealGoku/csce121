#ifndef DSTACK_H
#define DSTACK_H

class StackDouble {
public:
	double* A;
	int capacity;
	int length;
	StackDouble();
	~StackDouble();
	void push(double element);
	double pop();
};

#endif