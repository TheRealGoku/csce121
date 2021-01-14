#include <iostream>
#include <fstream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using namespace std;

Course::Course(std::string id, std::string title, Date startTime, Date endTime) : startTime(startTime), endTime(endTime) {
	this->id = id;
	this->title = title;
}
string Course::getID() {
	return id;
}
string Course::getTitle() {
	return title;
}
Date Course::getStartTime() {
	return startTime;
}
Date Course::getEndTime() {
	return endTime;
}

void Course::addAttendanceRecord(AttendanceRecord ar) {
	bool check = true;
	if (startTime <= ar.getDate() && ar.getDate() <= endTime) {
		attendanceRecords.push_back(ar);
	}
	else {
		cout << "did not save this record." << endl;
	}
}


void Course::outputAttendance() {
	if (attendanceRecords.size() == 0) {
		cout << "No Records" << endl;
	}
	else {
		for (int i = 0; i < attendanceRecords.size(); i++) {
			AttendanceRecord a = attendanceRecords[i];
			cout << a.getDate().getDateTime() << "," << a.getCourseID() << "," << a.getStudentID() << endl;
		}
	}
}
void Course::outputAttendance(std::string student_id) {
	if (attendanceRecords.size() == 0) {
		cout << "No Records" << endl;
	}
	else {
		int cnt = 0;
		for (int i = 0; i < attendanceRecords.size(); i++) {
			AttendanceRecord a = attendanceRecords[i];
			if (a.getStudentID() == student_id) {
				cout << a.getDate().getDateTime() << "," << a.getCourseID() << "," << student_id << endl;
				cnt++;
			}
		}
		if (cnt == 0) {
			cout << "No Records" << endl;
		}
	}
}
