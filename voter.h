#pragma once
#include "user.h"
using namespace std;
class voter :public user
{
private:
public:
	voter(string name, string password) :user(name,password) {}
	bool isLogin() {
		cout << "Voter logged in successfully." << endl;
		return 1;
	}
};

