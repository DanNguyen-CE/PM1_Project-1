/*************************************************************************
//																		//
//	Programming Methodology I (14:332:252)								//
//	PROJECT 1 -- "Banking System"										//
//																		//
//	Daniel Nguyen														//
//	Section 1															//
//	March 2018															//
//																		//
*************************************************************************/

// Headers & Libraries
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <iomanip>
#include <typeinfo>
#include <limits>
#include <random>
#undef max

// Declaring Externally Shared Variable
extern int selection;

// Creating Structure
struct Account {
	int accountNumber;
	std::string firstName;
	std::string lastName;
	double accountBalance;
	bool active;
};

// Function Prototypes

void menu(std::vector<Account> &Accounts);

void makeAccount(std::vector<Account> &Accounts);
void depositAccount(std::vector<Account> &Accounts);
void withdrawAccount(std::vector<Account> &Accounts);
void Transfer(std::vector<Account> &Accounts);
void printAccount(std::vector<Account> &Accounts);
void ActiveDeactive(std::vector<Account> &Accounts);
void deleteAccount(std::vector<Account> &Accounts);
void printAllAccounts(std::vector<Account> &Accounts);
void quit();

void sortAccounts(std::vector<Account> &Accounts);
void validInput(bool&);
void validInput(int&, int&, int&, std::vector<Account> &Accounts);
void validInput(double&);