/*
Nick Bischoff
Data Structures
Project 3
File Name: main.cpp
File(s) needed: QuadProbing.h , gjb_hash.h
Purpose: This program is to aide in the testing of a home grown Quadratic Probing hash table, a Linear probing hashtable provided by student GREGORY BROWN, and a STL Hash Map because it is the STL representation of a hash table. This program prompts the user to run the test between the three hashing techniques with insertion, with and without collisions, search, or deletion. Then the screen will clear and prompt the user for an amount of integers to input into the tables to either be inserted or inserted and then searched for or deleted. The run times of the insertion and search and deletion are recorded depending on which option is selected and then the program will rank the structures fastest to slowest and their recorded run times for that test. This program utilizes a do while loop for repeating menu functionality so the user does not have to exit the program to run another test, the structures are not emptied at the end of the insertion test to show how each technique handles collision. validation is also utilized for each user prompt.

***SPECIAL THANKS TO CLASSMATE GREGORY BROWN FOR EXCHANGING HIS HOMEGROWN LINEAR PROBING HASH CODE FOR THE PURPOSE OF TESTING IN THIS PROJECT***

*/
#include "QuadProbing.h"
#include "gjb_hash.h"
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <iterator>
#include <algorithm>

using std::unordered_map;
using std::cout;
using std::cin;
using std::endl;
using std::streamsize;
using std::numeric_limits;

//prototypes
int menu();
void insertionNoCollisions();
void insertionCollisions();
void searching();
void deleting();

// U can be any type we want to test. here it's the type of data in the sequence to be sorted; can be changed to any other type for which assignment (=) and less-than comparisons (<) are defined.
typedef int U;

int main()
{
    menu();
    return 0;
}

//pre: sorting function must exist for the menu to have working options
//post: The user can now navigate this program with the help of the function that provides a user interface complete with validation
int menu()
{
    // variables for switch statement
    int choice;
    int key = 0;

    // While loop controls the repeating functionality of the menu after each operation is completed.
    while (1)
    {
        cout << "*****************************************************************************************************" << endl;
        cout << "****            Project 3 Quadratic Probing vs Linear Probing vs STL HashMap                      ***" << endl;
        cout << "*****************************************************************************************************" << endl;
        cout << endl;
        cout << "**** Menu *******************************************************************************************" << endl;
        cout << " 1. Insertion without collisions" << endl;
        cout << " 2. Insertion with collisions" << endl;
        cout << " 3. Search" << endl;
        cout << " 4. Deletion" << endl;
        cout << " 5. Quit Program" << endl;
        cout << endl;
        // Menu choice input validation, will ONLY accept a choice of 1-5.
        do{
                cout << "Enter choice: ";
                cin >> choice;
                if(cin.fail() || choice < 1 || choice > 5)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << " \n* Please enter a numeric option from the selection above *\n" << endl;
                }
           }while(cin.fail() || choice < 1 || choice > 5);

        // Switch statement controls which test will be called based on the user's choice from the menu.
        switch(choice)
        {
            // call function that records and displays results of the tests for insertion without collisions
        case 1:
            {
                insertionNoCollisions();
                // pause and clear screen
                system("pause");
                system("cls");
            }
            break;
            // call function that records and displays results of the tests for insertion with collisions
        case 2:
            {
                insertionCollisions();
                // pause and clear screen
                system("pause");
                system("cls");
            }
            break;
            // call function that records and displays results of the tests for search
        case 3:
            {
                searching();
                // pause and clear screen
                system("pause");
                system("cls");
            }
            break;
              // call function that records and displays results of the tests for deletion
        case 4:
            {

                deleting();
                // pause and clear screen
                system("pause");
                system("cls");
            }
            break;
            // break loop for menu and exit the program
        case 5:
            return 0;
        }
    }
}

//pre: menu function must exist, classes for hash methods must exist
//post: We can now use this function to select an amount of integers to insert and run a test between the hashes and this function will load up the tables with ascending integers to not allow for //collisions to test for advantages of using sorted keys with the hash's and then this function will tell us the runtimes of each and which is
//faster for the test
void insertionNoCollisions()
{
    unordered_map<U, U> mySTLHash;

    // vaiable to get size from user
    int input = 0;

    // clear the screen of the menu and display this new one for the size
    system("cls");
    cout << "The integer load sizes to choose from are: " << endl;
    cout << "  10" << endl;
    cout << "  100" << endl;
    cout << "  1,000" << endl;
    cout << "  5,000" <<endl;
    cout << "  10,000" << endl;
    cout << "  15,000" << endl;
    cout << "  20,000" << endl;
    cout << "  25,000" << endl;
    cout << "  30,000" << endl;
    cout << "  50,000" << endl;
    cout << "  100,000" << endl;
    cout << "  500,000" << endl;
    cout << "  1,000,000" << endl;
    cout << "  100,000,000" << endl;
    cout << endl;
    cout << " what size to use? ";

    do
    {
        cin >> input;
        //quad probe object
        QuadProbing qp(input);
        // Gregory Brown's object for his Linear probe
        gjb_hash* hashTable = new gjb_hash(input);

        //This validates the user input for size is an integer.
        while(cin.fail())
        {
            //Try again if an option isn't chosen
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "* Please select an option from the menu * ";
            cin >> input;
        }
        cout << "The bigger sizes might take some time to calculate.\nOne moment please..." << endl;
        // validate the option to make sure its from the menu
        if(input == 10 ||input == 100 ||input == 1000 || input == 5000 || input == 10000 || input == 15000 || input == 20000 || input == 25000 || input == 30000 || input == 50000 || input == 100000|| input == 500000 || input == 1000000
            || input == 100000000)
        {
            //Record insertion for quad probe
            auto startQuad = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < input; ++i)
            {
                qp.insert(i);
            }

            auto endQuad = std::chrono::high_resolution_clock::now();

            //Record insertion for linear probe
            auto startLinear = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < input; ++i)
            {
                hashTable->insert(i,i);
            }

            auto endLinear = std::chrono::high_resolution_clock::now();

            //Record insertion for STL hashmap
            auto startSTL = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < input; ++i)
            {
               mySTLHash.insert(std::pair<U, U>{input, input});
            }

            auto endSTL = std::chrono::high_resolution_clock::now();

            //cast to micro seconds .
            auto durationQuad = std::chrono::duration_cast<std::chrono::microseconds>(endQuad - startQuad);
            auto durationLinear = std::chrono::duration_cast<std::chrono::microseconds>(endLinear - startLinear);
            auto durationSTL = std::chrono::duration_cast<std::chrono::microseconds>(endSTL - startSTL);
            //variables to use if else statement to determine winners
            double q = std::chrono::duration<double>(durationQuad).count();
            double l = std::chrono::duration<double>(durationLinear).count();
            double s =  std::chrono::duration<double>(durationSTL).count();
            //now display the winner, second place, and third place.
            cout << endl;
            cout << "1st: ";

            //Quad 1st.
            if(q <= l && q <= s )
            {
                cout << "QuadProbe " << q << " microseconds\n2nd: ";

                //Linear is 2nd.
                if(l <= s)
                {
                    cout << "LinearProbe " << l << " microseconds\n3rd: STL in " << s << " microseconds" << endl;
                }
                //STL hashmap is 2nd.
                else
                {
                    cout << "STL in " << s << " microseconds\n3rd: LinearProbe in " << l << " microseconds" << endl;
                }
            }
            //Linear is 1st.
            else if(l <= q && l <= s)
            {
                cout << "LinearProbe in " << l << " microseconds\n2nd: ";

                // Quad is 2nd.
                if(q <= s)
                {
                    cout << "QuadProbe " << q << " microseconds\n3rd: STL in " << s << " microseconds" << endl;
                }
                //STL is 2nd.
                else
                {
                    cout << "STL in " << s << " microseconds\n3rd: QuadProbe   in " << q << " microseconds" << endl;
                }
            }
            //STL is 1st.
            else
            {
                 cout << "STL in " << s << " microseconds\n2nd: ";

                 //Quad is 3rd.
                 if(q <= l)
                 {
                    cout << "QuadProbe " << q << " microseconds\n3rd: LinearProbe in " << l << " microseconds" << endl;
                 }
                 //Linear is 2nd.
                 else
                 {
                    cout << "Linear in " << l << " seconds\n3rd: QuadProbe in " << q << " microseconds" << endl;
                 }
            }
            cout << endl;
        }
        // error message if user puts in size not on menu
        else
        {
           cout << "* Please select an option from the menu * ";
        }
    }
    // end of do while loop for validation of the size
    while(input != 10 && input != 100 && input!= 1000 && input != 5000 && input != 10000 && input != 15000 && input != 20000 && input != 25000 && input != 30000 && input != 50000 && input != 100000&& input != 500000 && input != 1000000
           && input != 100000000);
}

//pre: menu function must exist, classes for hash methods must exist
//post: We can now use this function to select an amount of integers to insert and run a test between the hashes and this function will load the tables with randomly generated integers to allow for //collisions, then this function will tell us the runtimes of each and which is
//faster for the test
void insertionCollisions()
{
    unordered_map<U, U> mySTLHash;

    // vaiable to get size from user
    int input = 0;

    // clear the screen of the menu and display this new one for the size
    system("cls");
    cout << "The integer load sizes to choose from are: " << endl;
    cout << "  10" << endl;
    cout << "  100" << endl;
    cout << "  1,000" << endl;
    cout << "  5,000" <<endl;
    cout << "  10,000" << endl;
    cout << "  15,000" << endl;
    cout << "  20,000" << endl;
    cout << "  25,000" << endl;
    cout << "  30,000" << endl;
    cout << "  35,000" << endl;
    cout << "  40,000" << endl;
    cout << "  45,000" << endl;
    cout << endl;
    cout << " what size to use? ";

    do
    {
        cin >> input;
        //quad probe object
        QuadProbing qp(input);
        // Gregory Brown's object for his Linear probe
        gjb_hash* hashTable = new gjb_hash(input);

        //This validates the user input for size is an integer.
        while(cin.fail())
        {
            //Try again if an option isn't chosen
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "* Please select an option from the menu * ";
            cin >> input;
        }
        cout << "The bigger sizes might take some time to calculate.\nOne moment please..." << endl;
        // validate the option to make sure its from the menu
        if(input == 10 ||input == 100 ||input == 1000 || input == 5000 || input == 10000 || input == 15000 || input == 20000 || input == 25000 || input == 30000 || input == 35000 || input == 40000 || input == 45000)
        {
            //Record insertion for quad probe
            auto startQuad = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < input; ++i)
            {
                //qp.insert(i);
                qp.insert(std::rand() % 1000);
            }

            auto endQuad = std::chrono::high_resolution_clock::now();

            //Record insertion for linear probe
            auto startLinear = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < input; ++i)
            {
                //hashTable->insert(i,i);
                hashTable->insert(std::rand() % 1000, std::rand() % 1000);
            }

            auto endLinear = std::chrono::high_resolution_clock::now();

            //Record insertion for STL hashmap
            auto startSTL = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < input; ++i)
            {
              // mySTLHash.insert(std::pair<U, U>{input, input});
               mySTLHash.insert(std::pair<U, U>{std::rand() % 1000, std::rand() % 1000});
            }

            auto endSTL = std::chrono::high_resolution_clock::now();

            //cast to micro seconds .
            auto durationQuad = std::chrono::duration_cast<std::chrono::microseconds>(endQuad - startQuad);
            auto durationLinear = std::chrono::duration_cast<std::chrono::microseconds>(endLinear - startLinear);
            auto durationSTL = std::chrono::duration_cast<std::chrono::microseconds>(endSTL - startSTL);
            //variables to use if else statement to determine winners
            double q = std::chrono::duration<double>(durationQuad).count();
            double l = std::chrono::duration<double>(durationLinear).count();
            double s =  std::chrono::duration<double>(durationSTL).count();
            //now display the winner, second place, and third place.
            cout << endl;
            cout << "1st: ";

            //Quad 1st.
            if(q <= l && q <= s )
            {
                cout << "QuadProbe " << q << " microseconds\n2nd: ";

                //Linear is 2nd.
                if(l <= s)
                {
                    cout << "LinearProbe " << l << " microseconds\n3rd: STL in " << s << " microseconds" << endl;
                }
                //STL hashmap is 2nd.
                else
                {
                    cout << "STL in " << s << " microseconds\n3rd: LinearProbe in " << l << " microseconds" << endl;
                }
            }
            //Linear is 1st.
            else if(l <= q && l <= s)
            {
                cout << "LinearProbe in " << l << " microseconds\n2nd: ";

                // Quad is 2nd.
                if(q <= s)
                {
                    cout << "QuadProbe " << q << " microseconds\n3rd: STL in " << s << " microseconds" << endl;
                }
                //STL is 2nd.
                else
                {
                    cout << "STL in " << s << " microseconds\n3rd: QuadProbe   in " << q << " microseconds" << endl;
                }
            }
            //STL is 1st.
            else
            {
                 cout << "STL in " << s << " microseconds\n2nd: ";

                 //Quad is 3rd.
                 if(q <= l)
                 {
                    cout << "QuadProbe " << q << " microseconds\n3rd: LinearProbe in " << l << " microseconds" << endl;
                 }
                 //Linear is 2nd.
                 else
                 {
                    cout << "Linear in " << l << " seconds\n3rd: QuadProbe in " << q << " microseconds" << endl;
                 }
            }
            cout << endl;
        }
        // error message if user puts in size not on menu
        else
        {
           cout << "* Please select an option from the menu * ";
        }
    }
    // end of do while loop for validation of the size
    while(input != 10 && input != 100 && input!= 1000 && input != 5000 && input != 10000 && input != 15000 && input != 20000 && input != 25000 && input != 30000 && input != 35000 && input != 40000  && input != 45000);
}
//pre: menu function must exist, trees must exist
//post: We can now use this function to select an amount of integers to insert and then delete and run a test between the hashes and this function will tell us the runtimes of
//each and which is faster for the test
void searching()
{
    // the stl hashMap
    unordered_map<U, U> mySTLHash;

    // vaiable to get size from user
    int input = 0;
    int key = 0;

    // clear the screen of the menu and display this new one for the size
    system("cls");
    cout << "The integer load sizes to choose from are: " << endl;
    cout << "  10" << endl;
    cout << "  100" << endl;
    cout << "  1,000" << endl;
    cout << "  5,000" <<endl;
    cout << "  10,000" << endl;
    cout << "  15,000" << endl;
    cout << "  20,000" << endl;
    cout << "  25,000" << endl;
    cout << "  30,000" << endl;
    cout << "  35,000" << endl;
    cout << "  100,000,000" << endl;
    cout << endl;
    cout << " what size to use? ";

    do{
        cin >> input;
        QuadProbing qp(input);
        gjb_hash* hashTable = new gjb_hash(input);


        //This validates the user input for size is an integer.
        while(cin.fail())
        {
            //Try again if an option isn't chosen
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "* Please select an option from the menu * ";
            cin >> input;
        }
        cout << "The bigger sizes might take some time to calculate.\nOne moment please..." << endl;
//        // validate the option to make sure its from the menu
        if(input == 10 ||input == 100 ||input == 1000 || input == 5000 || input == 10000 || input == 15000 || input == 20000 || input == 25000 || input == 30000 || input == 35000
            || input == 100000000)
        {
            // populate the structures
            for(auto i = 0; i < input; ++i)
            {
                qp.insert(i);
            }
            for (int i = 0; i < input; ++i)
            {
                hashTable->insert(i,i);
            }
            for (int i = 0; i < input; ++i)
            {
                mySTLHash.insert(std::pair<U, U>{input, input});
            }
            do{
                cout << "Enter key 0 - " << input -1 << " to search for: " << endl;
                cout << "Enter key ";
                cin >> key;

                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << " \n* Please enter a number *\n" << endl << endl;
                }
            }while(cin.fail());
            // record runtime Quad
            auto startQuad = std::chrono::high_resolution_clock::now();

            qp.search(key);

            auto endQuad = std::chrono::high_resolution_clock::now();

            //Record runtime Linear
            auto startLinear = std::chrono::high_resolution_clock::now();

            hashTable->search_key(key);

            auto endLinear = std::chrono::high_resolution_clock::now();

            //Record  runtime STL
            auto startSTL = std::chrono::high_resolution_clock::now();

             mySTLHash.find(key);

            auto endSTL = std::chrono::high_resolution_clock::now();

            //cast to micro seconds .
            auto durationQuad = std::chrono::duration_cast<std::chrono::microseconds>(endQuad - startQuad);
            auto durationLinear = std::chrono::duration_cast<std::chrono::microseconds>(endLinear - startLinear);
            auto durationSTL = std::chrono::duration_cast<std::chrono::microseconds>(endSTL - startSTL);
            //variables to use if else statement to determine winners
            double q = std::chrono::duration<double>(durationQuad).count();
            double l = std::chrono::duration<double>(durationLinear).count();
            double s =  std::chrono::duration<double>(durationSTL).count();
            //now display the winner, second place, and third place.
            cout << endl;
            cout << "1st: ";

            //Quad 1st.
            if(q <= l && q <= s )
            {
                cout << "QuadProbe " << q << " microseconds\n2nd: ";

                //Linear is 2nd.
                if(l <= s)
                {
                    cout << "LinearProbe " << l << " microseconds\n3rd: STL in " << s << " microseconds" << endl;
                }
                //STL hashmap is 2nd.
                else
                {
                    cout << "STL in " << s << " microseconds\n3rd: QuadProbe in " << q << " microseconds" << endl;
                }
            }
            //Linear is 1st.
            else if(l <= q && l <= s)
            {
                cout << "LinearProbe in " << l << " microseconds\n2nd: ";

                // Quad is 2nd.
                if(q <= s)
                {
                    cout << "QuadProbe " << q << " microseconds\n3rd: STL in " << s << " microseconds" << endl;
                }
                //STL is 2nd.
                else
                {
                    cout << "STL in " << s << " microseconds\n3rd: QuadProbe   in " << q << " microseconds" << endl;
                }
            }
            //STL is 1st.
            else
            {
                 cout << "STL in " << s << " microseconds\n2nd: ";

                 //Quad is 3rd.
                 if(q <= l)
                 {
                    cout << "QuadProbe " << q << " microseconds\n3rd: LinearProbe in " << l << " microseconds" << endl;
                 }
                 //Linear is 2nd.
                 else
                 {
                    cout << "Linear in " << l << " seconds\n3rd: Quad in " << q << " microseconds" << endl;
                 }
            }
            cout << endl;
        }
        // error message if user puts in size not on menu
        else
        {
           cout << "* Please select an option from the menu * ";
        }
    }
    // end of do while loop for validation of the size
    while(input != 10 && input != 100 && input!= 1000 && input != 5000 && input != 10000 && input != 15000 && input != 20000 && input != 25000 && input != 30000 && input != 35000
           && input != 100000000);
}

//pre: menu function must exist, trees must exist
//post: We can now use this function to select an amount of integers to insert and then delete and run a test between the hashes and this function will tell us the runtimes of
//each and which is faster for the test
void deleting()
{
   // the stl hashMap
    unordered_map<U, U> mySTLHash;

    // vaiable to get size from user
    int input = 0;
    int key = 0;

    // clear the screen of the menu and display this new one for the size
    system("cls");
    cout << "The integer load sizes to choose from are: " << endl;
    cout << "  10" << endl;
    cout << "  100" << endl;
    cout << "  1,000" << endl;
    cout << "  5,000" <<endl;
    cout << "  10,000" << endl;
    cout << "  15,000" << endl;
    cout << "  20,000" << endl;
    cout << "  25,000" << endl;
    cout << "  30,000" << endl;
    cout << "  35,000" << endl;
    cout << "  45,000" << endl;
    cout << "  1,000,000" << endl;
    cout << endl;
    cout << " what size to use? ";

    do{
        cin >> input;
        QuadProbing qp(input);
        gjb_hash* hashTable = new gjb_hash(input);

        //This validates the user input for size is an integer.
        while(cin.fail())
        {
            //Try again if an option isn't chosen
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "* Please select an option from the menu * ";
            cin >> input;
        }
        cout << "The bigger sizes might take some time to calculate.\nOne moment please..." << endl;
//        // validate the option to make sure its from the menu
        if(input == 10 ||input == 100 ||input == 1000 || input == 5000 || input == 10000 || input == 15000 || input == 20000 || input == 25000 || input == 30000 || input == 35000 || input == 45000
            || input == 1000000)
        {
            // populate the structures
            for(auto i = 0; i < input; ++i)
            {
                qp.insert(i);
            }
            for (int i = 0; i < input; ++i)
            {
                hashTable->insert(i,i);
            }
            for (int i = 0; i < input; ++i)
            {
                mySTLHash.insert(std::pair<U, U>{i, i});
            }

            // record runtime Quad
            auto startQuad = std::chrono::high_resolution_clock::now();

            for(int i = 0; i < input; ++i)
            {
                // this function preforms VERY slow after 45,000 so allow the other two to race and leave this one out after 45,000.
                if(input <= 45000)
                {
                    qp.deletion(i);
                }
            }

            auto endQuad = std::chrono::high_resolution_clock::now();

            //Record runtime Linear
            auto startLinear = std::chrono::high_resolution_clock::now();

            for(int i = 0; i < input; ++i)
            {
                hashTable->delete_key(i);
            }

            auto endLinear = std::chrono::high_resolution_clock::now();

            //Record  runtime STL set
            auto startSTL = std::chrono::high_resolution_clock::now();

            for(int i = 0; i < input; ++i)
            {
                mySTLHash.erase(i);
            }

            auto endSTL = std::chrono::high_resolution_clock::now();

            //cast to micro seconds .
            auto durationQuad = std::chrono::duration_cast<std::chrono::microseconds>(endQuad - startQuad);
            auto durationLinear = std::chrono::duration_cast<std::chrono::microseconds>(endLinear - startLinear);
            auto durationSTL = std::chrono::duration_cast<std::chrono::microseconds>(endSTL - startSTL);
            //variables to use if else statement to determine winners
            double q = std::chrono::duration<double>(durationQuad).count();
            double l = std::chrono::duration<double>(durationLinear).count();
            double s =  std::chrono::duration<double>(durationSTL).count();
            //now display the winner, second place, and third place.
            cout << endl;
            cout << "1st: ";

            //Quad 1st.
            if(q <= l && q <= s )
            {
                cout << "QuadProbe " << q << " microseconds\n2nd: ";

                //Linear is 2nd.
                if(l <= s)
                {
                    cout << "LinearProbe " << l << " microseconds\n3rd: STL in " << s << " microseconds" << endl;
                }
                //STL hashmap is 2nd.
                else
                {
                    cout << "STL in " << s << " microseconds\n3rd: QuadProbe in " << q << " microseconds" << endl;
                }
            }
            //Linear is 1st.
            else if(l <= q && l <= s)
            {
                cout << "LinearProbe in " << l << " microseconds\n2nd: ";

                // Quad is 2nd.
                if(q <= s)
                {
                    cout << "QuadProbe " << q << " microseconds\n3rd: STL in " << s << " microseconds" << endl;
                }
                //STL is 2nd.
                else
                {
                    cout << "STL in " << s << " microseconds\n3rd: QuadProbe   in " << q << " microseconds" << endl;
                }
            }
            //STL is 1st.
            else
            {
                 cout << "STL in " << s << " microseconds\n2nd: ";

                 //Quad is 3rd.
                 if(q <= l)
                 {
                    cout << "QuadProbe " << q << " microseconds\n3rd: LinearProbe in " << l << " microseconds" << endl;
                 }
                 //Linear is 2nd.
                 else
                 {
                    cout << "Linear in " << l << " seconds\n3rd: Quad in " << q << " microseconds" << endl;
                 }
            }
            cout << endl;
        }
        // error message if user puts in size not on menu
        else
        {
           cout << "* Please select an option from the menu * ";
        }
    }
    // end of do while loop for validation of the size
    while(input != 10 && input != 100 && input!= 1000 && input != 5000 && input != 10000 && input != 15000 && input != 20000 && input != 25000 && input != 30000 && input != 35000 && input != 45000
           && input != 1000000);
}

//pre: Hash table class "QuadProbing" must exist.
//post: The program can now insert into the hash table using quadratic probing.
void QuadProbing::insert(int key)
{
    int hashValue = key % this->size_t;

    // insert from the minimum value
    if (this->hashTable[hashValue] == INT_MIN)
    {
        // if no collision then insert
        this->hashTable[hashValue] = key;
        // cout << key << " inserted into hash table" << endl;
    }
    else
    {
        // if there is collision, iterate through every quadratic value:
        for (int i = 0; i < this->size_t; i++)
        {
            // quadratic function
            int newHashValue = (hashValue + i * i) % this->size_t;
            if (hashTable[newHashValue] == INT_MIN)
            {
                hashTable[newHashValue] = key;
                return;
            }
        }// out of space
        cout << "no slot in the hash table for this key." << endl;
    }
}
//pre: Hash table class called QuadProbing must exist, insert method must exist and be called to have values in hash table.
//post: The program can now search through the hash table for quadratic values and return and display if the value is in the table.
int QuadProbing::search(int key)
{
    int hashValue = key % this->size_t;
    //iterate through every quadratic value
    for (int i = 0; i < this->size_t; i++)
    {
        int newHashValue = (hashValue + i * i) % this->size_t;
        // if found then display and return found
        if (hashTable[newHashValue] == key)
        {
            //cout << key << " found in table" << endl;
            return 1;
        }
        // if not found then display and return not found
        else if ((hashTable[newHashValue] != key) )
        {
            cout << "key not found in table" << endl;
            return -1;
        }
    }
    return 1;
}

//pre: Hash table class called QuadProbing must exist, insert method must exist and be called to have values in hash table, search function must exist to search for existing keys in the table.
//post: The program can now search for and delete an key in the table and replace it with a tombstone.
void QuadProbing::deletion(int key)
{
    int hashValue = key % this->size_t;
    // first search for the key in the table
    if(search(key) == -1)
    {
        cout << "key not in table, cannot delete it" << endl;
    }
    else
    {
       // cout << key << " deleted from hash table " << endl;
        int newHashValue;
        for (int i = 0; i < this->size_t; i++)
        {
            int newHashValue = (hashValue + i * i) % this->size_t;
            // if found then display and return found
            if (hashTable[newHashValue] == key)
            {
                // replace key value with a tombstone (delete value)
                key = -1;
                hashTable[newHashValue] = key;
            }
        }
        // uncomment to see that the delete function is working properly (you will see a -1 in the position of the key)
        //cout << "key deleted, here is the new table: " << endl;
        //displayTable();
    }
}
//pre: Hash table class called QuadProbing must exist, insert method must exist and be called to have values in hash table
//post: The program can now display the values in the hash table with this function
// NOTE: this function is only to check that the quadprobing methods are functioning correctly.
void QuadProbing::displayTable()
{
    cout << "The hash table values are: ";
    for (int i = 0; i < this->size_t; i++)
    {
        if (this->hashTable[i] == INT_MIN)
        {
            cout << "-";
        }
        else
        {
            cout << this->hashTable[i];
        }
        if (i != this->size_t - 1)
        {
            cout << ", ";
        }
    }
}
