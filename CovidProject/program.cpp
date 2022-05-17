#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

void menu();
void studentin();
void studentout();
void staffin();
void staffout();


int main() {
	menu();
	return 0;
}

void menu() {
	int choice;
	do {
		cout << "------------------------------------------------------------" << endl;
		cout << "Press number 1 - Enter your detail for COVID-Test Recommendation" << endl;
		cout << "Press number 2 - Submit your COVID " << endl;
		cout << "Press number 3 - Display student record" << endl;
		cout << "Press number 4 - Display staff record" << endl;
		cin >> choice;
		cout << "------------------------------------------------------------" << endl;
	} while (choice < 1 || choice > 4);
	switch (choice) {
	case 1:
		studentout();
		break;
	case 2:
		staffout();
		break;
	case 3:
		studentin();
		break;
	case 4:
		staffin();
		break;
	}
}

void studentout() {
	string name;
	string id;
	string course;
	string units;
	string grades;
	cout << "Enter name: ";
	cin >> name;
	cout << "Enter ID: ";
	cin >> id;
	cout << "Enter course: ";
	cin >> course;
	cout << "Enter Units: ";
	cin >> units;
	cout << "Enter grades: ";
	cin >> grades;

	ofstream studentsfile;
	studentsfile.open("students.txt", std::ofstream::app);
	studentsfile << name << "\t" << id << "\t" << course << "\t" << units << "\t" << grades << endl;
	studentsfile.close();

	main();
}

void studentin() {
	ifstream studentsfile;
	string line;
	studentsfile.open("students.txt");
	while (getline(studentsfile, line)) {
		cout << line << endl;
	}

	main();
}

void staffin() {
	ifstream stafffile;
	string line;
	stafffile.open("staff.txt");
	while (getline(stafffile, line)) {
		cout << line << endl;
	}

	main();
}

void staffout() {
	string name;
	string id;
	string course;
	string units;
	string classtime;
	cout << "Enter name: ";
	cin >> name;
	cout << "Enter ID: ";
	cin >> id;
	cout << "Enter course: ";
	cin >> course;
	cout << "Enter Units: ";
	cin >> units;
	cout << "Enter Class time: ";
	cin >> classtime;

	ofstream stafffile;
	stafffile.open("staff.txt", std::ofstream::app);
	stafffile << name << "\t" << id << "\t" << course << "\t" << units << "\t" << classtime << endl;
	stafffile.close();

	main();
}
