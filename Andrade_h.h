

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

// Declare Struct
struct node
{
// Declare structvariables and pointers
	char info, temp;
	node *current, *first, *last, *link, *newFirst, *newLast, *check, *del;
};

// Function Prototypes
void GetNames();
void ChangeNames(node& name);
void Output(node name);