#include "election.h"
#include <iostream>
#include <string>
#include <fstream>
#include "candidate.h"
#include "voter.h"
#include <ctime>
#include<cstdlib>
using namespace std;

int election::fileLenght(string fileName) {
	ifstream file((fileName + ".txt"));
	if (!file.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file." << fileName << endl;
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
election::election(string name = "", string date = "0", string time = "0", int numRegioons = 0) {
	electionName = name;
	electionDate = date;
	electionTime = time;
	numberOfRegions = numRegioons;
	regionCodes = new string[numRegioons];
}

void election::setElectionName(string name) {
	electionName = name;
}
void election::setElectionDate(string date) {
	electionDate = date;
}
void election::setElectionTime(string time) {
	electionTime = time;
}
void election::setRegionCodes(string* codes, int numRegions) {
	regionCodes = new string[numRegions];
	for (int i = 0; i < numRegions; i++) {
		regionCodes[i] = codes[i];
	}
	numberOfRegions = numRegions;
}
string election::getElectionName() {
	return electionName;
}
string election::getElectionDate() {
	return electionDate;
}
string election::getElectionTime() {
	return electionTime;
}
string* election::getRegionCodes() {
	return regionCodes;
}
int election::getNumberOfRegions() {
	return numberOfRegions;
}
void election::displayElectionDetails() {
	cout << "---------------------------------------------------" << endl;
	cout << "Election Name: " << electionName << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Election Date: " << electionDate << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Election Time: " << electionTime << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Duration: " << duration << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Region Codes: ";
	cout << "---------------------------------------------------" << endl;
	/*for (int i = 0; i< 1; i++) {
		cout << regionCodes[i] << " ";
	}*/
	//for (int i = 0; i < numOfCandidates; i++) {
	displayCandiates(selCandidates, numOfCandidates);
	cout << "---------------------------------------------------" << endl;
	//}
	cout << endl;
}
candidate* election::getCandidateArray() {
	int totalCandidates = fileLenght("candidate");
	candidate* candiArray = new candidate[totalCandidates];
	ifstream candidateFile("candidate.txt");
	if (!candidateFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file." << endl;
		cout << "---------------------------------------------------" << endl;
		return nullptr;
	}
	for (int i = 0; i < totalCandidates; i++)
	{
		string name, cnic, partyId;
		getline(candidateFile, name, '*');
		getline(candidateFile, cnic, '*');
		getline(candidateFile, partyId, '\n');
		candiArray[i].setName(name);
		candiArray[i].setCnic(cnic);
		candiArray[i].setPartyName(partyId);
	}
	return candiArray;
}

void election::displayCandiates(candidate* candiArray, int totalCandis) {
	
	cout << "---------------------------------------------------" << endl;
	cout << "Candidates:" << endl;
	cout << "---------------------------------------------------" << endl;
	for (int i = 0; i < totalCandis; i++) {
		cout << "---------------------------------------------------" << endl;
		cout << "Name: " << candiArray[i].getName() << endl;
	
		cout << "CNIC: " << candiArray[i].getCnic() << endl;
	
		cout << "Party Name: " << getPartyNameToSetInCandidate(stoi(candiArray[i].getPartyName())) << endl;
		candiArray[i].getPartyNameInString();
		cout << "---------------------------------------------------" << endl;
	}

}
candidate* deleteAcandy(candidate* candiArray, int candyIndex, int total) {
	// Create a new array with size reduced by 1  
	candidate* tempArray = new candidate[total - 1];

	for (int i = 0, j = 0; i < total; i++) {
		if (i != candyIndex) {
			tempArray[j++] = candiArray[i];
		}
	}

	// Free the old array memory  
	delete[] candiArray;

	// Return the new array  
	return tempArray;
}candidate* election::addSelectedCandidate(candidate candi, candidate* selectedCandidates, int lenOfSelectedCandis) {
	cout << "---------------------------------------------------" << endl;
	cout << "Adding candidate to selectedCandidates array..." << endl;
	cout << "---------------------------------------------------" << endl;
	// Create new array with size +1
	candidate* tempArray = new candidate[lenOfSelectedCandis + 1];

	// Copy existing candidates (if any)
	if (lenOfSelectedCandis > 0) {
		for (int i = 0; i < lenOfSelectedCandis; i++) {
			tempArray[i] = selectedCandidates[i];
		}
	}

	// Add the new candidate
	tempArray[lenOfSelectedCandis] = candi;

	// Free old memory
	delete[] selectedCandidates;

	// Return new array
	return tempArray;
}

candidate* election::selectCandidates() {
	int totalCandidates = fileLenght("candidate");
	cout << "---------------------------------------------------" << endl;
	cout << "total candidates are " << totalCandidates << endl;
	cout << "---------------------------------------------------" << endl;
	candidate* candiArray = new candidate[totalCandidates];
	candiArray = getCandidateArray();
	ifstream candidateFile("candidate.txt");
	if (!candidateFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file." << endl;
		cout << "---------------------------------------------------" << endl;
		return nullptr;
	}
	bool selectNext = true;
	candidate* selectedCandidates;
	selectedCandidates = nullptr;
	int selectedCandidatesLength = 0;
	while (selectNext) {
		if (totalCandidates == 0) {
			cout << "---------------------------------------------------" << endl;
			cout << "No candidates available." << endl;
			cout << "---------------------------------------------------" << endl;
			break;
		}
		displayCandiates(candiArray, totalCandidates);
		cout << "---------------------------------------------------" << endl;
		cout << "Select a candidate by entering their CNIC: ";
		string cnic;
		cin >> cnic;
		cout << "---------------------------------------------------" << endl;

		for (int i = 0; i < totalCandidates; i++) {
			if (candiArray[i].getCnic() == cnic) {
			
				selectedCandidates = addSelectedCandidate(candiArray[i], selectedCandidates, selectedCandidatesLength);
				selectedCandidatesLength++;
			
				cout << "---------------------------------------------------" << endl;
				cout << "Candidate selected: " << candiArray[i].getName() << endl;
				cout << "---------------------------------------------------" << endl;

				//delete that candidate from that array and add it to selected candies
				candiArray = deleteAcandy(candiArray, i, totalCandidates);

				totalCandidates--;

				reEnterYN:
				cout << "---------------------------------------------------" << endl;
				cout << "Do You want to add More Candidates (y/n): ";
				cout << "---------------------------------------------------" << endl;
				char choice;
				cin >> choice;
				if (choice == 'y' || choice == 'Y') {
					selectNext = true;
				}
				else if (choice == 'n' || choice == 'N') {
					selectNext = false;
					break;
				}
				else {
					cout << "---------------------------------------------------" << endl;
					cout << "|| Invalid choice. Please enter a Char (Y-N).  ||" << endl;
					cout << "---------------------------------------------------" << endl;
					system("pause");
					system("clear");
					goto reEnterYN;
				}

			}
		
		}
		
		if (selectNext == false) {
			break;
		}
		else {
			cout << "---------------------------------------------------" << endl;
			cout << "Candidate not found. Please try again." << endl;
			cout << "---------------------------------------------------" << endl;
		}
		

	}
	delete[] candiArray;
	ofstream lengh("lenghOfSelectedCandies.txt");
	lengh << selectedCandidatesLength;
	lengh.close();
	cout << "---------------------------------------------------" << endl;
	cout << "selected candidates are " << selectedCandidatesLength << endl;
	cout << "---------------------------------------------------" << endl;
	displayCandiates(selectedCandidates, selectedCandidatesLength);
	cout << "---------------------------------------------------" << endl;
	return selectedCandidates;

}
void election::addElectionToFileWithCandies(int timeType, string fileName) {
	int totalCandidates = fileLenght("candidate");

	candidate* candiArray = new candidate[totalCandidates];
	cout << "---------------------------------------------------" << endl;
	cout << "Here Is list of '"<<totalCandidates<<"' candidates" << endl;
	cout << "---------------------------------------------------" << endl;
	ofstream electionFile(fileName + ".txt", ios::app);

	if (!electionFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	

	candiArray = selectCandidates();

	int len;
	ifstream fileF("lenghOfSelectedCandies.txt");
	fileF >> len;
	
	int selectedCandidatesLength = len;
	
	ofstream electionVoteFile(to_string(electionId) + ".txt", ios::app);
	ofstream electionVoteFileToMain("electionData.txt", ios::app);
	ofstream electionNameFile("electionNames.txt", ios::app);
	electionNameFile << electionId << "*" << electionName << "*" << selectedCandidatesLength << endl;
	electionNameFile.close();

	electionFile << electionId << "*" << electionName << "*" << electionDate << "*" << electionTime << "*" << timeType;
	electionVoteFileToMain << electionId << "*" << electionName << "*" << electionDate << "*" << electionTime << "*" << timeType;

	for (int i = 0; i < numberOfRegions; i++) {
		electionFile << "*" << regionCodes[i] << "*" << selectedCandidatesLength;
		electionVoteFileToMain << "*" << regionCodes[i] << "*" << selectedCandidatesLength;
	}
	for (int i = 0; i < selectedCandidatesLength; i++) {
		electionFile << "*" << candiArray[i].getCnic();
		electionVoteFileToMain << "*" << candiArray[i].getCnic();
		electionVoteFile << electionId << "*" << candiArray[i].getCnic() << "*" << 0 << endl;
	}
	electionFile << "*0" << endl;
	electionVoteFileToMain << "*0" << endl;
	electionVoteFileToMain.close();
	electionVoteFile.close();




	cout << "---------------------------------------------------" << endl;
	cout << "Election saved to file." << endl;


	cout << "---------------------------------------------------" << endl;

}

void election::loadElectionFromFile(string fileName, int load) {

	int fileLen = fileLenght(fileName);
	ifstream electionFile(fileName + ".txt");
	if (!electionFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	//string electionName, electionDate, electionTime, regionCode;
	//string duration;
	//string selectedCandi;
	//int selectedCandiInt;
	//int* regionCodes;
	string line;
	for (int i = 0; i < fileLen; i++)
	{
		//cout << "load is L:: " << load << endl;

		if (i < load - 1) {
			getline(electionFile, line, '\n');
		}
	}
	string electionIdStr;
	getline(electionFile, electionIdStr, '*');
	electionId = stoi(electionIdStr);
	
	getline(electionFile, electionName, '*');
	getline(electionFile, electionDate, '*');
	getline(electionFile, electionTime, '*');
	
	string durationStr;
	getline(electionFile, durationStr, '*');
	duration = stoi(durationStr);

	getline(electionFile, regionCode, '*');
	string numOfCandidatesStr;
	getline(electionFile, numOfCandidatesStr, '*');
	numOfCandidates = stoi(numOfCandidatesStr);
	string* candidateCnic = new string[numOfCandidates];
	selCandidates = new candidate[numOfCandidates];
	//selCandidatesCnic = 
	ifstream candidateVoteFile(to_string(electionId) + ".txt");
	if (!candidateVoteFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	string temp;
	for (int i = 0; i < numOfCandidates; i++) {

		getline(candidateVoteFile, temp, '*');
		
		getline(candidateVoteFile, temp, '*');
	
		getline(candidateVoteFile, temp, '\n');
		
		selCandidates[i].setVoteCount(stoi(temp));


		getline(electionFile, candidateCnic[i], '*');

		selCandidates[i].getCandidateByCnic(candidateCnic[i]);
		selCandidates[i].setPartyString(getPartyNameToSetInCandidate(stoi(candidateCnic[i])));

	}
	string isActiveStr;
	getline(electionFile, isActiveStr, '\n');
	if (isActiveStr == "1") {
		isActive = true;
	}
	else {
		isActive = false;
	}
	electionFile.close();
}
void election::saveElectionVotesToFile() {
	ofstream candidateVote(to_string(electionId) + ".txt");
	if (!candidateVote.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file to save candidate votes." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	for (int i = 0; i < numOfCandidates; i++) {
		candidateVote << electionId << "" << selCandidates[i].getCnic() << "" << selCandidates[i].getVoteCount();
		candidateVote << endl;
	}cout << "---------------------------------------------------" << endl;
	cout << "candidateVote ssaved to file :: " << selCandidates[0].getName() << "::" << selCandidates[0].getVoteCount() << endl;
	cout << "---------------------------------------------------" << endl;
	candidateVote.close();
}

void election::castVote(voter* v, int candidateId) {
	cout << "---------------------------------------------------" << endl;
	cout << "Casting vote for candidate with ID: " << candidateId << endl;
	cout << "---------------------------------------------------" << endl;
	for (int i = 0; i < numOfCandidates; i++) {
		if (selCandidates[i].getCnicInt() == candidateId) {
			selCandidates[i].incrementVoteCount();
			cout << "---------------------------------------------------" << endl;
			cout << "Vote count for candidate " << selCandidates[i].getName() << ": " << selCandidates[i].getVoteCount() << endl;
			saveCandidateVotesToFile(selCandidates);


			cout << "---------------------------------------------------" << endl;
			cout << "Vote casted successfully for candidate: " << selCandidates[i].getName() << endl;
			cout << "---------------------------------------------------" << endl;
			break;
		}
	}
}
void election::saveCandidateVotesToFile(candidate* candi) {
	ofstream candidateVote(to_string(electionId) + ".txt");
	if (!candidateVote.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file to save candidate votes." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	for (int i = 0; i < getTotalCandidates();i++) {
		candidateVote << electionId << "*" << candi[i].getCnic() << "*" << candi[i].getVoteCount() << endl;
	}
	cout << "---------------------------------------------------" << endl;
	cout << "candidateVote ssaved to file :: " << candi->getName() << "::" << candi->getVoteCount() << endl;
	cout << "---------------------------------------------------" << endl; 
	candidateVote.close();
}
string election::getPartyNameToSetInCandidate(int id) {
	int len = fileLenght("partyNames");
	ifstream partyNameFile("partyNames.txt");
	if (!partyNameFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file." << endl;
		cout << "---------------------------------------------------" << endl;
		return "not found";
	}
	string partyId, partyName;
	for (int i = 0; i < len; i++) {
		getline(partyNameFile, partyId, '*');
		getline(partyNameFile, partyName, '\n');
		if (partyId == to_string(id)) {
		
			return partyName;
		}



	}
	return "not found";




}
time_t election::calculateFutureTime(int amount, int type) {
	time_t now = time(NULL); // current time in seconds

	if (type == 1) {
		now += amount * 24 * 60 * 60; // Add days in seconds
		cout << "---------------------------------------------------" << endl;
		cout << "Election Time in days is " << amount << endl;
		cout << "---------------------------------------------------" << endl;

	}
	else if (type == 3) {
		now += amount /** 60 * 60*/; // Add seconds
		cout << "---------------------------------------------------" << endl; 
		cout << "Election Time in seconds is " << amount << endl;
		cout << "---------------------------------------------------" << endl;
	}
	else if (type == 2) {
		now += amount * 60 * 60; // Add hours in hours
		cout << "---------------------------------------------------" << endl; 
		cout << "Election Time  in hours is " << amount << endl;
		cout << "---------------------------------------------------" << endl;
	}
	else {
		cout << "---------------------------------------------------" << endl;
		cerr << "Invalid type. Use 'd' for days or 'h' for hours.\n''s' for seconds\n";
		cout << "---------------------------------------------------" << endl;
	}
	
	futureTime = now;
	return now;
}

bool election::hasTimePassed(time_t futureTime) {
	time_t now = time(NULL);
	
	return now >= futureTime;
}