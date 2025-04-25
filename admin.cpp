#include "admin.h"
#include <iostream>
#include <string>
#include <fstream>
#include "user.h"
#include "election.h"
#include "candidate.h"
#include "voter.h"

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
	if (checkIfUserExists(snic, "voter")) {
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
		cout << "Enter PartyId according to National Party Meeting held By Prof.Dr.Muhammad Husnain\nYou may read some Party IDs in PartyDetails.txt ";
		string partyId;
		cin >> partyId;
		if (checkIfPartyIdExists(partyId))
		{
			cout << "Party Candidate already exists." << endl;
			cout << "Press 1 to Re Enter Credentials\nPress 2 to Skip this candidate" << endl;
			int choice;
			cin >> choice;
			if (choice == 1)
				goto AgainEnterData;
			else
				continue;
			
		}
		addUserToFile(name, snic, partyId, "candidate");
	}

}

void admin::createElection() {
	reEnterName:
	cout << "Enter ( 1 - 3 ) Respectively\n1 : National\n2 : Local \n3 : Regional ";
	int choice;
	string name; 
	cin >> choice;
	if (choice == 1) {
		cout << "You have selected National Election" << endl;
		name = "National Election";
	}
	else if (choice == 2) {
		cout << "You have selected Local Election" << endl;
		name = "Local Election";
	}
	else if (choice == 3) {
		cout << "You have selected Regional Election" << endl;
		name = "Regional Election";
	}
	else {
		cout << "Invalid choice." << endl;
		goto reEnterName;
	}
	cout << "Enter Election Date: ";
	string date;
	cin >> date;
	string time;

	reEnterHrs:
	cout << "Enter Election Time :: Press 1 - 2 repectively\n1 : Hours\nDays ";
	int choice1;
	cin >> choice1;
	if (choice1 == 1) {
		cout << "You have selected Hours" << endl;
		cout << "Enter Time in Hours: ";
		cin >> time;
	}
	else if (choice1 == 2) {
		cout << "You have selected Days" << endl;
		cout << "Enter Time in Days: ";
		cin >> time;

	}
	else {
		cout << "Invalid choice." << endl;
		goto reEnterHrs;
	}

	//cout << "Enter Number of Regions: ";
	int numRegions=1;
	
	string* regionCodes = new string[numRegions];
	for (int i = 0; i < numRegions; i++) {
		cout << "Enter Region Code " << i + 1 << ": ";
		cin >> regionCodes[i];
	}
	election e(name, date, time, numRegions);
	e.setRegionCodes(regionCodes, numRegions);
	// were using numRegions due to change of plan disccused by our team
	// here num regions show that you have slected hours or days
	if (choice1 == 1)
		numRegions = 1;
	else if (choice1 == 2)
		numRegions = 2;

	e.addElectionToFileWithCandies(numRegions);
	delete[] regionCodes;
}