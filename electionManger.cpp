#include "electionManger.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int electionManger::countNumOfElections(string fileName) {
	// Implement the logic to count local elections
	int count = 0;
	ifstream file(fileName + ".txt");
	if (!file.is_open()) {
		cerr << "Error opening file in counting :: " << fileName << endl;
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
	cout << "refereshin...." << endl;
	countLocal = countNumOfElections("localElection");
	countNational = countNumOfElections("nationalElection");
	countRegional = countNumOfElections("regionalElection");
	local = new localElection[countLocal];
	national = new nationalElection[countNational];
	regional = new regionalElection[countRegional];
	ifstream localFile("localElection.txt");
	if (!localFile.is_open()) {
		cerr << "Error opening local file to load data." << endl;
		return;
	}
	int load = 0;
	for (int i = 0; i < countLocal; i++) {
		load++;
		local[i].loadElectionFromFile("localElection", load);
	}
	ifstream nationalFile("nationalElection.txt");
	if (!nationalFile.is_open()) {
		cerr << "Error opening national file to load data." << endl;
		return;
	}
	//cout << "before region lodin elction" << endl;
	load = 0;
	for (int i = 0; i < countNational; i++) {
		load++;

		cout << "count regional is " << countRegional << endl;
		cout << "lodaing local election::" << i << endl;
		national[i].loadElectionFromFile("nationalElection", load);
	}
	cout << "after region lodin elction" << endl;

	ifstream regionalFile("regionalElection.txt");
	if (!regionalFile.is_open()) {
		cerr << "Error opening regional file to load data." << endl;
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



}
electionManger::electionManger() {
	refreshAllData();

}
void electionManger::displayAllElectionNames() {

	if (countLocal == 0) {
		cout << "No Local Election" << endl;
	}
	else {
		cout << "Local Elections: " << endl;

		for (int i = 0; i < countLocal; i++) {
			if (local[i].getIsActice() == true) {
				cout << "Name :: " << local[i].getElectionName() << endl;
				cout << "ID :: " << local[i].getElectionId() << endl;
			}
			
		}
	}
	if (countNational == 0) {
		cout << "No National Election" << endl;;
	}
	else {

		cout << "National Elections: " << endl;
		for (int i = 0; i < countNational; i++) {
			if (national[i].getIsActice() == true) {
				cout << "Name :: " << national[i].getElectionName() << endl;
				cout << "ID :: " << national[i].getElectionId() << endl;
			}
			
		}
	}
	if (countRegional == 0) {
		cout << "No Regional Election" << endl;
	}
	else {

		cout << "Regional Elections: " << endl;
		for (int i = 0; i < countRegional; i++) {
			if (regional[i].getIsActice() == true) {
				cout << "Name :: " << regional[i].getElectionName() << endl;
				cout << "ID :: " << regional[i].getElectionId() << endl;
			}
			
		}
	}
}
int* electionManger::displayLocalElections(int type) {  
   if (countLocal == 0) {  
       cout << "No Local Election" << endl;  
       int* regionChoices = new int[1];  
       regionChoices[0] = -1;  
       return regionChoices;  
   } else {  
       int counter = 0;  
       int* Choices = new int[countLocal + 1];  
       cout << "Local Elections: " << endl;  
       for (int i = 0; i < countLocal; i++) {  
           if (type == 1) {  
               if (local[i].getIsActice() == false) {  
                   continue;  
               }  
           } else if (type == 0) {  
               if (local[i].getIsActice() == true) {  
                   continue;  
               }  
           }  
           cout << "Name :: " << local[i].getElectionName() << endl;  
           cout << "ID :: " << local[i].getElectionId() << endl;  
           if (type == 3) {  
               cout << "Election Status :: " << local[i].getIsActice() << endl;  
           }  
           Choices[counter + 1] = local[i].getElectionId();  
           cout << Choices[counter + 1] << "::" << local[i].getElectionId() << endl;  
           counter++;  
       }  
       if (counter == 0) {  
           counter = -1;  
           cout << "No Local Elections Activated YET" << endl;  
       }  
       Choices[0] = counter;  
       if (counter > 0) {  
           cout << "election at choices 1: " << Choices[1] << endl;  
       }  
       return Choices;  
   }  
}


int* electionManger::displayNationalElections(int type) { 
	if (countNational == 0) {
		cout << "No national Election" << endl;
		int* regionChoices = new int[1];
		regionChoices[0] = -1;
		return regionChoices;
	}
	else {
		int counter = 0;
		int* Choices = new int[countNational + 1];
		cout << "national Elections: " << endl;
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
			cout << "Name :: " << national[i].getElectionName() << endl;
			cout << "ID :: " << national[i].getElectionId() << endl;
			if (type == 3) {
				cout << "Election Status :: " << national[i].getIsActice() << endl;
			}
			Choices[counter + 1] = national[i].getElectionId();
			cout << Choices[counter + 1] << "::" << national[i].getElectionId() << endl;
			counter++;
		}
		if (counter == 0) {
			counter = -1;
			cout << "No Local Elections Activated YET" << endl;
		}
		Choices[0] = counter;
		if (counter > 0) {
			cout << "election at choices 1: " << Choices[1] << endl;
		}
		return Choices;
	}
}


int* electionManger::displayRegionalElections(int type) {
	if (countRegional == 0) {
		cout << "No regional Election" << endl;
		int* regionChoices = new int[1];
		regionChoices[0] = -1;
		return regionChoices;
	}
	else {
		int counter = 0;
		int* Choices = new int[countRegional + 1];
		cout << "regional Elections: " << endl;
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
			cout << "Name :: " << regional[i].getElectionName() << endl;
			cout << "ID :: " << regional[i].getElectionId() << endl;
			if (type == 3) {
				cout << "Election Status :: " << regional[i].getIsActice() << endl;
			}
			Choices[counter + 1] = regional[i].getElectionId();
			cout << Choices[counter + 1] << "::" << regional[i].getElectionId() << endl;
			counter++;
		}
		if (counter == 0) {
			counter = -1;
			cout << "No Local Elections Activated YET" << endl;
		}
		Choices[0] = counter;
		if (counter > 0) {
			cout << "election at choices 1: " << Choices[1] << endl;
		}
		return Choices;
	}
}



void electionManger::displayAllElectionInDetails() {
	cout << "Local Elections: " << endl;
	for (int i = 0; i < countLocal; i++) {
		local[i].displayElectionDetails();
	}
	cout << "National Elections: " << endl;
	for (int i = 0; i < countNational; i++) {
		national[i].displayElectionDetails();
	}
	cout << "Regional Elections: " << endl;
	for (int i = 0; i < countRegional; i++) {
		regional[i].displayElectionDetails();
	}
}
void electionManger::displayAllCandidates() {

	cout << "Local Candidates: " << endl;
	for (int i = 0; i < countLocal; i++) {
		local[i].displayCandiates(local[i].getCandidateArray(), local[i].getNumberOfRegions());
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
		cerr << "Error opening file to check vote status." << endl;
		return false;
	}
	string electionId, cnic;
	while (getline(checkFile, electionId, '*')) {
		getline(checkFile, cnic, '\n');
		if (stoi(electionId) == id && cnic == voterr->getCnic()) {
			checkFile.close();
			return true; // User has already voted
		}
	}
	checkFile.close();

	return false; // User has not voted
}
void electionManger::saveVoterVoteStatusToFile(int id) {
	ofstream file("voterVoteStatus.txt", ios::app);
	if (!file.is_open()) {
		cerr << "Error opening file to save vote status." << endl;
		return;
	}
	file << id << "*" << voterr->getCnic() << endl;
	file.close();

}
void electionManger::casteVoteInElection(election* e, int size, int* choices) {

cout << "Enter Election ID: ";
int id;
cin >> id;
bool isElectionFound = false;
cout << "Choices :: at 0 is " << choices[0] << endl;
for (int i = 1; i < choices[0] + 1; i++) {
	cout << "choices::::" << choices[i] << endl;
	if (choices[i] == id) {
		isElectionFound = true;
		cout << "electionFound" << endl;
	}
}
if (isElectionFound == false) {
	cout << "Election not found...." << endl;
	return;
}
// Check if the user has already voted in this election
if (checkIfUserAlreadyVoted(id)) {
	cout << "You have already voted in this election." << endl;
	return;
}
int index = -1;
for (int i = 0; i < size; i++) {
	if (e[i].getElectionId() == id) {
		index = i;
		cout << "Election Found :: " << index << endl;
		break;
	}
}
if (index != -1) {
	// Check if the election time has passed
	if (e[index].hasTimePassed(e[index].getFutureTime())) {
		cout << "Election time has passed. You cannot vote." << endl;
		return;
	}

	e[index].displayCandiates(e[index].getSelectedCandidates(), e[index].getTotalCandidates());
	cout << "Enter Candidate ID: ";
	int candidateId;
	cin >> candidateId;

	// Check if the candidate ID is valid
	for (int i = 0; i < e[index].getTotalCandidates(); i++) {
		if (e[index].getSelectedCandidates()[i].getCnicInt() == candidateId) {
			e[index].castVote(voterr, candidateId);
			saveVoterVoteStatusToFile(id);
			cout << "Vote casted successfully." << endl;
			return;
		}
	}
	cout << "Invalid Candidate ID." << endl;
} else {
	cout << "Election not found." << endl;
}
}
void electionManger::castVote() {
reSelectVoteType:
	cout << "Enter Which type of Election you want to cast vote for" << endl;
	cout << "1. Local Election" << endl;
	cout << "2. National Election" << endl;
	cout << "3. Regional Election" << endl;
	cout << "4. Exit" << endl;
	int choice;
	cin >> choice;
	int* electionChoice;
	if (choice == 1) {
		cout << "Local Election" << endl;
		electionChoice = displayLocalElections(1);
		cout << "Election aftere choice " << electionChoice[1] << endl;
		if (electionChoice[0] != -1) {

			casteVoteInElection(local, countLocal, electionChoice);
		}
		else goto reSelectVoteType;



	}
	else if (choice == 2) {
		cout << "National Election" << endl;
		electionChoice = displayNationalElections(1);

		if (electionChoice[0] != -1)
		{

			casteVoteInElection(national, countNational, electionChoice);
		}
		else goto reSelectVoteType;

	}
	else if (choice == 3) {
		cout << "Regional Election" << endl;
		electionChoice = displayRegionalElections(1);

		if (electionChoice[0] != -1) {

			casteVoteInElection(regional, countRegional, electionChoice);
		}
		else goto reSelectVoteType;
	}
	else if (choice == 4) {
		cout << "exiting..." << endl;
		return;
	}

	else {
		cout << "Invalid choice." << endl;
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
		cerr << "Error opening file to check vote history." << endl;
		return;
	}
	cout << "History Of Elections You Voted For" << endl;
	string idStr, voterCnicStr;
	int electionIdInt;
	while (getline(historyFile, idStr, '*')) {
		electionIdInt = stoi(idStr);
		getline(historyFile, voterCnicStr, '\n');
		if (voterCnicStr == voterr->getCnic()) {
			cout << "Election ID: " << idStr ;
			cout << " :: ElectionName : " <<getElectionNameById(electionIdInt)  << endl;
		}
	}
	historyFile.close();
	cout << "End Of History" << endl;


}
string electionManger::getElectionNameById(int id) {

	ifstream checkNameFile("electionNames.txt");
	if (!checkNameFile.is_open()) {
		cerr << "Error opening file to check election names." << endl;
		return "";
	}
	string electionId, electionName,temp;
	while (getline(checkNameFile, electionId, '*')) {
		getline(checkNameFile, electionName, '*');
		getline(checkNameFile, temp, '\n');
		if (stoi(electionId) == id) {
			checkNameFile.close();
			return electionName;
		}
	}
	checkNameFile.close();
	return "";

}

void electionManger::displayResultsWithId(int electionId) {

	ifstream electionName("electionNames.txt");
	if (!electionName.is_open()) {
		cerr << "Error opening file to check election names." << endl;
		return;
	}
	string electionIdStr, electionNameStr, totalCandidates;
	while (getline(electionName, electionIdStr, '*')) {
		getline(electionName, electionNameStr, '*');
		getline(electionName, totalCandidates, '\n');
		if (stoi(electionIdStr) == electionId) {
			cout << "Election ID: " << electionIdStr << endl;
			cout << "Election Name: " << electionNameStr << endl;
			cout << "Total Candidates: " << totalCandidates << endl;
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
		cerr << "Error opening file to check election names." << endl;
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
	cout << "Results: " << endl;
	for (int i = 0; i < totalCandidatesInt; i++) {
		cout << "Candidate ID: " << candidateCnic[i] << endl;
		cout << "Vote Count: " << candidateVoteCount[i] << endl;
		
	}
	delete[] candidateCnic;
	delete[] candidateVoteCount;
	cout << "End Of Results" << endl;



}
void electionManger::displayResults() {
	cout << "Enter " << endl;
reSelectVoteType:
	cout << "1. Local Election" << endl;
	cout << "2. National Election" << endl;
	cout << "3. Regional Election" << endl;
	cout << "4. Exit" << endl;
	int choice;
	cin >> choice;
	int* electionChoice;
	if (choice == 1) {
		cout << "Local Election" << endl;
		electionChoice = displayLocalElections(3);
		if (electionChoice[0] != -1) {
			int id = getIdFromUserTodDisplayResult(electionChoice);
			if (id != -1) {
				displayResultsWithId(id);
			}
			//casteVoteInElection(local, countLocal, electionChoice);

		}
		else goto reSelectVoteType;



	}
	else if (choice == 2) {
		cout << "National Election" << endl;
		electionChoice = displayNationalElections(3);
		if (electionChoice[0] != -1)
		{
			
		int id = getIdFromUserTodDisplayResult(electionChoice);
		if (id != -1) {
			displayResultsWithId(id);
		}

			//casteVoteInElection(national, countNational, electionChoice);
		}
		else goto reSelectVoteType;

	}
	else if (choice == 3) {
		cout << "Regional Election" << endl;
		electionChoice = displayRegionalElections(3);

		if (electionChoice[0] != -1) {
			int id = getIdFromUserTodDisplayResult(electionChoice);
			if (id != -1) {
				displayResultsWithId(id);
			}
			//casteVoteInElection(regional, countRegional, electionChoice);
		}
		else goto reSelectVoteType;
	}
	else if (choice == 4) {
		cout << "exiting..." << endl;
		return;
	}

	else {
		cout << "Invalid choice." << endl;
		goto reSelectVoteType;
	}



}
void electionManger::actiDeactiElectionAdmin(bool parity) {
	int intBoolParity;
	if (parity)
		intBoolParity = 0;
	else intBoolParity = 1;

	cout << "Enter " << endl;
reSelectVoteType:
	cout << "1. Local Election" << endl;
	cout << "2. National Election" << endl;
	cout << "3. Regional Election" << endl;
	cout << "4. Exit" << endl;
	int choice;
	cin >> choice;
	int* electionChoice;
	if (choice == 1) {
		cout << "Local Election" << endl;
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
		cout << "National Election" << endl;
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
		cout << "Regional Election" << endl;
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
		cout << "exiting..." << endl;
		return;
	}

	else {
		cout << "Invalid choice." << endl;
		goto reSelectVoteType;
	}



}
void electionManger::actiDeactiElectionUsingId(int id,int type,bool parity) {

	if (type == 1) {
		//cout << "Local Election" << endl;
		for (int i = 0; i < countLocal; i++) {
			if (local[i].getElectionId() == id) {
				local[i].setIsActive(parity);

				if (parity == false)
					cout << "Local Election DeActivated :: " <<local[i].getElectionId()<< endl;
				else {
				
				cout << "Local Election Activated" << endl;
				local[i].calculateFutureTime(stoi(local[i].getElectionTime()),local[i].getTimeType());

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
				if (parity == false)
					cout << "National Election DeActivated ID::" << national[i].getElectionId() << endl;
				else
				{
				cout << "National Election Activated" << endl;
			
				national[i].calculateFutureTime(stoi(national [i] .getElectionTime()),national[i].getTimeType());


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
				if (parity == false)
					cout << "Regional Election DeActivated" << endl;
				else {
				regional[i].calculateFutureTime(stoi(regional[i].getElectionTime()), regional[i].getTimeType());
					//cout << "Regional Election Activated" << endl;
				cout << "Regional Election Activated" << endl;
				}
				return;
			}
		}
	}
	else {
		cout << "Invalid choice." << endl;
		return;
	}
	
}
int electionManger::getIdFromUserTodDisplayResult(int* choices) {

	cout << "Enter Election ID: ";

	int id;
	cin >> id;
	bool isElectionFound = false;
	for (int i = 1; i < choices[0] + 1; i++) {
		if (choices[i] == id) {
			isElectionFound = true;
		}
	}
	if (isElectionFound == false) {
		cout << "Election not found...." << endl;
		return -1;
	}
	return id;


}
void electionManger::setFutureEndTime() {


}