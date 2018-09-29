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

// Header
#include "functions.h"

// Declaring Variables
int index = -1;
int selection;

//=============================================================================================//

// Main Menu
void menu(std::vector<Account> &Accounts) {

	Sleep(1000);

	std::cout
		<< "\n ============================================\n      ~~ Rutgers U. Banking Systems. ~~\n ============================================\n"
		<< " Welcome! Select Options Below:\n\n"
		<< "   1. Make new account.\n"
		<< "   2. Deposit to an account.\n"
		<< "   3. Withdraw from an account.\n"
		<< "   4. Transfer Money from one account to another.\n"
		<< "   5. Display an account.\n"
		<< "   6. Activate/Deactivate an account.\n"
		<< "   7. Delete an account.\n"
		<< "   8. Display all accounts.\n"
		<< "   9. Quit.\n\n"
		<< " Selection: ";

	// Recives input and checks if valid number from 1-9.
	do {
		std::cin >> selection;

		if (selection < 1 || selection > 9 || typeid(selection) != typeid(int)) {
			std::cout << " /!\\ ERROR! Invalid number. Must select a number from 1-9! /!\\ \n\n";
			std::cout << " Selection: ";
			std::cin.clear();
			std::cin.ignore();
		}
	} while (selection < 1 || selection > 9);

	switch (selection) {
	case 1: makeAccount(Accounts);
		break;
	case 2: depositAccount(Accounts);
		break;
	case 3: withdrawAccount(Accounts);
		break;
	case 4: Transfer(Accounts);
		break;
	case 5: printAccount(Accounts);
		break;
	case 6: ActiveDeactive(Accounts);
		break;
	case 7: deleteAccount(Accounts);
		break;
	case 8: printAllAccounts(Accounts);
		break;
	case 9: quit();
		break;
	}
}

//=============================================================================================//

// 1. Account Creation
void makeAccount(std::vector<Account> &Accounts) {

	// Defining variables.
	double accountBalance;
	int i = 0; int j = 0;

	// Increments index.
	++index;

	// Resizes vector.
	Accounts.resize(index + 1);

	// Better than using rand() and srand(). This yields more varied random results.
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1000, 9999);

	// Creates random 4 digit bank account number (and makes sure there are no duplicates).
	do {

		Accounts[index].accountNumber = dis(gen);

		for (i; i <= (index + 1); i++) {

			if (i == (index + 1)) {
				j = 1;
				break;
			}

			if (i <= index && (i != index)) {
				if (Accounts[index].accountNumber == Accounts[i].accountNumber) {
					break;
				}
			}
		}

	} while (j == 0);

	std::cout << "\n Creating Bank Account: #" << Accounts[index].accountNumber << std::endl;

	// Requests & recieves first name (can be anything except being empty).
	std::cout << " Enter First Name: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
		std::getline(std::cin, Accounts[index].firstName);

		if (Accounts[index].firstName.empty()) {
			std::cout << " /!\\ ERROR! Invalid name. Please try again! /!\\ \n\n";
			std::cout << " Enter First Name: ";
		}
	} while (Accounts[index].firstName.empty());

	// Requests & recieves last name (can be anything except being empty).
	std::cout << " Enter Last Name: ";
	do {
		std::getline(std::cin, Accounts[index].lastName);

		if (Accounts[index].lastName.empty()) {
			std::cout << " /!\\ ERROR! Invalid name. Please try again! /!\\ \n\n";
			std::cout << " Enter Last Name: ";
		}
	} while (Accounts[index].lastName.empty());

	// Requests & recieves starting balance.
	std::cout << " Enter Initial Balance: $";
	std::cin >> accountBalance;
	validInput(accountBalance);
	Accounts[index].accountBalance = accountBalance;

	// Automatically sets "Active" (with aesthetic loading time).
	std::cout << "\n Activating Account ";
	Sleep(1000);
	std::cout << ". ";
	Sleep(1000);
	std::cout << ". ";
	Sleep(1000);
	std::cout << ". ";
	Sleep(1000);
	std::cout << "\n Success! This account has now been activated!\n\n";
	Accounts[index].active = 1;
}

// 2. Deposit to an Account
void depositAccount(std::vector<Account> &Accounts) {

	// Defining variables.
	int accountNumber;
	double depositAmount;
	int i = 0; int j = 0;

	// Make sure there is at least one account in the system.
	if (index < 0) {
		std::cout << "\n /!\\ There are currently no accounts yet. Please create an account before attempting to use this option. /!\\\n";
		return;
	}

	// Requests & recieves account number.
	std::cout << "\n Enter account number for deposit: #";
	std::cin >> accountNumber;
	validInput(accountNumber, i, j, Accounts);

	// If account DNE or is Inactive, user is returned to menu.
	if (j == 1) {
		return;
	}

	// Requests & recieves deposit amount.
	std::cout << " Enter amount to be deposited: $";
	std::cin >> depositAmount;
	validInput(depositAmount);

	// Adds to account balance.
	Accounts[i].accountBalance += depositAmount;

	std::cout << "\n Deposit Successful!\n New Balance: $" << std::setprecision(2) << std::fixed << Accounts[i].accountBalance << std::endl;
}

// 3. Withdraw from an Account
void withdrawAccount(std::vector<Account> &Accounts) {

	// Defining variables
	int accountNumber;
	double withdrawAmount;
	int i = 0; int j = 0;

	// Make sure there is at least one account in the system
	if (index < 0) {
		std::cout << "\n /!\\ There are currently no accounts yet. Please create an account before attempting to use this option. /!\\\n";
		return;
	}

	// Requests & recieves account number
	std::cout << "\n Enter account number for withdrawl: #";
	std::cin >> accountNumber;
	validInput(accountNumber, i, j, Accounts);

	// If account DNE or is Inactive, user is returned to menu.
	if (j == 1) {
		return;
	}

	// Requests & recieves withdrawl amount.
	std::cout << " Enter amount to be withdrawn: $";
	std::cin >> withdrawAmount;
	validInput(withdrawAmount);

	// Subtracts from account balance.
	Accounts[i].accountBalance -= withdrawAmount;

	std::cout << "\n Withdraw Successful!\n New Balance: $" << std::setprecision(2) << std::fixed << Accounts[i].accountBalance << std::endl;
}

// 4. Transfer from one Account to another Account
void Transfer(std::vector<Account> &Accounts) {

	int accountNumber; int accountNumber2;
	double transferAmount;
	int i = 0; int j = 0; int k = 0; int l = 0;

	// Make sure there is at least two accounts in the system
	if (index < 1) {
		std::cout << "\n /!\\ There are currently less than two accounts. Please create more accounts before attempting to use this option. /!\\\n";
		return;
	}

	// Requests & recieves account number
	std::cout << "\n Enter account number of sender: #";
	std::cin >> accountNumber;
	validInput(accountNumber, i, j, Accounts);

	// If account DNE or is Inactive, user is returned to menu.
	if (j == 1) {
		return;
	}

	// Requests & recieves account number
	std::cout << " Enter account number for reciever: #";
	std::cin >> accountNumber2;
	validInput(accountNumber2, k, j, Accounts);

	// If account DNE or is Inactive, user is returned to menu.
	if (j == 1) {
		return;
	}

	// Requests & recieves transfer amount.
	std::cout << "\n Enter amount to be transferred: $";
	std::cin >> transferAmount;
	validInput(transferAmount);

	// Subtracts from sender balance.
	Accounts[i].accountBalance -= transferAmount;

	// Adds to reciever balance.
	Accounts[k].accountBalance += transferAmount;

	std::cout
		<< "\n Transfer Successful!\n Sender's New Balance: $" << std::setprecision(2) << std::fixed << Accounts[i].accountBalance << std::endl
		<< " Reciever's New Balance: $" << std::setprecision(2) << std::fixed << Accounts[k].accountBalance << std::endl;

}

// 5. Display an Account
void printAccount(std::vector<Account> &Accounts) {

	// Defining variables
	int accountNumber;
	int i = 0; int j = 0;

	// Make sure there is at least one account in the system
	if (index < 0) {
		std::cout << "\n /!\\ There are currently no accounts yet. Please create an account before attempting to use this option. /!\\\n";
		return;
	}

	// Requests & recieves account number
	std::cout << "\n Enter account number to display: #";
	std::cin >> accountNumber;
	validInput(accountNumber, i, j, Accounts);

	// Prints selected account (note: does not matter if active or not)
	std::cout
		<< "\n Account Number: #" << std::left << std::setw(9) << std::setfill(' ')
		<< Accounts[i].accountNumber << "Account Balance: $" << std::setprecision(2) << std::fixed << Accounts[i].accountBalance << std::endl

		<< " Last Name: " << std::left << std::setw(15) << std::setfill(' ')
		<< Accounts[i].lastName << "First Name: " << Accounts[i].firstName << "\n\n";

}

// 6. Activate / Deactivate an Account
void ActiveDeactive(std::vector<Account> &Accounts) {

	// Defining variables
	int accountNumber;
	bool active;
	int i = 0; int j = 0;

	// Make sure there is at least one account in the system
	if (index < 0) {
		std::cout << "\n /!\\ There are currently no accounts yet. Please create an account before attempting to use this option. /!\\\n";
		return;
	}

	// Requests & recieves account number
	std::cout << "\n Enter account number for activation/deactivation: #";
	std::cin >> accountNumber;
	validInput(accountNumber, i, j, Accounts);

	// If account DNE or is Inactive, user is returned to menu.
	if (j == 1) {
		return;
	}

	// Requests & recieves input
	std::cout << "\n 0. Deactivate\n" << " 1. Activate\n\n" << " Selection: ";
	std::cin >> active;
	validInput(active);

	// Activates or deactivates account depending on user input.
	Accounts[i].active = active;

	if (active == 0)
		std::cout << "\n Deactivation Successful!\n";

	else if (active == 1)
		std::cout << "\n Activation Successful!\n";

}

// 7. Delete an Account
void deleteAccount(std::vector<Account> &Accounts) {

	// Defining variables
	int accountNumber;
	int i = 0; int j = 0;

	// Make sure there is at least one account in the system
	if (index < 0) {
		std::cout << "\n /!\\ There are currently no accounts yet. Please create an account before attempting to use this option. /!\\\n";
		return;
	}

	// Requests & recieves account number
	std::cout << "\n Enter account number for deletion: #";
	std::cin >> accountNumber;
	validInput(accountNumber, i, j, Accounts);

	// If account DNE or is Inactive, user is returned to menu.
	if (j == 1) {
		return;
	}

	// Deletes account by pushing all accounts in front of it backwards to fill in the gap.
	for (i += 1; i <= index; i++) {
		Accounts[i - 1].accountNumber = Accounts[i].accountNumber;
		Accounts[i - 1].firstName = Accounts[i].firstName;
		Accounts[i - 1].lastName = Accounts[i].lastName;
		Accounts[i - 1].accountBalance = Accounts[i].accountBalance;
		Accounts[i - 1].active = Accounts[i].active;
	}

	index--;

	std::cout << "\n Account has been sucessfully deleted.\n";
}

// 8. Print All Accounts
void printAllAccounts(std::vector<Account> &Accounts) {

	// Make sure there is at least one account in the system
	if (index < 0) {
		std::cout << "\n /!\\ There are currently no accounts yet. Please create an account before attempting to use this option. /!\\\n";
		return;
	}

	std::cout << "\n ============================================\n     ~~ Displaying All Active Accounts ~~\n ============================================\n";

	for (int i = 0; i <= index; i++) {

		if (Accounts[i].active == 1) {
			std::cout

				<< "\n Account Number: #" << std::left << std::setw(9) << std::setfill(' ')
				<< Accounts[i].accountNumber << "Account Balance: $" << std::setprecision(2) << std::fixed << Accounts[i].accountBalance << std::endl

				<< " Last Name: " << std::left << std::setw(15) << std::setfill(' ')
				<< Accounts[i].lastName << "First Name: " << Accounts[i].firstName << "\n\n";
		}
	}

	std::cout << "\n ============================================\n    ~~ Displaying All Inactive Accounts ~~\n ============================================\n";

	for (int i = 0; i <= index; i++) {

		if (Accounts[i].active == 0) {
			std::cout

				<< "\n Account Number: #" << std::left << std::setw(9) << std::setfill(' ')
				<< Accounts[i].accountNumber << "Account Balance: $" << std::setprecision(2) << std::fixed << Accounts[i].accountBalance << std::endl

				<< " Last Name: " << std::left << std::setw(15) << std::setfill(' ')
				<< Accounts[i].lastName << "First Name: " << Accounts[i].firstName << "\n\n";
		}
	}

}

// 9. Quitting Sequence
void quit() {

	// Purely for aesthetic purposes only. No functionality here.
	std::cout << "\n Bank will now close!\n Unfortunately, due to the simplicity of this program, ALL data will now be deleted!\n\n";
	Sleep(1000);
	std::cout << " || Daniel Nguyen 173005214\n || Programming Methodology I -- Professor Yangyong Zhang\n || Copyright (c) 2018\n\n";
	Sleep(1000);
	std::cout << " Systems shutting down ";
	Sleep(1000);
	std::cout << ". ";
	Sleep(1000);
	std::cout << ". ";
	Sleep(1000);
	std::cout << ". ";
	Sleep(1000);

}

//=============================================================================================//

// Sorting Accounts (by Account Number)
void sortAccounts(std::vector<Account> &Accounts) {
	int n, k, sm_index, smallest = 0;

	// Checks for smallest account number in vector
	for (k = 0; k <= index; k++) {
		smallest = Accounts[k].accountNumber;
		sm_index = k;

		for (n = k + 1; n <= index; n++) {
			if (Accounts[n].accountNumber < smallest) {
				smallest = Accounts[n].accountNumber;
				smallest = n;

				// Swaps accounts
				int temp1;
				std::string temp2; std::string temp3;
				double temp4;
				bool temp5;

				temp1 = Accounts[sm_index].accountNumber;
				temp2 = Accounts[sm_index].firstName;
				temp3 = Accounts[sm_index].lastName;
				temp4 = Accounts[sm_index].accountBalance;
				temp5 = Accounts[sm_index].active;

				Accounts[sm_index].accountNumber = Accounts[smallest].accountNumber;
				Accounts[sm_index].firstName = Accounts[smallest].firstName;
				Accounts[sm_index].lastName = Accounts[smallest].lastName;
				Accounts[sm_index].accountBalance = Accounts[smallest].accountBalance;
				Accounts[sm_index].active = Accounts[smallest].active;

				Accounts[smallest].accountNumber = temp1;
				Accounts[smallest].firstName = temp2;
				Accounts[smallest].lastName = temp3;
				Accounts[smallest].accountBalance = temp4;
				Accounts[smallest].active = temp5;
			}
		}
	}

}

// validInput (w/ function overloading for different types)
void validInput(bool &active) {

	while (active < 0 || active > 1){

			std::cout << " /!\\ ERROR! Input must be 0 or 1. Please try again! /!\\ \n\n" << " Selection: ";

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> active;
	}

}
void validInput(int &accountNumber, int &i, int &j, std::vector<Account> &Accounts) {

	if (accountNumber < 1000 || accountNumber > 9999 || typeid(accountNumber) != typeid(int)){
		std::cout <<  "/!\\ ERROR! Invalid value. Must be a positive 4 digit number. / !\\ \n\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		j = 1;
		return;
	}

	for (i; i <= (index + 1); i++) {

		if (i == (index + 1)) {
			std::cout << " /!\\ ERROR! Account not found. /!\\ \n\n";
			j = 1;
			return;
		}

		if (i <= index) {
			if (Accounts[i].accountNumber == accountNumber && Accounts[i].active == 0) {
				std::cout << " /!\\ This account is INACTIVE! You can activate it by selecting option 6. /!\\ \n\n";
				j = 1;
				return;
			}
		}

		if (i <= index) {
			if (Accounts[i].accountNumber == accountNumber && Accounts[i].active == 1) {
				j = 0;
				break;
			}
		}
	}
}
void validInput(double &amount) {

	while (amount < 0 || (typeid(amount) != typeid(double))){

			std::cout << " /!\\ ERROR! Invalid value. Must be a positive number. /!\\ \n\n" << " Enter amount: $";

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> amount;
	} 
}

//=============================================================================================//