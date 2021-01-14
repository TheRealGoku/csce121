#include "functions.h"
#include "provided.h"
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::runtime_error;

int main() {
	int ngames;// = 100;
	int duration;// = 1;
	string titles;// = "titles.txt";
	string preffile;// = "prefs-only-99.txt";
	string planfile;// = "plan-365-99.txt";
	
	cout << "Please enter the number of games and the duration: ";
	cin >> ngames;
	cin >> duration;
	if (ngames < 0 || ngames > MAX_NB_GAMES || duration < 0 || duration > 365) {
		cout << "Invalid input." << endl;
		return 1;
	}
	
	cout << "Please enter name of file with titles: ";
	cin >> titles;
	cout << "Please enter name of file with preferences: ";
	cin >> preffile;
	cout << "Please enter name of file with plan: ";
	cin >> planfile;

	string gameTitles[MAX_NB_GAMES];
	int prefs[MAX_NB_GAMES];
	int plan[366];
	try {
		readGameTitles(titles, ngames, gameTitles);	
		readPrefs(preffile, ngames, prefs);
		readPlan(planfile, plan);
	} catch (runtime_error &error) {
		cout << error.what() << endl;
		return 1;
	}
	
	
	int start = findBestVacation(duration, prefs, plan);
	cout << "Best start day is " << start << endl << "Games to be played:" << endl;
	printGamesPlayedInVacation(start, duration, plan, gameTitles, ngames);
	return 0;
}