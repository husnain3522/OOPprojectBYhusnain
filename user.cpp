#include "user.h"
#include <iostream>
#include <string>
#include <fstream>
#include"election.h"
using namespace std;

user::user(string n,string snic, string p) : name(n),cnic(snic), password(p) {

}

string user::getCnic() {
	return cnic;
}
void user::setCnic(string c) {
	cnic = c;
}
string user::getName() {
	return name;
}
string user::getPassword() {
	return password;
}
void user::setName(string n) {
	name = n;
}
void user::setPassword(string p) {
	password = p;
}
//bool user::isLogin() {
//
//	return true; // Placeholder for actual login logic
//}

void user::display() {
	system("cls");
	cout << "---------------------------------------------------" << endl;
	cout << "Name: " << name << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "CNIC: " << cnic << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Password: " << password << endl;
	cout << "---------------------------------------------------" << endl;
}
int user::fileLenght() {
	ifstream file("admin.txt");
	if (!file.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file." << endl;
		cout << "---------------------------------------------------" << endl;
		return -1;
	}
	int count = 0;
	string line;
	while (getline(file, line)) {
		count++;
	}
	file.close();
	return count;
}
int user::fileLenght(string fileName) {
	ifstream file(fileName + ".txt");
	if (!file.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file." << endl;
		cout << "---------------------------------------------------" << endl;
		return -1;
	}
	int count = 0;
	string line;
	while (getline(file, line)) {
		count++;
	}
	file.close();
	return count;
}
void user::addUserToFile(string name, string snic, string password, string fileName) {
	// checking if cnic already exists

	ofstream userFile((fileName + ".txt"), ios::app);
	if (!userFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	else {
		userFile << name << "*" << snic << "*" << password << endl;
		cout << fileName << " saved to file." << endl;
		cout << "---------------------------------------------------" << endl;
	}
	userFile.close();
}
bool user::checkIfUserExists(string inputCnic, string fileName) {
	ifstream userFile(fileName + ".txt");
	if (!userFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file." << endl;
		cout << "---------------------------------------------------" << endl;
		return false;
	}
	string serchedCnic;
	string temp;
	while (getline(userFile, temp, '*'))
	{
		getline(userFile, serchedCnic, '*');
		if (serchedCnic == inputCnic) {
			userFile.close();
			cout << "---------------------------------------------------" << endl;
			cout << "CNIC already exists." << endl;
			cout << "---------------------------------------------------" << endl;
			return true;
		}
		getline(userFile, temp, '\n');
	}
	userFile.close();
	return false;

}
void user::checkCredentials(string inputCnic, string inputPassword, string fileName) {
	ifstream userFile(fileName + ".txt");
	if (!userFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	string serchedCnic;
	string serchedPassword;
	string temp;
	while (getline(userFile, temp, '*'))
	{
		getline(userFile, serchedCnic, '*');
		getline(userFile, serchedPassword, '\n');
		if (serchedCnic == inputCnic && serchedPassword == inputPassword) {
			userFile.close();
			cout << "---------------------------------------------------" << endl;
			cout << "Login successful." << endl;
			cout << "---------------------------------------------------" << endl;
			return;
		}
	}
	cout << "---------------------------------------------------" << endl;
	cout << "Login failed to "<<fileName<< ".Something MisMatched" << endl;
	cout << "---------------------------------------------------" << endl;
}
bool user::checkIfPartyIdExists(string partyId) {
	ifstream partyFile("candidate.txt");
	if (!partyFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file." << endl;
		cout << "---------------------------------------------------" << endl;
		return false;
	}
	string serchedPartyId;
	string temp;
	while (getline(partyFile, temp, '*'))
	{
		getline(partyFile, serchedPartyId, '*');
		if (serchedPartyId == partyId) {
			partyFile.close();
			cout << "---------------------------------------------------" << endl;
			cout << "Party ID already exists." << endl;
			cout << "---------------------------------------------------" << endl;
			return true;
		}
		getline(partyFile, temp, '\n');
	}
	partyFile.close();
	cout << "---------------------------------------------------" << endl;
	cout << "Party ID does not exist." << endl;
	cout << "---------------------------------------------------" << endl;
	return false;
}
void user::viewElections() {
	ifstream electionFile("election.txt");
	if (!electionFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	election elec;
	string electionType, electionName, electionDate, electionTime,elecCodeNumberStr,selectedCandiStr,* selectedCandi;
	int elecCodeNumberInt,selectedCandiInt;
	int* regionCodes;
	
	while (getline(electionFile,electionName,'*')) {
		getline(electionFile, electionDate, '*');
		getline(electionFile, electionTime, '*');
		getline(electionFile, elecCodeNumberStr, '*');
		elecCodeNumberInt = stoi(elecCodeNumberStr);
		regionCodes = new int[elecCodeNumberInt];
		for (int i = 0; i < elecCodeNumberInt; i++) {
			getline(electionFile, elecCodeNumberStr, '*');
			regionCodes[i] = stoi(elecCodeNumberStr);
		}
		getline(electionFile, selectedCandiStr, '*');
		selectedCandiInt = stoi(selectedCandiStr);
		selectedCandi = new string[selectedCandiInt];
		for (int i = 0; i < selectedCandiInt; i++) {
			getline(electionFile, selectedCandiStr, '*');
			selectedCandi[i] = selectedCandiStr;
		}
		elec.setElectionName(electionName);
		elec.setElectionDate(electionDate);
		elec.setElectionTime(electionTime);
		 
		//elec.setRegionCodes(regionCodes, elecCodeNumberInt);


;
	}

		//cout << line << end
	electionFile.close();
}