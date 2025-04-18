#include "user.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

user::user(string n,string snic, string p) : name(n),cnic(snic), password(p) {

}

string user::getCnic() {
	return cnic;
}
void user::setCnic(string c) {
	cnic = c;
}
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
	cout << "CNIC: " << cnic << endl;
	cout << "Password: " << password << endl;
}
int user::fileLenght() {
	ifstream file("admin.txt");
	if (!file.is_open()) {
		cerr << "Error opening file." << endl;
		return -1;
	}
	int count = 0;
	string line;
	while (getline(file, line)) {
		count++;
	}
	file.close();
	return count;
}

void user::addUserToFile(string name, string snic, string password, string fileName) {
	// checking if cnic already exists

	ofstream userFile((fileName + ".txt"), ios::app);
	if (!userFile.is_open()) {
		cerr << "Error opening file." << endl;
		return;
	}
	userFile << name << "*" << snic << "*" << password << endl;
		cout << fileName << " saved to file." << endl;
	userFile.close();
}
bool user::checkIfUserExists(string inputCnic, string fileName) {
	ifstream userFile(fileName + ".txt");
	if (!userFile.is_open()) {
		cerr << "Error opening file." << endl;
		return false;
	}
	string serchedCnic;
	string temp;
	while (getline(userFile, temp, '*'))
	{
		getline(userFile, serchedCnic, '*');
		if (serchedCnic == inputCnic) {
			userFile.close();

			return true;
		}
		getline(userFile, temp, '\n');
	}
	userFile.close();
	return false;

}