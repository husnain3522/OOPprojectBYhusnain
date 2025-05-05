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
public://change please
	//well use this class to get all data to load from files and be ready when to evaluate what
	int countNumOfElections(string);
	electionManger();
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




};

