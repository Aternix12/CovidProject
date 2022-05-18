#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

void menu();
void yourdetails();
void teststatus();
void displaylocations();
void updatepatient();
void displaypatient();


int main() {
	menu();
	return 0;
}

void menu() {	//Main Menu
	int choice;
	do {
		cout << "------------------------------------------------------------" << endl;
		cout << "Press number 1 - Enter your detail for COVID-Test Recommendation" << endl;
		cout << "Press number 2 - Submit your COVID Test Status & Update the Location Database" << endl;
		cout << "Press number 3 - Display the Updated Location (High Risk for COVID)" << endl;
		cout << "Press number 4 - Update COVID Patient Details" << endl;
		cout << "Press number 5 - Display the COVID Positive Patient Details" << endl;
		cout << "Press number 6 - Quit" << endl;
		cin >> choice;
		cout << "------------------------------------------------------------" << endl;
	} while (choice < 1 || choice > 6);
	switch (choice) {
	case 1:
		yourdetails();
		break;
	case 2:
		teststatus();
		break;
	case 3:
		displaylocations();
		break;
	case 4:
		updatepatient();
		break;
	case 5:
		displaypatient();
		break;
	case 6:
		break;
	}
}

void yourdetails() {
	cout << "Enter your Details" << endl;
	string name;
	string id;
	string course;
	string units;
	string classtime;
	cout << "Enter ID: ";
	cin >> id;
	cout << "Enter name: ";
	cin >> name;
	cout << "Enter course: ";
	cin >> course;
	cout << "Enter Units: ";
	cin >> units;
	cout << "Enter Class time: ";
	cin >> classtime;

	ofstream stafffile;
	stafffile.open("database.txt", ofstream::app);
	stafffile << name << "\t" << id << "\t" << course << "\t" << units << "\t" << classtime << endl;
	stafffile.close();
}

void teststatus() {

}

void displaylocations() {	//Display Locations
	string line;
	cout << "High Risk Locations:" << endl;
	ifstream locations("locations.txt");
	if (locations.is_open())
	{
		while (getline(locations, line))
		{
			cout << line << endl;
		}
	}
	locations.close();
	main();
}

void updatepatient() {
	string id;
	cout << "Enter Patient ID to Update: ";
	cin >> id;
	string line;
	ifstream database("database.txt");
	if (database.is_open())
	{
		while (getline(database, line))
		{
			if (line.substr(0, 3) == id) {	//Successful find of ID

			}	
		}
	}
	else cout << "Unable to open file";
	database.close();


}

void displaypatient() {		//Display Patients
	string line;
	cout << left << "Id" << "\t" << "Name" << "\t\t" << "DOB" << "\t" << "Address" << "\t" << "Visited Location"  << "Date" << "\t" << "Travel" << "\t" << "Covid" << "\t" << "Status" << endl;

	ifstream database("database.txt");
	if (database.is_open())
	{
		if (database.peek() == ifstream::traits_type::eof()) {
			cout << "Database file is empty!" << endl;
			main();
		}
		while (getline(database, line))
		{
			cout << line << endl;
		}
	}
	else cout << "Unable to open file";
	database.close();
	main();
}



/*
void yourdetails() {
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
*/