#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <numeric>
#include <iostream>
#include "grade_calculator.h"
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// TODO(student): implement these methods

double GradeCalculator::exam_average() const {
	double t = 0;
	double n = 0;
	if (has_final_exam) {
		t = accumulate(exam_grades.begin(), exam_grades.end(), 0) + final_exam;
		n = exam_grades.size() + 1;
	}
	else {
		t = accumulate(exam_grades.begin(), exam_grades.end(), 0);
		n = exam_grades.size() + 1;
	}
    return ceil((t / n));
} 

double GradeCalculator::zybook_average() const {
	double n = (zybook_participation_grades.size() + zybook_challenge_grades.size());
	double t = (accumulate(zybook_participation_grades.begin(), zybook_participation_grades.end(), 0) + accumulate(zybook_challenge_grades.begin(), zybook_challenge_grades.end(), 0)) + 15 * n;
	if (t / n > 100) {
		return 100;
	}
    return (t / n) * 1.0;
}

double GradeCalculator::hw_average() const {
	double t = (accumulate(hw_grades.begin(), hw_grades.end(), 0));
	double t2 = 0.0;
	for (int i = 0; i < hw_redemption_grades.size(); i++) {
		if (hw_redemption_grades[i] != 0 && hw_redemption_grades[i] > hw_grades[i]) {
			t2 += ((hw_redemption_grades[i] - hw_grades[i]) / 2);
		}
	}
	double n = (hw_grades.size());
    return ((t + t2) / n) * 1.0;
}

double GradeCalculator::lw_average() const {
	double t = accumulate(lw_grades.begin(), lw_grades.end(), 0);
	double n = lw_grades.size();
    return (t / n) * 100;
}

// does not apply modifiers
double GradeCalculator::final_grade_numeric() const {
    return (0.5 * exam_average() + 0.07 * zybook_average() + 0.35 * hw_average() + 0.08 * lw_average());
}

// includes application of modifiers
char GradeCalculator::final_grade_letter() const {
    double total = final_grade_numeric();
	if (!has_syllabus_ack) {
		return 'F';
	}
	else {
		if (exam_average() < 60) {
			return 'D';
		}
		if (total >= 90 && total <= 100) {
			return 'A';
		}
		else if (total >= 80) {
			return 'B';
		}
		else if (total >= 70) {
			return 'C';
		}
		else if (total >= 60) {
			return 'D';
		}
		else {
			return 'F';
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

void GradeCalculator::read_final_exam(std::ifstream& fin) {
    has_final_exam = true;
    fin >> final_exam;
    if (fin.fail()) {
        throw std::runtime_error("failed to read final exam grade");
    }
}

void GradeCalculator::read_exam_hw_redemption_zybook(std::ifstream& fin, const std::string& category) {
    unsigned number;
    fin >> number;
    if (fin.fail()) {
        throw std::runtime_error("failed to read " + category + " number");
    }

    std::vector<double>* vec;
    if (category == "exam") {
        vec = &exam_grades;
    } else if (category == "hw") {
        vec = &hw_grades;
    } else if (category == "hw-redemption") {
        vec = &hw_redemption_grades;
    } else if (category == "zybook") {
        char type;
        fin >> type;
        if (fin.fail()) {
            // HOW TO REACH THIS?
            throw std::runtime_error("failed to read " + category + " type");
        }
        switch (type) {
            case 'p': vec = &zybook_participation_grades; break;
            case 'c': vec = &zybook_challenge_grades; break;
            default: throw std::runtime_error("unrecognized zybook assignment type: " + type);
        }
    } else {
        throw std::runtime_error("unrecognized category: " + category);
    }
    
    double grade;
    fin >> grade;
    if (fin.fail()) {
        throw std::runtime_error("failed to read "+category+" grade");
    }

    while (number > vec->size()) {
        vec->push_back(0);
    }

    vec->at(number-1) = grade;
}

void GradeCalculator::read_lw(std::ifstream& fin) {
    unsigned number;
    fin >> number;
    if (fin.fail()) {
        throw std::runtime_error("failed to read lw number");
    }

    std::string str;
    fin >> str;
    if (fin.fail()) {
        // HOW TO REACH THIS?
        throw std::runtime_error("failed to read lw grade");
    }

    while (number > lw_grades.size()) {
        lw_grades.push_back(false);
    }

    if (str == "0" || str == "false") {
        lw_grades.at(number-1) = false;
    } else if (str == "1" || str == "true") {
        lw_grades.at(number-1) = true;
    } else {
        throw std::runtime_error("invalid lw grade value: " + str);
    }
}

void GradeCalculator::read_syllabus_ack(std::ifstream& fin) {
    std::string str;
    fin >> str;
    if (fin.fail()) {
        // HOW TO REACH THIS?
        throw std::runtime_error("failed to read syllabus-ack type");
    }
    if (str == "0" || str == "false") {
        has_syllabus_ack = false;
    } else if (str == "1" || str == "true") {
        has_syllabus_ack = true;
    } else {
        throw std::runtime_error("invalid syllabus-ack grade value: " + str);
    }
}

void GradeCalculator::load_grades(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        throw std::runtime_error("could not open file");
    }
    while (!fin.eof()) {
        std::string category;
        fin >> category;
        if (fin.fail()) {
            if (fin.eof()) {
                continue;
            } 
            // HOW TO REACH THIS?
            throw std::runtime_error("failed to read category");
        }
        if (category == "final-exam") {
            read_final_exam(fin);
        } else if (category == "exam" || category == "hw" || category == "hw-redemption" || category == "zybook") {
            read_exam_hw_redemption_zybook(fin, category);
        } else if (category == "lw") {
            read_lw(fin);
        } else if (category == "syllabus-ack") {
            read_syllabus_ack(fin);
        } else {
            throw std::runtime_error("invalid category: " + category);
        }
    }
}