#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include "School.h"
#include "AttendanceRecord.h"
#include "Course.h"

using namespace std;

void School::addCourses(string filename) {
	ifstream ifs(filename);
	if (!ifs.is_open()) {
		cout << "Unable to open file: " << filename << endl;
		return;
	}
	while (!ifs.eof()) {
		string line;
		getline(ifs, line);
		istringstream ss(line);
		
		string id;
		string starthr;
		string startmin;
		string endhr;
		string endmin;
		string title;
		
		getline(ss, id, ',');
		getline(ss, starthr, ':');
		getline(ss, startmin, ',');
		getline(ss, endhr, ':');
		getline(ss, endmin, ',');
		getline(ss, title);
		
		if (!ss.fail()) {
			bool check = true;
			for (int i = 0; i < courses.size(); i++) {
				if (courses[i].getID() == id) {
					check = false;
				}
			}
			if (check) {
				courses.push_back(Course(id, title, Date(stoi(starthr), stoi(startmin), 0), Date(stoi(endhr), stoi(endmin), 0)));
			}
		}
	}
}

void School::addStudents(string filename) {
	ifstream ifs(filename);
	if (!ifs.is_open()) {
		cout << "Unable to open file: " << filename << endl;
		return;
	}
	while (!ifs.eof()) {
		string line;
		getline(ifs, line);
		istringstream ss(line);
		string uin;
		getline(ss, uin, ',');
		string name;
		getline(ss, name);
		if (!ss.fail()) {
		  students.push_back(Student(uin, name));
		}
	}
}

void School::addAttendanceData(std::string filename) {
	ifstream ifs(filename);
	if (!ifs.is_open()) {
		cout << "Unable to open file: " << filename << endl;
		return;
	}
	while (!ifs.eof()) {
		string y;
		string m;
		string d;
		string hr;
		string min;
		string sec;
		string c;
		string id;
		string line;
		
		getline(ifs, line);
		istringstream iss(line);
		
		getline(iss, y, '-');
		getline(iss, m, '-');
		getline(iss, d, ' ');
		getline(iss, hr, ':');
		getline(iss, min, ':');
		getline(iss, sec, ',');
		getline(iss, c, ',');
		getline(iss, id);
		
		for (int i = 0; i < courses.size(); i++) {
			if (courses[i].getID() == c) {
				courses[i].addAttendanceRecord(AttendanceRecord(c, id, Date(stoi(y), stoi(m), stoi(d), stoi(hr), stoi(min), stoi(sec))));
				break;
			}
		}		
		
	}
}

void School::listCourses() {
	if (courses.size() == 0) {
		cout << "No Courses" << endl;
	}
	else {
		for (int i = 0; i < courses.size(); i++) {
			cout << courses[i].getID() << "," << courses[i].getStartTime().getDateTime().substr(6, 5) << "," << courses[i].getEndTime().getDateTime().substr(6, 5) << "," << courses[i].getTitle() << endl;
		}
	}
}

void School::listStudents() {
	if (students.size() == 0) {
		cout << "No Students" << endl;
	}
	else {
		for (int i = 0; i < students.size(); i++) {
			cout << students[i].get_id() << "," << students[i].get_name() << endl;
		}
	}
	
}

void School::outputCourseAttendance(std::string course_id) {
	for (int i = 0; i < courses.size(); i++) {
		if (courses[i].getID() == course_id) {
			courses[i].outputAttendance();
		}
	}
}

void School::outputStudentAttendance(std::string student_id, std::string course_id) {
	for (int i = 0; i < courses.size(); i++) {
		if (courses[i].getID() == course_id) {
			courses[i].outputAttendance(student_id);
		}
	}
}






