#include "electionManger.h"
#include <iostream>
#include <string>
#include<cstdlib>
#include <fstream>
using namespace std;

int electionManger::countNumOfElections(string fileName) {
	// Implement the logic to count local elections
	int count = 0;
	ifstream file(fileName + ".txt");
	if (!file.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file in counting :: " << fileName << endl;
		cout << "---------------------------------------------------" << endl;
		return -1;

	}
	string line;
	while (getline(file, line)) {
		count++;
	}
	file.close();
	return count;



}
void electionManger::refreshAllData() {
	//cout << "---------------------------------------------------" << endl;
	countLocal = countNumOfElections("localElection");
	countNational = countNumOfElections("nationalElection");
	countRegional = countNumOfElections("regionalElection");
	local = new localElection[countLocal];
	national = new nationalElection[countNational];
	regional = new regionalElection[countRegional];
	ifstream localFile("localElection.txt");
	if (!localFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening local file to load data." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	int load = 0;
	for (int i = 0; i < countLocal; i++) {
		load++;
		local[i].loadElectionFromFile("localElection", load);
	}
	ifstream nationalFile("nationalElection.txt");
	if (!nationalFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening national file to load data." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	//cout << "before region lodin elction" << endl;
	load = 0;
	for (int i = 0; i < countNational; i++) {
		load++;
		national[i].loadElectionFromFile("nationalElection", load);
	}
	//cout << "after region lodin elction" << endl;

	ifstream regionalFile("regionalElection.txt");
	if (!regionalFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening regional file to load data." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	load = 0;
	for (int i = 0; i < countRegional; i++) {
		load++;

		regional[i].loadElectionFromFile("regionalElection", load);
	}
	localFile.close();
	nationalFile.close();
	regionalFile.close();

	system("cls");

}
electionManger::electionManger() {
	refreshAllData();

}
void electionManger::displayAllElectionNames() {

	if (countLocal == 0) {
		cout << "---------------------------------------------------" << endl;
		cout << "No Local Election" << endl;
		cout << "---------------------------------------------------" << endl;
	}
	else {
		cout << "Local Elections: " << endl;

		for (int i = 0; i < countLocal; i++) {
			if (local[i].getIsActice() == true) {
				cout << "---------------------------------------------------" << endl;
				cout << "Name :: " << local[i].getElectionName() << endl;
				cout << "---------------------------------------------------" << endl;
				cout << "ID :: " << local[i].getElectionId() << endl;
			}
			
		}	cout << "---------------------------------------------------" << endl;
	}
	if (countNational == 0) {
		cout << "---------------------------------------------------" << endl;
		cout << "No National Election" << endl;
		cout << "---------------------------------------------------" << endl;
	}
	else {
		cout << "---------------------------------------------------" << endl;
		cout << "National Elections: " << endl;
		cout << "---------------------------------------------------" << endl;
		for (int i = 0; i < countNational; i++) {
			if (national[i].getIsActice() == true) {
				cout << "---------------------------------------------------" << endl;
				cout << "Name :: " << national[i].getElectionName() << endl;
				cout << "---------------------------------------------------" << endl;
				cout << "ID :: " << national[i].getElectionId() << endl;
				cout << "---------------------------------------------------" << endl;
			}
			
		}
	}
	if (countRegional == 0) {
		cout << "---------------------------------------------------" << endl;
		cout << "No Regional Election" << endl;
		cout << "---------------------------------------------------" << endl;
	}
	else {
		cout << "---------------------------------------------------" << endl;
		cout << "Regional Elections: " << endl;
		for (int i = 0; i < countRegional; i++) {
			if (regional[i].getIsActice() == true) {
				cout << "---------------------------------------------------" << endl;
				cout << "Name :: " << regional[i].getElectionName() << endl;
				cout << "---------------------------------------------------" << endl;
				cout << "ID :: " << regional[i].getElectionId() << endl;
				cout << "---------------------------------------------------" << endl;
			}
			
		}
	}
}
int* electionManger::displayLocalElections(int type) {  
   if (countLocal == 0) {  
	   cout << "---------------------------------------------------" << endl;
       cout << "No Local Election" << endl;  
	   cout << "---------------------------------------------------" << endl;
       int* regionChoices = new int[1];  
       regionChoices[0] = -1;  
       return regionChoices;  
   } else {  
       int counter = 0;  
       int* Choices = new int[countLocal + 1];  
	   cout << "---------------------------------------------------" << endl;
       cout << "Local Elections: " << endl;  
	   cout << "---------------------------------------------------" << endl;
       for (int i = 0; i < countLocal; i++) {  
           if (type == 1) {  
			   cout << "---------------------------------------------------" << endl;
               if (local[i].getIsActice() == false) {  
                   continue;  
				   cout << "---------------------------------------------------" << endl;
               }  
           } else if (type == 0) {  
			   cout << "---------------------------------------------------" << endl;
               if (local[i].getIsActice() == true) {  
                   continue;  
				   cout << "---------------------------------------------------" << endl;
               }  
           } 	cout << "---------------------------------------------------" << endl;
           cout << "Name :: " << local[i].getElectionName() << endl;  
		   cout << "---------------------------------------------------" << endl;
           cout << "ID :: " << local[i].getElectionId() << endl;  
		   cout << "---------------------------------------------------" << endl;
           if (type == 3) {  
			   cout << "---------------------------------------------------" << endl;
               cout << "Election Status :: " << local[i].getIsActice() << endl;  
			   cout << "---------------------------------------------------" << endl;
           }  
           Choices[counter + 1] = local[i].getElectionId();  
		   cout << "---------------------------------------------------" << endl;
           cout << Choices[counter + 1] << "::" << local[i].getElectionId() << endl;
		   cout << "---------------------------------------------------" << endl;
           counter++;  
       }  
       if (counter == 0) {  
           counter = -1;  
		   cout << "---------------------------------------------------" << endl;
           cout << "No Local Elections Activated YET" << endl;  
		   cout << "---------------------------------------------------" << endl;
       }  
       Choices[0] = counter;  
       if (counter > 0) {  
		   cout << "---------------------------------------------------" << endl;
           cout << "election at choices 1: " << Choices[1] << endl;  
		   cout << "---------------------------------------------------" << endl;
       }  
       return Choices;  
   }  
}


int* electionManger::displayNationalElections(int type) { 
	if (countNational == 0) {
		cout << "---------------------------------------------------" << endl;
		cout << "No national Election" << endl;
		cout << "---------------------------------------------------" << endl;
		int* regionChoices = new int[1];
		regionChoices[0] = -1;
		return regionChoices;
	}
	else {
		int counter = 0;
		int* Choices = new int[countNational + 1];
		cout << "---------------------------------------------------" << endl;
		cout << "national Elections: " << endl;
		cout << "---------------------------------------------------" << endl;
		for (int i = 0; i < countNational; i++) {
			if (type == 1) {
				if (national[i].getIsActice() == false) {
					continue;
				}
			}
			else if (type == 0) {
				if (national[i].getIsActice() == true) {
					continue;
				}
			}
			cout << "---------------------------------------------------" << endl;
			cout << "Name :: " << national[i].getElectionName() << endl;
			cout << "---------------------------------------------------" << endl;
			cout << "ID :: " << national[i].getElectionId() << endl;
			cout << "---------------------------------------------------" << endl;
			if (type == 3) {
				cout << "---------------------------------------------------" << endl;
				cout << "Election Status :: " << national[i].getIsActice() << endl;
				cout << "---------------------------------------------------" << endl;
			}
			Choices[counter + 1] = national[i].getElectionId();
			cout << "---------------------------------------------------" << endl;
			cout << Choices[counter + 1] << "::" << national[i].getElectionId() << endl;
			cout << "---------------------------------------------------" << endl;
			counter++;
		}
		if (counter == 0) {
			counter = -1;
			cout << "---------------------------------------------------" << endl;
			cout << "No Local Elections Activated YET" << endl;
			cout << "---------------------------------------------------" << endl;
		}
		Choices[0] = counter;
		if (counter > 0) {
			cout << "---------------------------------------------------" << endl;
			cout << "election at choices 1: " << Choices[1] << endl;
			cout << "---------------------------------------------------" << endl;
		}
		return Choices;
	}
}


int* electionManger::displayRegionalElections(int type) {
	if (countRegional == 0) {
		cout << "---------------------------------------------------" << endl;
		cout << "No regional Election" << endl;
		cout << "---------------------------------------------------" << endl;
		int* regionChoices = new int[1];
		regionChoices[0] = -1;
		return regionChoices;
	}
	else {
		int counter = 0;
		int* Choices = new int[countRegional + 1];
		cout << "---------------------------------------------------" << endl;
		cout << "regional Elections: " << endl;
		cout << "---------------------------------------------------" << endl;
		for (int i = 0; i < countRegional; i++) {
			if (type == 1) {
				if (regional[i].getIsActice() == false) {
					continue;
				}
			}
			else if (type == 0) {
				if (regional[i].getIsActice() == true) {
					continue;
				}
			}
			cout << "---------------------------------------------------" << endl;
			cout << "Name :: " << regional[i].getElectionName() << endl;
			cout << "---------------------------------------------------" << endl;
			cout << "ID :: " << regional[i].getElectionId() << endl;
			cout << "---------------------------------------------------" << endl;
			if (type == 3) {
				cout << "---------------------------------------------------" << endl;
				cout << "Election Status :: " << regional[i].getIsActice() << endl;
				cout << "---------------------------------------------------" << endl;
			}
			Choices[counter + 1] = regional[i].getElectionId();
			cout << "---------------------------------------------------" << endl;
			cout << Choices[counter + 1] << "::" << regional[i].getElectionId() << endl;
			cout << "---------------------------------------------------" << endl;
			counter++;
		}
		if (counter == 0) {
			counter = -1;
			cout << "---------------------------------------------------" << endl;
			cout << "No Local Elections Activated YET" << endl;
			cout << "---------------------------------------------------" << endl;
		}
		Choices[0] = counter;
		if (counter > 0) {
			cout << "---------------------------------------------------" << endl;
			cout << "election at choices 1: " << Choices[1] << endl;
			cout << "---------------------------------------------------" << endl;
		}
		return Choices;
	}
}



void electionManger::displayAllElectionInDetails() {
	cout << "---------------------------------------------------" << endl;
	cout << "Local Elections: " << endl;
	cout << "---------------------------------------------------" << endl;
	for (int i = 0; i < countLocal; i++) {
		cout << "---------------------------------------------------" << endl;
		local[i].displayElectionDetails();
		cout << "---------------------------------------------------" << endl;
	}
	cout << "---------------------------------------------------" << endl;
	cout << "National Elections: " << endl;
	cout << "---------------------------------------------------" << endl;
	for (int i = 0; i < countNational; i++) {
		cout << "---------------------------------------------------" << endl;
		national[i].displayElectionDetails();
		cout << "---------------------------------------------------" << endl;
	}	
	cout << "---------------------------------------------------" << endl;
	cout << "Regional Elections: " << endl;
	cout << "---------------------------------------------------" << endl;
	for (int i = 0; i < countRegional; i++) {
		cout << "---------------------------------------------------" << endl;
		regional[i].displayElectionDetails();
		cout << "---------------------------------------------------" << endl;
	}
}
void electionManger::displayAllCandidates() {
	cout << "---------------------------------------------------" << endl;
	cout << "Local Candidates: " << endl;
	cout << "---------------------------------------------------" << endl;
	for (int i = 0; i < countLocal; i++) {
		cout << "---------------------------------------------------" << endl;
		local[i].displayCandiates(local[i].getCandidateArray(), local[i].getNumberOfRegions());
		cout << "---------------------------------------------------" << endl;
	}
	//cout << "National Candidates: " << endl;
	//for (int i = 0; i < countNational; i++) {
	//	national[i].displayCandiates(national[i].getCandidateArray(), national[i].getNumberOfRegions());
	//}
	//cout << "Regional Candidates: " << endl;
	//for (int i = 0; i < countRegional; i++) {
	//	regional[i].displayCandiates(regional[i].getCandidateArray(), regional[i].getNumberOfRegions());
	//}
}
bool electionManger::checkIfUserAlreadyVoted(int id) {
	// Check if the user has already voted in the election with the given ID
	ifstream checkFile("voterVoteStatus.txt");
	if (!checkFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file to check vote status." << endl;
		cout << "---------------------------------------------------" << endl;
		return false;
	}
	string electionId, cnic;
	while (getline(checkFile, electionId, '*')) {
		getline(checkFile, cnic, '\n');
		if (stoi(electionId) == id && cnic == voterr->getCnic()) {
			checkFile.close();
			cout << "---------------------------------------------------" << endl;
			cout << "You have already voted in this election." << endl;
			cout << "---------------------------------------------------" << endl;
			return true; // User has already voted
		}
	}
	checkFile.close();

	return false; // User has not voted
}
void electionManger::saveVoterVoteStatusToFile(int id) {
	ofstream file("voterVoteStatus.txt", ios::app);
	if (!file.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file to save vote status." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	file << id << "*" << voterr->getCnic() << endl;
	file.close();

}
void electionManger::casteVoteInElection(election* e, int size, int* choices) {
	cout << "---------------------------------------------------" << endl;
cout << "Enter Election ID: ";
int id;
cin >> id;
cout << "---------------------------------------------------" << endl;
bool isElectionFound = false;
cout << "---------------------------------------------------" << endl;
cout << "Choices :: at 0 is " << choices[0] << endl;
cout << "---------------------------------------------------" << endl;
for (int i = 1; i < choices[0] + 1; i++) {
	cout << "---------------------------------------------------" << endl;
	cout << "choices::::" << choices[i] << endl;
	cout << "---------------------------------------------------" << endl;
	if (choices[i] == id) {
		isElectionFound = true;
		cout << "---------------------------------------------------" << endl;
		cout << "electionFound" << endl;
		cout << "---------------------------------------------------" << endl;
	}
}
if (isElectionFound == false) {
	cout << "---------------------------------------------------" << endl;
	cout << "Election not found...." << endl;
	cout << "---------------------------------------------------" << endl;
	return;
}
// Check if the user has already voted in this election
if (checkIfUserAlreadyVoted(id)) {
	cout << "---------------------------------------------------" << endl;
	cout << "You have already voted in this election." << endl;
	cout << "---------------------------------------------------" << endl;
	return;
}
int index = -1;
for (int i = 0; i < size; i++) {
	if (e[i].getElectionId() == id) {
		index = i;
		cout << "---------------------------------------------------" << endl;
		cout << "Election Found :: " << index << endl;
		cout << "---------------------------------------------------" << endl;
		break;
	}
}
if (index != -1) {
	// Check if the election time has passed
	if (e[index].hasTimePassed(e[index].getFutureTime())) {
		cout << "---------------------------------------------------" << endl;
		cout << "Election time has passed. You cannot vote." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}

	e[index].displayCandiates(e[index].getSelectedCandidates(), e[index].getTotalCandidates());
	cout << "---------------------------------------------------" << endl;
	cout << "Enter Candidate ID: ";

	int candidateId;
	cin >> candidateId;
	cout << "---------------------------------------------------" << endl;
	// Check if the candidate ID is valid
	for (int i = 0; i < e[index].getTotalCandidates(); i++) {
		if (e[index].getSelectedCandidates()[i].getCnicInt() == candidateId) {
			e[index].castVote(voterr, candidateId);
			saveVoterVoteStatusToFile(id);
			cout << "---------------------------------------------------" << endl;
			cout << "Vote casted successfully." << endl;
			cout << "---------------------------------------------------" << endl;
			return;
		}
	}
	cout << "---------------------------------------------------" << endl;
	cout << "Invalid Candidate ID." << endl;
	cout << "---------------------------------------------------" << endl;
} else {
	cout << "---------------------------------------------------" << endl;
	cout << "Election not found." << endl;
	cout << "---------------------------------------------------" << endl;
}
}
void electionManger::castVote() {
reSelectVoteType:
	cout << "---------------------------------------------------" << endl;
	cout << "Enter Which type of Election you want to cast vote for" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "1. Local Election" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "2. National Election" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "3. Regional Election" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "4. Exit" << endl;
	cout << "---------------------------------------------------" << endl;
	int choice;
	cin >> choice;
	int* electionChoice;
	if (choice == 1) {
		cout << "---------------------------------------------------" << endl;
		cout << "Local Election" << endl;
		cout << "---------------------------------------------------" << endl;
		electionChoice = displayLocalElections(1);
		cout << "---------------------------------------------------" << endl;
		cout << "Election aftere choice " << electionChoice[1] << endl;
		cout << "---------------------------------------------------" << endl;
		if (electionChoice[0] != -1) {

			casteVoteInElection(local, countLocal, electionChoice);
		}
		else goto reSelectVoteType;



	}
	else if (choice == 2) {
		cout << "---------------------------------------------------" << endl;
		cout << "National Election" << endl;
		cout << "---------------------------------------------------" << endl;
		electionChoice = displayNationalElections(1);
		cout << "---------------------------------------------------" << endl;

		if (electionChoice[0] != -1)
		{

			casteVoteInElection(national, countNational, electionChoice);
		}
		else goto reSelectVoteType;

	}
	else if (choice == 3) {
		cout << "---------------------------------------------------" << endl;
		cout << "Regional Election" << endl;
		cout << "---------------------------------------------------" << endl;
		electionChoice = displayRegionalElections(1);
		cout << "---------------------------------------------------" << endl;

		if (electionChoice[0] != -1) {

			casteVoteInElection(regional, countRegional, electionChoice);
		}
		else goto reSelectVoteType;
	}
	else if (choice == 4) {
		cout << "---------------------------------------------------" << endl;
		cout << "exiting..." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}

	else {
		cout << "---------------------------------------------------" << endl;
		cout << "Invalid choice." << endl;
		cout << "---------------------------------------------------" << endl;
		goto reSelectVoteType;
	}



}
localElection* electionManger::getLocalElections() {
	return local;
}
nationalElection* electionManger::getNationalElections() {
	return national;
}
regionalElection* electionManger::getRegionalElections() {
	return regional;
}
void electionManger::checkVoteHistory() {
	ifstream historyFile("voterVoteStatus.txt");	
	if (!historyFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file to check vote history." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	cout << "---------------------------------------------------" << endl;
	cout << "History Of Elections You Voted For" << endl;
	cout << "---------------------------------------------------" << endl;
	string idStr, voterCnicStr;
	int electionIdInt;
	while (getline(historyFile, idStr, '*')) {
		electionIdInt = stoi(idStr);
		getline(historyFile, voterCnicStr, '\n');
		if (voterCnicStr == voterr->getCnic()) {
			cout << "---------------------------------------------------" << endl;
			cout << "Election ID: " << idStr ;
			cout << "---------------------------------------------------" << endl;
			cout << " :: ElectionName : " <<getElectionNameById(electionIdInt)  << endl;
			cout << "---------------------------------------------------" << endl;
		}
	}
	historyFile.close();
	cout << "---------------------------------------------------" << endl;
	cout << "End Of History" << endl;
	cout << "---------------------------------------------------" << endl;


}
string electionManger::getElectionNameById(int id) {

	ifstream checkNameFile("electionNames.txt");
	if (!checkNameFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file to check election names." << endl;
		cout << "---------------------------------------------------" << endl;
		return "";
	}
	string electionId, electionName,temp;
	while (getline(checkNameFile, electionId, '*')) {
		getline(checkNameFile, electionName, '*');
		getline(checkNameFile, temp, '\n');
		if (stoi(electionId) == id) {
			checkNameFile.close();
			cout<< "---------------------------------------------------" << endl;	
			cout << "Election ID: " << electionId << endl;
			cout << "Election Name: " << electionName << endl;
			cout << "---------------------------------------------------" << endl;
			return electionName;
		}
	}
	checkNameFile.close();
	return "";

}

void electionManger::displayResultsWithId(int electionId) {

	ifstream electionName("electionNames.txt");
	if (!electionName.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file to check election names." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	string electionIdStr, electionNameStr, totalCandidates;
	while (getline(electionName, electionIdStr, '*')) {
		getline(electionName, electionNameStr, '*');
		getline(electionName, totalCandidates, '\n');
		if (stoi(electionIdStr) == electionId) {
			cout << "---------------------------------------------------" << endl;
			cout << "Election ID: " << electionIdStr << endl;
			cout << "---------------------------------------------------" << endl;
			cout << "Election Name: " << electionNameStr << endl;
			cout << "---------------------------------------------------" << endl;
			cout << "Total Candidates: " << totalCandidates << endl;
			cout << "---------------------------------------------------" << endl;
			break;
		}
	}
	electionName.close();
	int totalCandidatesInt = stoi(totalCandidates);
	
	// Now read the election data file to get the results

	//cout << "elction id is :: " << electionId << endl;
	string id = to_string(electionId);
	//cout << "elction id is :: " <<id << endl;

	ifstream electionData( id + ".txt");
	if (!electionData.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error opening file to check election names." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	int *candidateCnic = new int[totalCandidatesInt];
	int* candidateVoteCount = new int[totalCandidatesInt];
	string temp;
		string candidateCnicStr, candidateVoteCountStr;
	for (int i = 0; i < totalCandidatesInt; i++) {
		getline(electionData, temp, '*');
		getline(electionData, temp, '*');
		candidateCnic[i] = stoi(temp);
		//cout << "CNIC" << endl;
		getline(electionData, temp ,'\n');

		candidateVoteCount[i]= stoi(temp);
		/*candidateCnic[i] = stoi(candidateCnicStr);
		candidateVoteCount[i] = stoi(candidateVoteCountStr);*/
	}
	electionData.close();
	cout << "---------------------------------------------------" << endl;
	cout << "Results: " << endl;
	cout << "---------------------------------------------------" << endl;
	for (int i = 0; i < totalCandidatesInt; i++) {
		cout << "---------------------------------------------------" << endl;
		cout << "Candidate ID: " << candidateCnic[i] << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "Vote Count: " << candidateVoteCount[i] << endl;
		cout << "---------------------------------------------------" << endl;
		
	}
	delete[] candidateCnic;
	delete[] candidateVoteCount;
	cout << "---------------------------------------------------" << endl;
	cout << "End Of Results" << endl;
	cout << "---------------------------------------------------" << endl;


}
void electionManger::displayResults() {
	cout << "---------------------------------------------------" << endl;
	cout << "Enter " << endl;
reSelectVoteType:
	cout << "---------------------------------------------------" << endl;
	cout << "1. Local Election" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "2. National Election" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "3. Regional Election" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "4. Exit" << endl;
	cout << "---------------------------------------------------" << endl;
	int choice;
	cin >> choice;
	int* electionChoice;
	if (choice == 1) {
		cout << "---------------------------------------------------" << endl;
		cout << "Local Election" << endl;
		cout << "---------------------------------------------------" << endl;
		electionChoice = displayLocalElections(3);
		if (electionChoice[0] != -1) {
			int id = getIdFromUserTodDisplayResult(electionChoice);
			if (id != -1) {
				cout << "---------------------------------------------------" << endl;
				displayResultsWithId(id);
				cout << "---------------------------------------------------" << endl;
			}
			//casteVoteInElection(local, countLocal, electionChoice);

		}
		else goto reSelectVoteType;



	}
	else if (choice == 2) {
		cout << "---------------------------------------------------" << endl;
		cout << "National Election" << endl;
		cout << "---------------------------------------------------" << endl;
		electionChoice = displayNationalElections(3);
		if (electionChoice[0] != -1)
		{
			
		int id = getIdFromUserTodDisplayResult(electionChoice);
		if (id != -1) {
			cout << "---------------------------------------------------" << endl;
			displayResultsWithId(id);
			cout << "---------------------------------------------------" << endl;
		}

			//casteVoteInElection(national, countNational, electionChoice);
		}
		else goto reSelectVoteType;

	}
	else if (choice == 3) {
		cout << "---------------------------------------------------" << endl;
		cout << "Regional Election" << endl;
		cout << "---------------------------------------------------" << endl;
		electionChoice = displayRegionalElections(3);

		if (electionChoice[0] != -1) {
			int id = getIdFromUserTodDisplayResult(electionChoice);
			if (id != -1) {
				cout << "---------------------------------------------------" << endl;
				displayResultsWithId(id);
				cout << "---------------------------------------------------" << endl;
			}
			//casteVoteInElection(regional, countRegional, electionChoice);
		}
		else goto reSelectVoteType;
	}
	else if (choice == 4) {
		cout << "---------------------------------------------------" << endl;
		cout << "exiting..." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}

	else {
		cout << "---------------------------------------------------" << endl;
		cout << "Invalid choice." << endl;
		cout << "---------------------------------------------------" << endl;
		goto reSelectVoteType;
	}



}
void electionManger::actiDeactiElectionAdmin(bool parity) {
	int intBoolParity;
	if (parity)
		intBoolParity = 0;
	else intBoolParity = 1;
	cout << "---------------------------------------------------" << endl;
	cout << "Enter " << endl;
reSelectVoteType:
	cout << "---------------------------------------------------" << endl;
	cout << "1. Local Election" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "2. National Election" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "3. Regional Election" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "4. Exit" << endl;
	cout << "---------------------------------------------------" << endl;
	int choice;
	cin >> choice;
	int* electionChoice;
	if (choice == 1) {
		cout << "---------------------------------------------------" << endl;
		cout << "Local Election" << endl;
		cout << "---------------------------------------------------" << endl;
		electionChoice = displayLocalElections(intBoolParity);
		if (electionChoice[0] != -1) {
			int id = getIdFromUserTodDisplayResult(electionChoice);
			if (id != -1) {
				//displayResultsWithId(id);
				actiDeactiElectionUsingId(id, choice,parity);
			}
			//casteVoteInElection(local, countLocal, electionChoice);

		}
		else goto reSelectVoteType;



	}
	else if (choice == 2) {
		cout << "---------------------------------------------------" << endl;
		cout << "National Election" << endl;
		cout << "---------------------------------------------------" << endl;
		electionChoice = displayNationalElections(intBoolParity);
		if (electionChoice[0] != -1)
		{

			int id = getIdFromUserTodDisplayResult(electionChoice);
			if (id != -1) {
				//displayResultsWithId(id);
				actiDeactiElectionUsingId(id, choice,parity);
			}

			//casteVoteInElection(national, countNational, electionChoice);
		}
		else goto reSelectVoteType;

	}
	else if (choice == 3) {
		cout << "---------------------------------------------------" << endl;
		cout << "Regional Election" << endl;
		cout << "---------------------------------------------------" << endl;
		electionChoice = displayRegionalElections(intBoolParity);

		if (electionChoice[0] != -1) {
			int id = getIdFromUserTodDisplayResult(electionChoice);
			if (id != -1) {
				//displayResultsWithId(id);
				actiDeactiElectionUsingId(id, choice,parity);

			}
			//casteVoteInElection(regional, countRegional, electionChoice);
		}
		else goto reSelectVoteType;
	}
	else if (choice == 4) {
		cout << "---------------------------------------------------" << endl;
		cout << "exiting..." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}

	else {
		cout << "---------------------------------------------------" << endl;
		cout << "Invalid choice." << endl;
		cout << "---------------------------------------------------" << endl;
		goto reSelectVoteType;
	}



}
void electionManger::actiDeactiElectionUsingId(int id,int type,bool parity) {

	if (type == 1) {
		//cout << "Local Election" << endl;
		for (int i = 0; i < countLocal; i++) {
			if (local[i].getElectionId() == id) {
				local[i].setIsActive(parity);

				if (parity == false) {
					cout << "---------------------------------------------------" << endl;
					cout << "Local Election DeActivated :: " << local[i].getElectionId() << endl;
					cout << "---------------------------------------------------" << endl;
				}
				else {
					cout << "---------------------------------------------------" << endl;
				cout << "Local Election Activated" << endl;
				cout << "---------------------------------------------------" << endl;
				local[i].calculateFutureTime(stoi(local[i].getElectionTime()),local[i].getTimeType());
				cout << "---------------------------------------------------" << endl;
				}
				return;
			}
		}
	}
	else if (type == 2) {
		//cout << "National Election" << endl;
		for (int i = 0; i < countNational; i++) {
			if (national[i].getElectionId() == id) {
				national[i].setIsActive(parity);
				if (parity == false) {
					cout << "---------------------------------------------------" << endl;
					cout << "National Election DeActivated ID::" << national[i].getElectionId() << endl;
					cout << "---------------------------------------------------" << endl;
				}
				else
				{
					cout << "---------------------------------------------------" << endl;
				cout << "National Election Activated" << endl;
				cout << "---------------------------------------------------" << endl;
				national[i].calculateFutureTime(stoi(national [i] .getElectionTime()),national[i].getTimeType());
				cout << "---------------------------------------------------" << endl;

				}

				return;
			}
		}
	}
	else if (type == 3) {
		//cout << "Regional Election" << endl;
		for (int i = 0; i < countRegional; i++) {
			if (regional[i].getElectionId() == id) {
				regional[i].setIsActive(parity);
				if (parity == false) {
					cout << "---------------------------------------------------" << endl;
					cout << "Regional Election DeActivated" << endl;
					cout << "---------------------------------------------------" << endl;
				}
				else {
					cout << "---------------------------------------------------" << endl;
				regional[i].calculateFutureTime(stoi(regional[i].getElectionTime()), regional[i].getTimeType());
					//cout << "Regional Election Activated" << endl;
				cout << "---------------------------------------------------" << endl;
				cout << "Regional Election Activated" << endl;
				cout << "---------------------------------------------------" << endl;
				}
				return;
			}
		}
	}
	else {
		cout << "---------------------------------------------------" << endl;
		cout << "Invalid choice." << endl;
		cout << "---------------------------------------------------" << endl;
		return;
	}
	
}
int electionManger::getIdFromUserTodDisplayResult(int* choices) {
	cout << "---------------------------------------------------" << endl;
	cout << "Enter Election ID: ";
	cout << "---------------------------------------------------" << endl;
	int id;
	cin >> id;
	bool isElectionFound = false;
	for (int i = 1; i < choices[0] + 1; i++) {
		if (choices[i] == id) {
			cout << "---------------------------------------------------" << endl;
			cout << "Election Found" << endl;
			cout << "---------------------------------------------------" << endl;
			isElectionFound = true;
		}
	}
	if (isElectionFound == false) {
		cout << "---------------------------------------------------" << endl;
		cout << "Election not found...." << endl;
		cout << "---------------------------------------------------" << endl;
		return -1;
	}
	return id;


}
void electionManger::setFutureEndTime() {


}