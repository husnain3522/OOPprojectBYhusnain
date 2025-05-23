#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "user.h"
#include "voter.h"
#include "admin.h"
#include "election.h"
#include "candidate.h"
#include "regionalElection.h"
#include "localElection.h"
#include "nationalElection.h"

using namespace std;
class electionManger /*:public election*/
{
//protected:
private:
	localElection *local;
	nationalElection *national;
	regionalElection *regional;
	int countLocal, countNational, countRegional;
	voter* voterr;
public://change please
	//well use this class to get all data to load from files and be ready when to evaluate what
	int countNumOfElections(string);
	void setVoter(voter * v) {
		voterr = v;
	}
	voter getVoter() {
		return *voterr;
	}
	electionManger();
	void setCurrentVoter(voter* v);
	//electionManger() {
	//	countLocal = 0;
	//	countNational = 0;
	//	countRegional = 0;
	//	local = nullptr;
	//	national = nullptr;
	//	regional = nullptr;
	//}
	void refreshAllData();
	void displayAllCandidates();
	void displayAllElectionNames();
	void displayAllElectionInDetails();
	void displayAllElectionForCasting();
	void castVote();
	localElection* getLocalElections();
	nationalElection* getNationalElections();
	regionalElection* getRegionalElections();
	int * displayRegionalElections(int);
	int * displayLocalElections(int);
	int * displayNationalElections(int);
	//int* displayLocalElectionsOnlyNonActive(); 
	//int* displayNationalElectionsOnlyNonActive(); 
	//int* displayRegionalElectionsOnlyNonActive();

	void casteVoteInElection(election*,int,int*);
	bool checkIfUserAlreadyVoted(int);
	void saveVoterVoteStatusToFile(int);
	void saveCandidateVotesToFile(int);
	void checkVoteHistory();
	string getElectionNameById(int id);
	void displayResultsWithId(int); 
	void displayResults();
	int getIdFromUserTodDisplayResult(int*);
	candidate* getCandidateByCnic(string);
	void actiDeactiElectionAdmin(bool);
	void actiDeactiElectionUsingId(int,int,bool);
	void setFutureEndTime();



};

