#include <iostream>
#include <string>
#include <cstdlib>
// no other includes are allowed

using std::cout;
using std::cin;
using std::endl;
using std::string;

// if the limit doubled minuse the number of items is an even number, increase the limit
void surprise(unsigned int n, unsigned int &max) {
  n *= 2;
  int diff = max-n;
  if (abs(diff) % 3 == 0) {
    cout << "Surprise your limit was increased by 1!" << endl;
    max += 1;
  }
}

// update items, but only if adding the new items would result in the number of items being less than or equal to half the limit plus one
void addItems(unsigned int &i, unsigned int cap) {//i is updated but not returned so pass by reference
  unsigned int numItemsToAdd = 0;
  cin >> numItemsToAdd;
  
  if ((numItemsToAdd + i) > cap) {  // if we try to get more than limit, 
    i /= 2; //   take away half of your items
    cout << "You lost half your items!" << endl;
  }
  else if (numItemsToAdd == 1) { // if only 1, add it regardless
    i++;
  }
  else {
    cap = (cap - i) / 2; // change cap to number of slots left
    if (numItemsToAdd > cap) { // if more than half of what's left, add only one
      i++;
    }
    else {// otherwise add numItemsToAdd
      i += numItemsToAdd;
    }
  }
}

void doStuff(unsigned int &items, unsigned int &limit) {
  //items is changed in addItems, and limit is changed in suprise
  //they arent returned so they must be passed by reference
  addItems(items, limit);
  surprise(items, limit);
}

void printStatus(unsigned int n, unsigned int limit) {
    cout << "Status: " << endl;
    cout << " - items: " << n << endl;
    cout << " - limit: " << limit << endl;
}  

int main() {
  unsigned int myItems = 0;
  unsigned int myLimit = 0;
  
  cin >> myLimit;
  
  while (myItems < myLimit) {
    printStatus(myItems, myLimit);
    doStuff(myItems, myLimit);
  }
  
  printStatus(myItems, myLimit);

  cout << "yah!" << endl;
  return 0;
}