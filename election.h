#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "candidate.h"
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
	string electionId;
	int numOfCandidates;
	int duration;
	string* selCandidatesCnic;
public:

	candidate* addSelectedCandidate(candidate candi, candidate* selectedCandidate,int);
	election() {
		electionName = "";
		electionDate = "";
		electionTime = "";
		regionCodes = nullptr;
		numberOfRegions = 0;
		electionId = "";
	};
	candidate* getCandidateArray();
	void displayCandiates(candidate*,int);
	election(string, string, string, int);
	void setElectionId(string id);
	string getElectionId();
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


