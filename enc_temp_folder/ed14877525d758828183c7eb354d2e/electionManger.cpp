#include "electionManger.h"
#include <iostream>
#include <string>
#include<cstdlib> 
#include<sstream>
#include <fstream>


using namespace std;
bool checkInputElectionManger(string input, string tag);

int electionManger::countNumOfElections(string fileName) {
    int count = 0;
    ifstream file(fileName + ".txt");
    if (!file.is_open()) {
        
        cout << "---------------------------------------------------" << endl;
        cerr << "Error: Could not open file '" << fileName << ".txt' for counting." << endl;
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

    countLocal = countNumOfElections("localElection");
    countNational = countNumOfElections("nationalElection");
    countRegional = countNumOfElections("regionalElection");

    // Dynamically allocate memory only if count > 0
    if (countLocal > 0) local = new localElection[countLocal]; else local = nullptr;
    if (countNational > 0) national = new nationalElection[countNational]; else national = nullptr;
    if (countRegional > 0) regional = new regionalElection[countRegional]; else regional = nullptr;


    if (countLocal > 0) {
        ifstream localFile("localElection.txt");
        if (!localFile.is_open()) {
            cout << "---------------------------------------------------" << endl;
            cerr << "Error: Could not open localElection.txt to load data." << endl;
            cout << "---------------------------------------------------" << endl;
            // Potentially return or handle error more gracefully
        }
        else {
            int load = 0;
            for (int i = 0; i < countLocal; i++) {
                load++; // load seems to be 1-based index for file reading
                local[i].loadElectionFromFile("localElection", load);
            }
            localFile.close();
        }
    }

    if (countNational > 0) {
        ifstream nationalFile("nationalElection.txt");
        if (!nationalFile.is_open()) {
            cout << "---------------------------------------------------" << endl;
            cerr << "Error: Could not open nationalElection.txt to load data." << endl;
            cout << "---------------------------------------------------" << endl;
        }
        else {
            int load = 0;
            for (int i = 0; i < countNational; i++) {
                load++;
                national[i].loadElectionFromFile("nationalElection", load);
            }
            nationalFile.close();
        }
    }

    if (countRegional > 0) {
        ifstream regionalFile("regionalElection.txt");
        if (!regionalFile.is_open()) {
            cout << "---------------------------------------------------" << endl;
            cerr << "Error: Could not open regionalElection.txt to load data." << endl;
            cout << "---------------------------------------------------" << endl;
        }
        else {
            int load = 0;
            for (int i = 0; i < countRegional; i++) {
                load++;
                regional[i].loadElectionFromFile("regionalElection", load);
            }
            regionalFile.close();
        }
    }

    system("cls");
}

electionManger::electionManger() {
    local = nullptr;     // Initialize pointers to nullptr
    national = nullptr;
    regional = nullptr;
    countLocal = 0;
    countNational = 0;
    countRegional = 0;
    voterr = nullptr; // Initialize voterr if it's a member
    refreshAllData();
}

void electionManger::displayAllElectionNames() {
    system("cls");
    cout << "---------------------------------------------------" << endl;
    cout << "||            Available Elections                ||" << endl;
    cout << "---------------------------------------------------" << endl;

    bool electionsFound = false;

    if (countLocal == 0) {
        cout << "---------------------------------------------------" << endl;
        cout << "||           No Local Elections Found            ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }
    else {
        cout << "Local Elections: " << endl;
        for (int i = 0; i < countLocal; i++) {
            if (local[i].getIsActice() == true) { // Only display active elections
                cout << "---------------------------------------------------" << endl;
                cout << "  Name: " << local[i].getElectionName() << endl;
                cout << "  ID  : " << local[i].getElectionId() << endl;
                electionsFound = true;
            }
        }
        cout << "---------------------------------------------------" << endl;
    }

    if (countNational == 0) {
        cout << "---------------------------------------------------" << endl;
        cout << "||         No National Elections Found           ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }
    else {
        cout << "National Elections: " << endl;
        for (int i = 0; i < countNational; i++) {
            if (national[i].getIsActice() == true) { // Only display active elections
                cout << "---------------------------------------------------" << endl;
                cout << "  Name: " << national[i].getElectionName() << endl;
                cout << "  ID  : " << national[i].getElectionId() << endl;
                electionsFound = true;
            }
        }
        cout << "---------------------------------------------------" << endl;
    }

    if (countRegional == 0) {
        cout << "---------------------------------------------------" << endl;
        cout << "||         No Regional Elections Found           ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }
    else {
        cout << "Regional Elections: " << endl;
        for (int i = 0; i < countRegional; i++) {
            if (regional[i].getIsActice() == true) { // Only display active elections
                cout << "---------------------------------------------------" << endl;
                cout << "  Name: " << regional[i].getElectionName() << endl;
                cout << "  ID  : " << regional[i].getElectionId() << endl;
                electionsFound = true;
            }
        }
        cout << "---------------------------------------------------" << endl;
    }

    if (!electionsFound && countLocal == 0 && countNational == 0 && countRegional == 0) {
        // This condition is partially covered by individual checks,
        // but this catches if all counts are zero initially.
        cout << "---------------------------------------------------" << endl;
        cout << "||       No Active Elections Available           ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }
    else if (!electionsFound) {
        // This catches the case where there are elections, but none are active.
        cout << "---------------------------------------------------" << endl;
        cout << "||      No Currently Active Elections to Display   ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }
    
}

// Helper function to create title for displayElectionType functions
void displayElectionListTitle(const string& typeName, int filterType) {
    cout << "---------------------------------------------------" << endl;
    cout << "||         Listing " << typeName << " Elections         ||" << endl;
    if (filterType == 1) {
        cout << "||              (Active Only)                  ||" << endl;
    }
    else if (filterType == 0) {
        cout << "||             (Inactive Only)                 ||" << endl;
    }
    else if (filterType == 3) {
        cout << "||           (Active & Inactive)               ||" << endl;
    }
    cout << "---------------------------------------------------" << endl;
}


int* electionManger::displayLocalElections(int type) {
    if(type != 3)
    system("cls");
    displayElectionListTitle("Local", type);

    if (countLocal == 0) {
        cout << "---------------------------------------------------" << endl;
        cout << "||           No Local Elections Exist.           ||" << endl;
        cout << "---------------------------------------------------" << endl;
        int* noElectionChoices = new int[1];
        noElectionChoices[0] = -1; // Indicates no elections
        // system("pause"); // Optional
        return noElectionChoices;
    }

    int* Choices = new int[countLocal + 1]; // Choices[0] stores the count of displayed elections
    int displayCounter = 0;

    for (int i = 0; i < countLocal; i++) {
        bool displayThis = false;
        if (type == 1 && local[i].getIsActice() == true) { // Active only
            displayThis = true;
        }
        else if (type == 0 && local[i].getIsActice() == false) { // Inactive only
            displayThis = true;
        }
        else if (type == 3) { // All (active and inactive)
            displayThis = true;
        }

        if (displayThis) {
            cout << "---------------------------------------------------" << endl;
            cout << "  Name  : " << local[i].getElectionName() << endl;
            cout << "  ID    : " << local[i].getElectionId() << endl;
            if (type == 3) { // Display status if showing all
                cout << "  Status: " << (local[i].getIsActice() ? "Active" : "Inactive") << endl;
            }
            
            Choices[displayCounter + 1] = local[i].getElectionId();
            
            displayCounter++;
        }
    }
    cout << "---------------------------------------------------" << endl;

    if (displayCounter == 0) {
        Choices[0] = -1; // No elections matched the criteria
        if (type == 1) cout << "||     No Active Local Elections Found.          ||" << endl;
        else if (type == 0) cout << "||    No Inactive Local Elections Found.         ||" << endl;
        else cout << "||      No Local Elections to Display.           ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }
    else {
        Choices[0] = displayCounter; 
    }
  
    return Choices;
}

int* electionManger::displayNationalElections(int type) {
  
    system("cls");
    displayElectionListTitle("National", type);

    if (countNational == 0) {
        cout << "---------------------------------------------------" << endl;
        cout << "||         No National Elections Exist.          ||" << endl;
        cout << "---------------------------------------------------" << endl;
        int* noElectionChoices = new int[1];
        noElectionChoices[0] = -1;
     
        return noElectionChoices;
    }

    int* Choices = new int[countNational + 1];
    int displayCounter = 0;

    for (int i = 0; i < countNational; i++) {
        bool displayThis = false;
        if (type == 1 && national[i].getIsActice() == true) {
            displayThis = true;
        }
        else if (type == 0 && national[i].getIsActice() == false) {
            displayThis = true;
        }
        else if (type == 3) {
            displayThis = true;
        }

        if (displayThis) {
            cout << "---------------------------------------------------" << endl;
            cout << "  Name  : " << national[i].getElectionName() << endl;
            cout << "  ID    : " << national[i].getElectionId() << endl;
            if (type == 3) {
                cout << "  Status: " << (national[i].getIsActice() ? "Active" : "Inactive") << endl;
            }
            Choices[displayCounter + 1] = national[i].getElectionId();
            displayCounter++;
        }
    }
    cout << "---------------------------------------------------" << endl;

    if (displayCounter == 0) {
        Choices[0] = -1;
        if (type == 1) cout << "||   No Active National Elections Found.         ||" << endl;
        else if (type == 0) cout << "||  No Inactive National Elections Found.       ||" << endl;
        else cout << "||    No National Elections to Display.         ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }
    else {
        Choices[0] = displayCounter;
    }
  
    return Choices;
}

int* electionManger::displayRegionalElections(int type) {
    if (type != 3)
    system("cls");
    displayElectionListTitle("Regional", type);

    if (countRegional == 0) {
        cout << "---------------------------------------------------" << endl;
        cout << "||         No Regional Elections Exist.          ||" << endl;
        cout << "---------------------------------------------------" << endl;
        int* noElectionChoices = new int[1];
        noElectionChoices[0] = -1;
     
        return noElectionChoices;
    }

    int* Choices = new int[countRegional + 1];
    int displayCounter = 0;

    for (int i = 0; i < countRegional; i++) {
        bool displayThis = false;
        if (type == 1 && regional[i].getIsActice() == true) {
            displayThis = true;
        }
        else if (type == 0 && regional[i].getIsActice() == false) {
            displayThis = true;
        }
        else if (type == 3) {
            displayThis = true;
        }

        if (displayThis) {
            cout << "---------------------------------------------------" << endl;
            cout << "  Name  : " << regional[i].getElectionName() << endl;
            cout << "  ID    : " << regional[i].getElectionId() << endl;
            if (type == 3) {
                cout << "  Status: " << (regional[i].getIsActice() ? "Active" : "Inactive") << endl;
            }
            Choices[displayCounter + 1] = regional[i].getElectionId();
            displayCounter++;
        }
    }
    cout << "---------------------------------------------------" << endl;

    if (displayCounter == 0) {
        Choices[0] = -1;
        if (type == 1) cout << "||   No Active Regional Elections Found.         ||" << endl;
        else if (type == 0) cout << "||  No Inactive Regional Elections Found.       ||" << endl;
        else cout << "||    No Regional Elections to Display.         ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }
    else {
        Choices[0] = displayCounter;
    }
   
    return Choices;
}


void electionManger::displayAllElectionInDetails() {
    system("cls");
    cout << "---------------------------------------------------" << endl;
    cout << "||        Detailed Election Information          ||" << endl;
    cout << "---------------------------------------------------" << endl;

    bool foundAny = false;

    if (countLocal > 0) {
        cout << "Local Elections Details: " << endl;
        cout << "---------------------------------------------------" << endl;
        for (int i = 0; i < countLocal; i++) {
            local[i].displayElectionDetails(); // Assumes this function prints its own separators
            cout << "---------------------------------------------------" << endl;
            foundAny = true;
        }
    }
    else {
        cout << "No Local Elections to display details for." << endl;
        cout << "---------------------------------------------------" << endl;
    }

    if (countNational > 0) {
        cout << "National Elections Details: " << endl;
        cout << "---------------------------------------------------" << endl;
        for (int i = 0; i < countNational; i++) {
            national[i].displayElectionDetails();
            cout << "---------------------------------------------------" << endl;
            foundAny = true;
        }
    }
    else {
        cout << "No National Elections to display details for." << endl;
        cout << "---------------------------------------------------" << endl;
    }

    if (countRegional > 0) {
        cout << "Regional Elections Details: " << endl;
        cout << "---------------------------------------------------" << endl;
        for (int i = 0; i < countRegional; i++) {
            regional[i].displayElectionDetails();
            cout << "---------------------------------------------------" << endl;
            foundAny = true;
        }
    }
    else {
        cout << "No Regional Elections to display details for." << endl;
        cout << "---------------------------------------------------" << endl;
    }

    if (!foundAny) {
        cout << "||      No elections found in the system.        ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }
    // system("pause"); // Optional
}

void electionManger::displayAllCandidates() {
    system("cls");
    cout << "---------------------------------------------------" << endl;
    cout << "||              Candidate Listings               ||" << endl;
    cout << "---------------------------------------------------" << endl;
    bool foundAnyCandidates = false;

    if (countLocal > 0) {
        cout << "Local Election Candidates: " << endl;
        for (int i = 0; i < countLocal; i++) {
            cout << "--- Candidates for Local Election: " << local[i].getElectionName() << " (ID: " << local[i].getElectionId() << ") ---" << endl;
            // The getNumberOfRegions() in displayCandidates might be a misnomer if it means candidate count
            local[i].displayCandiates(local[i].getCandidateArray(), local[i].getNumberOfRegions()); // Assuming getNumberOfRegions returns candidate count for this context or displayCandidates handles it
            cout << "---------------------------------------------------" << endl;
            foundAnyCandidates = true;
        }
    }
    else {
        cout << "No Local Elections to display candidates for." << endl;
        cout << "---------------------------------------------------" << endl;
    }

   
    if (!foundAnyCandidates && countLocal == 0) { // Adjust if National/Regional uncommented
        cout << "|| No candidates to display for any election.    ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }
    
}


bool electionManger::checkIfUserAlreadyVoted(int electionId) {
    if (!voterr) { // Ensure voterr object is set
        cout << "---------------------------------------------------" << endl;
        cerr << "Error: Voter information not available to check vote status." << endl;
        cout << "---------------------------------------------------" << endl;
        return true; 
    }
    ifstream checkFile("voterVoteStatus.txt");
    if (!checkFile.is_open()) {
        cout << "---------------------------------------------------" << endl;
        cerr << "Error: Could not open voterVoteStatus.txt to check status." << endl;
        cout << "---------------------------------------------------" << endl;
        return false; 
    }
    string fileElectionId, fileCnic;
    while (getline(checkFile, fileElectionId, '*')) {
        getline(checkFile, fileCnic, '\n');
        if (stoi(fileElectionId) == electionId && fileCnic == voterr->getCnic()) {
            checkFile.close();
          
            return true;
        }
    }
    checkFile.close();
    return false;
}

void electionManger::saveVoterVoteStatusToFile(int electionId) {
    if (!voterr) { // Ensure voterr object is set
        cout << "---------------------------------------------------" << endl;
        cerr << "Error: Voter information not available to save vote status." << endl;
        cout << "---------------------------------------------------" << endl;
        return;
    }
    ofstream file("voterVoteStatus.txt", ios::app);
    if (!file.is_open()) {
        cout << "---------------------------------------------------" << endl;
        cerr << "Error: Could not open voterVoteStatus.txt to save status." << endl;
        cout << "---------------------------------------------------" << endl;
        return;
    }
    file << electionId << "*" << voterr->getCnic() << endl;
    file.close();
}

void electionManger::casteVoteInElection(election* e_arr, int size, int* choices) {

    cout << "---------------------------------------------------" << endl;
    cout << "||         Cast Your Vote in Election            ||" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Enter Election ID from the list above: ";
    int selected_election_id;
    cin >> selected_election_id;
    cout << "---------------------------------------------------" << endl;

    bool isElectionFoundInChoices = false;

    for (int i = 1; i <= choices[0]; i++) {
        if (choices[i] == selected_election_id) {
            isElectionFoundInChoices = true;

            break;
        }
    }

    if (!isElectionFoundInChoices) {
        cout << "---------------------------------------------------" << endl;
        cout << "|| Error: Election ID " << selected_election_id << " is not valid or not listed. ||" << endl;
        cout << "---------------------------------------------------" << endl;

        return;
    }

    if (checkIfUserAlreadyVoted(selected_election_id)) {
        cout << "---------------------------------------------------" << endl;
        cout << "||      You have already voted in this election.   ||" << endl;
        cout << "||              Cannot vote again.               ||" << endl;
        cout << "---------------------------------------------------" << endl;

        return;
    }

    int electionIndex = -1;
    for (int i = 0; i < size; i++) {
        if (e_arr[i].getElectionId() == selected_election_id) {
            electionIndex = i;

            break;
        }
    }

    if (electionIndex != -1) {
        if (!e_arr[electionIndex].getIsActice()) {
            cout << "---------------------------------------------------" << endl;
            cout << "|| Error: This election is currently not active. ||" << endl;
            cout << "||               Cannot cast vote.               ||" << endl;
            cout << "---------------------------------------------------" << endl;

            return;
        }

        if (e_arr[electionIndex].hasTimePassed(e_arr[electionIndex].getFutureTime())) {
            cout << "---------------------------------------------------" << endl;
            cout << "||  Error: The voting period for this election   ||" << endl;
            cout << "||                 has passed.                   ||" << endl;
            cout << "---------------------------------------------------" << endl;

            return;
        }
        system("cls");
        cout << "---------------------------------------------------" << endl;
        cout << "|| Candidates for Election: " << e_arr[electionIndex].getElectionName() << " (ID: " << selected_election_id << ") ||" << endl;
        cout << "---------------------------------------------------" << endl;

        e_arr[electionIndex].displayCandiates(e_arr[electionIndex].getSelectedCandidates(), e_arr[electionIndex].getTotalCandidates());
        cout << "---------------------------------------------------" << endl;
        cout << "Enter Candidate CNIC (ID) to vote for: ";
        int candidate_cnic_id;
        cin >> candidate_cnic_id;
        cout << "---------------------------------------------------" << endl;

        bool validCandidate = false;

        for (int i = 0; i < e_arr[electionIndex].getTotalCandidates(); i++) {
            if (e_arr[electionIndex].getSelectedCandidates()[i].getCnicInt() == candidate_cnic_id) {
                validCandidate = true;
                break;
            }
        }

        if (validCandidate) {
            e_arr[electionIndex].castVote(voterr, candidate_cnic_id); // voterr needs to be a valid Voter object
            saveVoterVoteStatusToFile(selected_election_id);
            system("cls");
            cout << "---------------------------------------------------" << endl;
            cout << "||          Vote Cast Successfully!              ||" << endl;
            cout << "---------------------------------------------------" << endl;
        }
        else {
            cout << "---------------------------------------------------" << endl;
            cout << "|| Error: Invalid Candidate ID entered.          ||" << endl;
            cout << "---------------------------------------------------" << endl;
        }
    }
    else {

        cout << "---------------------------------------------------" << endl;
        cout << "||  Internal Error: Election data not found.     ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }

}
void electionManger::castVote() {
    if (!voterr) {
        system("cls");
        cout << "---------------------------------------------------" << endl;
        cout << "|| Error: Voter not logged in or identified.     ||" << endl;
        cout << "||         Cannot proceed with voting.           ||" << endl;
        cout << "---------------------------------------------------" << endl;
     
        return;
    }
reSelectVoteType:
    system("cls");
    cout << "---------------------------------------------------" << endl;
    cout << "||            Cast Your Vote Menu                ||" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Select Election Type to Vote In:" << endl;
    cout << "  1. Local Election" << endl;
    cout << "  2. National Election" << endl;
    cout << "  3. Regional Election" << endl;
    cout << "  4. Back to Previous Menu" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Enter your choice (1-4): ";
    string choiceStr;
    cin >> choiceStr;

    if (!checkInputElectionManger(choiceStr, "Choice")) {
        system("pause");
        goto reSelectVoteType;

    }
    int choice = stoi(choiceStr);
    cout << "---------------------------------------------------" << endl;

    int* electionChoices = nullptr; // Use a single pointer

    switch (choice) {
    case 1:
      
        electionChoices = displayLocalElections(1); // Type 1 for active elections
        if (electionChoices && electionChoices[0] != -1) {
            casteVoteInElection(local, countLocal, electionChoices);
        }
        else {
            cout << "No active Local Elections to vote in." << endl;
             system("pause");
            goto reSelectVoteType; // Or offer to go back
        }
        delete[] electionChoices; // Clean up
        break;
    case 2:
       
        electionChoices = displayNationalElections(1);
        if (electionChoices && electionChoices[0] != -1) {
            casteVoteInElection(national, countNational, electionChoices);
        }
        else {
            cout << "No active National Elections to vote in." << endl;
             system("pause");
            goto reSelectVoteType;
        }
        delete[] electionChoices;
        break;
    case 3:
       
        electionChoices = displayRegionalElections(1);
        if (electionChoices && electionChoices[0] != -1) {
            casteVoteInElection(regional, countRegional, electionChoices);
        }
        else {
            cout << "No active Regional Elections to vote in." << endl;
             system("pause");
            goto reSelectVoteType;
        }
        delete[] electionChoices;
        break;
    case 4:
        cout << "Returning to previous menu..." << endl;
     
        return;
    default:
        cout << "---------------------------------------------------" << endl;
        cout << "|| Invalid choice. Please try again.             ||" << endl;
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
    system("cls");
    cout << "---------------------------------------------------" << endl;
    cout << "||              Your Voting History              ||" << endl;
    cout << "---------------------------------------------------" << endl;

    if (!voterr) {
        cout << "---------------------------------------------------" << endl;
        cout << "|| Error: Voter not logged in or identified.     ||" << endl;
        cout << "||         Cannot display voting history.        ||" << endl;
        cout << "---------------------------------------------------" << endl;
       
        return;
    }

    ifstream historyFile("voterVoteStatus.txt");
    if (!historyFile.is_open()) {
        cout << "---------------------------------------------------" << endl;
        cerr << "Error: Could not open voterVoteStatus.txt to check history." << endl;
        cout << "---------------------------------------------------" << endl;
       
        return;
    }

    string idStr, voterCnicStr;
    int electionIdInt;
    bool historyFound = false;
    while (getline(historyFile, idStr, '*')) {
        getline(historyFile, voterCnicStr, '\n');
        if (voterCnicStr == voterr->getCnic()) {
            historyFound = true;
            electionIdInt = stoi(idStr);
            cout << "---------------------------------------------------" << endl;
            cout << "  Voted in Election ID : " << idStr << endl;
            string elecName = getElectionNameById(electionIdInt); // This also prints, might be redundant
            if (!elecName.empty()) {
                // getElectionNameById already prints details, so this might be extra:
                // cout << "  Election Name        : " << elecName << endl;
            }
            else {
                cout << "  (Could not retrieve election name)" << endl;
            }
            cout << "---------------------------------------------------" << endl;
        }
    }
    historyFile.close();

    if (!historyFound) {
        cout << "---------------------------------------------------" << endl;
        cout << "||          No voting history found.             ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }
    else {
        cout << "---------------------------------------------------" << endl;
        cout << "||            End of Voting History              ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }
    // system("pause"); // Optional
}

string electionManger::getElectionNameById(int id) {
    ifstream checkNameFile("electionNames.txt");
    if (!checkNameFile.is_open()) {
       
        return "";
    }
    string electionIdFromFile, electionNameFromFile, tempDetails;
    while (getline(checkNameFile, electionIdFromFile, '*')) {
        getline(checkNameFile, electionNameFromFile, '*'); // Name
        getline(checkNameFile, tempDetails, '\n');      // Rest of the line (e.g., candidate count)
        if (stoi(electionIdFromFile) == id) {
            checkNameFile.close();
          
            return electionNameFromFile;
        }
    }
    checkNameFile.close();
    return ""; // Not found
}


void electionManger::displayResultsWithId(int electionId) {
    system("cls");
    cout << "---------------------------------------------------" << endl;
    cout << "||          Election Results Display             ||" << endl;
    cout << "---------------------------------------------------" << endl;

    ifstream electionNameFile("electionNames.txt");
    if (!electionNameFile.is_open()) {
        cout << "---------------------------------------------------" << endl;
        cerr << "Error: Could not open electionNames.txt to get details." << endl;
        cout << "---------------------------------------------------" << endl;
      
        return;
    }
    string electionIdStr, currentElectionNameStr, totalCandidatesStr;
    bool electionMetaFound = false;
    while (getline(electionNameFile, electionIdStr, '*')) {
        getline(electionNameFile, currentElectionNameStr, '*');
        getline(electionNameFile, totalCandidatesStr, '\n');
        if (stoi(electionIdStr) == electionId) {
            electionMetaFound = true;
            cout << "---------------------------------------------------" << endl;
            cout << "  Election ID      : " << electionIdStr << endl;
            cout << "  Election Name    : " << currentElectionNameStr << endl;
            cout << "  Total Candidates : " << totalCandidatesStr << endl; // In this election's setup
            cout << "---------------------------------------------------" << endl;
            break;
        }
    }
    electionNameFile.close();

    if (!electionMetaFound) {
        cout << "---------------------------------------------------" << endl;
        cout << "|| Error: Election metadata not found for ID " << electionId << ".||" << endl;
        cout << "---------------------------------------------------" << endl;
    
        return;
    }
    if (totalCandidatesStr.empty() || stoi(totalCandidatesStr) == 0) {
        cout << "---------------------------------------------------" << endl;
        cout << "|| No candidates were registered for this election.||" << endl;
        cout << "||           No results to display.                ||" << endl;
        cout << "---------------------------------------------------" << endl;
        
        return;
    }
    int totalCandidatesInt = stoi(totalCandidatesStr);

    string resultFileName = to_string(electionId) + ".txt";
    ifstream electionDataFile(resultFileName);
    if (!electionDataFile.is_open()) {
        cout << "---------------------------------------------------" << endl;
        cerr << "Error: Could not open results file '" << resultFileName << "'." << endl;
        cout << "||       Results might not be available yet.       ||" << endl;
        cout << "---------------------------------------------------" << endl;
     
        return;
    }

    int* candidateCnics = new int[totalCandidatesInt];
    int* candidateVoteCounts = new int[totalCandidatesInt];
    string cnicStr, voteCountStr, candidateNameStr; // Added candidateNameStr

    cout << "||                Voting Results                 ||" << endl;
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < totalCandidatesInt; i++) {
        if (!getline(electionDataFile, candidateNameStr, '*')) break; // Candidate Name
        if (!getline(electionDataFile, cnicStr, '*')) break;          // CNIC
        if (!getline(electionDataFile, voteCountStr, '\n')) break;    // Vote Count

        candidateCnics[i] = stoi(cnicStr);
        candidateVoteCounts[i] = stoi(voteCountStr);

        cout << "  Candidate Name: " << candidateNameStr << endl;
        cout << "  Candidate ID  : " << candidateCnics[i] << endl;
        cout << "  Vote Count    : " << candidateVoteCounts[i] << endl;
        cout << "---------------------------------------------------" << endl;
    }
    electionDataFile.close();
    delete[] candidateCnics;
    delete[] candidateVoteCounts;

    cout << "||              End Of Results                 ||" << endl;
    cout << "---------------------------------------------------" << endl;
    
}

void electionManger::displayResults() {
reSelectTypeForResults:
    system("cls");
    viewElectionResultsMenu:
    cout << "---------------------------------------------------" << endl;
    cout << "||        View Election Results Menu             ||" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Select Election Type to View Results For:" << endl;
    cout << "  1. Local Election" << endl;
    cout << "  2. National Election" << endl;
    cout << "  3. Regional Election" << endl;
    cout << "  4. Back to Previous Menu" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Enter your choice (1-4): ";
    string choiceStr;
    cin >> choiceStr;

    if (!checkInputElectionManger(choiceStr, "Choice")) {
        system("pause");
        goto viewElectionResultsMenu;

    }
    int choice = stoi(choiceStr);

  

    int* electionChoicesList = nullptr;
    int electionIdToDisplay = -1;

    switch (choice) {
    case 1:
        electionChoicesList = displayLocalElections(3); // Type 3 for all (active/inactive)
        if (electionChoicesList && electionChoicesList[0] != -1) {
            electionIdToDisplay = getIdFromUserTodDisplayResult(electionChoicesList);
            if (electionIdToDisplay != -1) {
                displayResultsWithId(electionIdToDisplay);
            }
        }
        else {
            cout << "No Local Elections found to display results for." << endl;
           
        }
        if (electionChoicesList) delete[] electionChoicesList;
        break;
    case 2:
        electionChoicesList = displayNationalElections(3);
        if (electionChoicesList && electionChoicesList[0] != -1) {
            electionIdToDisplay = getIdFromUserTodDisplayResult(electionChoicesList);
            if (electionIdToDisplay != -1) {
                displayResultsWithId(electionIdToDisplay);
            }
        }
        else {
            cout << "No National Elections found to display results for." << endl;
           
        }
        if (electionChoicesList) delete[] electionChoicesList;
        break;
    case 3:
        electionChoicesList = displayRegionalElections(3);
        if (electionChoicesList && electionChoicesList[0] != -1) {
            electionIdToDisplay = getIdFromUserTodDisplayResult(electionChoicesList);
            if (electionIdToDisplay != -1) {
                displayResultsWithId(electionIdToDisplay);
            }
        }
        else {
            cout << "No Regional Elections found to display results for." << endl;
            
        }
        if (electionChoicesList) delete[] electionChoicesList;
        break;
    case 4:
        cout << "Returning to previous menu..." << endl;
       
        return;
    default:
        cout << "---------------------------------------------------" << endl;
        cout << "|| Invalid choice. Please try again.             ||" << endl;
        cout << "---------------------------------------------------" << endl;
        
        goto reSelectTypeForResults;
    }
   
}

void electionManger::actiDeactiElectionAdmin(bool activate) { // 'parity' renamed to 'activate'
    int filterType; // 0 for inactive (to activate them), 1 for active (to deactivate them)
    string actionVerb;

    if (activate) { // If true, we want to activate an election (so list inactive ones)
        filterType = 0; // List inactive elections
        actionVerb = "Activate";
    }
    else { 
        filterType = 1; // List active elections
        actionVerb = "Deactivate";
    }

reSelectTypeForActivation:
    system("cls");
    cout << "---------------------------------------------------" << endl;
    cout << "||      " << actionVerb << " Election Menu             ||" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Select Election Type to " << actionVerb << ":" << endl;
    cout << "  1. Local Election" << endl;
    cout << "  2. National Election" << endl;
    cout << "  3. Regional Election" << endl;
    cout << "  4. Back to Previous Menu" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Enter your choice (1-4): ";
    char choice;
    cin >> choice;
   
    int* electionChoicesList = nullptr;
    int electionIdToModify = -1;

    switch (choice) {
    case '1':
        electionChoicesList = displayLocalElections(filterType);
        if (electionChoicesList && electionChoicesList[0] != -1) {
            electionIdToModify = getIdFromUserTodDisplayResult(electionChoicesList); // Reusing this helper
            if (electionIdToModify != -1) {
                actiDeactiElectionUsingId(electionIdToModify, 1, activate);
            }
        }
        else {
            cout << "No Local Elections matching criteria to " << actionVerb << "." << endl;
             system("pause");
        }
        if (electionChoicesList) delete[] electionChoicesList;
        break;
    case '2':
        electionChoicesList = displayNationalElections(filterType);
        if (electionChoicesList && electionChoicesList[0] != -1) {
            electionIdToModify = getIdFromUserTodDisplayResult(electionChoicesList);
            if (electionIdToModify != -1) {
                actiDeactiElectionUsingId(electionIdToModify, 2, activate);
            }
        }
        else {
            cout << "No National Elections matching criteria to " << actionVerb << "." << endl;
             system("pause");
        }
        if (electionChoicesList) delete[] electionChoicesList;
        break;
    case '3':
        electionChoicesList = displayRegionalElections(filterType);
        if (electionChoicesList && electionChoicesList[0] != -1) {
            electionIdToModify = getIdFromUserTodDisplayResult(electionChoicesList);
            if (electionIdToModify != -1) {
                actiDeactiElectionUsingId(electionIdToModify, 3, activate);
            }
        }
        else {
            cout << "No Regional Elections matching criteria to " << actionVerb << "." << endl;
             system("pause");
        }
        if (electionChoicesList) delete[] electionChoicesList;
        break;
    case '4':
        cout << "Returning to previous menu..." << endl;
   
        return;
    default:
        cout << "---------------------------------------------------" << endl;
        cout << "|| Invalid choice. Please try again.             ||" << endl;
        cout << "---------------------------------------------------" << endl;
         system("pause");
        goto reSelectTypeForActivation;
    }
   
}

void electionManger::actiDeactiElectionUsingId(int id, int type, bool activate) { // 'parity' renamed
    system("cls"); 
    string electionTypeName;
    bool success = false;

    if (type == 1) { // Local
        electionTypeName = "Local";
        for (int i = 0; i < countLocal; i++) {
            if (local[i].getElectionId() == id) {
                if (local[i].getIsActice() == activate) { // Already in desired state
                    cout << "---------------------------------------------------" << endl;
                    cout << "|| Local Election (ID: " << id << ") is already " << (activate ? "Activated." : "Deactivated.") << " ||" << endl;
                    cout << "---------------------------------------------------" << endl;
                }
                else {
                    local[i].setIsActive(activate);
                    if (activate) { // If activating, calculate future time
                        local[i].calculateFutureTime(stoi(local[i].getElectionTime()), local[i].getTimeType());
                    }
                    success = true;
                }
                break;
            }
        }
    }
    else if (type == 2) { // National
        electionTypeName = "National";
        for (int i = 0; i < countNational; i++) {
            if (national[i].getElectionId() == id) {
                if (national[i].getIsActice() == activate) {
                    cout << "---------------------------------------------------" << endl;
                    cout << "|| National Election (ID: " << id << ") is already " << (activate ? "Activated." : "Deactivated.") << " ||" << endl;
                    cout << "---------------------------------------------------" << endl;
                }
                else {
                    national[i].setIsActive(activate);
                    if (activate) {
                        national[i].calculateFutureTime(stoi(national[i].getElectionTime()), national[i].getTimeType());
                    }
                    success = true;
                }
                break;
            }
        }
    }
    else if (type == 3) { // Regional
        electionTypeName = "Regional";
        for (int i = 0; i < countRegional; i++) {
            if (regional[i].getElectionId() == id) {
                if (regional[i].getIsActice() == activate) {
                    cout << "---------------------------------------------------" << endl;
                    cout << "|| Regional Election (ID: " << id << ") is already " << (activate ? "Activated." : "Deactivated.") << " ||" << endl;
                    cout << "---------------------------------------------------" << endl;
                }
                else {
                    regional[i].setIsActive(activate);
                    if (activate) {
                        regional[i].calculateFutureTime(stoi(regional[i].getElectionTime()), regional[i].getTimeType());
                    }
                    success = true;
                }
                break;
            }
        }
    }
    else {
        cout << "---------------------------------------------------" << endl;
        cout << "|| Internal Error: Invalid election type.        ||" << endl;
        cout << "---------------------------------------------------" << endl;
       
        return;
    }

    if (success) {
        cout << "---------------------------------------------------" << endl;
        cout << "|| " << electionTypeName << " Election (ID: " << id << ") has been successfully "
            << (activate ? "Activated." : "Deactivated.") << " ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }
    else if (!((type == 1 && countLocal > 0 && local[0].getIsActice() == activate) || // check if it was already in state
        (type == 2 && countNational > 0 && national[0].getIsActice() == activate) ||
        (type == 3 && countRegional > 0 && regional[0].getIsActice() == activate))) {
        // If not successful and not already in desired state, then it means election ID was not found for that type
        cout << "---------------------------------------------------" << endl;
        cout << "|| Error: " << electionTypeName << " Election with ID " << id << " not found. ||" << endl;
        cout << "---------------------------------------------------" << endl;
    }
     system("pause"); // Optional
}


int electionManger::getIdFromUserTodDisplayResult(int* choices) {
   
    cout << "---------------------------------------------------" << endl;
    cout << "Enter Election ID from the list above: ";
    int id_input;
    cin >> id_input;
   
    bool isElectionFound = false;
    
    for (int i = 1; i <= choices[0]; i++) {
        if (choices[i] == id_input) {
            isElectionFound = true;
            break;
        }
    }

    if (isElectionFound) {
    
        return id_input;
    }
    else {
        cout << "---------------------------------------------------" << endl;
        cout << "|| Error: Invalid Election ID '" << id_input << "' entered.      ||" << endl;
        cout << "|| Please select an ID from the displayed list.  ||" << endl;
        cout << "---------------------------------------------------" << endl;
        // system("pause"); // Optional
        return -1; // Indicates error or invalid selection
    }
}

void electionManger::setFutureEndTime() {

// This function is not implemented in the provided code.
// You might want to implement it based on your requirements.
}


void electionManger::setCurrentVoter(voter* v) { // Assuming Voter is the class/struct type
    voterr = v;
}

bool checkInputElectionManger(string input, string tag) {

    //checking if it is storing int valur or string
    stringstream ss(input);
    int num;
    char extra;

    // Try to parse an integer
    if (!(ss >> num)) {
        cout << "---------------------------------------------------" << endl;
        cout << "Error: " << tag << " '" << input << "' " << tag << " Must be in NUMERIC." << endl;
        cout << "---------------------------------------------------" << endl;
        return false;
    }

    // Check if there's any non-integer character left
    if (ss >> extra) {
        cout << "---------------------------------------------------" << endl;
        cout << "Error: " << tag << " '" << input << "' " << tag << " Must be in NUMERIC." << endl;
        cout << "---------------------------------------------------" << endl;
        return false;
    }

    return true;


}