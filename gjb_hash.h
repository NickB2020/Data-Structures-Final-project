/*
 * COPYRIGHT(C) 2022 Greg Brown.All Rights Reserved.
 * Project #: 3 - Hashing
 * Author : Greg Brown, 4209379
 * Date : April 7, 2022
 * Files: gjb_hash.h
 *
 * This header file is used to declare a version of a Linear Probe Hashing structure, it may be modified
 *		to suit the user's testing and to accommodate that user's program calling on this
 *		data structure
 *
 * If changes are made, please state such modifications in the comments. Thank you.
 */

#ifndef GJB_HASH_H
#define GJB_HASH_H

#include <iostream>

class gjb_hash
{
private:
	//Struct to hold the data for each entry in the table
	struct table_node
	{
		//Initializing the key and the values to -1 to show empty values
		int key = -1;
		int value = -1;
	};

	//Declaring the variable to handle the table
	table_node** table;
	//Declaring the variable to handle the size of the table
	long tableSize;

	//Function to determine the next free space if a collision occurred
	//	Input: index that caused the collision
	//	Output: index that holds a useable free space
	long _collision_resolution_free_space(long);

	//Function to determine the location of the key
	//	Input: index of the initial collision, key being searched
	//	Output: index of the found key
	long _collision_resolution_key(long, int);

	//Function to determine the initial index
	//	Input: value of the key to be inserted into the table
	//	Output: initial index where the key will be inserted if no collisions
	long _determine_index(int);

public:
	//Default constructor
	//	Input: nothing
	//	Output: nothing (an empty hash table)
	gjb_hash();

	//Constructor for predetermined table size
	//	Input: number of elements for the table to start with
	//	Output: nothing (an empty hash table)
	gjb_hash(long);

	//Default destructor
	//	Input: nothing
	//	Output: nothing (memory freed from table)
	~gjb_hash();

	//Insert function for new key and value
	//	Input: integer key value, integer value
	//	Output: nothing (key-value pair inserted into table)
	void insert(int, int);

	//Key deletiong function
	//	Input: integer key value
	//	Output: nothing (key replaced with tombstone)
	void delete_key(int);

	//Key search function
	//	Input: integer key value
	//	Output: integer value referenced by key
	int search_key(int);

	//Table print function
	//	Input: nothing
	//	Output: nothing (table keys and values printed to console)
	void print_table();
};

gjb_hash::gjb_hash()
{
	//Table handler set to null and count set to zero for empty table
	table = nullptr;
	tableSize = 0;
}

gjb_hash::gjb_hash(long inputCount)
{
	//Initializing table to table_node pointer array double the input amount
	table = new table_node * [inputCount * 2]{ nullptr };

	//Initializing count to double the input amount
	tableSize = inputCount * 2;
}

long gjb_hash::_determine_index(int key)
{
	//Make sure the key is a positive value
	if (key < 0)
		key = key * -1;

	//Returns the modulo of the input key
	return key % tableSize;
}

long gjb_hash::_collision_resolution_free_space(long position)
{
	//Declaring and initializing an index to 0
	long index = 0;

	//Iterating through the table from the input position until a free space or tombstone is found
	while (*(table + position + index) != nullptr && (*(table + position + index))->key != -1)
	{
		//Index is increased if current location is not a free space
		index++;

		//If the index exceeds the size of the table, loop to the beginning of the table
		if (index + position >= tableSize)
			index = -position;
	}

	//Retun the index of the located free space
	return position + index;
}

long gjb_hash::_collision_resolution_key(long position, int key)
{
	//Declaring and initializing an index to 0
	long index = 0;

	//Iterating through the table from the input position until the key is located
	while ((*(table + position + index))->key != key)
	{
		//If the current position doesn't contain the key, increase the index
		index++;

		//If the index exceeds the size of the table, wrap around to the beginning of the table
		if (index + position >= tableSize)
			index = -position;
	}

	//Return the index of the located key
	return position + index;
}

void gjb_hash::insert(int key, int value)
{
	//Determine the initial index where the key should be inserted
	long tablePosition = _determine_index(key);

	//If the initial index isn't a free space, call the free space collision resolution function
	if (*(table + tablePosition) != nullptr && (*(table + tablePosition))->key != -1)
		tablePosition = _collision_resolution_free_space(tablePosition);

	//If a free space is found...
	if (tablePosition != -1)
	{
		//Determine if it's a tombstone, if not...
		if (*(table + tablePosition) == nullptr)
		{
			//...declare a new table_node and initialize values to the input key and value
			table_node* tempPtr = new table_node();
			tempPtr->key = key;
			tempPtr->value = value;

			//Have the pointer at the table position point to the new node
			*(table + tablePosition) = tempPtr;
		}
		else
		{
			//...otherwise just change the tombstone values
			(*(table + tablePosition))->key = key;
			(*(table + tablePosition))->value = value;
		}

		//Return successfully
		return;
	}

	//If a free space wasn't found, then return an error message and return
	std::cout << "Error Finding Space in Table to Insert Value" << std::endl;
	return;
}

void gjb_hash::delete_key(int key)
{
	//Determine the initial index from the input key
	long tablePosition = _determine_index(key);

	//If the initial location doesn't hold the key, call the collision resolution policy to find the key index
	if ((*(table + tablePosition))->key != key)
		tablePosition = _collision_resolution_key(tablePosition, key);

	//Change the key to -1 to make the table_node a tombstone
	(*(table + tablePosition))->key = -1;

	return;
}

int gjb_hash::search_key(int key)
{
	//Determine the initial index based on the input key
	long tablePosition = _determine_index(key);

	//If the table position doesn't hold that key, perform the collision resolution to find the index
	if ((*(table + tablePosition))->key != key)
		tablePosition = _collision_resolution_key(tablePosition, key);

	//Return the value of the found index
	return (*(table + tablePosition))->value;
}

void gjb_hash::print_table()
{
	//Iterate through the table and print the key and value for each index
	std::cout << "Key : Value" << std::endl;
	for (long i = 0; i < tableSize; i++)
	{
		if (*(table + i) == nullptr)
			std::cout << "-1 : -1" << std::endl;
		else
			std::cout << (*(table + i))->key << " : " << (*(table + i))->value << std::endl;
	}

	return;
}

gjb_hash::~gjb_hash()
{
	//If the table wasn't already destroyed ...
	if (table != nullptr)
	{
		//...iterate through the table and free all indexes that hold data
		for (long i = 0; i < tableSize; i++)
		{
			if (*(table + i) != nullptr)
				free(*(table + i));
		}

		//Free the memory of the table itself
		free(table);
		table = nullptr;
	}
}

#endif