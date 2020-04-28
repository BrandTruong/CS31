/* array.cpp : This file contains the 'main' function. Program execution begins and ends there.
CSProject4 arrays.cpp
By Brandon Truong 11/05/19
*/

//declaration of libraries and standard namespace
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//declares all necessary functions
int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);

int main()
{
	string h[7] = { "mick", "marie", "fiona", "rudy", "", "gordon", "lindsey" };
	assert(lookup(h, 7, "gordon") == 5);
	assert(lookup(h, 7, "fiona") == 2);
	assert(lookup(h, 2, "fiona") == -1);
	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "mick", "marie", "lindsey", "nancy" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "mick?" && g[3] == "nancy?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "lindsey?" && g[3] == "marie?");

	string e[4] = { "fiona", "rudy", "", "gordon" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "marie", "marie", "marie", "rudy", "rudy" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "lindsey", "fiona", "mike" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "lindsey");

	assert(separate(h, 7, "lindsey") == 3);

	cout << "All tests succeeded" << endl;
}
int appendToAll(string a[], int n, string value) {
	//tests if n is negative and returns if true
	if (n < 0) {
		return -1;
	}
	//loops through string and adds value to end
	for (int i = 0; i < n; i++) {
		a[i] += value;
	}
	return n;
}
int lookup(const string a[], int n, string target) {
	//loops through string and uses equality operator to check
	for (int i = 0; i < n ; i++) {
		if (a[i] == target) {
			return i;
		}
		else {
			continue; //very unnecessary but oh well lmao
		}
	}
	return -1;
}
int positionOfMax(const string a[], int n) {
	//checks to see if n is negative
	if (n < 0) {
		return -1;
	}
	//uses comparison operators alongside a for loop to find the max string
	int max = 0;
	string maxString = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] > maxString) {
			//replaces value if greater than previous value of maxString
			max = i;
			maxString = a[i];
		}
	}
	return max;
}
int rotateLeft(string a[], int n, int pos) {
	string original = a[pos]; //holds onto the original value before everything is shifted
	for (int i = pos; i < n - 1; i++) {
		a[i] = a[i + 1]; //replaces current element with the element after
	}
	a[n-1] = original; //replaces last element with the one at pos
	return pos;
}
int countRuns(const string a[], int n) {
	//counts elements by comparing with the one before, starting at 1 for element at a[0]
	int count = 1;
	for (int i = 1; i < n; i++) {
		if (a[i] != a[i - 1]) {
			count++;
		}
	}
	return count;
}
int flip(string a[], int n) {
	string orig = "";
	for (int i = 0; i < n/2; i++) {
		//flips the array by replacing half of the array, ie. first replaced with the last, second with second last, etc
		orig = a[i];
		a[i] = a[n - 1 - i];
		a[n - 1 - i] = orig;
	}
	return n;
}
int differ(const string a1[], int n1, const string a2[], int n2) {
	//finds which number n1 or n2 is lower and set the number of times looped to lowestNum
	int lowestNum = 0;
	if (n1 <= n2) {
		lowestNum = n1;
	}
	else {
		lowestNum = n2;
	}
	for (int i = 0; i < lowestNum; i++) {
		if (a1[i] != a2[i]) {
			return i; //finds first value not equal to each other if exists
		}
	}
	return lowestNum;
}
int subsequence(const string a1[], int n1, const string a2[], int n2) {
	int startPoint = -1;
	bool repeatLoop = true;
	bool satisfiesSubsequence = true;
	while (repeatLoop) {
		repeatLoop = false;
		for (int i = startPoint + 1; i < n1; i++) {
			if (a1[i] == a2[0]) {
				startPoint = i; //finds the position of an element in a1 that is equal to a2[0], repeating if the first position does not satisfy
				repeatLoop = true;
				break;
			}
		}
		satisfiesSubsequence = true;
		for (int j = startPoint; j < startPoint + n2; j++) {
			if (a1[j] != a2[j - startPoint]) {
				satisfiesSubsequence=false; //tests to see if the elements are the same afterwards by going through a loop of however many elements are in a2
				break;
			}
		}
	}
	if (satisfiesSubsequence) {
		return startPoint;
	}
	else {
		return -1;
	}
}
int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	//goes through nested loop to test if a1 contains any elements in a2
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			if (a1[i] == a2[j]) {
				return i;
			}
		}
	}
	return -1;
}
int separate(string a[], int n, string separator) {
	//sets the array to alphabetical order cause separating by separator takes more effort and achieves the same idea or less than at front
	string alphabetical = "";
	int positionOfAlpha = 0;
	for (int i = 0; i < n; i++) {
		alphabetical = a[i];
		positionOfAlpha = i;
		for (int j = i+1; j < n; j++) {
			if (a[j] < alphabetical) {
				alphabetical = a[j];
				positionOfAlpha = j;
			}
		}
		a[positionOfAlpha] = a[i];
		a[i] = alphabetical;
	}
	//finds first value where element of array is greater than separator
	for (int k = 0; k < n; k++) {
		if (a[k] >= separator) {
			return k;
		}
	}
	return n;
}