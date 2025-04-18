#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "user.h"
class candidate :public user
{
protected:

	string partyName;
public:
	void setLoginStatus(bool status) { loginStatus = status; }

	string getPartyName();
	void setPartyName(string p);
	bool isLogin(string name, string cnic, string password) override;
	/*candidate(string n, string cnin, string p,) : user(n, cnic, p) {
		
	};*/
};

