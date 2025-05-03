#include "candidate.h"
#include <cstring>

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
       return;
   }
   string Sname, Scnic, partyId;
   while (getline(candidateFile, Sname, '*')) {
       getline(candidateFile, Scnic, '*');
       getline(candidateFile, partyId, '\n');
       if (inputCnic == Scnic) { 
           isCnicFound = true;
           partyName = partyId;
           cnic = inputCnic;
           name = Sname;
           break;
       }
   }
   if (!isCnicFound) {
       cout << "CNIC not found."<<inputCnic << endl;
   }
   candidateFile.close();
}

