#include<iostream>
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
#include"admin.h"
#include<fstream>
#include<string>
#include "election.h"
#include "candidate.h"
#include "regionalElection.h"
#include "localElection.h"
#include "nationalElection.h"
#include "electionManger.h"

using namespace std;
admin checkAdmin(string , string , string );
voter checkVoter(string, string, string);
admin checkCandidate(string, string , string);



int main() {
	electionManger em;

	logIn:
	cout << "Welcome to Online Voting System" << endl;
	cout << "1. Admin" << endl;
	cout << "2. Voter" << endl;
	cout << "Enter your choice: ";
	int choice;
	cin >> choice;
	if (choice == 1) {
		cout << "Enter name: ";
		string name;
		cin >> name;
		cout << "Enter CNIC: ";
		string snic;
		cin >> snic;
		cout << "Enter password: ";
		string password;
		cin >> password;
		
		admin a;

		a = checkAdmin( snic, password,"admin");
		if (a.getCnic() == "") {
	
			a.setLoginStatus(false);
	
		}
		else a.setLoginStatus(true);
		if (a.getLoginStatus() == false) {
			// add what to do after failed login
			return 0;
		}
		else {




			int adminChoice;
			do {
				cout << "1. Add Voter" << endl;
				cout << "2. Add Admin" << endl;
				cout << "3. Add Candidate" << endl;
				cout << "4. Create Election" << endl;
				cout << "5. Show ALl Election Names" << endl;
				cout << "6. Exit" << endl;


				cout << "Enter your choice: ";
				cin >> adminChoice;
				switch (adminChoice) {
				case 1:
					a.addVoter();
					break;
				case 2:
					a.addAdmin();
					break;
				case 3:
					a.addCandidate();
					break;
				case 4:
					a.createElection();
					break;
				case 5 :
					//em.displayAllElectionNames();
					em.displayAllElectionInDetails();

					break;
				case 6:
					a.setLoginStatus(false);
					goto logIn;
					break;

				default:
					cout << "Invalid choice." << endl;
				}
			} while (adminChoice != 4);
		}
	}
	else if (choice == 2) {
		cout << "Enter name: ";
		string name;
		cin >> name;

		cout << "Enter CNIC: ";
		string snic;
		cin >> snic;
		cout << "Enter password: ";
		string password;
		cin >> password;
		voter v(name , snic, password);
		v = checkVoter(snic, password, "voter");
		if (v.getCnic() == "") {
			v.setLoginStatus(false);
		}
		else v.setLoginStatus(true);

		if (v.getLoginStatus() == true) {
			cout << "Welcome To Voter Panel" << endl;
			int voterChoice;
			do {
				cout << "1. View Elections" << endl;
				cout << "2. Cast Vote" << endl;
				cout << "3. Check Vote Status" << endl;
				cout << "4. Exit" << endl;
				cout << "Enter your choice: ";
				cin >> voterChoice;
				switch (voterChoice) {
				case 1:
					//v.viewElections();
					break;
				case 2:
					//v.castVote();
					break;
				case 3:
					//v.checkVoteStatus();
					break;
				case 4:
					v.setLoginStatus(false);
					goto logIn;
					break;

				default:
					cout << "Invalid choice." << endl;
				}
			} while (voterChoice != 4);
		}

	}
	else {
		cout << "Invalid choice." << endl;
	}

return 0;
}

admin checkAdmin(string inputCnic, string inputPassword, string fileName) {
	
		ifstream userFile(fileName + ".txt");
		if (!userFile.is_open()) {
			cerr << "Error opening file." << endl;
			return admin();
		}
		string serchedCnic;
		string serchedPassword;
		string serchedName;
		while (getline(userFile, serchedName, '*'))
		{
			getline(userFile, serchedCnic, '*');
			getline(userFile, serchedPassword, '\n');
			if (serchedCnic == inputCnic && serchedPassword == inputPassword) {
				userFile.close();
				cout << "Login successful." << endl;
				admin temp(serchedName, serchedCnic, serchedPassword);
				temp.setLoginStatus(true);	
				return temp;
			}
		}
		cout << "Login failed to " << fileName << ". Something MisMatched" << endl;
		userFile.close();
		return admin();
	
	
}
voter checkVoter(string inputCnic, string inputPassword, string fileName) {
	ifstream userFile(fileName + ".txt");
	if (!userFile.is_open()) {
		cerr << "Error opening file." << endl;
		return voter();
	}
	string serchedCnic;
	string serchedPassword;
	string serchedName;
	while (getline(userFile, serchedName, '*'))
	{
		getline(userFile, serchedCnic, '*');
		getline(userFile, serchedPassword, '\n');
		if (serchedCnic == inputCnic && serchedPassword == inputPassword) {
			userFile.close();
			cout << "Login successful." << endl;
			voter temp(serchedName, serchedCnic, serchedPassword);
			return temp;
		}
	}
	cout << "Login failed to " << fileName << ". Something MisMatched" << endl;

	userFile.close();
	return voter();
}