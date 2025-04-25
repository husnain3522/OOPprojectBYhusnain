#include "candidate.h"
bool candidate::isLogin(string name, string cnic, string password) {

	return 0;


}
void candidate::setPartyName(string p) {
	partyName = p;
}
string candidate::getPartyName() {
	return partyName;
}



void candidate::getCandidateByCnic(string inputCnic) {
	candidate candi;
	bool isCnicFound = false;
	ifstream candidateFile("candidate.txt");
	if (!candidateFile.is_open()) {
		cerr << "Error opening file." << endl;
		return ;
	}
	string name, cnic, partyId;
	while (getline(candidateFile, name, '*')) {
		getline(candidateFile, cnic, '*');
		getline(candidateFile, partyId, '\n');
		if (inputCnic == cnic) {
			isCnicFound = true;
		/*	candi.setName(name);
			candi.setCnic(cnic);
			candi.setPartyName(partyId);
			break;*/
			partyName = partyId;
			cnic = inputCnic;
			this->name = name;
			break;
		}
	}
	if (!isCnicFound) {
		cout << "CNIC not found." << endl;
	}
	candidateFile.close();

	//return candi
}

