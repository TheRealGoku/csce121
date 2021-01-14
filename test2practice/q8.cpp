#include <iostream>

using namespace std;

int countPositiveRows(int **mat, int n) {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		bool check = true;
		for (int j = 0; j < n; j++) {
			if (mat[i][j] < 0) {
				check = false;
			}
		}
		if (check) {
			cnt++;
		}
	}
	return cnt;
}

int** newMatrix (int **inMatrix, int n, int &newN) {
	newN = countPositiveRows(inMatrix, n);
	int **ans = new int*[newN];
	for (int i = 0; i < newN; i++) {
		ans[i] = new int[n];
	}
	int idx = 0;
	for (int i = 0; i < n; i++) {
		bool check = true;
		for (int j = 0; j < n; j++) {
			if (inMatrix[i][j] < 0) {
				check = false;
			}
		}
		if (check) {
			ans[idx][j] = inMatrix[i][j];
			idx++;
		}
	}
	return ans;
}

int main() {
	int p1[] = {1, 2, 3, 4, 5};
	int p2[] = {-1, 2, 3, 4, 5};
	int p3[] = {65, 684 ,26 ,-25 ,656};
	int p4[] = {68294, 982864, 398, -456, 231};
	int p5[] = {5, 4, 3, 2, 1};
	int n = 5;
	int *inMatrix[] = {p1, p2, p3, p4, p5};
	int newn = 0;
	int **newMatrix = (inMatrix, 5, newn);
	
	for (int i = 0; i < newn; i++) {
		for (int j = 0; j < n; j++) {
			cout << newMatrix[i][j] << " " << endl;
		}
		cout << endl;
		delete[] newMatrix[i];
		newMatrix[i] = nullptr;
	}
	delete[] newMatrix;
	newMatrix = nullptr;
}



