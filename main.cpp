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

// Main Function
int main() {

	// Creating Vector
	std::vector <Account> bankAccounts;

	// Main Program Loop (indefinitely until user quits program)
	while (selection != 9) {
		menu(bankAccounts); // Calls Menu Function
		sortAccounts(bankAccounts); // Sorts accounts every loop iteration
	}

	return 0;
}