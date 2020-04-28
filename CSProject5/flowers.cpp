/* flowers.cpp : This file contains the 'main' function. Program execution begins and ends there.
	CS31Project5 flowers.cpp
	By Brandon Truong 11/15/19
*/

//bypass certain stack exceed error
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:6262)

#include "utilities.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <random>
#include <utility>
#include <cassert>
#include <cstring>
using namespace std;

//defined global constants
const int MAXWORDS = 10000;
const int MAXCHARLEN = 10000;

//Sets up directory for words
const char WORDFILENAME[] = ""; 

//declare functions for readability
int checkInput(char input[], const char words[][7], int nWords);
int flowersAndBees(const char words[][7], int wordnum, char input[]);
int playOneRound(const char words[][7], int nWords, int wordnum);

int main() {
	char wordList[MAXWORDS][MAXWORDLEN + 1];
	int nWords = getWords(wordList, MAXWORDS, WORDFILENAME); //initializes starting array and number of words in wordList
	cerr << nWords << endl;
	if (nWords < 1) {
		cout << "No words were loaded, so I can't play the game" << endl; //causes game to terminate immediately if getWords returns less than 1
		cerr << "Invalid directory to WORDFILENAME" << endl;
		exit(1);
	}
	//asks how many rounds to play and runs a for-loop for that amount of times
	int rounds;
	cout << "How many rounds do you want to play? ";
	cin >> rounds;
	cin.ignore(MAXCHARLEN, '\n');
	if (rounds < 0) {
		cout << "The number of rounds must be positive." << endl;
		exit(1); //terminates program if rounds is negative
	}
	//initializes score variables and mystery word
	char mysteryWord[MAXCHARLEN] = "";
	int sum=0, min=0, max = 0;
	double average = 0.00;
	for (int i = 0; i < rounds; i++) {
		int random = randInt(0, nWords-1);
		strcpy(mysteryWord, wordList[random]); //finds random integer and copies word from wordList to mysteryWord
		cerr << mysteryWord << " is the hidden word" << endl; 
		cout << "Round " << i+1 << "\n" << "The mystery word is " << strlen(mysteryWord) << " letters long." << endl;
		int tries = playOneRound(wordList, nWords, random); //goes through function and returns number of tries into variable
		cout << "You got it in " << tries;
		if (tries == 1) { //writes try if ==1, tries if not
			cout << " try." << endl;
		}
		else {
			cout << " tries." << endl;
		}
		if (i == 0) { //sets min to the first round's amount of tries at the start of loop only
			min = tries;
		}
		sum += tries; //calculates score variables
		if (tries > max) {
			max = tries;
		}
		if (tries < min) {
			min = tries;
		}
		cout.setf(ios::fixed);
		cout.precision(2); //shows only 2 decimal digits in doubles
		average = sum / (i + 1.00);
		cout << "Average: " << average << ", minimum: " << min << ", maximum: " << max << "\n" << endl;
	}

}
int checkInput(char input[], const char words[][7], int nWords) {
	int length = strlen(input);
	if (length > MAXWORDLEN || length < MINWORDLEN) { //checks if input is of valid length
		cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
		cerr << "Invalid length" << endl;
		return 1;
	}
	for (int i = 0; i < length; i++) { //checks if input contains only lowercase letters
		if (!islower(input[i])) {
			cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
			cerr << "Only lowercase letters are allowed" << endl;
			return 1;
		}
	}
	bool checkWordList = false; //checks if word is in wordList
	for (int i = 0; i < nWords; i++) {
		if (strcmp(input, words[i]) == 0) { //use strcmp to compare c strings of wordList and user input
			checkWordList = true;
		}
	}
	if (!checkWordList) {
	cout << "I don't know that word." << endl;
	cerr << "Not in wordList" << endl;
	return 1;
	}
	return 0; //returns 1 if fails any conditions, 0 if passes all 
}
int flowersAndBees(const char words[][7], int wordnum, char input[]) {
	if (strcmp(input, words[wordnum]) == 0) { //returns 0 if matching word
		return 0;
	}
	int flowers = 0;
	int bees = 0;
	for (int i = 0; i < (int)strlen(words[wordnum]); i++) {
		if (input[i] == words[wordnum][i]) { //checks to see if flower at i
				flowers++;
				input[i] = ' '; 
		}
		else {
			for (int j = 0; j < (int) strlen(input); j++) {
				if (input[j] == words[wordnum][i]) { //breaks from loop if any character in input is a bee for the character in words[wordnum][i], assuming no flowers
					bees++;
					input[j] = ' '; //makes sure that character in input will never be a bee or flower for more than one character
					break;
				}
			}
		}
	}
	cout << "Flowers: " << flowers << ", Bees: " << bees << endl; //prints out amount of flowers and bees, then returns 1 if input!=word
	return 1;
}
int playOneRound(const char words[][7], int nWords, int wordnum) {
	if (nWords < 0 || wordnum < 0 || wordnum >= nWords) {
		return -1; //fails if conditions fail, should never return -1 if run from main
	}
	int numberOfRounds = 1;
	bool repeatLoop = true;
	while (repeatLoop) { //repeats loop until checkWord returns 0, thus meaning input matches mysteryWord
		char input[MAXCHARLEN] = "";
		cout << "Trial word: ";
		cin >> input;
		cin.ignore(MAXCHARLEN, '\n');
		int checkConditions = checkInput(input, words, nWords); //checks conditions and runs if statement if all conditions passed, otherwise numberOfRounds is incremented by 1
		if (checkConditions == 0) {
			int checkWord = flowersAndBees(words, wordnum, input);
			if (checkWord == 0) {
				repeatLoop = false; //stops loop if input matches with given word
			}
			else {
				numberOfRounds++;
			}
		}
		else {
			numberOfRounds++;
		}
	}
	return numberOfRounds;
}

