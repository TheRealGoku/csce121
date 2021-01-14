#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int loadArrays(string filename, double donations[], string fundraisers[], int numdonors[], int size) {
  ifstream ifs (filename);
  if (!ifs.is_open()) {
    throw  "Could not open file";
  }
 int index = 0;
 while (!ifs.eof() && index < size) {
    string line;
    getline(ifs, line);
    cout << line << endl;
    double sum = 0;
    int cnt = 0;
    istringstream iss (line);
    double num = 0;
    do {
      iss >> num;
      if (iss.good()) {
        sum += num;
        cnt++;
      }
    } while(iss.good()); 
    iss.clear();
    //iss.ignore(500, '\n'); 
    string name;
    iss >> name;
    donations[index] = sum/cnt;
    numdonors[index] = cnt;
    fundraisers[index] = name;
    index++;
  }
  return index;
}

void printArrays(double donations[], string fundraisers[], int numdonors[], int size) {
  for (int i=0; i<size; ++i) {
    cout << fundraisers[i] << ": " << donations[i] << " (" << numdonors[i] << ")" << endl;
  }
}

int main() {
  const int maxSize = 10;
  double donations[maxSize];
  string fundRaisers[maxSize];
  int numdonors[maxSize];
  int size = loadArrays("donors.txt", donations, fundRaisers, numdonors, maxSize);
  printArrays(donations, fundRaisers, numdonors, size);
}