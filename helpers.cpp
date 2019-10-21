#include <iostream>
#include <algorithm> 

#include "helpers.h"

using namespace std;

void printSep(int n){
	cout << "\n\n\n\n\n";

}

string removeSpaces(string str){
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	return str;
}


