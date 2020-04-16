/*hashmap.h*/

//
// References: original non-collision code written by Prof. Hummel (UIC)
// 
// Hashmap implements a hash table, assuming that the hash function isn't perfect
// and that the class can handle collisions. The class provides
// the underlying hash table along with insert() and search() functions;
// the user of this class must provided a Hash(key, N) function that 
// hashes the given key and returns an integer in the range 0..N-1, 
// inclusive, if the key is valid.  If the key is invalid, the Hash() 
// function must return a negative value.
// 
//
// The hash function is provided in the calls to insert and search.
// Pass the name of your hash function as the 3rd parameter.  Example:
//
//   int myHash(string key, int N)
//   { ... }
//
//   int N = 10000;
//   hashmap<string, double>  hmap(N);  
//
//   if (hmap.insert("deep-dish pizza", 19.99, myHash))
//     cout << "inserted" << endl;
//   else
//     cout << "not inserted?!" << endl;
// 

#pragma once

#include <iostream>
#include <functional>

using namespace std;

template<typename KeyT, typename ValueT>
class hashmap
{
private:
  struct HashEntry
  {
    bool   ContainsData;  // false => empty, true => contains data
    KeyT   Key;           // (key, value)
    ValueT Value;

    HashEntry()
    {
      ContainsData = false;
    }
  };

  HashEntry* HT;  // hash table array of structs
  int        N;   // capacity of hash table (# of locations or array size)
  
  //helper function called in the copy constructor and operator= functions 
  void deepCopyHelper(const hashmap& other){
  
	//allocate memory for new hashmap
	
	this->N = other.N; //number of elements in the original hash table 
	this->HT = new HashEntry[N]; //actually creating the hash tbale array 
	
	//set a for loop that makes sure that every vairable is being added into the struct for every hash table element
    for (int i = 0; i < N; i++)
    {	
		//only copy when the struct contains data 
		if(other.HT[i].ContainsData){
			 //then set all of the new elements equal to the old ones 
			 HT[i].ContainsData = other.HT[i].ContainsData; 
			 HT[i].Key = other.HT[i].Key;
			 HT[i].Value = other.HT[i].Value;
	
		 }  
	 }
  }
  


public:
  //
  // constructor: N is the size of the underlying hash table
  //
  hashmap(int N)
  {
    this->N = N;
    this->HT = new HashEntry[N];
  }
  
  //
  // destructor
  //
  virtual ~hashmap()
  {
    delete[] this->HT;
  }

  //
  // getN
  //
  // Returns the capacity of the hash table, i.e. the value N that
  // was passed to the constructor.
  //
  int getN() const
  {
    return this->N;
  }

  //
  // copy constructor
  //
  // Make a deep copy of the entire hashmap 
  // 
   
  hashmap(const hashmap& other)
  {
	deepCopyHelper(other);
  }
   
  
  // operator=
  //
  // Properly free memory and make a deep copy of the hash table 
  //
  
  hashmap& operator=(const hashmap& other)
  {
    //
    // TODO - call clear function to clear all structs in the hash table, 
    // and call the copy constructor 
	
	delete[] HT; //delete or "clear" the contents of the initial hashmap 
	deepCopyHelper(other); //call the copy helper and use other 
	return *this;
	
	
  }

  //
  // insert
  //
  // Inserts the given (key, value) pair into the hash table, overwriting
  // the previous value if already inserted.  If the insert was successful
  // then true is returned, otherwise false is returned (meaning the key
  // was not hashed successfully, e.g. due to improper formatting).
  //
  // NOTE: the caller must provide a function Hash(key, N) that returns
  // an integer in the the range 0..N-1, inclusive, if the key is valid.
  // If the key is invalid, the hash function must return a negative
  // integer. The hash function is provided by simply calling insert
  // with the name of your hash function.  Example:
  //
  //   int myHash(string key, int N)
  //   { ... }
  //
  //   int N = 10000;
  //   hashmap<string, double>  hmap(N);  
  //
  //   if (hmap.insert("deep-dish pizza", 19.99, myHash))
  //     cout << "inserted" << endl;
  //   else
  //     cout << "not inserted?!" << endl;
  //
  bool insert(KeyT key, ValueT value, function<int(KeyT,int)> Hash)
  {
    //
    // Call the provided hash function with the key, and N, the size
    // of our hash table:
    //
    
	int index = Hash(key, N);
	int bucketsProbed = 0; //create another counter that counts for the insertions 

    //
    // insert:
    //
    if (index < 0 || index >= N)  // invalid key or hash function:
    {
      return false;
    }
    else  // valid array index, store into hash table:
    {
	  while (bucketsProbed < N){
		  //if the key already exists and contains data then change the value 
		  if (HT[index].ContainsData && HT[index].Key == key){
			  HT[index].Value = value;
			  HT[index].ContainsData = true;  // array location now contains data
			  return true;
		  }
		  if (!HT[index].ContainsData){
			  HT[index].Key = key;
			  HT[index].Value = value;
			  HT[index].ContainsData = true; 
			  return true;
			  }
			
		index = (index + 1) % N; //increment the index to account for the new size 
		bucketsProbed++; //increase the number of total insertions 
	
	 }//end of while loop 
   }  
	return false; 
  }//ends the function 
  

  //
  // search
  //
  // Searches the hash table for the matching key, and if found then
  // (1) the value is returned via the reference parameter and (2) true
  // is returned.  If the key could not be found, or if the hash 
  // function returned an invalid value (e.g. due to an improperly 
  // formatted key), then false is returned.
  //
  // NOTE: the caller must provide a function Hash(key, N) that returns
  // an integer in the the range 0..N-1, inclusive, if the key is valid.
  // If the key is invalid, the hash function must return a negative
  // integer. The hash function is provided by simply calling search
  // with the name of your hash function.  Example:
  //
  //   int myHash(string key, int N)
  //   { ... }
  //
  //   int N = 10000;
  //   hashmap<string, double>  hmap(N);
  //   ...
  //   double price;
  //   if (hmap.search("deep-dish pizza", price, myHash))
  //     cout << "deep-dish piazza costs " << price << endl;
  //   else
  //     cout << "not found?!" << endl;
  //
  bool search(KeyT key, ValueT& value, function<int(KeyT,int)> Hash) const
  {
    //
    // Call the provided hash function with the key, and N, the size
    // of our hash table:
    //
  
	  int index = Hash(key, N);
	  int bucketsProbed = 0;

    //
    // search:
    //
		if (index < 0 || index >= N)  // invalid key or hash function:
		{
		  return false;
		}
		
		//when the number of insertions is less than the size of the hashmap and that element in the 
		// hashmap contains data, then check if that key has a matching value 
		while ((bucketsProbed < N) && (HT[index].ContainsData))  // hash table contains data:
		{
			if (HT[index].Key == key){
				 value = HT[index].Value;
				 return true;
			  }
			  
			  index = (index + 1) % N;
			  bucketsProbed++;
			  
		}
		
		return false; 
	
  }//end of function 
  
//Command 5 helper function that Move keys into a vector that will be called in command 5 

vector<KeyT> keyStationVector(function<int(KeyT,int)> Hash){
	//create the vector 
	vector <KeyT> stationIDkey;
	
	//goes through all of the keys in the hash table and adds them to a vector 
	for (int i = 0; i < N; i++ ){
		if (HT[i].ContainsData){
			stationIDkey.push_back(HT[i].Key);
		}
	}
	
	return stationIDkey;
	
}


}; // end of class 
