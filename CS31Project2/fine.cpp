/* fine.cpp : This file contains the 'main' function. Program execution begins and ends there.
CS31 Project 2 by Brandon Truong
10/12/19

*/

#include <iostream> //includes source file
#include <string> //allows the usage of string
using namespace std; //provides scope to identifiers

int main() {

	//takes inputt for defendant

	cout << "Defendant: ";
	string name;
	getline(cin, name); //input is declared in name variable
	if (name == "") {
		cout << "---\nYou must enter a defendant name." << endl; //if the string is empty, then the code outputs this line
		return 1; //ends the main function if inputs are invalid
	}

	//takes input for amount paid

	cout << "Amount paid (in thousands): ";
	int amt;
	cin >> amt;
	cin.ignore(1000, '\n'); //clears cin stream so that line 29 getline() is unaffected
	if (amt < 0) {
		cout << "---\nThe amount paid must not be negative." << endl; //outputs message if amount paid is negative
		return 1;
	}

	//asks if there were fake athlete credentials

	cout << "Fake athlete? (y/n): ";
	string fake;
	bool fakeAthlete;
	getline(cin, fake);
	if (fake == "y") { //outputs true if the string given is "y", false if "n", and the error message if anything else
		fakeAthlete = true;
	} else if (fake == "n") {
		fakeAthlete = false;
	} else {
		cout << "---\nYou must enter y or n." << endl;
		return 1;
	}

	//calculates fine and outputs if valid

	double fine = 20.0; //base amount for fine
	if (amt > 250) { //runs if amount paid is more than 250
		fine += (amt - 250.0) * .14; //calculates amount above 250 thousand
		amt = 250;
	}
	if (amt > 40) { //calculates amount more than initial 40 thousand and not above 250 total
		if (fakeAthlete) { //runs if bool fakeAthlete is true, else other statement goes through
			fine += (amt - 40.0) * .22; //converts amt from int to double, then finds the resulting fine afterwards
		}
		else {
			fine += (amt - 40.0) * .10;
		}
		amt = 40;
	}
	fine += .66 * amt; //calculates first 40 thousand paid to Stinger
	cout.setf(ios::fixed); //fixes the double output
	cout.precision(1); //makes the output to 1 decimal point
	cout << "---\nThe suggested fine for " << name << " is $" << fine << " thousand." << endl; //outputs message with suggested fine if all inputs are valid
}