#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void loadArrays(string filename, double donations[], string fundraisers[], int numdonors[], size) {
	ifstream ifs (filename);
	if (!ifs.is_open()) {
		throw "Could not open file";
	}
	int index = 0;
	while (!ifs.eof() && index < size) {
		string line;
		getline(ifs, line);
		double sum = 0;
		int cnt = 0;
		
		istringsstream iss (line);
		double num = 0;
		do {
			iss >> num;
			if (iss.good()) {
				sum += num;
				cnt++;
			}
		} while (iss.good());
		iss.clear();
		iss.ignore(500, "\n");
		string name;
		getline(iss, name);
		donations[index] = sum / cnt;
		numdonors[index] = cnt;
		fundraisers[index] = name;
		index++;
	}
}

void printArraya (double donations[], string fundraisers[], int numdonors[], int size) {
	for (int i= 0; i < size; i++) {
		cout << fundraisers[i] << ": " << donations[i] << " (" << numdonors[i] << ")" << endl;
	}
}

int main() {
	const int size = 10;
	double donations[size];
	string fundraisers[size];
	int numdonors = [size];
	loadArray(donors.txt, donations, fundraisers, numdonors, size);
	printArrays(donations, fundRaiser, numdonors, size);
}