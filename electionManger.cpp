#include "electionManger.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int electionManger::countNumOfElections(string fileName) {
	// Implement the logic to count local elections
	int count = 0;
	ifstream file(fileName+".txt");
	if (!file.is_open()) {
		cerr << "Error opening file in counting :: "<<fileName << endl;
		return -1;

	}
	string line;
	while (getline(file, line)) {
		count++;
	}
	file.close();
	return count;



}
void electionManger::refreshAllData() {
	cout << "refereshin...." << endl;
	countLocal = countNumOfElections("localElection");
	countNational = countNumOfElections("nationalElection");
	countRegional = countNumOfElections("regionalElection");
	local = new localElection[countLocal];
	national = new nationalElection[countNational];
	regional = new regionalElection[countRegional];
	ifstream localFile("localElection.txt");
	if (!localFile.is_open()) {
		cerr << "Error opening local file to load data." << endl;
		return;
	}
	int load = 0;
	for (int i = 0; i < countLocal; i++) {
		load++;
		local[i].loadElectionFromFile("localElection",load);
	}
	ifstream nationalFile("nationalElection.txt");
	if (!nationalFile.is_open()) {
		cerr << "Error opening national file to load data." << endl;
		return;
	}
	cout << "before region lodin elction" << endl;
	load = 0;
	for (int i = 0; i < countNational; i++) {
		load++;

		cout << "count regional is " << countRegional << endl;
		cout << "lodaing local election::" << i << endl;
		national[i].loadElectionFromFile("nationalElection",load);
	}
	cout << "after region lodin elction" << endl;

	ifstream regionalFile("regionalElection.txt");
	if (!regionalFile.is_open()) {
		cerr << "Error opening regional file to load data." << endl;
		return;
	}
	load = 0;
	for (int i = 0; i < countRegional; i++) {
		load++;

		regional[i].loadElectionFromFile("regionalElection",load);
	}
	localFile.close();
	nationalFile.close();
	regionalFile.close();



}
electionManger::electionManger() {
	refreshAllData();

}
void electionManger::displayAllElectionNames() {

	if (countLocal == 0) {
		cout << "No Local Election" << endl;
	}
	else {
	cout << "Local Elections: " << endl;

	for (int i = 0; i < countLocal; i++) {
		cout << "Name :: " << local[i].getElectionName() << endl;
		//cout << "ID :: " << local[i] << endl;
		cout << "ID :: " << local[i].getElectionId() << endl;
	}
	}
	if (countNational == 0) {
		cout << "No National Election" << endl;;
	}
	else {

	cout << "National Elections: " << endl;
	for (int i = 0; i < countNational; i++) {
		cout<<"Name :: " << national[i].getElectionName() << endl;
		cout << "ID :: " << national[i].getElectionId() << endl;
	}
	}
	if (countRegional == 0) {
		cout << "No Regional Election"<<endl;
	}
	else {

	cout << "Regional Elections: " << endl;
	for (int i = 0; i < countRegional; i++) {
		cout<<"Name :: " << regional[i].getElectionName() << endl;
		cout << "ID :: " << regional[i].getElectionId() << endl;

	}
	}
}
void electionManger::displayLocalElections(){
	cout << "Local Elections: " << endl;
	for (int i = 0; i < countLocal; i++) {
		cout << "Name :: " << local[i].getElectionName() << endl;
		cout << "ID :: " << local[i].getElectionId() << endl;
	}
}
void electionManger::displayNationalElections() {
	cout << "National Elections: " << endl;
	for (int i = 0; i < countNational; i++) {
		cout << "Name :: " << national[i].getElectionName() << endl;
		cout << "ID :: " << national[i].getElectionId() << endl;
	}
}
void electionManger::displayRegionalElections() {
	cout << "Regional Elections: " << endl;
	for (int i = 0; i < countRegional; i++) {
		cout << "Name :: " << regional[i].getElectionName() << endl;
		cout << "ID :: " << regional[i].getElectionId() << endl;
	}
}
 
void electionManger::displayAllElectionInDetails() {
	cout << "Local Elections: " << endl;
	for (int i = 0; i < countLocal; i++) {
		local[i].displayElectionDetails();
	}
	cout << "National Elections: " << endl;
	for (int i = 0; i < countNational; i++) {
		national[i].displayElectionDetails();
	}
	cout << "Regional Elections: " << endl;
	for (int i = 0; i < countRegional; i++) {
		regional[i].displayElectionDetails();
	}
}
void electionManger::displayAllCandidates() {
	
	cout << "Local Candidates: " << endl;
	for (int i = 0; i < countLocal; i++) {
		local[i].displayCandiates(local[i].getCandidateArray(), local[i].getNumberOfRegions());
	}
	//cout << "National Candidates: " << endl;
	//for (int i = 0; i < countNational; i++) {
	//	national[i].displayCandiates(national[i].getCandidateArray(), national[i].getNumberOfRegions());
	//}
	//cout << "Regional Candidates: " << endl;
	//for (int i = 0; i < countRegional; i++) {
	//	regional[i].displayCandiates(regional[i].getCandidateArray(), regional[i].getNumberOfRegions());
	//}
}
bool electionManger::checkIfUserAlreadyVoted(int id) {
	// Check if the user has already voted in the election with the given ID
	ifstream checkFile("voterVoteStatus.txt");
	if (!checkFile.is_open()) {
		cerr << "Error opening file to check vote status." << endl;
		return false;
	}
	string electionId, cnic;
	while (getline(checkFile, electionId, '*')) {
		getline(checkFile, cnic, '\n');
		if (stoi(electionId) == id && cnic == voterr->getCnic()) {
			checkFile.close();
			return true; // User has already voted
		}
	}
	checkFile.close();

	return false; // User has not voted
}
void electionManger::saveVoterVoteStatusToFile(int id) {
	ofstream file("voterVoteStatus.txt", ios::app);
	if (!file.is_open()) {
		cerr << "Error opening file to save vote status." << endl;
		return;
	}
	file << id<< "*" << voterr->getCnic() << endl;
	file.close();

}
void electionManger::casteVoteInElection(election* e, int size) {

	cout << "Enter Election ID: ";
	int id;
	cin >> id;
	// Check if the user has already voted in this election
	if (checkIfUserAlreadyVoted(id)) {
		cout << "You have already voted in this election." << endl;
		return;
	}
	int index = -1;
	for (int i = 0; i < size; i++) {
		if (e[i].getElectionId() == id) {
			index = i;
			cout << "Election Found :: " << index << endl;
			break;
		}
	}
	if (index != -1) {
		e[index].displayCandiates(e[index].getSelectedCandidates(), e[index].getTotalCandidates());
		cout << "Enter Candidate ID: ";
		int candidateId;
		cin >> candidateId;
		
		// Check if the candidate ID is valid
		for (int i = 0; i < e[index].getTotalCandidates(); i++) {
			if (e[index].getSelectedCandidates()[i].getCnicInt() == candidateId) {
				e[index].castVote(voterr, candidateId);
				saveVoterVoteStatusToFile(id);
				cout << "Vote casted successfully." << endl;
				return;
			}
		}
		
	}
	else {
		cout << "Election not found." << endl;
	}

}
void electionManger::castVote(){
	reSelectVoteType:
	cout << "Enter Which type of Election you want to cast vote for" << endl;
	cout << "1. Local Election" << endl;
	cout << "2. National Election" << endl;
	cout << "3. Regional Election" << endl;
	int choice;
	cin >> choice;
	if (choice == 1) {
		cout << "Local Election" << endl;
		displayLocalElections();
		casteVoteInElection(local, countLocal);


	}
	else if (choice == 2) {
		cout << "National Election" << endl;
		displayNationalElections();
		casteVoteInElection(national, countNational);
	}
	else if (choice == 3) {
		cout << "Regional Election" << endl;
		displayRegionalElections();
		casteVoteInElection(regional, countRegional);
	}
	else {
		cout << "Invalid choice." << endl;
		goto reSelectVoteType;
	}
	


}
localElection* electionManger::getLocalElections() {
	return local;
}
nationalElection* electionManger::getNationalElections() {
	return national;
}
regionalElection* electionManger::getRegionalElections() {
	return regional;
}
