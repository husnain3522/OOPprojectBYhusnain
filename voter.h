#pragma once
#include "user.h"
using namespace std;
class voter :public user
{
protected:
	bool isLoginVar = false;

public:
	voter(string name,string snic, string password) :user(name,snic,password) {}
	bool isLogin() {
		cout << "Voter logged in successfully." << endl;
		return 1;
	}
	bool isLogin(string name, string cnic, string password) override;
};


