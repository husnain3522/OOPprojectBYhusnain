#include "election.h"
#include <iostream>
#include <string>
#include <fstream>
#include "candidate.h"
using namespace std;
int election::fileLenght(string fileName) {
	ifstream file((fileName+".txt"));
	if (!file.is_open()) {
		cerr << "Error opening file."<<fileName << endl;
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
election::election(string name="", string date="0", string time="0",int numRegioons=0) {
	electionName = name;
	electionDate = date;
	electionTime = time;
	numberOfRegions = numRegioons;
	regionCodes = new string[numRegioons];
}
void election::setElectionId(string id) {
	electionId = id;
}
string election::getElectionId() {
	return electionId;
}
void election::setElectionName(string name) {
	electionName = name;
}
void election::setElectionDate(string date) {
	electionDate = date;
}
void election::setElectionTime(string time) {
	electionTime = time;
}	
void election::setRegionCodes(string* codes, int numRegions) {
	regionCodes = new string[numRegions];
	for (int i = 0; i < numRegions; i++) {
		regionCodes[i] = codes[i];
	}
	numberOfRegions = numRegions;
}
string election::getElectionName() {
	return electionName;
}
string election::getElectionDate() {
	return electionDate;
}
string election::getElectionTime() {
	return electionTime;
}
string* election::getRegionCodes() {
	return regionCodes;
}
int election::getNumberOfRegions() {
	return numberOfRegions;
}
void election::displayElectionDetails() {
	cout << "Election Name: " << electionName << endl;
	cout << "Election Date: " << electionDate << endl;
	cout << "Election Time: " << electionTime << endl;
	cout << "Number of Regions: " << numberOfRegions << endl;
	cout << "Region Codes: ";
	for (int i = 0; i < numberOfRegions; i++) {
		cout << regionCodes[i] << " ";
	}
	cout << endl;
}
candidate* election::getCandidateArray() {
	int totalCandidates = fileLenght("candidate");
	candidate* candiArray = new candidate[totalCandidates];
	ifstream candidateFile("candidate.txt");
	if (!candidateFile.is_open()) {
		cerr << "Error opening file." << endl;
		return nullptr;
	}
	for (int i = 0; i < totalCandidates; i++)
	{
		string name, cnic, partyId;
		getline(candidateFile, name, '*');
		getline(candidateFile, cnic, '*');
		getline(candidateFile, partyId,'\n');
		candiArray[i].setName(name);
		candiArray[i].setCnic(cnic);
		candiArray[i].setPartyName(partyId);
	}
	return candiArray;
}

void election::displayCandiates(candidate * candiArray) {
//find candidates in array

  
       int totalCandidates = 0;  
       while (!candiArray[totalCandidates].getName().empty()) {  
           totalCandidates++;  
       }  
	   int totalCandi = totalCandidates;
    
  
	cout << "Candidates:" << endl;
	for (int i = 0; i< totalCandi; i++) {
		cout << "Name: " << candiArray[i].getName() << endl;
		cout << "CNIC: " << candiArray[i].getCnic() << endl;
		cout << "Party Name: " << candiArray[i].getPartyName() << endl;
	}
	delete[] candiArray;
}
candidate* deleteAcandy(candidate* candiArray, int candyIndex, int total) {  
   // Create a new array with size reduced by 1  
   candidate* tempArray = new candidate[total - 1];  

   for (int i = 0, j = 0; i < total; i++) {  
       if (i != candyIndex) {  
           tempArray[j++] = candiArray[i];  
       }  
   }  

   // Free the old array memory  
   delete[] candiArray;  

   // Return the new array  
   return tempArray;  
}
candidate* election::addSelectedCandidate(candidate candi, candidate* selectedCandidates) {  
   // Calculate the total number of candidates in the selectedCandidates array  
   int totalCandidates = 0;  
   if (selectedCandidates != nullptr) {  
       while (selectedCandidates[totalCandidates].getName() != "") {  
           totalCandidates++;  
       }  
   }  

   // Create a new array with size increased by 1  
   candidate* tempArray = new candidate[totalCandidates + 1];  

   // Copy existing candidates to the new array  
   for (int i = 0; i < totalCandidates; i++) {  
       tempArray[i] = selectedCandidates[i];  
   }  

   // Add the new candidate to the array  
   tempArray[totalCandidates] = candi;  

   // Free the old array memory  
   delete[] selectedCandidates;  

   // Return the new array  
   return tempArray;  
}
candidate* election::selectCandidates() {
	int totalCandidates = fileLenght("candidate");
	candidate* candiArray = new candidate[totalCandidates];
	ifstream candidateFile("candidate.txt");
	if (!candidateFile.is_open()) {
		cerr << "Error opening file." << endl;
		return nullptr;
	}
	bool selectNext = true;
	candidate* selectedCandidates ;
	selectedCandidates = nullptr;
	while (selectNext) {
		displayCandiates(candiArray);
		cout << "Select a candidate by entering their CNIC: ";
		string cnic;
		cin >> cnic;
		for (int i = 0; i < totalCandidates; i++) {
			if (candiArray[i].getCnic() == cnic) {
				//add that candidate to selected candidates
				addSelectedCandidate(candiArray[i], selectedCandidates);
				cout << "Candidate selected: " << candiArray[i].getName() << endl;


				//delete that candidate from that array and add it to selected candies
				candiArray = deleteAcandy(candiArray, i, totalCandidates);
				totalCandidates--;
				cout << "Do You want to add More Candidates (y/n): ";
				char choice;
				cin >> choice;
				if (choice == 'y' || choice == 'Y') {
					selectNext = true;
				}
				else {
					selectNext = false;
					break;
				}

			}

		}
		if (selectNext == false) {
			break;
		}
		else {
			cout << "Candidate not found. Please try again." << endl;
		}
		//show all candidates

	}
	delete[] candiArray;
	return selectedCandidates;

}
void election::addElectionToFileWithCandies() {
	cout << "Here Is list of candidates" << endl;
	int totalCandidates = fileLenght("candidate");
	cout << "Flile lenght is " << totalCandidates << endl;
	candidate *candiArray = new candidate[totalCandidates];
	ofstream electionFile("candidate.txt");

	if (!electionFile.is_open()) {
		cerr << "Error opening file." << endl;
		return;
	}

	  candiArray = selectCandidates();
	  //find lenght of selected candidates
	  int selectedCandidatesLength = 0;
	  while (candiArray[selectedCandidatesLength].getName() != "") {
		  selectedCandidatesLength++;
	  }	
	  //write selected candidates to file

	  electionFile << electionName << "*" << electionDate << "*" << electionTime << "*" << numberOfRegions << "*";
	  for (int i = 0; i < numberOfRegions; i++) {
		  electionFile << regionCodes[i] << "*";
	  }
	  for (int i = 0; i < selectedCandidatesLength; i++) {
		  electionFile << candiArray[i].getName() << "*" << candiArray[i].getCnic() << "*" << candiArray[i].getPartyName() << "*";
	  }
	  electionFile << endl;
	  cout << "Election saved to file." << endl;


	

}