#include "election.h"
#include <iostream>
#include <string>
#include <fstream>
#include "candidate.h"
using namespace std;
int election::fileLenght(string fileName) {
	ifstream file(fileName+".txt");
	if (!file.is_open()) {
		cerr << "Error opening file." << endl;
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
election::election(string name="", string date="0", string time="0",int numRegioons=0) {
	electionName = name;
	electionDate = date;
	electionTime = time;
	numberOfRegions = numRegioons;
	regionCodes = new string[numRegioons];
}
void election::setElectionId(string id) {
	electionId = id;
}
string election::getElectionId() {
	return electionId;
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
	cout << "Election Name: " << electionName << endl;
	cout << "Election Date: " << electionDate << endl;
	cout << "Election Time: " << electionTime << endl;
	cout << "Number of Regions: " << numberOfRegions << endl;
	cout << "Region Codes: ";
	for (int i = 0; i < numberOfRegions; i++) {
		cout << regionCodes[i] << " ";
	}
	cout << endl;
}
candidate* election::getCandidateArray() {
	int totalCandidates = fileLenght("candidates");
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
		getline(candidateFile, partyId,'\n');
		candiArray[i].setName(name);
		candiArray[i].setCnic(cnic);
		candiArray[i].setPartyName(partyId);
	}
	return candiArray;
}
void election::displayCandiates(candidate * candiArray) {
	int totalCandi = fileLenght("candidates");
	cout << "Candidates:" << endl;
	for (int i = 0; i< totalCandi; i++) {
		cout << "Name: " << candiArray[i].getName() << endl;
		cout << "CNIC: " << candiArray[i].getCnic() << endl;
		cout << "Party Name: " << candiArray[i].getPartyName() << endl;
	}
	delete[] candiArray;
}

void election::addCandidatesToElection() {
	cout << "Here Is list of candidates" << endl;
	int totalCandidates = fileLenght("candidates");
	candidate *candiArray = new candidate[totalCandidates];
	ifstream candidateFile("candidate.txt");
	if (!candidateFile.is_open()) {
		cerr << "Error opening file." << endl;
		return;
	}
	  candiArray = getCandidateArray();


	

}