#include <iostream>
#include <stdexcept>
#include "picture_hanging.h"

using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::out_of_range;

int main() {
    size_t n = 0;
    //cout << "Enter the amount of values in the sequence: " << endl;
    cin >> n;
    if(cin.fail()) {
        cout << "invalid input" << endl;
        return 1;
    }

    //cout << "Enter the values in your sequence: ";
    int* A = new int[n];
    for(unsigned int i = 0; i < n; ++i) {
        cin >> A[i];
        if(cin.fail()) {
            cout << "invalid input" << endl;
            return 1;
        }
    }
    bool stable = false, correct = false;
    try{
        stable = isStable(A, n);
        correct = isCorrect(A, n);
        removeDuplicates(A, n);
    } catch(out_of_range& except) {
        cout << except.what() << endl;
    }

    //unique numbers
    cout << "sequence uses " << n << " nails" << endl;
    
    //isStable output
    cout << "sequence is ";
    if(!stable) {
        cout << "not ";
    }
    cout << "stable" << endl;

    //isCorrect output
    cout << "sequence is ";
    if(!correct) {
        cout << "not ";
    }
    cout << "correct" << endl;
	delete[] A;
    return 0;
}