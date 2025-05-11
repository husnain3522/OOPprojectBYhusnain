#include "admin.h"
#include <iostream>
#include <string>
#include <fstream>
#include "user.h"
#include "election.h"
#include "candidate.h"
#include "voter.h"
#include<sstream>
#include<cstdlib> 

using namespace std;
bool checkInput(string input,string tag);

bool admin::isLogin(string name, string cnic, string password) {
	if (isLoginVar) {
		cout << "---------------------------------------------------" << endl;
		cout << "||              Login Successful                 ||" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "---------------------------------------------------" << endl;
		return 1;
			}
	else {
		cout << "---------------------------------------------------" << endl;
		cout << "||                 Login Failed                  ||" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "---------------------------------------------------" << endl;
		return 0;
			}
}

//default constructor for admin 


void admin::saveAdminToFile() {
	ofstream adminFile("admin.txt", ios::app);
	if (!adminFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error: Could not open admin.txt for writing." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	// Check if the CNIC of the current admin object already exists in the file
	if (checkIfUserExists(cnic, "admin")) { 
		cout << "---------------------------------------------------" << endl;
		cout << "Error: CNIC '" << cnic << "' already exists for an admin." << endl;
		cout << "Admin details were not saved." << endl;
		cout << "---------------------------------------------------" << endl;
		system("cls"); //  Clears the error message.
		return;
	}
	else {
		adminFile << name << "*" << cnic << "*" << password << endl; 
		cout << "---------------------------------------------------" << endl;
		cout << "Admin details (" << name << ") saved to admin.txt successfully." << endl;
		cout << "---------------------------------------------------" << endl;
	}
	adminFile.close();
}

void admin::addVoter() {
	system("cls");
	cout << "---------------------------------------------------" << endl;
	cout << "||               Add New Voter                   ||" << endl;
	cout << "---------------------------------------------------" << endl;
	string name, snic, password;

	cout << "Enter Voter's Name: ";
	cin >> name;
	cout << "---------------------------------------------------" << endl;

	cout << "Enter Voter's CNIC: ";
	cin >> snic;
	cout << "---------------------------------------------------" << endl;
	if (!checkInput(snic,"CNIC")) {
		system("pause");
		return;

	}

	if (checkIfUserExists(snic, "voter")) {
		cout << "---------------------------------------------------" << endl;
		cout << "Error: CNIC '" << snic << "' already exists for a voter." << endl;
		cout << "Cannot add duplicate voter." << endl;
		cout << "---------------------------------------------------" << endl;
		 system("pause"); 
		system("cls"); 
		return;
	}
	else {
		cout << "Enter Voter's Password: ";
		cin >> password;
		

		addUserToFile(name, snic, password, "voter");
		system("cls"); // Clear input prompts before showing success message.
		cout << "---------------------------------------------------" << endl;
		cout << "||         Voter Added Successfully!             ||" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "Name: " << name << endl;
		cout << "CNIC: " << snic << endl;
		cout << "---------------------------------------------------" << endl;
		 system("pause"); 
		 system("cls"); 
	}
}

void admin::addAdmin() {
	system("cls");
	cout << "---------------------------------------------------" << endl;
	cout << "||               Add New Admin                   ||" << endl;
	cout << "---------------------------------------------------" << endl;
	string name, snic, password;

	cout << "Enter Admin's Name: ";
	cin >> name;
	cout << "---------------------------------------------------" << endl;

	cout << "Enter Admin's CNIC: ";
	cin >> snic;
	if (!checkInput(snic,"CNIC")) {
		system("pause");
		return;

	}

	cout << "---------------------------------------------------" << endl;

	if (checkIfUserExists(snic, "admin")) {
		cout << "---------------------------------------------------" << endl;
		cout << "Error: CNIC '" << snic << "' already exists for an admin." << endl;
		cout << "Cannot add duplicate admin." << endl;
		cout << "---------------------------------------------------" << endl;
		 system("pause"); 
		system("cls"); // Clears the error message.
		return;
	}
	else {
		cout << "Enter Admin's Password: ";
		cin >> password;
		

		addUserToFile(name, snic, password, "admin");
		system("cls"); // Clear input prompts before showing success message.
		cout << "---------------------------------------------------" << endl;
		cout << "||         Admin Added Successfully!             ||" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "Name: " << name << endl;
		cout << "CNIC: " << snic << endl;
		cout << "---------------------------------------------------" << endl;
		 system("pause"); 
	}
}

void admin::addCandidate() {
	system("cls");
	cout << "---------------------------------------------------" << endl;
	cout << "||            Add New Candidate(s)               ||" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "How many Candidates do you want to add? ";
	int num;
	string numStr;
	cin >> numStr;
	if (!checkInput(numStr,"Num Of Candidates")) {
		system("pause");
		return;

	}
	num = stoi(numStr);

	system("cls"); //  Clears after getting 'num'.

		string name, snic, partyId;
	for (int i = 0; i < num; i++) {
	AgainEnterData:
		system("cls"); // Clear screen for each new candidate or re-entry
		cout << "---------------------------------------------------" << endl;
		cout << "||      Adding Candidate " << (i + 1) << " of " << num << "             ||" << endl;
		cout << "---------------------------------------------------" << endl;

		cout << "Enter Name for Candidate " << (i + 1) << ": ";


		cin >> name;
		cout << "---------------------------------------------------" << endl;
	
		cout << "Enter CNIC for Candidate " << (i + 1) << ": ";
		cin >> snic;
		if (!checkInput(snic,"CNIC")) {
			system("pause");
			goto AgainEnterData;

		}

		cout << "---------------------------------------------------" << endl;

		if (checkIfUserExists(snic, "candidate")) {
			cout << "---------------------------------------------------" << endl;
			cout << "Error: CNIC '" << snic << "' already exists for a candidate." << endl;
			cout << "Please re-enter details for Candidate " << (i + 1) << "." << endl;
			cout << "---------------------------------------------------" << endl;
			 system("pause"); 
			system("cls"); 
			goto AgainEnterData;
		}
		else {
			cout << "Enter Party ID for Candidate " << (i + 1) << ": ";
			cin >> partyId;
			system("cls"); 

			if (checkIfPartyIdExists(partyId)) {
				cout << "---------------------------------------------------" << endl;
				cout << "Error: Party ID '" << partyId << "' is already assigned." << endl;
				cout << "---------------------------------------------------" << endl;
			
				system("cls"); 

				cout << "---------------------------------------------------" << endl;
				cout << "Options for Candidate " << (i + 1) << " (Party ID conflict):" << endl;
				cout << "  1: Re-enter all credentials for this candidate" << endl;
				cout << "  2: Skip adding this candidate" << endl;
				cout << "---------------------------------------------------" << endl;
				cout << "Your choice (1 or 2): ";
				int choice;
				cin >> choice;
				system("cls"); // Clear choice prompt before action

				if (choice == 1)
					goto AgainEnterData;
				else {
					cout << "---------------------------------------------------" << endl;
					cout << "Skipping Candidate " << (i + 1) << "." << endl;
					cout << "---------------------------------------------------" << endl;
					
					system("cls");
					continue; // Skip this candidate
				}
			}
			addUserToFile(name, snic, partyId, "candidate");
			
			cout << "---------------------------------------------------" << endl;
			cout << "||      Candidate Added Successfully!            ||" << endl;
			cout << "---------------------------------------------------" << endl;
			cout << "Candidate " << (i + 1) << ": " << name << " (Party ID: " << partyId << ")" << endl;
			cout << "---------------------------------------------------" << endl;
			 system("pause"); 
			system("cls"); 
		}
	}
	
	cout << "---------------------------------------------------" << endl;
	cout << "||       All Candidates Processed.               ||" << endl;
	cout << "---------------------------------------------------" << endl;
	
}


void admin::createElection(int id) {
	string name, date, time_duration_value, fileNameToStoreName;
	int election_type_choice, time_unit_choice;

reEnterName:
	system("cls");
	cout << "---------------------------------------------------" << endl;
	cout << "||             Create New Election               ||" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Select Election Type:" << endl;
	cout << "  1 : National Election" << endl;
	cout << "  2 : Local Election" << endl;
	cout << "  3 : Regional Election" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Enter your choice (1-3): ";
	cin >> election_type_choice;



	if (election_type_choice == 1) {
		system("cls");
		name = "National Election";
		fileNameToStoreName = "nationalElection";
		cout << "---------------------------------------------------" << endl;
		cout << "||     Selected: National Election               ||" << endl;
		cout << "---------------------------------------------------" << endl;
	}
	else if (election_type_choice == 2) {
		system("cls");
		name = "Local Election";
		fileNameToStoreName = "localElection";
		cout << "---------------------------------------------------" << endl;
		cout << "||       Selected: Local Election                ||" << endl;
		cout << "---------------------------------------------------" << endl;
	}
	else if (election_type_choice == 3) {
		system("cls");
		name = "Regional Election";
		fileNameToStoreName = "regionalElection";
		cout << "---------------------------------------------------" << endl;
		cout << "||     Selected: Regional Election               ||" << endl;
		cout << "---------------------------------------------------" << endl;
	}
	else {
		system("cls");
		cout << "---------------------------------------------------" << endl;
		cout << "|| Invalid choice. Please enter a number (1-3).  ||" << endl;
		cout << "---------------------------------------------------" << endl;
		goto reEnterName;
	}

	cout << "Enter Election Date (e.g., YYYY-MM-DD): ";
	cin >> date;
	system("cls"); 

reEnterHrs:
	
	cout << "---------------------------------------------------" << endl;
	cout << "||        Configure Election Duration            ||" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Select Election Duration Unit:" << endl;
	cout << "  1 : Days" << endl;
	cout << "  2 : Hours" << endl;
	cout << "  3 : Seconds" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Enter your choice (1-3): ";
	string time_unit_choiceStr;
	cin >> time_unit_choiceStr;
	if (!checkInput(time_unit_choiceStr,"Duration Option")) {
		system("pause");
		system("cls");
		goto reEnterHrs;
	}
	time_unit_choice = stoi(time_unit_choiceStr);



	int durationTypeIndicator = 0; // Used for addElectionToFileWithCandies

	if (time_unit_choice == 1) {
		enterDays:
		system("cls");
		cout << "---------------------------------------------------" << endl;
		cout << "||         Duration Unit: Days                   ||" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter Election Duration (in Days): ";
		string time_duration_valueStr;
		cin >> time_duration_valueStr;
		if (!checkInput(time_duration_valueStr, "Duration")) {
			system("pause");
			goto enterDays;

		}
		time_duration_value = stoi(time_duration_valueStr);
		durationTypeIndicator = 1;
		system("cls"); 
	}
	else if (time_unit_choice == 2) {
		enterHours:
		system("cls");
		cout << "---------------------------------------------------" << endl;
		cout << "||         Duration Unit: Hours                  ||" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter Election Duration (in Hours): ";
		string time_duration_valueStr;
		cin >> time_duration_valueStr;
		if (!checkInput(time_duration_valueStr,"Duration")) {
			system("pause");
			goto enterHours;

		}
		time_duration_value = stoi(time_duration_valueStr);


		durationTypeIndicator = 2;
		system("cls"); 
	}
	else if (time_unit_choice == 3) {
		enterSeconds:
		system("cls");
		cout << "---------------------------------------------------" << endl;
		cout << "||         Duration Unit: Seconds                ||" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter Election Duration (in Seconds): ";
		string time_duration_valueStr;
		cin >> time_duration_valueStr;
		if (!checkInput(time_duration_valueStr, "Duration")) {
			system("pause");
			goto enterSeconds;

		}
		time_duration_value = stoi(time_duration_valueStr);

		durationTypeIndicator = 3;
		system("cls");
	}
	else {
		system("cls");
		cout << "---------------------------------------------------" << endl;
		cout << "|| Invalid choice. Please enter a number (1-3).  ||" << endl;
		cout << "---------------------------------------------------" << endl;
		
		goto reEnterHrs;
	}

	// Region Codes (as per original logic, numRegions is fixed to 1 for input here)
	int numInputRegions = 1; // Based on original code: int numRegions=1;
	string* regionCodes = new string[numInputRegions];

	// Screen is clear from previous step.
	cout << "---------------------------------------------------" << endl;
	cout << "||           Configure Region Code(s)            ||" << endl;
	cout << "---------------------------------------------------" << endl;
	for (int i = 0; i < numInputRegions; i++) {
		cout << "Enter Region Code " << i + 1 << ": ";
		cin >> regionCodes[i];
		cout << "---------------------------------------------------" << endl;
	}
	system("cls"); // Original placement: Clears after all region codes are entered.

	election e(name, date, time_duration_value, numInputRegions); // Original constructor uses numInputRegions
	e.setElectionId(id);
	e.setRegionCodes(regionCodes, numInputRegions); // Sets the actual region codes

	
	e.addElectionToFileWithCandies(durationTypeIndicator, fileNameToStoreName);
	delete[] regionCodes;

	// Screen is clear. Display success message.
	cout << "---------------------------------------------------" << endl;
	cout << "||   Election (" << name << ") Created Successfully!  ||" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Details:" << endl;
	cout << "  ID: " << id << endl;
	cout << "  Date: " << date << endl;
	cout << "  Duration: " << time_duration_value;
	if (time_unit_choice == 1) cout << " Days" << endl;
	else if (time_unit_choice == 2) cout << " Hours" << endl;
	else if (time_unit_choice == 3) cout << " Seconds" << endl;
	cout << "---------------------------------------------------" << endl;
	
}

bool checkInput(string input,string tag) {

	//checking if it is storing int valur or string
	stringstream ss(input);
	int num;
	char extra;

	// Try to parse an integer
	if (!(ss >> num)) {
		cout << "---------------------------------------------------" << endl;
		cout << "Error: "<<tag<<" '" << input << "' " << tag << " Must be in NUMERIC." << endl;
		cout << "---------------------------------------------------" << endl;
		return false;
	}

	// Check if there's any non-integer character left
	if (ss >> extra) {
		cout << "---------------------------------------------------" << endl;
		cout << "Error: " << tag << " '" << input << "' " << tag << " Must be in NUMERIC." << endl;
		cout << "---------------------------------------------------" << endl;
		return false;
	}

	return true;


}