#include "admin.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
bool admin::isLogin() {
	cout << "Admin logged in successfully." << endl;
	return 1;
}
//default constructor for admin
admin::admin() {
	saveAdminToFile();
}


void admin::saveAdminToFile() {  
   ofstream adminFile("admin.txt", ios::app);  
   if (!adminFile.is_open()) {  
       cerr << "Error opening file." << endl;  
       return;  
   }  
   adminFile << name << "*" << cnic << "*" << password << endl;  
   cout << "Admin saved to file." << endl;  
   adminFile.close();  
}
void admin::addVoter() {
	cout << "Enter name: ";
	string name;
	cin >> name;
	cout << "Enter CNIC: ";
	string snic;
	cin >> snic;
	// check if cnic already exists
	if (checkIfUserExists(snic, "voter.txt")) {
		cout << "CNIC already exists." << endl;
		return;
	}
	cout << "Enter password: ";
	string password;
	cin >> password;

	addUserToFile(name, snic, password, "voter");

	
}
void admin::addAdmin() {
	cout << "Enter name: ";
	string name;
	cin >> name;
	cout << "Enter CNIC: ";
	string snic;
	cin >> snic;
	// check if cnic already exists
	if (checkIfUserExists(snic, "admin.txt")) {
		cout << "CNIC already exists." << endl;
		return;
	}
	cout << "Enter password: ";
	string password;
	cin >> password;
	addUserToFile(name, snic, password, "admin");

}
void admin::addCandidate() {
	cout << "Enter name: ";
	string name;
	cin >> name;
	cout << "Enter CNIC: ";
	string snic;
	cin >> snic;
	// check if cnic already exists
	if (checkIfUserExists(snic, "candidate.txt")) {
		cout << "CNIC already exists." << endl;
		return;
	}
	cout << "Enter password: ";
	string password;
	cin >> password;
	addUserToFile(name, snic, password, "candidate");
}