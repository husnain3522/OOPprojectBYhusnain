#include "admin.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
bool admin::isLogin(string name, string cnic, string password) {

	if (isLoginVar)
		return 1;
	else 
		return 0;


}
//default constructor for admin

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
	if (checkIfUserExists(snic, "admin")) {
		cout << "CNIC already exists." << endl;
		return;
	}
	cout << "Enter password: ";
	string password;
	cin >> password;
	addUserToFile(name, snic, password, "admin");

}
void admin::addCandidate() {

	cout << "How many Candidates you want to add" << endl;
	int num;
	cin >> num;
	for (int i = 0; i < num; i++) {
		AgainEnterData:
		cout << "Enter name: ";
		string name;
		cin >> name;
		cout << "Enter CNIC: ";
		string snic;
		cin >> snic;
		// check if cnic already exists
		if (checkIfUserExists(snic, "candidate")) {
			cout << "CNIC already exists." << endl;
			goto AgainEnterData;
		}
		cout << "Enter password: ";
		string password;
		cin >> password;
		addUserToFile(name, snic, password, "candidate");
	}

	cout << "Enter name: ";
	string name;
	cin >> name;
	cout << "Enter CNIC: ";
	string snic;
	cin >> snic;
	// check if cnic already exists
	if (checkIfUserExists(snic, "candidate")) {
		cout << "CNIC already exists." << endl;
		return;
	}
	cout << "Enter password: ";
	string password;
	cin >> password;
	addUserToFile(name, snic, password, "candidate");
}
