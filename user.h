#pragma once
#include <iostream>
using namespace std;	
class user

{
	//class user {
	//private:
	//	string name, password;
	//public:
	//	user(string n, string p) : name(n), password(p) {}
	//	string getName() { return name; }
	//	string getPassword() { return password; }
	//	void setName(string n) { name = n; }
	//	void setPassword(string p) { password = p; }
	//	virtual bool login() = 0;

	//};
protected:
	string name;
	string password;
	string cnic;
	bool loginStatus = false;
public:
	void setLoginStatus(bool status) { loginStatus = status; }
	bool getLoginStatus() { return loginStatus; }
	string getCnic();
	void setCnic(string c);
	string getName();
	string getPassword();
	void setName(string n);
	void setPassword(string p);
	user(string n,string cninc, string p);
	virtual bool isLogin(string name, string cnic, string password) = 0;//pure virtual function
	void display();
	user(){} //default constructor for user
	int fileLenght();
	void addUserToFile(string, string, string, string);
	bool checkIfUserExists(string cnic , string fileName);
	void checkCredentials(string cnic, string password, string fileName);
};

