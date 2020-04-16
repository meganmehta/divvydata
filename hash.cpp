/*hash.cpp*/

// Hashing of stations, trip Id, and bike ID
// 

#include <iostream>
#include <string>
#include <cctype>  /*isdigit*/
#include <regex>   /*regular expressions*/

#include "hash.h"

using namespace std;

//
// isNumeric
//
// Returns true if the given string is numeric (all digits), false
// if not.  If the string is empty, false is returned since there 
// are no digits present.
//
bool isNumeric(string s)
{
	//
	// A string is numeric if it contains 1 or more digits, so let's
	// use a regular expression to check that.
	//
	// we are using POSIX basic notation for regular expressions, see
	//   https://en.cppreference.com/w/cpp/regex/ecmascript
	// where [:d:] means digit, [[:d:]] means match a single digit.
	// The + means match the preceding sub-expression 1 or more times.
	//
	regex pattern("[[:d:]]+", regex::ECMAScript);

	smatch matchResults;  // provides more details on the match

	if (regex_match(s, matchResults, pattern))
		return true;
	else
		return false;
}


//
// Hash 1 - searching stations by ID number 
// 
// Hashes the given station ID number and returns the rest of the information 
// on that station. So the key is supposed to be the ID number while the struct 
// contains the abbrev, fullname, latitude, longitude, capacity, online_date
//

int Hash1(string id, int N)
{
	int index = 0;
	//so the ID number is the exact place in the hash table 
	if (isNumeric(id)){
		index = stoi(id);
	}
	else{
		return -1;
	}
	
	return index % N;
}


//
// Hash 2 - searching for station based on abbreviation 
//
// Hashes the given abbreviation string and returns the rest of the information 
// on that station. So the key is supposed to be the abbreviation while the struct 
// contains the id, fullname, latitude, longitude, capacity, online_date
//

int Hash2(string abbrev, int N)
{
	//using the bernstein version 
	unsigned long long stringhash = 5381;
	
	if (isNumeric(abbrev)){
		return -1;
	}
	
	else{
		//class example about hasing strings 
		for (char c: abbrev){
			stringhash = ((stringhash << 5) + stringhash) + c;
		}
		
	}
	//mod operator on size of the hashmap 
	return stringhash % N;
}

//
// Hash 3 - searching trips by trip ID number 
// 
// Hashes the given trip ID number  and returns the rest of the information 
// on that trip. So the key is supposed to be the trip ID number and return 
// the struct filled with the information on the starttime, stoptime,
// bikeid, duration, from, to, identifies, birthyear.
// size of hashmap = 2,500,000 

int Hash3(string tripId, int N)
{
	//the trip ID always starts with the string "Tr" followed by 8 digits 
	string prefix = tripId.substr(0,2); //checks to see if the prefix is "Tr"
	int index = 0;
	
	if (prefix == "Tr"){
		//use the nummerical values as the index 
		index = stoi(tripId.substr(2)); 
	}
	else{
		return -1;
	}
	
	return index % N;
}

//
// Hash 4 - searching by bike ID
// 
// Hashes the given bike ID number and returns the rest of the information 
// on all of the trips from that bik. So the key is supposed to be the 
// bike ID number and return the structs filled with the information on 
// the starttime, stoptime, trip id, duration, from, to, identifies, birthyear
//

int Hash4(string bikeId, int N)
{
	int index = 0;
	//all bikeId's start with a B 
	if (bikeId[0] == 'B'){
		index = stoi(bikeId.erase(0,1));
	}
	else{
		return -1;
	}
	
	return index % N;
}

