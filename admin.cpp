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
	cout << "Enter Election Name: ";
	string name;
	cin >> name;
	cout << "Enter Election Date: ";
	string date;
	cin >> date;
	cout << "Enter Election Time: ";
	string time;
	cin >> time;
	cout << "Enter Number of Regions: ";
	int numRegions;
	cin >> numRegions;
	string* regionCodes = new string[numRegions];
	for (int i = 0; i < numRegions; i++) {
		cout << "Enter Region Code " << i + 1 << ": ";
		cin >> regionCodes[i];
	}
	election e(name, date, time, numRegions);
	e.setRegionCodes(regionCodes, numRegions);
	e.addElectionToFileWithCandies();
	delete[] regionCodes;
}