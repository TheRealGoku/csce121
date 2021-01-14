#include <fstream>
#include <iostream>
#include "functions.h"
using std::ifstream;
using std::istringstream;
using std::string;
using std::getline;
using std::cout;
using std::endl;
using std::runtime_error;

void readPrefs(string fileName, int ngames, int prefs[]) {
	ifstream ifs(fileName);
	if (!ifs.is_open()) {
		throw runtime_error("Invalid preferences file.");
	}
	for (int i = 0; i < ngames; i++) {
		prefs[i] = 0;
	}
	while (!ifs.eof()) {		
		int idx;
		int rating;
		if (ifs >> idx && ifs >> rating && idx < ngames && idx > -1 && rating > -1 && rating < 6) {
			prefs[idx] = rating;
		}
	}
}

void readPlan(string fileName, int plan[]) {
	ifstream ifs(fileName);
	if (!ifs.is_open()) {
		throw runtime_error("Invalid plan file.");
	}
	int gameid;
	int day;
	while (!ifs.eof()) {		
        if (ifs >> day && ifs >> gameid && day > 0 && day <= 366) {
            plan[day] = gameid;
        }
	}
}

int computeFunLevel(int start, int duration, int prefs[], int plan[]) {
	int sum = 0;
	if (duration > 0 && start + duration <= 366) {
		for (int i = start; i < start + duration; i++) {	
			sum += prefs[plan[i]];
			//cout << i << " " << plan[i] << " " << sum << endl;
		}
	}
	else {
		throw std::invalid_argument("Input is invalid.");
	}
	return sum;
}

int findBestVacation(int duration, int prefs[], int plan[]) {
	if (duration > 365 || duration < 0) {
		throw std::invalid_argument("Invalid duration.");
	}
	int sum = 0;
	int idx = 0;
	for (int i = 1; i <= 366 - duration; i++) {
		int x = computeFunLevel(i, duration, prefs, plan);
		if (x > sum) {
			sum = x;
			idx = i;
		}
	}
	return idx;
}






