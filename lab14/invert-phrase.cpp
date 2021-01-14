#include <iostream>
#include <string>
#include <sstream>
#include "Stack.h"

using namespace std;

int main() {
    Stack<string> s;

    string in;
	getline(cin, in);
	in = in.substr(0, in.length() - 1);
	istringstream iss(in);
	while(iss) {
		string word;
		iss >> word;
		s.push(word);
	}
	
	string out = "";
	while (!s.isEmpty()) {
		out += s.pop();
		out += " ";
	}
    cout << out.substr(1, out.length() - 1) << endl;
    return 0;
}
