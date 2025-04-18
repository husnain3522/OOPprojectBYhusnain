#include "user.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

user::user(string n, string p) : name(n), password(p) {}
string user::getName() {
	return name;
}
string user::getPassword() {
	return password;
}
void user::setName(string n) {
	name = n;
}
void user::setPassword(string p) {
	password = p;
}
bool user::isLogin() {

	return true; // Placeholder for actual login logic
}
void user::display() {
	cout << "Name: " << name << endl;
	cout << "Password: " << password << endl;
}
void user::saveUserToFile() {
	// Placeholder for file saving logic
	ofstream file("user.txt");
	if (!file) {
		cerr << "Error opening file." << endl;
		return;
	}
	else {
		file << name << "*" << password << endl;
		file.close();
	}

	
	cout << "User saved to file." << endl;

}