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

	if (isLoginVar) {
		cout << "---------------------------------------------------" << endl;
		cout << "Login Successful" << endl;
		return 1;
		cout << "---------------------------------------------------" << endl;
	}
	else {
		cout << "---------------------------------------------------" << endl;
		cout << "Login Failed" << endl;
		return 0;
		cout << "---------------------------------------------------" << endl;
	}

}
//default constructor for admin

void admin::saveAdminToFile() {  
   ofstream adminFile("admin.txt", ios::app);  
   if (!adminFile.is_open()) {  
	   cout << "---------------------------------------------------" << endl;
       cerr << "Error opening file." << endl;  
	   cout << "---------------------------------------------------" << endl;
       return;  
   }  
   //check that cnic already exist
   if (checkIfUserExists(cnic, "admin")) {
	   cout << "---------------------------------------------------" << endl;
	   cout << "CNIC already exists." << endl;
	   cout << "---------------------------------------------------" << endl;
	   return;
   }
   else {
	   cout << "---------------------------------------------------" << endl;
	   adminFile << name << "*" << cnic << "*" << password << endl;
	   cout << "Admin saved to file." << endl;
	   cout << "---------------------------------------------------" << endl;
   }
   adminFile.close();
}
void admin::addVoter() {
	cout << "---------------------------------------------------" << endl;
	cout << "Enter name: ";
	string name;
	cin >> name;
	cout << "---------------------------------------------------" << endl;
	cout << "Enter CNIC: ";
	string snic;
	cin >> snic;
	cout << "---------------------------------------------------" << endl;
	// check if cnic already exists
	if (checkIfUserExists(snic, "voter")) {
		cout << "---------------------------------------------------" << endl;
		cout << "CNIC already exists." << endl; 
		cout << "---------------------------------------------------" << endl;
		return;
	}
	else {
		cout << "---------------------------------------------------" << endl;
		cout << "Enter password: ";
		string password;
		cin >> password;
		cout << "---------------------------------------------------" << endl;
		addUserToFile(name, snic, password, "voter");
		cout << "Voter saved to file." << endl;
		cout << "---------------------------------------------------" << endl;
	}
	
}
void admin::addAdmin() {
	cout << "---------------------------------------------------" << endl;
	cout << "Enter name: ";
	string name;
	cin >> name;
	cout << "---------------------------------------------------" << endl;
	cout << "Enter CNIC: ";
	string snic;
	cin >> snic;
	cout << "---------------------------------------------------" << endl;
	// check if cnic already exists
	if (checkIfUserExists(snic, "admin")) {
		cout << "---------------------------------------------------" << endl;
		cout << "CNIC already exists." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	else {
		cout << "---------------------------------------------------" << endl;
		cout << "Enter password: ";
		string password;
		cin >> password;
		cout << "---------------------------------------------------" << endl; 
		addUserToFile(name, snic, password, "admin");
		cout << "Admin saved to file." << endl;
		cout << "---------------------------------------------------" << endl;
	}
}
void admin::addCandidate() {
	cout << "---------------------------------------------------" << endl;
	cout << "How many Candidates you want to add" << endl;
	int num;
	cin >> num;
	for (int i = 0; i < num; i++) {
	AgainEnterData:
		cout << "---------------------------------------------------" << endl;
		cout << "Enter name: ";
		string name;
		cin >> name;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter CNIC: ";
		string snic;
		cin >> snic;
		cout << "---------------------------------------------------" << endl;
		// check if cnic already exists
		if (checkIfUserExists(snic, "candidate")) {
			cout << "---------------------------------------------------" << endl;
			cout << "CNIC already exists." << endl;
			cout << "---------------------------------------------------" << endl;
			goto AgainEnterData;
		}
		else {
			cout << "---------------------------------------------------" << endl;
			cout << "Enter PartyId according to National Party Meeting  ";
			string partyId;
			cin >> partyId;
			if (checkIfPartyIdExists(partyId))
			{
				cout << "---------------------------------------------------" << endl;
				cout << "Party Candidate already exists." << endl;
				cout << "---------------------------------------------------" << endl;
				cout << "Press 1 to Re Enter Credentials\nPress 2 to Skip this candidate" << endl;
				cout << "---------------------------------------------------" << endl;
				int choice;
				cin >> choice;
				if (choice == 1)
					goto AgainEnterData;
				else
					continue;

			}
			addUserToFile(name, snic, partyId, "candidate");
			cout << "Candidate saved to file." << endl;
			cout << "---------------------------------------------------" << endl;
		}
	}

}

void admin::createElection(int id) {
reEnterName:
	cout << "---------------------------------------------------" << endl;
	cout << "Enter ( 1 - 3 ) Respectively\n1 : National\n2 : Local \n3 : Regional \n";
	cout << "---------------------------------------------------" << endl;
	int choice;
	string name; 
	cin >> choice;
	string fileNameToStoreName;
	if (choice == 1) {
		cout << "---------------------------------------------------" << endl;
		cout << "You have selected National Election" << endl;
		name = "National Election";
		fileNameToStoreName = "nationalElection";
	}
	else if (choice == 2) {
		cout << "---------------------------------------------------" << endl;
		cout << "You have selected Local Election" << endl;
		name = "Local Election";
		fileNameToStoreName = "localElection";
	}
	else if (choice == 3) {
		cout << "---------------------------------------------------" << endl;
		cout << "You have selected Regional Election" << endl;
		name = "Regional Election";
		fileNameToStoreName = "regionalElection";
	}
	else {
		cout << "---------------------------------------------------" << endl;
		cout << "Invalid choice." << endl;
		cout << "---------------------------------------------------" << endl;
		goto reEnterName;
	}
	cout << "---------------------------------------------------" << endl;
	cout << "Enter Election Date: ";
	string date;
	cin >> date;
	string time;
	cout << "---------------------------------------------------" << endl;
reEnterHrs:
	cout << "---------------------------------------------------" << endl;
	cout << "Enter Election Time :: Press 1 - 2 repectively\n1 : Days\n2 Hours \n3 Seconds \n";
	cout << "---------------------------------------------------" << endl;
	int choice1;
	cin >> choice1;
	if (choice1 == 1) {
		cout << "---------------------------------------------------" << endl;
		cout << "You have selected Days" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter Time in Days: ";
		cout << "---------------------------------------------------" << endl;
		cin >> time;
	}
	else if (choice1 == 2) {
		cout << "---------------------------------------------------" << endl;
		cout << "You have selected Hours" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter Time in Hours: ";
		cout << "---------------------------------------------------" << endl;
		cin >> time;

	}
	else if (choice1 == 3) {
		cout << "---------------------------------------------------" << endl;
		cout << "You have selected Seconds" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter Time in Seconds: ";
		cout << "---------------------------------------------------" << endl;
		cin >> time;

	}
	else {
		cout << "---------------------------------------------------" << endl;
		cout << "Invalid choice." << endl;
		cout << "---------------------------------------------------" << endl;
		goto reEnterHrs;
	}

	//cout << "Enter Number of Regions: ";
	int numRegions=1;
	
	string* regionCodes = new string[numRegions];
	for (int i = 0; i < numRegions; i++) {
		cout << "---------------------------------------------------" << endl;
		cout << "Enter Region Code " << i + 1 << ": ";
		cin >> regionCodes[i];
		cout << "---------------------------------------------------" << endl;
	}
	
	election e(name, date, time, numRegions);
	e.setElectionId(id);
	e.setRegionCodes(regionCodes, numRegions);
	// were using numRegions due to change of plan disccused by our team
	// here num regions show that you have slected hours or days
	if (choice1 == 1)
		numRegions = 1;
	else if (choice1 == 2)
		numRegions = 2;
	else if (choice1 == 3)
		numRegions = 3;

	e.addElectionToFileWithCandies(numRegions,fileNameToStoreName);
	delete[] regionCodes;
}
