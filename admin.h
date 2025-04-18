#pragma once
#include "user.h"
class admin :public user
{
private:
public:
	bool isLogin() {
		cout << "Admin logged in successfully." << endl;
		return 1;
	}
};

