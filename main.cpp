

#include "Andrade_h.h"

int main()
{
	// Declare Variables
	node name;

	// Functions
	GetNames();			// Gets the names from the text file names.txt and removes spaces and outputs to blank.txt
	ChangeNames(name);	// Store first, last, middle names in a linked list
	Output(name);		// Prints header and old and new names

	return 0;
}

// Function that gets one character at a time from file and removes extra spaces
void GetNames()
{	
	// Declares and opens names.txt and a blank.txt
	ifstream infile;
	ofstream outfile;
	infile.open("names.txt");
	outfile.open("blank.txt");

	// Declares and set char variables to 0
	char current = 0;	// Starts at the beginning of name
	char previous = 0;	// Used to compare current to previous node with char
	
	while (infile.get(current))// Grabs one char at a time and stores in current (grabs spaces as well)
	{
		if (current == ' ' && previous == ' ')//Checks to see if there are 2 spaces in a row
		{	
			// Does nothing
		}
		else 
		{
			previous = current;		//Sets current to previous
			outfile << previous;	//Outputs to blank.txt
		}	
	}	

	// Closes in and out files
	infile.close();
	outfile.close();
}			

//Function that creates a linked list from the names grabbed from GetNames
void ChangeNames(node& name)
{
	// Declares and opens blank.txt
	ifstream infile;
	infile.open("blank.txt");

	// Initializes pointers first and last equal to NULL
	name.first = NULL;
	name.last = NULL;

	// Loop while not at end of file
	while (!infile.eof())
	{	
		if (infile.peek() == '\n')	//Checks if NEXT node is the end of the line
		{
			name.temp = '\n';				// Puts endline into temp
			name.current = new node;		// Creates a new node
			name.current->info = name.temp;	// Puts the char in the new node's info
			name.current->link = NULL;		// Sets new node's link to null
		}
		else						//Grabs the char
		{
			infile.get(name.temp);			// Gets char from file and stores it in temp
			name.current = new node;		// Creates a new node
			name.current->info = name.temp;	// Puts the char in the new node's info
			name.current->link = NULL;		// Sets new node's link to NULL
		}

		if (name.first == NULL)		//If it's at the first node
		{
			name.first = name.current;		// Makes the "first" pointer point to the first node
			name.last = name.current;		// Makes the "last pointer point to the first node
		}
		else if (name.temp == '\n')	//If it's at the end of the line
		{
			name.last->link = name.current;	// Inserts the new node to the end of the list
			name.last = name.current;		// Makes the "last" pointer point to the new node
			infile >> name.temp;			// Stores char in temp
			name.current = new node;		// Creates a new node
			name.current->info = name.temp;	// Stores the char in the new node
			name.current->link = NULL;		// Sets new node's link to NULL
			name.last->link = name.current;	// Inserts the new node to the end of the list
			name.last = name.current;		// Makes the "last" pointer point to the new node
		}
		else
		{
			name.last->link = name.current;	// Inserts the new node to the end of the list
			name.last = name.current;		// Makes the end point to the new node
		}
	}

	// Sets newFirst pointer and current pointer equal to the beginning pointer
	name.newFirst = name.first;
	name.current = name.newFirst;

	// Loops until current equals the last node
	while (name.current != name.last)
	{
		// Checks to see if what's in current's info equals a comma, endline, or the last node
		if (name.current->info != ',' && name.current->info != '\n' && name.current != name.last)
		{
			// While loop that moves current forward as long as that current's info does not equal a comma, endline, or last node
			while (name.current->info != '\n' && name.current->info != ',' && name.current != name.last)
			{
				name.current = name.current->link;
			}
		}

		// If a comma is found then leave order 
		else if (name.current->info == ',')		// If comma: Advances current to the endline and sets newFirst equal to current
		{
			// While loop moves current forward until it reaches endline or last node
			while (name.current->info != '\n' && name.current->link != name.last)
			{
				name.current = name.current->link;	// Sets current link to name.current
			}

			// All names are in correct order if they are before the newFirst pointer
			name.newFirst = name.current;

		}

		// Runs if current's info is a \n
		else if (name.current->info == '\n')
		{
			// Checks to see if name is in correct order
			if (name.newFirst == name.current)		
			{
				name.current = name.current->link;	// moves current one link to start new name
			} // End of if

			// If names are not in the correct order, changes last to first
			else if (name.newFirst != name.current)
			{
				name.newLast = name.current;				// Makes newLast point to endline
				name.current = new node;					// Creates a new node
				name.current->info = ' ';					// Adds a space in the front of the name
				name.current->link = name.newFirst->link;	// Makes the new node point to first node
				name.newFirst->link = name.current;			// Makes newFirst point to space
				name.current = new node;					// Creates a new node
				name.current->info = ',';					// Adds a comma in the front of space node
				name.current->link = name.newFirst->link;	// Makes the new node point to first node
				name.newFirst->link = name.current;			// Makes newFirst point to comma
				name.check = name.newFirst->link;			// Sets check equal to the front node
				
				// Do/While loop that moves last name to front one node at a time
				do
				{
					// When check->link->info equals \n, it points check back to the front node
					if (name.check->link->info == '\n')
					{
						name.check = name.newFirst->link;	// Puts newFirst->link into name.check
						
						// Moves check forward until check->link->link->info equals \n
						while (name.check->link->link->info != '\n')	
						{
							name.check = name.check->link;
						} // End of while
					} // End of if

					// Used for processing the very first name
					else
					{
						// Moves check forward until check->link->link->info equals \n
						while (name.check->link->link->info != '\n')
						{
							name.check = name.check->link;
						}	// End of while
					}	// End of if

					name.temp = name.check->link->info;				// Stores info into temp
					name.del = name.check->link;					// Points del to node to be deleted
					name.check->link = name.del->link;				// Skips node to be deleted
					delete name.del;								// Deletes node

					// If temp equals ' ' (space) then the name is in correct order
					if (name.temp != ' ')
					{
						name.current = new node;				// Creates new node
						name.current->info = name.temp;				// Stores temp into info
						name.current->link = name.newFirst->link;	// Points link to front node
						name.newFirst->link = name.current;			// Points newFirst to new node
					} // End of if

					// When done processing name, breaks out of loop 
					else
					{
						break;
					}	// End of else
				}while (name.temp != ' ');	// End Do/While loop
			} // End of else if
		} // End of else if
	} // End of while

	infile.close();	// Closes infile

} // End of ChangeNames function

void Output(node name)
{
	// Declares and opens infile
	ifstream infile;
	infile.open("names.txt");

	// Declares and sets values to string variables for headers
	string Line1 = "------------------------------";
	string Line2 = "------------------------------";

	// Declares string array that stores each name as is in the Names.txt file
	string printName[10];

	// Sets current equal to first to output the first node
	name.current = name.first;

	// Prints header
	cout << "Original" << setw(44) << "Changed\n" << Line1 << setw(45) << Line2 << "\n";
	
	// For loop that outputs one line at a time
	for (int index = 0; index < 10; index++)
		{
			// Grabs complete line as is and stores it into array
			getline(infile, printName[index]);

			// Prints Original Name
			cout << left << printName[index] << setw(44 - printName[index].size()) << ' ';

			// While loop that prints Changed name
			while (name.current->info != '\n' && name.current != name.last)
			{
				cout << name.current->info;
				name.current = name.current->link;
			} // End of while

			
			name.current = name.current->link;		// Moves current forward one link to skip endline
			cout << endl;							// Moves line down
		}
	
	// Closes infile
	infile.close();
} //End of Output function