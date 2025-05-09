#include "voter.h"
bool voter::isLogin(string name, string cnic, string password) {

	if (isLoginVar) {
		cout << "---------------------------------------------------" << endl;
		cout << "Login Successful" << endl;
		cout << "---------------------------------------------------" << endl;
		return 1;
	}
	else {
		cout << "---------------------------------------------------" << endl;
		cout << "Login Failed" << endl;
		cout << "---------------------------------------------------" << endl;
		return 0;
	}
}