#include<iostream>
#include<cstdlib> // For system("cls") and system("pause")

/*
Session-2025 Object Oriented Programming-Lab
Project Description: Online Voting System
No use of vector, maps or any other built-in libraries.
Objective: The Online Voting System is designed to provide a digital platform where eligible
voters can cast their votes in different types of elections (e.g., local, national, or regional).
The system aims to simplify the voting process, ensure transparency, and allow users to
participate in elections remotely and securely. The project will use Object-Oriented
Programming (OOP) principles like classes, inheritance, polymorphism, and abstraction to
create a modular, flexible, and extensible solution.
System Overview:
The Online Voting System will allow registered voters to authenticate, choose candidates,
and cast their votes electronically. The system will consist of various user roles (e.g., voter,
administrator) that interact with the system in different ways. It will also accommodate
different election types, each with its own set of rules, candidates, and processes.
Key Features:
1. User Authentication:
o Users will have to log in using their credentials (username/password).
o Only authenticated users can vote, ensuring election security.
2. User Roles:
o Voter: A registered voter can view the list of elections, vote for a candidate,
and check the status of their vote.
o Administrator: The administrator will have elevated privileges, including the
ability to create elections, add candidates, and manage the voting process.
The admin can also view voting results and ensure the integrity of the
election.
3. Election Management:
o The system will support different types of elections such as local, national,
and regional elections.
o Each election will have its own set of candidates, voting rules, and voting
methods.
o An administrator can create and modify election details, including the type of
election, the duration, and the list of candidates.

4. Voting Process:
o Voters will be able to select a candidate from a list and submit their vote.
Once the vote is cast, it will be recorded, and the system will prevent multiple
voting by the same user for a particular election.

o The system will ensure that once the voting period ends, the results can be
computed automatically based on the votes received.

5. Polymorphism in Elections:
o The system will use polymorphism to handle different types of elections, as
each election type (e.g., local vs. national) might have different voting
procedures or rules.
o The Election class will be a base class, and each specific election type (e.g.,
LocalElection, NationalElection) will be derived from it.
o Each derived class can override base class methods to implement its own
election-specific behavior (e.g., local elections might allow voting for more
candidates compared to national elections).

6. Candidate Management:
o The system will maintain a list of candidates for each election. Voters will be
able to view the list of candidates and their party affiliations (if applicable).
o Candidates can be added, modified, or removed by the administrator.
7. Results and Statistics:
o After the voting period has ended, the administrator will be able to view
detailed voting results.
o The system will display results in a user-friendly manner, such as graphs or
tables, showing the number of votes each candidate received.

Class Design:
1. User Class: A base class that will define the common attributes and methods for all
users (e.g., username, password, login()).
o Voter Class: Derived from the User class, this class represents a voter. It will
have methods like viewElections(), castVote(), and checkVoteStatus().
o Administrator Class: Also derived from the User class, the admin class will
include methods such as createElection(), addCandidate(), and
viewResults().

2. Election Class: A base class for elections with common properties and methods,
including startElection(), endElection(), and addCandidate().
o LocalElection Class: Derived from the Election class, this class will have
election-specific logic, like the ability to handle multiple candidates in a single
region.
o NationalElection Class: Another derived class, tailored for national
elections, potentially including rules like party affiliations and voting in multiple
regions.

3. Candidate Class: Represents the candidates running in an election. It will have
attributes like name, party affiliation, and the number of votes received.
o Methods: incrementVotes(), getVoteCount(), getCandidateInfo().

Object-Oriented Concepts Applied:
 Abstraction: By using abstract classes like Election and User, the system hides the
complex implementation details from the user. This ensures that each user only
interacts with the methods relevant to their role (voter or admin).
 Inheritance: The system uses inheritance to extend the base classes (e.g., User,
Election) to specialized classes like Voter, Administrator, and different election types
(LocalElection, NationalElection). This allows for code reusability and clarity.
 Polymorphism: Polymorphism allows the system to handle different types of
elections and user roles dynamically. By using virtual functions, the program can
invoke specific election rules (such as vote counting) for local and national elections
without needing to modify the core voting process.
 Encapsulation: All user data (credentials, votes, etc.) and election details (candidate
lists, voting methods) are encapsulated within respective classes. Only authorized
classes or methods have access to this data.
System Flow:
1. Administrator creates an election: The admin creates an election (e.g., national,
local) and adds candidates.
2. Voters login: Registered voters log in to the system to access the election.
3. Voting process: Voters view candidates, select one, and cast their vote.
4. End of voting period: Once the election period ends, the system calculates the
votes and generates results.
5. Results display: The administrator can view the final voting results and analyze the
data.

*/
#include "user.h"
#include "voter.h"
#include "admin.h" // Corrected from #include"admin.h"
#include <fstream>
#include <string>
#include "election.h"
#include "candidate.h"
#include "regionalElection.h"
#include "localElection.h"
#include "nationalElection.h"
#include "electionManger.h"

using namespace std;
admin checkAdmin(string, string, string);
voter checkVoter(string, string, string);
// admin checkCandidate(string, string , string); // This function is declared but not defined or used.
int electionIdGenerator();

int election::electionIdCounter = 3; // Static member initialization

int main() {
	system("cls"); // Clear screen at the very beginning

	electionManger em; // Initialize election manager, loads data

logIn:
	system("cls");
	cout << "---------------------------------------------------" << endl;
	cout << "||                                               ||" << endl;
	cout << "||       WELCOME TO THE ONLINE VOTING SYSTEM     ||" << endl;
	cout << "||                                               ||" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "|| Please select your role:                      ||" << endl;
	cout << "||   1. Administrator                            ||" << endl;
	cout << "||   2. Voter                                    ||" << endl;
	cout << "||   3. Exit System                              ||" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Enter your choice (1-3): ";
	int choice;
	cin >> choice;
	system("cls"); // Clear screen after choice

	if (choice == 1) { // Administrator Login
		cout << "---------------------------------------------------" << endl;
		cout << "||               Administrator Login             ||" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter Name: ";
		string name;
		cin >> name;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter CNIC: ";
		string snic;
		cin >> snic;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter Password: ";
		string password;
		cin >> password;
		cout << "---------------------------------------------------" << endl;
		system("cls"); // Clear login prompts

		admin a; // Default constructor
		a = checkAdmin(snic, password, "admin"); // Attempt login

		if (a.getCnic() == "") { // Login failed
			cout << "---------------------------------------------------" << endl;
			cout << "||                 LOGIN FAILED!                 ||" << endl;
			cout << "||     Invalid CNIC or Password for Admin.       ||" << endl;
			cout << "---------------------------------------------------" << endl;
			a.setLoginStatus(false);
			system("pause"); // Wait for user to acknowledge
			goto logIn; // Go back to main login screen
		}
		else { // Login successful
			a.setLoginStatus(true);
			// admin.isLogin() will print success, or we can print it here
			cout << "---------------------------------------------------" << endl;
			cout << "||          Admin Login Successful!              ||" << endl;
			cout << "||             Welcome, " << a.getName() << "!                 ||" << endl;
			cout << "---------------------------------------------------" << endl;
			system("pause");

			int adminChoice;
		adminPanel:
			system("cls");
			cout << "---------------------------------------------------" << endl;
			cout << "||              ADMINISTRATOR PANEL              ||" << endl;
			cout << "---------------------------------------------------" << endl;
			// The loop `while (adminChoice != 4)` seems to be an issue if 9 is the exit.
			// Kept as original to not change logic. Ideally, it should be `while(adminChoice != 9)`
			do {
				cout << "Please select an option:" << endl;
				cout << "  1. Add Voter" << endl;
				cout << "  2. Add Admin" << endl;
				cout << "  3. Add Candidate" << endl;
				cout << "  4. Create Election" << endl;
				cout << "  5. Show All Election Names" << endl;
				cout << "  6. Show Election Results" << endl;
				cout << "  7. Activate Election" << endl;
				cout << "  8. Deactivate Election" << endl;
				//cout << "9. Show All Candidates" << endl; // This was commented out
				cout << "  9. Logout and Return to Main Menu" << endl;
				cout << "---------------------------------------------------" << endl;
				cout << "Enter your choice (1-9): ";
				cin >> adminChoice;
				// system("cls"); // Clear menu before action (actions usually clear screen themselves)

				switch (adminChoice) {
				case 1:
					a.addVoter(); // This function should handle its own UI (cls, pause)
					//system("pause"); // Pause after action before returning to menu
					goto adminPanel;
					// break; // Unreachable due to goto
				case 2:
					a.addAdmin();
					//system("pause");
					goto adminPanel;
					// break; // Unreachable
				case 3:
					a.addCandidate();
					//system("pause");
					goto adminPanel;
					// break; // Unreachable
				case 4: {
					int id = electionIdGenerator();
					if (id != -1) {
						a.createElection(id);
						em.refreshAllData(); // Refresh data after new election
					}
					else {
						cout << "---------------------------------------------------" << endl;
						cout << "|| Error: Could not generate Election ID.        ||" << endl;
						cout << "---------------------------------------------------" << endl;
					}
					system("pause");
					goto adminPanel;
					// break; // Unreachable
				}
				case 5:
					system("cls");
					cout << "---------------------------------------------------" << endl;
					cout << "||          Displaying All Elections             ||" << endl;
					cout << "---------------------------------------------------" << endl;
					// em.displayAllElectionNames(); // This shows only active elections
					// The following calls show elections based on filter type 3 (all)
					// These functions (displayNationalElections etc.) handle their own system("cls")
					em.displayNationalElections(3); // Type 3: Show all (active & inactive)
					system("pause");
					em.displayLocalElections(3);
					system("pause");
					em.displayRegionalElections(3);
					system("pause");
					// em.displayAllElectionInDetails();
					// em.displayAllCandidates();
					// No goto here, loop will continue to display admin panel menu
					break;
				case 6:
					em.displayResults(); // Handles its own UI flow
					system("pause");
					break;
				case 7: // Activate Election
					em.actiDeactiElectionAdmin(true); // true for activate
					//em.refreshAllData(); // Refresh data after status change
					system("pause");
					break;
				case 8: // Deactivate Election
					em.actiDeactiElectionAdmin(false); // false for deactivate
					//em.refreshAllData(); // Refresh data after status change
					system("pause");
					break;
				case 9: // Exit Admin Panel
					a.setLoginStatus(false);
					system("cls");
					cout << "---------------------------------------------------" << endl;
					cout << "||           Admin Logged Out Successfully.      ||" << endl;
					cout << "---------------------------------------------------" << endl;
					system("pause");
					goto logIn; // Go back to main login screen
					// break; // Unreachable
				default:
					system("cls");
					cout << "---------------------------------------------------" << endl;
					cout << "|| Invalid choice. Please enter a number (1-9).||" << endl;
					cout << "---------------------------------------------------" << endl;
					system("pause");
					// No goto here, loop will continue to display admin panel menu
				}
			} while (adminChoice != 9); // Loop should ideally be controlled by choice 9
			// Original was `while (adminChoice != 4);`
			// Changed to 9 for logical exit from this menu.
			// If you want to keep original, note that gotos bypass this.
		}
	}
	else if (choice == 2) { // Voter Login
		cout << "---------------------------------------------------" << endl;
		cout << "||                  Voter Login                  ||" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter Name: ";
		string name;
		cin >> name;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter CNIC: ";
		string snic;
		cin >> snic;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter Password: ";
		string password;
		cin >> password;
		cout << "---------------------------------------------------" << endl;
		system("cls"); // Clear login prompts

		voter v(name, snic, password); // Create voter object (name is not used for login check here)
		v = checkVoter(snic, password, "voter"); // Attempt login

		if (v.getCnic() == "") { // Login failed
			cout << "---------------------------------------------------" << endl;
			cout << "||                 LOGIN FAILED!                 ||" << endl;
			cout << "||      Invalid CNIC or Password for Voter.      ||" << endl;
			cout << "---------------------------------------------------" << endl;
			v.setLoginStatus(false);
			system("pause");
			goto logIn; // Go back to main login screen
		}
		else { // Login successful
			v.setLoginStatus(true);
			cout << "---------------------------------------------------" << endl;
			cout << "||           Voter Login Successful!             ||" << endl;
			cout << "||             Welcome, " << v.getName() << "!                ||" << endl;
			cout << "---------------------------------------------------" << endl;
			system("pause");

			int voterChoice;
			em.setCurrentVoter(&v); // Set current voter in election manager
		voterPanel:
			system("cls");
			cout << "---------------------------------------------------" << endl;
			cout << "||                  VOTER PANEL                  ||" << endl;
			cout << "---------------------------------------------------" << endl;
			do {
				cout << "Please select an option:" << endl;
				cout << "  1. View Available Elections" << endl;
				cout << "  2. Cast Vote" << endl;
				cout << "  3. Check My Vote History" << endl;
				cout << "  4. Logout and Return to Main Menu" << endl;
				cout << "---------------------------------------------------" << endl;
				cout << "Enter your choice (1-4): ";
				cin >> voterChoice;
				// system("cls"); // Actions will clear screen if needed

				switch (voterChoice) {
				case 1:
					em.displayAllElectionNames(); // Shows only active elections by default
					system("pause");
					break;
				case 2:
					em.castVote();
					system("pause");
					break;
				case 3:
					em.checkVoteHistory();
					system("pause");
					break;
				case 4: // Exit Voter Panel
					v.setLoginStatus(false);
					em.setCurrentVoter(nullptr); // Clear current voter
					system("cls");
					cout << "---------------------------------------------------" << endl;
					cout << "||           Voter Logged Out Successfully.        ||" << endl;
					cout << "---------------------------------------------------" << endl;
					system("pause");
					goto logIn; // Go back to main login screen
					// break; // Unreachable
				default:
					system("cls");
					cout << "---------------------------------------------------" << endl;
					cout << "|| Invalid choice. Please enter a number (1-4).||" << endl;
					cout << "---------------------------------------------------" << endl;
					system("pause");
				}
			} while (voterChoice != 4); // Loop continues until user chooses to exit
		}
	}
	else if (choice == 3) { // Exit System
		system("cls");
		cout << "---------------------------------------------------" << endl;
		cout << "||         Thank you for using the Online        ||" << endl;
		cout << "||                  Voting System!               ||" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "||                 Exiting now...                ||" << endl;
		cout << "---------------------------------------------------" << endl;
		system("pause");
		return 0; // Exit the application
	}
	else { // Invalid role choice
		system("cls");
		cout << "---------------------------------------------------" << endl;
		cout << "|| Invalid role choice. Please try again.        ||" << endl;
		cout << "---------------------------------------------------" << endl;
		system("pause");
		goto logIn; // Go back to main login screen
	}

	return 0;
}

admin checkAdmin(string inputCnic, string inputPassword, string fileName) {
	ifstream userFile(fileName + ".txt");
	if (!userFile.is_open()) {
		// No system("cls") here, simple error message
		cout << "---------------------------------------------------" << endl;
		cerr << "Error: Could not open " << fileName << ".txt for authentication." << endl;
		cout << "---------------------------------------------------" << endl;
		return admin(); // Return default (empty) admin
	}
	string serchedName, serchedCnic, serchedPassword;
	while (getline(userFile, serchedName, '*')) {
		getline(userFile, serchedCnic, '*');
		getline(userFile, serchedPassword, '\n');
		if (serchedCnic == inputCnic && serchedPassword == inputPassword) {
			userFile.close();
			// Success message is handled by the main function for consistency
			admin temp(serchedName, serchedCnic, serchedPassword);
			// temp.setLoginStatus(true); // Login status set in main
			return temp;
		}
	}
	userFile.close();
	// Failure message is handled by the main function
	return admin(); // Return default (empty) admin if not found
}

voter checkVoter(string inputCnic, string inputPassword, string fileName) {
	ifstream userFile(fileName + ".txt");
	if (!userFile.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error: Could not open " << fileName << ".txt for authentication." << endl;
		cout << "---------------------------------------------------" << endl;
		return voter();
	}
	string serchedName, serchedCnic, serchedPassword;
	while (getline(userFile, serchedName, '*')) {
		getline(userFile, serchedCnic, '*');
		getline(userFile, serchedPassword, '\n');
		if (serchedCnic == inputCnic && serchedPassword == inputPassword) {
			userFile.close();
			voter temp(serchedName, serchedCnic, serchedPassword);
			// temp.setLoginStatus(true); // Login status set in main
			return temp;
		}
	}
	userFile.close();
	return voter();
}

int electionIdGenerator() {
	int electionId = 0; // Initialize to a default or error value
	ifstream fileIn("electionId.txt");
	if (!fileIn.is_open()) {
		// If file doesn't exist, maybe start IDs from 1 or a defined base
		// For now, treat as error or create the file with a starting ID.
		// Let's create it if it doesn't exist.
		ofstream createFile("electionId.txt");
		if (!createFile.is_open()) {
			cerr << "Critical Error: Could not create electionId.txt." << endl;
			return -1; // Critical failure
		}
		electionId = 0; // Start with ID 0, so first generated will be 1
		createFile << electionId << endl;
		createFile.close();
		// Now proceed to read and increment
	}
	else {
		fileIn >> electionId;
		fileIn.close();
	}

	ofstream fileOut("electionId.txt"); // Open in truncation mode to overwrite
	if (!fileOut.is_open()) {
		cout << "---------------------------------------------------" << endl;
		cerr << "Error: Could not open electionId.txt for writing." << endl;
		cout << "---------------------------------------------------" << endl;
		return -1; // Return error
	}
	electionId++; // Increment for the new election
	fileOut << electionId;
	fileOut.close();
	return electionId;
}