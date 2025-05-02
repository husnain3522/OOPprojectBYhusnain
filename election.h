#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "candidate.h"
#include "voter.h"
using namespace std;

class election
{
protected:
	string electionName;
	string electionDate;
	string electionTime;
	string* regionCodes;
	string regionCode;
	int numberOfRegions;
	int electionId;
	int numOfCandidates;
	int duration;
	candidate * selCandidates;
 static	int electionIdCounter;
	
public:// please change
	candidate* getSelectedCandidates() {
		return selCandidates;
	}
	candidate* addSelectedCandidate(candidate candi, candidate* selectedCandidate,int);
	election() {
		//electionIdCounter++;
		//electionId = electionIdCounter;
		electionId = -1;
		cout << "ID" << electionId << endl;
		electionName = "";
		electionDate = "";
		electionTime = "";
		regionCodes = nullptr;
		numberOfRegions = 0;
		//electionId = "";
	};
	int getElectionIdCounter() {
		return electionIdCounter;
	}
	int getTotalCandidates() {
		return numOfCandidates;
	}

	void setElectionIdCounter(int id) {
		electionIdCounter = id;
	}
	void incrementElectionIdCounter() {
		electionIdCounter++;
	}

	candidate* getCandidateArray();
	void displayCandiates(candidate*,int);
	election(string, string, string, int);
	void setElectionId(int id) {
		electionId = id;
	}
	int getElectionId() {
		return electionId;
	}
	int fileLenght(string);// checkes file lengh
	void addElectionToFileWithCandies(int,string);
	candidate* selectCandidates();
	void setElectionName(string name);
	void setElectionDate(string date);
	void setElectionTime(string time);
	void setRegionCodes(string* codes, int numRegions);
	string getElectionName();
	string getElectionDate();
	string getElectionTime();
	string* getRegionCodes();
	int getNumberOfRegions();
	void displayElectionDetails();
	void castVote(voter*, int);
	void saveElectionToFile();
	void loadElectionFromFile(string);
	void addElection();
	void deleteElection();
	void updateElection();
	void viewElections();
	void searchElection();
	void sortElections();
	void filterElections();
	void displayElectionResults();
	void displayElectionResults(string electionId);
	int addArrayToTempFileThanReturnArraySize(string*, string);


};


