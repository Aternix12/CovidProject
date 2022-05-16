/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{//patient data
    string line;
    cout << std::left << "Id" << "\t" << "Name" << "\t\t" << "DOB" << "\t" << "Address" << "\t\t" << "Date" << "\t" << "Travel " << "\t\t" << "Covid" << "\t" << "Status"<<endl;
    
    ifstream database("database.txt");
    if (database.is_open())
    {
        while (getline(database, line))
        {
            cout << line << endl;
        }
    }
    else cout << "Unable to open file";
    //symptom data
    cout << std::left << "Low risk"<< "\t\t" <<"Medium Risk"<<"\t\t"<<"High Risk"<<endl;
    ifstream symptom("symptom.txt");
    if (symptom.is_open())
    {
        while (getline(symptom, line))
        {
            cout << line << endl;
        }
    }
    //locations
    cout<<"High Risk Locations:"<<endl;
    ifstream locations("locations.txt");
    if (locations.is_open())
    {
        while (getline(locations, line))
        {
            cout << line << endl;
        }
    }
    return 0;
}