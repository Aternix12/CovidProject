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
bool checkid(string);
string symptomseverity(string);
bool islocation(string);


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
		cout << "Goodbye!" << endl;
		break;
	}
}

void yourdetails() {	//Enter your details and reccomend test
	cout << "Enter your Details" << endl;
	string id;
	string firstname;
	string lastname;
	string dob;
	string address;
	string date;
	string travel;
	string testresult;
	string status;

	cout << "Enter ID: ";
	cin >> id;
	if (checkid(id)) { //Checks if ID already exists
		cout << "ID already exists!" << endl;
		main();
	}	

	//Get Details
	cout << "Enter firstname: ";
	cin >> firstname;
	cout << "Enter lastname: ";
	cin >> lastname;
	cout << "Enter DOB: ";
	cin >> dob;
	cout << "Enter Address: ";
	cin.ignore();
	getline(cin, address);
	cout << "Have you traveled overseas? (Yes/No): ";
	cin >> travel;
	cin.ignore();

	//Select Symptoms - Determines Severity
	string usersymptoms;
	string severity;
	cout << "Enter symptom: ";
	getline(cin, usersymptoms);
	severity = symptomseverity(usersymptoms);
	if (severity == "Failed to Find!") {
		cout << severity << endl;
		main();
	}

	cout << "Your symptom severity is: " << severity << endl;

	//Select Location
	string userlocation;
	cout << "Enter location: ";
	getline(cin, userlocation);
	if (islocation(userlocation)) {
		cout << "High Risk Site!" << endl;
		//Reccomend the Test
		cout << "Please take a covid test!" << endl;
		//Add Patient Details to File
		ofstream database;
		database.open("database.txt", ofstream::app);
		if (database.good()) {
			database << id << "\t" << firstname << " " << lastname << "\t" << dob << "\t" << address << "\t\t" << travel << "\t" << "??" << "\t" << "alive" << endl;
			database.close();
			cout << "Successfully added you to database" << endl;
		}
		else {
			cout << "Was unable to open database file." << endl;
		}
		main();
	}
	else {	//Don't reccomend test
		cout << "Please isolate yourself at home." << endl;
		//Add Patient Details to File
		ofstream database;
		database.open("database.txt", ofstream::app);
		if (database.good()) {
			database << id << "\t" << firstname << " " << lastname << "\t" << dob << "\t" << address << "\t\t" << travel << "\t" << "??" << "\t" << "alive" << endl;
			database.close();
			cout << "Successfully added you to database" << endl;
		}
		else {
			cout << "Was unable to open database file." << endl;
		}
	}
}

void teststatus() {
	string id;
	cout << "Enter Patient ID for COVID Diagnosis: ";
	cin >> id;
	if (checkid(id)) {	//Found ID
		string positive;
		cout << "Did this patient test POSITIVE? (Yes/No)" << endl;
		cin >> positive;
		if (positive == "Yes") {	//If patient positive
			string line;
			ifstream databasein("database.txt");
			if (databasein.is_open())
			{
				while (getline(databasein, line))
				{
					if (line.substr(0, 3) == id) {	//Successful find of ID
						databasein.clear();
						long pos = databasein.tellg();
						databasein.close();
						ofstream databaseout("database.txt", ofstream::_Nocreate);
						databaseout.seekp(pos - 15);
						databaseout << "+ve";
						databaseout.close();
						cout << "Written Status!" << endl;
					}
				}
			}
			else cout << "Unable to open file";
			databasein.close();

			//Adding Location to Locations Database
			string newlocation;
			cin.ignore(256, '\n');
			cout << "Please enter your exposure site: ";
			getline(cin, newlocation);
			ofstream locations("locations.txt", ios::app);
			locations.flush();
			locations << newlocation << endl;
			cout << "Added location to locations list!" << endl;
			locations.close();	
			main();
		}
		else { //If patient negative
			string line;
			ifstream databasein("database.txt");
			if (databasein.is_open())
			{
				while (getline(databasein, line))
				{
					if (line.substr(0, 3) == id) {	//Successful find of ID
						databasein.clear();
						long pos = databasein.tellg();
						databasein.close();
						ofstream databaseout("database.txt", ofstream::_Nocreate);
						databaseout.seekp(pos - 15);
						databaseout << "-ve";
						databaseout.close();
						cout << "Written Status!";
						main();
					}
				}
			}
			else cout << "Unable to open file";
			databasein.close();
		}
	}
	else {
		cout << "Couldn't find ID" << endl;
		main();
	}
}

void displaylocations() {	//Display Locations
	string line;
	cout << "High Risk Locations:" << endl;
	ifstream locations("locations.txt");
	if (locations.is_open() && locations.good())
	{
		while (getline(locations, line))
		{
			cout << line << endl;
		}
	}
	locations.close();
	main();
}

void updatepatient() {	//Find and Update Patient by ID
	string id;
	cout << "Enter Patient ID to Update: ";
	cin >> id;
	if (checkid(id)) {	//Found ID
		string dead;
		cout << "Update Patient Status (alive/dead)" << endl;
		cin >> dead;
		if (dead == "dead") {	//If patient positive
			string line;
			ifstream databasein("database.txt");
			if (databasein.is_open())
			{
				while (getline(databasein, line))
				{
					if (line.substr(0, 3) == id) {	//Successful find of ID
						databasein.clear();
						long pos = databasein.tellg();
						databasein.close();
						ofstream databaseout("database.txt", ofstream::_Nocreate);
						databaseout.seekp(pos - 7);
						databaseout << "dead ";
						databaseout.close();
						cout << "Written Status!" << endl;
					}
				}
			}
			else cout << "Unable to open file";
			databasein.close();
		}
		else if (dead == "alive") {
			string line;
			ifstream databasein("database.txt");
			if (databasein.is_open())
			{
				while (getline(databasein, line))
				{
					if (line.substr(0, 3) == id) {	//Successful find of ID
						databasein.clear();
						long pos = databasein.tellg();
						databasein.close();
						ofstream databaseout("database.txt", ofstream::_Nocreate);
						databaseout.seekp(pos - 7);
						databaseout << "alive";
						databaseout.close();
						cout << "Written Status!" << endl;
					}
				}
			}
			else cout << "Unable to open file";
			databasein.close();
		}
		main();
	}
	else {
		cout << "Couldn't find ID" << endl;
		main();
	}
}

void displaypatient() {		//Display Patients
	string line;
	cout << left << "\nId" << "\t" << "Name" << "\t\t\t" << "DOB" << "\t\t" << "Address" << "\t\t\t" << "Travel" << "\t" << "Covid" << "\t" << "Status" << endl;

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

bool checkid(string id) {
	string line;
	ifstream database("database.txt");
	if (database.is_open())
	{
		while (getline(database, line))
		{
			if (line.substr(0, 3) == id) {	//Successful find of ID
				database.close();
				return true;
			}
		}
	}
	else cout << "Unable to open file";
	database.close();
	return false;
}

string symptomseverity(string usersymptoms) {
	string line;
	ifstream symptoms("symptom.txt");
	if (symptoms.is_open())
	{
		if (symptoms.peek() == ifstream::traits_type::eof()) {
			cout << "Unable to reccomend COVID Test - required data is missing" << endl;
			main();
		}
		while (getline(symptoms, line))
		{
			int pos = line.find(' ');
			string symp;
			symp = line.substr(pos + 1, line.size());
			if (symp == usersymptoms) {
				symptoms.close();
				return (line.substr(0, pos));
			}
		}
	}
	symptoms.close();
	return "Failed to Find!";
}

bool islocation(string userlocation) {
	string line;
	ifstream locations("locations.txt");
	if (locations.is_open())
	{
		if (locations.peek() == ifstream::traits_type::eof()) {
			cout << "Unable to reccomend COVID Test - required data is missing" << endl;
			main();
		}
		while (getline(locations, line))
		{
			if (userlocation == line) {
				locations.close();
				return true;
			}
		}
	}
	locations.close();
	return false;
}