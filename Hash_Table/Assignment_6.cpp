/*************************************************************************************************************************
Programming Assignment CS5343
Implement Hash table.
Pick 20 random words.  Each word must be of different lengths, maximum length 8 and minimum length 3. The words will be 
of letters a-zA-Z and the space character.  Insert them into a hash table.  
You can use a library for only the hash function.
The collision resolution scheme should be open addressing - quadratic.
Initially the table size is 31.  The program should increase the table size and rehash at load factor of .5
At the end print the total number of collisions you get.
Submit your code.

*************************************************************************************************************************/
#include <iostream>
#include <string>

using namespace std;

class Hash
{
private:
	//set an array of strings to initialize
	string *table;
	//initialize table size
	int table_size = 31;
	//values to hold the count of collisions and the count for the load factor
	int load = 0;
	int coll = 0;
	//method to return the new size of the table, doubles the size then gets the next prime number.
	int get_size(int size)
	{
		int newsize = size * 2;
		bool isPrime = false;
		while (isPrime != true)
		{
			isPrime = true;
			newsize = newsize++;
			int y = newsize / 2;
			for (int i = 2; i < y; i++)
			{
				if (newsize % i == 0)
					isPrime = false;
			}
		}
		return newsize;
	}
	//method to increase the size of the table.
	void increase_Table()
	{
		//initialize a new string table to hold the current hash table.
		string *temp;
		temp = new string[table_size];
		temp = table;
		//get the new table size.
		int size = table_size;
		table_size = get_size(size);
		//reset counter for load factor
		load = 0;
		//initialize the new hash table with the new size and empty cells.
		table = new string[table_size];
		for (int i = 0; i < table_size; i++)
			table[i] = "";
		//rehash the old table values to the new table.
		for (int i = 0; i < size; i++)
		{
			if (temp[i] != "")
			{
				insert(temp[i]);
			}
		}
	}
	//hash function to get the key from a string.  The function adds up all the integer values of each character in the
	//string, multiplies the value by its position, sums the values then mods value with table_size.
	int get_key(string str)
	{
		int key = 0;
		for (int i = 0; i != str.length(); i++)
		{
			char ch = str.at(i);
			int y = static_cast<int>(ch);
			key = key + (y *(i + 1));
		}
		return (key % table_size);
	}
	//return the load factor, as long as its less than 0.5 no resize.
	double get_load_factor()
	{
		return ((double)load / (double)table_size);
	}
	//method to check the load factor is less than 0.5
	bool check_load_factor()
	{
		if (get_load_factor() < 0.5)
			return true;
		else
			return false;
	}

public:
	
	//constructor
	Hash()
	{
		table = new string[table_size];

		for (int i = 0; i < table_size; i++)
		{
			table[i] = "";
		}
	}
	//method to insert a value into the table using the hash function, collisions solved using quadratic probing, collisions counted.
	void insert(string str)
	{
		//get the key of the word, set a boolean value for false and incrementer i to 1, used for collisions
		int key = get_key(str);
		bool empty = false;
		int i = 1;
		//if the load factor is less than 0.5 insert, else resize the table then insert.
		if (check_load_factor() == true)
		{
			//if the entry at the key is empty, add the word, else use quadratic probing to find an empty cell.
			if (table[key] == "")
			{
				table[key] = str;
				load++;
			}
			else
			{
				while (empty == false)
				{
					key = key + (i*i);
					if (key > table_size)
						while (table_size <= key)
							key = key - table_size;
					if (table[key] == "")
						empty = true;
					i++;
				}
				table[key] = str;
				load++;
				coll++;
			}
		}
		else
		{
			cout << "load size is " << get_load_factor() << " increasing table size and rehashing.\n";
			cout << "number of collisions at this point is: " << coll << endl;
			increase_Table();
			insert(str);
		}
	}
	//method to insert an array of words.
	void insert_list(string str[], int arr_size)
	{
		for (int i = 0; i < arr_size; i++)
			insert(str[i]);
	}
	
	//method to display the table.
	void display_table()
	{
		cout << endl;
		cout << "The table has the following values and keys: " << endl;
		for (int i = 0; i < table_size; i++)
		{
			if (table[i] != "")
			{
				cout << "Entry at " << i << " is " << table[i] << ", its key is " << get_key(table[i]) << endl;
			}
		}
		cout << endl << "Total number of collisions is: " << coll << endl;
		cout << "Final table size is: " << table_size << endl;
		cout << "Final load factor is: " << get_load_factor() << endl << endl;
		cout << endl;
	}

};

int main()
{
	cout << "This program implements a hash table for words made up of values a-z and A-z.  The word length is minimum";
	cout << " 3 letters and maximum of 8 letters.  The hash table initial size is 31 and increases the size when the";
	cout << " load factor is greater than 0.5.  Collisions are handled through quadratic probing.\n\n\n";
	//initialize an array of strings to hold the 20 words to be inserted into the hash table.
	string random_Words[20] = { "cat", "dog", "horse", "swine", "bull", "heifer", "calf", "puppy", "kitten", "foal", "Red", "Blue",
	"Black", "Orange", "Yellow", "Purple", "Green", "Pink", "Brown", "Violet" };

	Hash hashTable;
	hashTable.insert_list(random_Words, 20);
	hashTable.display_table();

	//initialize a new array of strings to hold 20 words to be inserted into the hash table.
	cout << endl << endl;
	cout << "New table and new words.\n\n";
	string arr_words[20] = {"Adverse", "Awarded", "quizzing", "buzzbait", "whizzers", "buzzkill", "zigzaggy", "fuzzball", "ScumBag", "JAZZY",
	"JACUZZI", "FRIZZIES", "EXCEPTED", "Blizzard", "WARMest", "armrest", "warrior", "Soldier", "random", "walking"};

	Hash hashTable2;
	hashTable2.insert_list(arr_words, 20);
	hashTable2.display_table();

	//for fun will try an array of 40 words combining both lists, to see the load factor and rehashing work.

	string arr2[40] = { "cat", "dog", "horse", "swine", "bull", "heifer", "calf", "puppy", "kitten", "foal", "Red", "Blue",
	"Black", "Orange", "Yellow", "Purple", "Green", "Pink", "Brown", "Violet", "Adverse", "Awarded", "quizzing", "buzzbait", 
	"whizzers", "buzzkill", "zigzaggy", "fuzzball", "ScumBag", "JAZZY",	"JACUZZI", "FRIZZIES", "EXCEPTED", "Blizzard", 
	"WARMest", "armrest", "warrior", "Soldier", "random", "walking" };

	cout << endl << endl << "New table combining both lists to see the resize and rehashing.\n\n";

	Hash hashTable3;
	hashTable3.insert_list(arr2, 40);
	hashTable3.display_table();
	

	getchar();
	return 0;
}