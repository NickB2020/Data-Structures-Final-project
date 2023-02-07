//Including the header file for the data structure and standard IO for console output
#include "gjb_hash.h"
#include <iostream>

void main()
{
	//Creating a new instance of my hash table implementation that will hold 20 elements
	gjb_hash* hashTable = new gjb_hash(20);

	//Declaring a value to search for
	int searchValue = std::rand() % 1000;

	//Filling the table with random keys and values then inserting the value to be
	//		searched for as a key with a random value associated with it
	for (int i = 0; i < 19; i++)
		hashTable->insert(std::rand() % 1000, std::rand() % 1000);
	hashTable->insert(searchValue, std::rand() % 1000);

	//Printing out the table to see what's currently being stored in it
	hashTable->print_table();

	//Searching for the key stored in the searchValue variable and displaying the associated value
	std::cout << "\nSearching for the Value Stored at Key: " << searchValue << std::endl <<
		"Value: " << hashTable->search_key(searchValue) << std::endl << std::endl;

	//Deleting the key stored in the searchValue variable
	std::cout << "Deleting Search Value: " << searchValue << std::endl << std::endl;
	hashTable->delete_key(searchValue);


	//Printing out the table to see what is now stored in it
	hashTable->print_table();

	hashTable->~gjb_hash();
	return;
}