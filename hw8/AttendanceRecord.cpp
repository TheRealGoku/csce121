#include <string>
#include "AttendanceRecord.h"
#include "Date.h"

using namespace std;

AttendanceRecord::AttendanceRecord(string course_id, string student_id, Date time) : time(time) {
	this->course_id = course_id;
	this->student_id = student_id;
}
string AttendanceRecord::getCourseID() {
	return course_id;
}
string AttendanceRecord::getStudentID() {
	return student_id;
}
Date AttendanceRecord::getDate() {
	return time;
}
