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
	string *regionCodes;
	int numberOfRegions;
	string electionId;
public:
	candidate* addSelectedCandidate(candidate candi, candidate* selectedCandidate);
	candidate* getCandidateArray();
	void displayCandiates(candidate*);
	election(string , string , string , int );
	void setElectionId(string id);
	string getElectionId();
	int fileLenght(string);// checkes file lengh
	void addElectionToFileWithCandies();
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
	void loadElectionFromFile();
	void addElection();
	void deleteElection();
	void updateElection();
	void viewElections();
	void searchElection();
	void sortElections();
	void filterElections();
	void displayElectionResults();
	void displayElectionResults(string electionId);

	

};



