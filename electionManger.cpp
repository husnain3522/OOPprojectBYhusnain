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
		cerr << "Error opening file :: "<<fileName << endl;
		return -1;

	}
	string line;
	while (getline(file, line)) {
		count++;
	}
	file.close();
	return count;


}
electionManger::electionManger() {
	countLocal = countNumOfElections("local");
	countNational =  countNumOfElections("national");
	countRegional = countNumOfElections("regional");
	local = new localElection[countLocal];
	national = new nationalElection[countNational];
	regional = new regionalElection[countRegional];
	ifstream localFile("local.txt");
	if (!localFile.is_open()) {
		cerr << "Error opening local file to load data." << endl;
		return;
	}
	for (int i = 0; i < countLocal; i++) {
		
	}



}