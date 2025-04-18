#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "user.h"
class candidate :public user
{
protected:
	string name;
	string cnic;
	string password;
	bool loginStatus = false;
	string partyName;
public:
	void setLoginStatus(bool status) { loginStatus = status; }
	bool getLoginStatus();
	string getCnic();
	void setCnic(string c);
	string getName();
	string getPassword();
	void setName(string n);
	void setPassword(string p);
	/*candidate(string n, string cnin, string p,) : user(n, cnic, p) {
		
	};*/
};

