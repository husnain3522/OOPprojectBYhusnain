#pragma once
#include "user.h"
class admin :public user
{
private:
public:
	//constructor
	admin(string name, string snic, string password) :user(name, snic, password) {
		//checking if cnic already exists
		if (checkIfUserExists(snic, "admin")) {
			cout << "CNIC already exists." << endl;
			return;
		}
		saveAdminToFile();
	};
	bool isLogin();

	void saveAdminToFile();

	admin();

	void addVoter();
	void addAdmin();
	void addCandidate();


};

