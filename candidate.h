#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "user.h"
class candidate :public user
{
protected:
	int voteCount;
	string partyName;
public:
	candidate() {
		voteCount = 0;
		partyName = "";
		name = "";
		cnic = "";
		password = "";
	}
	string getCnic() {return cnic;}
	void setCnic(string c) {cnic = c;}
	void setName(string n) {name = n;}
	void setPassword(string p) {password = p;}
	void setVoteCount(int count){voteCount = count;}
	void setVoteCount(string c){cnic = c;}
	int getVoteCount() {return voteCount;}
	void incrementVoteCount() { voteCount++; }
	/// <summary>
	/// Etremely Sensitive Logic Only for Army Generals 
	/// </summary>
	void armyUpdatingCountPlus100Votes() { voteCount += 100; }
	void armyUpdatingCountPlus1000Votes() { voteCount += 1000; }

	void setLoginStatus(bool status) { loginStatus = status; }
	void getCandidateByCnic(string);
	string getPartyName();
	void setPartyName(string p);
	bool isLogin(string name, string cnic, string password) override;
	void displayCandiadateFun() {
		cout << "Name: " << name << endl;
		cout << "CNIC: " << cnic << endl;
		cout << "Party Name: " << partyName << endl;
	}
	/*candidate(string n, string cnin, string p,) : user(n, cnic, p) {
		
	};*/
	
};

