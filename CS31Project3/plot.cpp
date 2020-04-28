/* plots.cpp : This file contains the 'main' function. Program execution begins and ends there.
CSProject3 plots.cpp
By Brandon Truong 10/26/19
*/

#include <iostream>
#include <string>
#include <cctype>
#include "grid.h"
#include  <cassert>
using namespace std;

//function declaration
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg);
int performCommands(string commandString, char& plotChar, int& mode, int& badPos);
//functions used in other commands
void endpoints(int& r, int& c, int distance, int dir);
int convertToInt(string s);
//defines global constant values
const int HORIZ = 0;
const int VERT = 1;
const int FG = 0;
const int BG = 1;

int main() {
	setSize(20, 30); //sets grid borders
	char currentChar = '*';
	int currentMode = FG;
	for (;;) {
		cout << "Enter a command string: ";
		string cmd;
		getline(cin, cmd);
		if (cmd == "")
			break;
		int position;
		int status = performCommands(cmd, currentChar, currentMode, position);
		switch (status) {
		case 0:
			draw();
			break;
		case 1:
			cout << "Syntax error at position " << position + 1 << endl;
			break;
		case 2:
			cout << "Cannot perform command at position " << position + 1 << endl;
			break;
		default:
			// It should be impossible to get here.
			cerr << "performCommands returned " << status << "!" << endl;
		}
	}
}
//implementation of plotLine
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg) {
	int r2 = r;	//defines the other endpoint of the line segment
	int c2 = c;
	endpoints(r2, c2, distance, dir);
	//tests for conditions
	bool fgbgIsValid = true;
	if (fgbg != BG && fgbg != FG) {
		fgbgIsValid = false;
		cerr << "Invalid fgbg value: neither 1 nor 0"<< endl;
	}
	bool dirIsValid = true;
	if (dir != VERT && dir != HORIZ) {
		dirIsValid = false;
		cerr << "Invalid dir value: neither 1 nor 0" << endl;
	}
	bool charIsValid = true;
	if (!isprint(plotChar)) {
		charIsValid = false;
		cerr << "Invalid char: nonprintable character" << endl;
	}
	bool lineIsValid = true;
	if (r < 1 || r > 20 || r2 < 1 || r2 > 20) {
		lineIsValid = false;
		cerr << "Invalid line: points are outside grid" << endl;
	}
	if (c < 1 || c > 30 || c2 < 1 || c2 > 30) {
		lineIsValid = false;
		cerr << "Invalid line: points are outside grid" << endl;
	}
	if (!(fgbgIsValid && dirIsValid && charIsValid && lineIsValid)) {
		return false;	//Does not succeed if not all conditions are valid, stops at this line
	}
	//set characters of the line
	if (distance >= 0) {
		for (int i = r; i <= r2; i++) {
			for (int j = c; j <= c2; j++) {
				if (fgbg == FG) {
					setChar(i, j, plotChar); //plots in the FG
				}
				else {
					if (getChar(i, j) == ' ') {
						setChar(i, j, plotChar); //plots in the BG and only if FG is a space char
					}
				}
			}
		}
	}
	else {
		for (int i = r2; i <= r; i++) {
			for (int j = c2; j <= c; j++) {
				if (fgbg == FG) {
					setChar(i, j, plotChar);
				}
				else {
					if (getChar(i, j) == ' ') {
						setChar(i, j, plotChar);
					}
				}
			}
		}
	}
	return true;
}
//implementation of performCommands
int performCommands(string commandString, char& plotChar, int& mode, int& badPos) {
	int r = 1;
	int c = 1;
	for (int j = 0; j < commandString.size(); j++) { //checks through entire length of string for errors
		char checkedPos = toupper(commandString[j]);
		if (checkedPos == 'F' || checkedPos == 'B') {
			j++;
			if (!isprint(commandString[j])) { //checks if character is printable
				badPos = j;
				cerr << "Invalid character";
				return 1;
			}
		}
		else if (checkedPos == 'V' || checkedPos == 'H') {
			int start = ++j;
			int len = 0;
			if (commandString[start] != '-' && !(isdigit(commandString[start]))) { //checks if initial character after is digit or - sign
				badPos = start;
				cerr << "Expected digit or minus sign at " << badPos << endl;
				return 1;
			}
			if (commandString[start] == '-') {
				j++; //if - sign, moves to next character
			}
			while (isdigit(commandString[j]) && len < 2) { //creates substring of digits, up to 2 digits
				len++;
				j++;
			}
			string VHInteger = commandString.substr(start, j - start);
			int distance = convertToInt(VHInteger); //converts string to integer
			int dir = 0;
			if (checkedPos == 'V') {
				dir = 1;
			}
			endpoints(r, c, distance, dir);
			if (r < 1 || r > 20 || c < 1 || c > 30) {
				cerr << "Invalid line: points are outside grid" << endl;
				badPos = start - 1;
				return 2;
			}
			j--;
		}
		else if (checkedPos == 'C') {
			; //only checks if char at j is 'C'
		}
		else {
			badPos = j;
			cerr << "Invalid command start" << endl;
			return 1;
		}
	}
	r = 1;
	c = 1;
	for (int i = 0; i < commandString.size(); i++) {
		char currentPos = toupper(commandString[i]);
		if (currentPos == 'F') {
			i++;
			mode = FG;
			plotChar = commandString[i];
		}
		else if(currentPos == 'B') {
			i++;
			mode = BG;
			plotChar = commandString[i];
		}
		else if (currentPos == 'V' || currentPos == 'H') {
			int dir = 0;
			if (currentPos == 'V') {
				dir = 1;
			}
			int start = ++i;
			int len = 0;
			if (commandString[start] == '-') {
				i++; //if - sign, moves to next character
			}
			while (isdigit(commandString[i]) && len < 2) { //creates substring of digits, up to 2 digits
				len++;
				i++;
			}
			string VHInteger = commandString.substr(start, i - start);
			int distance = convertToInt(VHInteger); //converts string to integer
			plotLine(r, c, distance, dir, plotChar, mode);
			endpoints(r, c, distance, dir);
			i--;
		}
		else if (currentPos == 'C') {
			clearGrid();
			mode = FG;
			plotChar = '*';
		}
	}	
	return 0;
}
int convertToInt(string s) { //assumes string includes only integers and optional - sign in front
	int value = 0;
	for (int i = 0; i < s.size(); i++) {
		value *= 10;
		if (isdigit(s[i])) {
			value += s[i] - '0';
		}
	}
	if (s[0] == '-') {
		value *= -1;
	}
	return value; //loops through string and converts char to int, then returns
}
void endpoints(int& r, int& c, int distance, int dir) {
	if (dir == HORIZ) {
		c += distance;
	}
	else if (dir == VERT) {
		r += distance;
	}
}
