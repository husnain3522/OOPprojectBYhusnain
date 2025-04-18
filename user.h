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
private:
	string name;
	string password;	
public:
	string getName();
	string getPassword();
	void setName(string n);
	void setPassword(string p);
	user(string n, string p);
	virtual bool isLogin() = 0;
	void display();
	void saveUserToFile();

};

