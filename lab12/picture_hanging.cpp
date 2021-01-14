#include <iostream>
#include <stdexcept>
#include "picture_hanging.h"

#define TODO(X) cout << "[TODO] " << __FUNCTION__ << ": " << X << endl;

using std::cout;
using std::endl;
using std::ostream;
using std::out_of_range;

/*
make a copy of src (elements 0..len-1)
*/
int* copy(const int src[], const size_t len) {
	int* c = new int[len];
	for (unsigned int i = 0; i < len; i++) {
		c[i] = src[i];
	}
    return c;
}

/*
return i such that A[i] = key, or -1 if key is not in A
*/
int find(const int A[], const size_t len, const int key) {
	for (unsigned int i = 0; i < len; i++) {
		if (A[i] == key) {
			return i;
		}
	}
    return -1;
}

/*
remove the specified number (cnt) of elements starting at specified index (idx)
*/
void remove(int A[], size_t& len, const size_t idx, const size_t cnt) {
	if (idx < len && cnt <= (len - idx)) {
		if (idx + cnt == len) {
			len = len - cnt;
		}
		else if (cnt == 0) {
			;
		}
		else {
			for (size_t i = idx; i < len - cnt; i++) {
				A[i] = A[i + cnt];
			}
			len = len - cnt;
		}
	}
	else {
		throw out_of_range("Index or Count are out of range");
		return;
	}
}

/*
remove all instances of duplicate values in A (including opposites, so 1 and -1 are the same)
*/
void removeDuplicates(int A[], size_t& len) {
	for (size_t i = 0; i < len; i++) {
		for (size_t j = i + 1; j < len; j++) {
			if (A[i] == A[j]) {
				remove(A, len, j, 1);
				j--;
			}
			else if (A[i] == -1 * A[j]) {
				remove(A, len, j, 1);
				j--;
			}
		}
	}
}

/*
returns true if str is not reducible (no canceling neighbors)
*/
bool isStable(const int A[], const size_t len) {
	if (len == 0) {
		return true;
	}
    for (unsigned int i = 0; i < len - 1; i++) {
		if (A[i] == -1 * A[i + 1]) {
			return false;
		}
	}
    return true;
}

/*
remove all instances of value
*/
void removeAll(int A[], size_t& len, const int value) {
    /*for (size_t i = 0; i < len; i++) {
		if (A[i] == value) {
			remove(A, len, i, 1);
			i--;
		}
	}*/
	int idx = find(A, len, value);
	while (idx != -1) {
		remove(A, len, idx, 1);
		idx = find(A, len, value);
	}
}

/*
repeatedly remove any pair of neighbors which are opposites (e.g. 1 and -1).
*/
void reduce(int A[], size_t& len) {
    bool nextNeighbor = false, lastNeighbor = false;
    while(!isStable(A, len)) {
        for(unsigned int i = 0; i < len; ++i) {
            if(i == 0) {
                nextNeighbor = (-1 * A[i]) == A[i + 1];
                if(nextNeighbor) {
                    remove(A, len, 0, 2);
                }
            } else if(i == len - 1) {
                lastNeighbor = (-1 * A[i]) == A[i - 1];
                if(lastNeighbor) {
                    remove(A, len, i - 1, 2);
                }
            } else {
                nextNeighbor = (-1 * A[i]) == A[i + 1];
                lastNeighbor = (-1 * A[i]) == A[i - 1];
                if(nextNeighbor) {
                    remove(A, len, i, 2);
                } else if(lastNeighbor) {
                    remove(A, len, i - 1, 2);
                }
            }
        }
    }
}

/*
return true if removing any single value (and it's opposite, e.g. 1 and -1) reduces the sequence to empty.
*/
void print(int A[], size_t len) {
	for (int i = 0; i < len; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
}
bool isCorrect(const int A[], const size_t len) {
	bool check = true;
	for (size_t i = 0; i < len; i++) {	
		size_t len2 = len;
		int *B = copy(A, len);
		removeAll(B, len2, A[i]);
		removeAll(B, len2, (-1 * A[i]));
		reduce(B, len2);
		if (len2 != 0) {
			check = false;
		}
		delete[] B;
	}
    return check;
}


