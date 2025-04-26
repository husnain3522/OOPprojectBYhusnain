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
	for (int i = 0; i < countLocal; i++) {
		local[i].loadElectionFromFile("localElection");
	}
	ifstream nationalFile("nationalElection.txt");
	if (!nationalFile.is_open()) {
		cerr << "Error opening national file to load data." << endl;
		return;
	}
	for (int i = 0; i < countNational; i++) {
		national[i].loadElectionFromFile("nationalElection");
	}
	ifstream regionalFile("regionalElection.txt");
	if (!regionalFile.is_open()) {
		cerr << "Error opening regional file to load data." << endl;
		return;
	}
	for (int i = 0; i < countRegional; i++) {
		regional[i].loadElectionFromFile("regionalElection");
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