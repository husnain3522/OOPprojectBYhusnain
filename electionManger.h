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
class electionManger
{
//protected:
private:
	localElection *local;
	nationalElection *national;
	regionalElection *regional;
	int countLocal, countNational, countRegional;
public:
	//well use this class to get all data to load from files and be ready when to evaluate what
	int countNumOfElections(string);

	localElection* getLocalElections();
	nationalElection* getNationalElections();
	regionalElection* getRegionalElections();




};

