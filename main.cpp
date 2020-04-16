/*main.cpp*/

//
// Megan Mehta
// Divvy Bike Data Hashing 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>    /*priority_queue*/
#include <utility>  /*pair*/

#include "util.h"
#include "hash.h"
#include "hashmap.h"

using namespace std;


//
// StationData (used in the first two hashmaps, when finding by station)
// 
// Contains all of the information about a particular station 
//
 
struct StationData
{
	string id; //int 
	string abbrev;
	string fullname;
	string latitude; //double 
	string longitude; //double 
	string capacity; //int 
	string online_date;
	
	StationData()
	{
		id = "";
		abbrev = "";
		fullname = "";
		latitude = "";
		longitude = "";
		capacity = "";
		online_date = "";
	}
};

//
// TripData (used in hashfunction related to tripID and bikeID)
// 
// Contains all of the information about a particular bike trip 
//
 
struct TripData
{
	string tripId;
	string startTime;
	string endTime;
	string bikeId;
	string tripDuration; //int
	string fromStationId; //int
	string toStationId; //int
	string identifies;
	string birthYear; //int 
	
	TripData()
	{
		tripId = "";
		startTime = "";
		endTime = "";
		bikeId = "";
		tripDuration = "";
		fromStationId = "";
		toStationId = "";
		identifies = "";
		birthYear = "";
	}
};

struct BikeData
{
	string bikeId;
	int usage;
	
	BikeData()
	{
		bikeId = "";
		usage = 0;
	}
};

//used in Command 5 for the priority queue 
class prioritize
{
public:
  bool operator()(const pair<string, double>& p1, const pair<string,double>& p2) const
  {
    //
    // if you want smaller values @ the end, return true if 
    // p1's value < p2's value.  if you want larger values
    // @ the end, return true if p1's value > p2's value.
    if (p1.second > p2.second){
		return true;
	}
    else if (p2.second > p1.second){
		return false;
	}
	else{
		return stoi(p1.first) > stoi(p2.first);
	}
		
  }
};

// Command 1 - lookup by station id 
//
//If the user inputs a numeric string, then assumes it's the station id then return 
//the appropriate struct that matches that station id, else if the station id isn't found 
//then print "Station not found" 
//

void StationLookup(string userCommand, hashmap< string, StationData >& stationsById ){
	  StationData stationLookupData;
	if (!stationsById.search(userCommand, stationLookupData, Hash1)){
		cout << "Station not found" << endl;
	}
	else{
		//print out the information stored in the value, and call by struct 
		cout << "Station: " << endl;
		cout << " ID: " << stationLookupData.id << endl;
		cout << " Abbrev: " << stationLookupData.abbrev << endl;
		cout << " Fullname: " << stationLookupData.fullname << endl;
		cout << " Location: " << "(" << stod(stationLookupData.latitude) << ", " << stod(stationLookupData.longitude) << ")" << endl;
		cout << " Capacity: " << stationLookupData.capacity << endl;
		cout << " Online date: " << stationLookupData.online_date << endl;
	}
	
  }//end of function 


// Command 2 - lookup by station abbreviation 
//
//If the user inputs a string with no numbers, then assume it's a lookup by the abbreviation 
//then search into the searchbyabbrev hashmap and return all of that station information
//

void AbbrevLookup(string userCommand, hashmap< string, StationData >& stationsByAbbrev){
	StationData abbrevStationData;
	if (!stationsByAbbrev.search(userCommand, abbrevStationData, Hash2)){
		cout << "Station not found" << endl;
	}
	else {
		cout << "Station: " << endl;
		cout << " ID: " << abbrevStationData.id << endl;
		cout << " Abbrev: " << abbrevStationData.abbrev << endl;
		cout << " Fullname: " << abbrevStationData.fullname << endl;
		cout << " Location: " << "(" << stod(abbrevStationData.latitude) << ", " << stod(abbrevStationData.longitude) << ")" << endl;
		cout << " Capacity: " << abbrevStationData.capacity << endl;
		cout << " Online date: " << abbrevStationData.online_date << endl;
	}
	
	
  }//end of function 


// Command 3 - lookup by trip ID 
//
//If the user inputs a string with the first part of the string "Tr104" then feed into 
//this command, which returns all of the infromation about the trip, when the trip ID 
//number is inserted 

void TripIDLookup(string userCommand, hashmap< string, TripData >& tripsById, hashmap< string, StationData >& stationsById){
	
	//create strings of the modified values beforehand 
	string durationTime; 
	string fromStation;
	string toStation;
	
	//call all of the value structs 
	StationData tripIdstation;
	TripData tripIdSearch;
    if (!tripsById.search(userCommand, tripIdSearch, Hash3)){
		cout << "Trip not found" << endl;
		return;
	}
	else{
		//calculates the duration time in seconds, minutes, and hours 
		int hours = stoi(tripIdSearch.tripDuration)/3600;
		int minutes = (stoi(tripIdSearch.tripDuration)/60) % 60;
		int seconds = stoi(tripIdSearch.tripDuration) % 60;
		
		if (hours == 0){
			durationTime = to_string(minutes) + " minutes, " + to_string(seconds) + " seconds";
		}
		else{
			durationTime = to_string(hours) + " hours, " + to_string(minutes) + " minutes, " + to_string(seconds) + " seconds";
		}
		
		//gets the station abbreviation based on from station id 
		if (stationsById.search(tripIdSearch.fromStationId, tripIdstation, Hash1)){
			fromStation = tripIdstation.abbrev;
		}
		
		//gets the to station abbreviation based on to station id 
		if (stationsById.search(tripIdSearch.toStationId, tripIdstation, Hash1)){
			toStation = tripIdstation.abbrev;
		}
		
		cout << "Trip: " << endl;
		cout << " ID: "<< tripIdSearch.tripId << endl;
		cout << " Starttime: " << tripIdSearch.startTime << endl;
		cout << " Bikeid: " << tripIdSearch.bikeId << endl;
		cout << " Duration: " << durationTime << endl;
		cout << " From station: " << fromStation + " (" + tripIdSearch.fromStationId + ")" << endl;
		cout << " To station: " << toStation + " (" + tripIdSearch.toStationId + ")" << endl;
		cout << " Rider Identifies as: " << tripIdSearch.identifies << endl;
		cout << " Birthyear: " << tripIdSearch.birthYear << endl;
		
	}
	
  }//end of function 

//Command 4 - lookup by bike Id 
//
//if the user inputs a bike ID (or a string that starts with B) then return the bikeId 
//and the amount of times it would used 
//

void BikeIdLookup(string userCommand, hashmap< string, BikeData >& bikesById){
	BikeData bikeSearchData; //initialize the data struct that values are from 
	if (!bikesById.search(userCommand, bikeSearchData, Hash4)){
		cout << "Bike not found" << endl;
	}
	else {
		//print out necessary information 
		cout << "Bike: "  << endl;
		cout << " ID: " << bikeSearchData.bikeId << endl;
		cout << " Usage: " << bikeSearchData.usage << endl;
	}
	
	
  }//end of function 

// Command 5 - Finding nearby stations based on longitude and latitude. 
//
//When the user enters the current longitude, latitude, and distance, then then
//the function returns a "list" with all of the nearest stations based on that list. 
//First, create a vector with all of the possible keys, then add the keys to a priority queue 
//if their distance is less than what the user inputted. 

void FindNearbyStations(string userCommand, hashmap< string, StationData >& stationsById){
	vector<string> stationKeys = stationsById.keyStationVector(Hash1);
	StationData stationKeyIds;
	
	//stream in the userinput, and convert to doubles 
	stringstream s(userCommand);
	
	string nearby, longitude, latitude, distance;
	
	getline(s, nearby, ' ');
	getline(s, latitude, ' ');
	getline(s, longitude, ' ');
	getline(s, distance, ',');
		
		
	string check = nearby;
	double userLongitude = stod(longitude);
	double userLatitude = stod(latitude);
	double userDistance = stod(distance);
	
	//initialize the variables that we'll get from the keys 
	double differenceDistance = 0;
	double givenLat = 0;
	double givenLong = 0;
	
	//declare priority queue
	priority_queue<pair<string, double>,
    vector<pair<string, double>>,
    prioritize>  pq;

	//goes through all of the keys in the initial vector 
	for (int i = 0; i < stationKeys.size(); i++){
		//if the keys exist in the vector
		if (stationsById.search(stationKeys[i], stationKeyIds, Hash1)){
			//"extract" the desired values: latitude, longitude, and calculate the distance based off those
			givenLat = stod(stationKeyIds.latitude);
			givenLong = stod(stationKeyIds.longitude);
			differenceDistance = distBetween2Points(userLatitude, userLongitude, givenLat, givenLong);
			//if the distance is less than the one that the user inputted, then add it to the queue 
			if (differenceDistance <= userDistance){
				pq.push(pair<string,double>(stationKeys[i], differenceDistance));
			}
		}
	}
	
	//print out all of the information in the queue 
	cout << "Stations within " << distance << " miles of (" << latitude << ", " << longitude << ")" << endl;
	if (pq.empty()){
		cout << " none found" << endl;
	}
	while (!pq.empty()){
		auto p = pq.top();
		pq.pop();
		
		cout << " station " << p.first << ": " << p.second << " miles" << endl;
	}
	

	
}
//Command 6 - Find similar trips 
//
//Finds similar trips that match the inputed one, starts by 
//searching for the stations near the start point and stations near the 
//end point. comparing the distances between the other starting and ending points 
//and records the stations that have a similar trip length 

void FindSimilarTrips(userCommand,hashmap< string, StationData >& stationsById, hashmap<string, TripData> &tripsById){
	
	set<int> nearStart;
	set<int> nearEnd; 
	
	TripData similarTrips;
	StationData originalStation;
	
	//splits the user input string 
	stringstream s(userCommand);
	
	string similar, tripId, distance;
	getline(s, similar, ' ');
	getline(s, tripId, ' ');
	getline(s, distance, ' ');
	
	//search the tripId for the starting and end point 
	if (tripsById.search(tripId, similarTrips, Hash3){
		string userStart = similarTrips.from;
		string userEnd = similarTrips.to;
	}
	//find the corresponding longitude and latitude for the start point (from)
	if (stationsById.search(userStart, originalStation, Hash1 ){
		double startLong = stod(originalStation.longitude);
		double startLat = stod(originalStation.latitude);
	}
	//find the corresponding longitude and latitude for the end point (to)
	if (stationsById.search(userEnd, originalStation, Hash1){
		double endLong = stod(originalStation.longitude);
		double endLat = stod(originalStation.latitude);
	}
	
	//all of the station Ids are now in a vector 
	vector<string> allKeys = stationsById.keyStationVector(Hash1);
	for (int i = 0; i < stationKeys.size(); i++){
		//if the keys exist in the vector
		if (stationsById.search(stationKeys[i], stationKeyIds, Hash1)){
			//"extract" the desired values: latitude, longitude, and calculate the distance based off those
			givenLat = stod(stationKeyIds.latitude);
			givenLong = stod(stationKeyIds.longitude);
			differenceDistance = distBetween2Points(userLatitude, userLongitude, givenLat, givenLong);
			//if the distance is less than the one that the user inputted, then add it to the queue 
			if (differenceDistance <= userDistance){
				pq.push(pair<string,double>(stationKeys[i], differenceDistance));
			}
		}
	}


// inputData
// 
// Given a filename (either the station data or trip data)
// inputs that data into the given hash table.
// 
bool inputStationData(string filename, hashmap< string, StationData >& stationsById,
	hashmap< string, StationData >& stationsByAbbrev)
{
	ifstream  infile(filename);
	
	if (!infile.good())
	{
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
	
	// file is open, start processing:
	string line;
	
	getline(infile, line);  // input and discard first row --- header row
	
	int totalStations = 0;
	
	while (getline(infile, line))
	{
		stringstream s(line);
		
		string id, abbrev, fullname, latitude, longitude, capacity, online_date;
		
		//
		// format: id, abbrev, fullname, latitude, longitude, capacity, online_date
		// 
		getline(s, id, ',');
		getline(s, abbrev, ','); 
		getline(s, fullname, ',');   
		getline(s, latitude, ',');
		getline(s, longitude, ',');
		getline(s, capacity, ',');
		getline(s, online_date, ',');
		
		//increment total number of stations 
		totalStations++;
		
		// store into hash table
		StationData sd;
		
		sd.id = id;
		sd.abbrev = abbrev;
		sd.fullname = fullname;
		sd.latitude = latitude;
		sd.longitude = longitude;
		sd.capacity = capacity;
		sd.online_date = online_date;
		
		
		//inserts into separate hashmaps based on the desired search method
		//based on the keys 
		stationsById.insert(id, sd, Hash1); //inserting into the first hashmap 
		stationsByAbbrev.insert(abbrev, sd, Hash2); //inserting into the second hashmap 
	
	}
	
	cout << "# of stations: " << totalStations << endl;
	
	return true;  // we have data to be processed:
}

bool inputTripData(string filename2, hashmap< string, TripData >& tripsById,
				   hashmap< string, BikeData >& bikesById){
	
	ifstream  infile(filename2);
	
	if (!infile.good())
	{
		cout << "**Error: unable to open '" << filename2 << "'..." << endl;
		return false;
	}
	
	// file is open, start processing:
	string line;
	
	getline(infile, line);  // input and discard first row --- header row
	
	int totalTrips = 0;
	int uniqueBikes = 0;

	while (getline(infile, line))
	{
		stringstream s(line);
		
		string tripId, startTime, endTime, bikeId, tripDuration;
		string fromStationId, toStationId, identifies, birthYear;
		
		//
		// format: id, abbrev, fullname, latitude, longitude, capacity, online_date
		// 
		getline(s, tripId, ',');
		getline(s, startTime, ','); 
		getline(s, endTime, ',');   
		getline(s, bikeId, ',');
		getline(s, tripDuration, ',');
		getline(s, fromStationId, ',');
		getline(s, toStationId, ',');
		getline(s, identifies, ',');
		getline(s, birthYear, ',');
		
		//increment total number of trips 
		totalTrips++;
		
		// store into hash table
		TripData td;
		BikeData bd;
		
		td.tripId = tripId;
		td.startTime = startTime;
		td.endTime = endTime;
		td.bikeId = bikeId;
		td.tripDuration = tripDuration;
		td.fromStationId = fromStationId;
		td.toStationId = toStationId;
		td.identifies = identifies;
		td.birthYear = birthYear;
		
		
		//if the bikeId isn't already in the struct, then add it and increase
		//the amount of unique bikes there are 
		if (!bikesById.search(bikeId, bd, Hash4)){
			bd.bikeId = bikeId;
			bd.usage = 1;
			uniqueBikes++;
		}
		//otherwise just increase the amount of times the bike was used 
		else{
			bd.usage++;
		}
		
		//inserting common data but into different hashmaps depending on the key 
		//this inserts the struct that you filled with all of the info into the hash table
		tripsById.insert(tripId, td, Hash3);
		bikesById.insert(bikeId, bd, Hash4 );
	}
	
	cout << "# of trips: " << totalTrips << endl;
	cout << "# of bikes: " << uniqueBikes << endl;
	
	return true;  // we have data to be processed:
}



int main()
{
	cout << "** DIVVY analysis program **" << endl;
	cout << endl;

	//create the hashmaps and input the assigned structs 
	hashmap<string, StationData> stationsById(10000);
	hashmap<string, StationData> stationsByAbbrev (10000);
	hashmap<string, TripData> tripsById(2500000);
	hashmap<string, BikeData> bikesById(50000);

	//
	// input the both file names
	// 
	
	string filename1;
	string filename2;
	
	cout << "Enter stations file> ";
	getline(cin, filename1);
	cout << "Enter trips file> ";
	getline(cin, filename2);
	cout << endl;
	
	
	cout << "Reading " << filename1 << endl;
	cout << "Reading " << filename2 << endl;
	cout << endl;
	
	//if all of the information is stored in the hashmaps, then return true for success
	bool success = inputStationData(filename1,stationsById,stationsByAbbrev);
	
	bool success2 = inputTripData(filename2,tripsById,bikesById);
	
	
	//
	// did we input anything?
	// 
	if (!success || !success2)
	{
		cout << "No data, file not found?" << endl;
		return 0;
	}
	
	//
	// allow the user to enter a command for whatever station/trip data they want to find 
	// 

	string userCommand = "";
	
	cout << endl;
	cout << "Please enter a command, help, or #> ";
	getline(cin, userCommand);

	//
	// user testing:
	//
	while (userCommand != "#")
	{
		//create a set of if-statements to see which 
		//command needs to be set in motion 
		if (userCommand == "help"){
		 cout << "Avaliable Commands: \n"
		 << "   Enter a station id (e.g. 341) \n"
		 << "   Enter a station abbreviation (e.g. Adler) \n"
		 << "   Enter a trip id (e.g. Tr10426561) \n"
		 << "   Enter a bike id (e.g. B5218) \n"
		 << "   Nearby stations (e.g. nearby 41.86 - 87.62 0.5) \n"
		 << "   Similar trips (e.g. similar Tr10426561) \n"
		 << endl;
		}

		else if (isNumeric(userCommand)){
			StationLookup(userCommand, stationsById);
		}
		
		else if (userCommand.substr(0,2) == "Tr"){
			TripIDLookup(userCommand, tripsById,stationsById);
		}
		else if (userCommand.substr(0,1) == "B"){
			BikeIdLookup(userCommand,bikesById);
		}
		else if (userCommand.substr(0,6) == "nearby"){
			FindNearbyStations(userCommand, stationsById);
		}
// 		else if (userCommand.substr(0,7) == "similar"){
			
// 		}
		else if (!isNumeric(userCommand)){
			AbbrevLookup(userCommand,stationsByAbbrev);
		}
		
		cout << endl;
		cout << "Please enter a command, help, or #> ";
		getline(cin, userCommand);
	}

	
	return 0;
}
