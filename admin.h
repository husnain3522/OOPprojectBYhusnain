#pragma once
#include "user.h"
class admin :public user
{
private:
	bool isLoginVar = false;
public:
	//constructor
	admin(string name="", string snic="", string password="") :user(name, snic, password) {
		////checking if cnic already exists
		//if (checkIfUserExists(snic, "admin")) {
		//	cout << "CNIC already exists." << endl;
		//	return;
		//}
		//saveAdminToFile();
	};


	void saveAdminToFile();
	bool isLogin(string name , string cnic , string password) override;
	void addVoter();
	void addAdmin();
	void addCandidate();
	void createElection();

};

