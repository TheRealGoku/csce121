#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Student.h"

using namespace std;

Student::Student(string student_id, string name) {
	this->id = student_id;
	this->name = name;
}
string Student::get_id() {
	return id;
}
string Student::get_name() {
	return name;
}

void Student::addCourse(std::string course_id) {
	bool check = true;
	for (int i = 0; i < course_ids.size(); i++) {
		if (course_ids[i] == course_id) {
			check = false;
		}
	}
	if (check) {
		course_ids.push_back(course_id);
	}
}
void Student::listCourses() {
	if (course_ids.size() == 0) {
		cout << "No Courses" << endl;
	}
	else {
		cout << "Courses for " << id << endl;
		for (int i = 0; i < course_ids.size(); i++) {
			cout << course_ids[i] << endl;
		}
	}
}
