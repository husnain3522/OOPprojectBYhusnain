#include "election.h"
#include <iostream>
#include <string>
#include <fstream>
#include "candidate.h"
#include "voter.h"
using namespace std;

int election::fileLenght(string fileName) {
	ifstream file((fileName + ".txt"));
	if (!file.is_open()) {
		cerr << "Error opening file." << fileName << endl;
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
//void election::setElectionId(int id) {
//	electionId = id;
//}
//int election::getElectionId() {
//	return electionId;
//}
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
	cout << "Election Name: " << electionName << endl;
	cout << "Election Date: " << electionDate << endl;
	cout << "Election Time: " << electionTime << endl;
	cout << "Duration: " << duration << endl;
	cout << "Region Codes: ";
	/*for (int i = 0; i< 1; i++) {
		cout << regionCodes[i] << " ";
	}*/
	//for (int i = 0; i < numOfCandidates; i++) {
		displayCandiates(selCandidates, numOfCandidates);
	//}
	cout << endl;
}
candidate* election::getCandidateArray() {
	int totalCandidates = fileLenght("candidate");
	candidate* candiArray = new candidate[totalCandidates];
	ifstream candidateFile("candidate.txt");
	if (!candidateFile.is_open()) {
		cerr << "Error opening file." << endl;
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

void election::displayCandiates(candidate* candiArray,int totalCandis) {
	//find candidates in array
	cout << "were are in display candidates" << endl;

	
	cout << "Total candis are " << totalCandis << endl;

	cout << "Candidates:" << endl;
	for (int i = 0; i < totalCandis; i++) {
		cout << "Name: " << candiArray[i].getName() << endl;
		cout << "Name 2: " << candiArray[i].getName() << endl;

		cout << "CNIC: " << candiArray[i].getCnic() << endl;
		cout << "Party Name: " << candiArray[i].getPartyName() << endl;
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
	cout << "Adding candidate to selectedCandidates array..." << endl;

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
	cout << "total candidates are " << totalCandidates << endl;
	candidate* candiArray = new candidate[totalCandidates];
	candiArray = getCandidateArray();
	ifstream candidateFile("candidate.txt");
	if (!candidateFile.is_open()) {
		cerr << "Error opening file." << endl;
		return nullptr;
	}
	bool selectNext = true;
	candidate* selectedCandidates;
	selectedCandidates = nullptr;
	int selectedCandidatesLength = 0;
	while (selectNext) {
		if (totalCandidates == 0) {
			cout << "No candidates available." << endl;
			break;
		}
		displayCandiates(candiArray,totalCandidates);
		cout << "Select a candidate by entering their CNIC: ";
		string cnic;
		cin >> cnic;
		cout << "we are just before cncin" << endl;
		for (int i = 0; i < totalCandidates; i++) {
			cout << "we are in for loop "<<i << endl;
		
	
			if (candiArray[i].getCnic() == cnic) {
				cout << "we are in if" << endl;
				//add that candidate to selected candidates
				cout << "we are selcting" << endl;
				selectedCandidates = addSelectedCandidate (candiArray[i], selectedCandidates, selectedCandidatesLength);
				selectedCandidatesLength++;
				cout << "we are selcted" << endl;

				cout << "Candidate selected: " << candiArray[i].getName() << endl;


				//delete that candidate from that array and add it to selected candies
				cout << "now we are deketing " << endl;
				candiArray = deleteAcandy(candiArray, i, totalCandidates);
				cout << "we deleted candi " << endl;

				totalCandidates--;
				cout << "Do You want to add More Candidates (y/n): ";
				char choice;
				cin >> choice;
				if (choice == 'y' || choice == 'Y') {
					selectNext = true;
				}
				else if (choice == 'n' || choice == 'N') {
					selectNext = false;
					break;
				}

			}
			cout << "were out of if" << endl;

		}
		cout << "were out of for loop" << endl;
		if (selectNext == false) {
			break;
		}
		else {
			cout << "Candidate not found. Please try again." << endl;
		}
		//show all candidates

	}
	delete[] candiArray;
	ofstream lengh("lenghOfSelectedCandies.txt");
	lengh << selectedCandidatesLength;
	lengh.close();
	cout << "selected candidates are " << selectedCandidatesLength << endl;
	displayCandiates(selectedCandidates, selectedCandidatesLength);

	return selectedCandidates;

}
void election::addElectionToFileWithCandies(int timeType,string fileName) {
	cout << "Here Is list of candidates" << endl;
	int totalCandidates = fileLenght("candidate");
	cout << "Flile lenght is " << totalCandidates << endl;
	candidate* candiArray = new candidate[totalCandidates];
	ofstream electionFile(fileName+".txt", ios::app);

	if (!electionFile.is_open()) {
		cerr << "Error opening file." << endl;
		return;
	}
	cout << "selected candis" << endl;

	candiArray = selectCandidates();

	int len;
	ifstream fileF("lenghOfSelectedCandies.txt");
	fileF >> len;
	cout << "after selected candis" << endl;
	//find lenght of selected candidates
	int selectedCandidatesLength = len;

	//write selected candidates to file
	ofstream electionVoteFile(to_string(electionId) + ".txt", ios::app);
	electionFile<<electionId<<"*" << electionName << "*" << electionDate << "*" << electionTime << "*" << timeType;
	for (int i = 0; i < numberOfRegions; i++) {
		electionFile<<"*" << regionCodes[i]<< "*" << selectedCandidatesLength;
	}
	for (int i = 0; i < selectedCandidatesLength; i++) {
		electionFile << "*" << candiArray[i].getCnic();
		electionVoteFile << electionId << "*" << candiArray[i].getCnic() << "*" << 0<<endl;
	}
	electionFile << endl;
	electionVoteFile.close();
	cout << "Election saved to file." << endl;




}

void election::loadElectionFromFile(string fileName,int load) {

	int fileLen = fileLenght(fileName);
	ifstream electionFile(fileName + ".txt");
	if (!electionFile.is_open()) {
		cerr << "Error opening file." << endl;
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
		cout << "load is L:: " << load << endl;
		
		if (i<load-1) {
			getline(electionFile, line,'\n');
		}
	}
	string electionIdStr;
		getline(electionFile, electionIdStr, '*');
		electionId = stoi(electionIdStr); 
		cout << "e;ection id in load is " << electionId << endl;
		getline(electionFile, electionName, '*');
		getline(electionFile, electionDate, '*');
		getline(electionFile, electionTime, '*');
		//int numRegions = stoi(duration);
		//regionCodes = new int[numRegions];
		/*for (int j = 0; j < numRegions; j++) {
			getline(electionFile, regionCode, '*');
			regionCodes[j] = stoi(regionCode);
		}*/
		string durationStr;
		getline(electionFile, durationStr, '*');
		duration = stoi(durationStr);

		getline(electionFile, regionCode, '*');
		string numOfCandidatesStr;
		getline(electionFile, numOfCandidatesStr, '*');
		numOfCandidates = stoi(numOfCandidatesStr);
		string *candidateCnic = new string[numOfCandidates];
		selCandidates = new candidate[numOfCandidates];
		//selCandidatesCnic = 
		ifstream candidateVoteFile(to_string(electionId) + ".txt");
		if (!candidateVoteFile.is_open()) {
			cerr << "Error opening file." << endl;
			return;
		}
		string temp;
		for (int i = 0; i < numOfCandidates; i++) {

			getline(candidateVoteFile, temp, '*');
			cout << "election id is " << temp << endl;
			getline(candidateVoteFile, temp, '*');
			cout << "candidate cnic is " << temp << endl;
			getline(candidateVoteFile, temp, '\n');
			cout << "vote count is " << temp << endl;
			selCandidates[i].setVoteCount(stoi(temp));

			if (i == numOfCandidates - 1) { // Note the -1 here
				getline(electionFile, candidateCnic[i], '\n');
			}
			else {
				getline(electionFile, candidateCnic[i], '*');
			}
			selCandidates[i].getCandidateByCnic(candidateCnic[i]);
		}


	


}
void election::saveElectionVotesToFile() {
	ofstream candidateVote(to_string(electionId) + ".txt");
	if (!candidateVote.is_open()) {
		cerr << "Error opening file to save candidate votes." << endl;
		return;
	}
	for (int i = 0; i < numOfCandidates; i++) {
		candidateVote << electionId << "*" << selCandidates[i].getCnic() << "*" << selCandidates[i].getVoteCount();
		candidateVote << endl;
	}
	cout << "candidateVote ssaved to file :: " << selCandidates[0].getName() << "::" << selCandidates[0].getVoteCount() << endl;
	candidateVote.close();
}

void election::castVote(voter* v, int candidateId) {
	cout << "Casting vote for candidate with ID: " << candidateId << endl;
	for (int i = 0; i < numOfCandidates; i++) {
		if (selCandidates[i].getCnicInt() == candidateId) {
			selCandidates[i].incrementVoteCount();
			cout << "Vote count for candidate " << selCandidates[i].getName() << ": " << selCandidates[i].getVoteCount() << endl;
			saveCandidateVotesToFile(&selCandidates[i]);
			cout << "Vote casted successfully for candidate: " << selCandidates[i].getName() << endl;
			break;
		}
	}
	saveElectionVotesToFile();
}
void election::saveCandidateVotesToFile( candidate* candi) {
	ofstream candidateVote ( to_string(electionId) + ".txt", ios::app);
	if (!candidateVote.is_open()) {
		cerr << "Error opening file to save candidate votes." << endl;
		return;
	}
	candidateVote <<electionId<< "*" << candi->getCnic() << "*" <<candi->getVoteCount() ;
	candidateVote << endl;
	cout << "candidateVote ssaved to file :: " << candi->getName() << "::" << candi->getVoteCount() << endl;
	candidateVote.close();
}