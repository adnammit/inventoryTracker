
//******************************************************
//
// 		WAREHOUSE MANAGER ::
//			A program for the management of inventory
// 		AMANDA RYMAN :: amanda.ryman@gmail.com
//		Portland State University :: Computer Science 162
// 		AUGUST 16, 2013 
//
//******************************************************
//
// 		NODE FUNCTIONS:
//
//			The node constructor implements each node with 
//	null values for the struct objects of node. The 
// 	destructor deletes dynamically allocated data.
//			
//			The remaining node functions typically perform
//	the most minute actions of the program: those involving 
//	the actual data of the inventory nodes such as reading 
//	in a name, displaying an item, or writing out individual
//	data to a file.
//
//******************************************************
//
//		ASSOCIATED FILES:
//			-- "main.cpp"
// 			-- "node.cpp"
//			-- "product.cpp"
// 			-- "inventory.h"
//
//******************************************************

#include "inventory.h"



//*************
//	CONSTRUCTOR

node::node()
{
	name=NULL;			
	quantity=0;
	cost=0.0;
	msrp=0.0;
	vendor=NULL;
	next=NULL;
}



//************
//	DESTRUCTOR

node::~node()
{
	delete[]name;
	delete[]vendor;
	if (next)
		delete next;
}



//****************************************
//			LOAD EACH MEMBER ITEM FROM THE 
//				EXTERNAL FILE
//
//	Sets up the initial NULL values for 
//		product class items

void node::loadEach(ifstream & read)
{
	char tempN[100];
	int tempQ=0;
	float tempC=0.0;
	float tempM=0.0;
	char tempV[100];

	read.get(tempN,100,'|');
	read.ignore(100,'|');
	read >> tempQ;
	read.ignore();
	read >> tempC;
	read.ignore();
	read >> tempM;
	read.ignore();
	read.get(tempV,100,'|');
	read.ignore(100,'|');

	name=new char[strlen(tempN)+1];
	strcpy(name, tempN);
	quantity=tempQ;
	cost=tempC;
	msrp=tempM;
	vendor=new char[strlen(tempV)+1];
	strcpy(vendor, tempV);
}



//**********************************
//			DISPLAY EACH MEMBER ITEM

void node::displayEach()
{
	cout 
		<< "\n\tNAME:\t\t" << name 
		<< "\n\tQUANTITY \t" << quantity
		<< "\n\tCOST:\t\t$" << cost 
		<< "\n\tITEM MSRP:\t$" << msrp
		<< "\n\tVENDOR:\t\t" << vendor << endl;
}



//************************************************
//			INCREASE INDIVIDUAL PRODUCT QUANTITIES
//
//	Gets the amount of quantity increase from the user
//		and changes the budget to reflect the purchase.

void node::increaseItem(float & budget)
{
	// 'num' stores the amount to increase the inventory by.
	int num=0;
	// 'totalItem' will track the item's value in order to change
	//		the budget accordingly.
	float totalItem=0.0;

// Display the item for the user:
	cout << "You have selected:\t" << name 
		<< "\nThere are currently " << quantity << " in stock."
		<< "\nHow many would you like to add to the inventory?\t";
	cin >> num;
	cin.ignore(100,'\n');


// -- Calculating how much that item costs and checking
//		that we can afford it:
	totalItem=num*cost;
	while (totalItem>budget || num<1)
	{
		if (num<1)
			cout << "Try a new number!";
		else
			cout << "That's all of our money! Try a smaller quantity:\t";
		cin >> num;
		cin.ignore(100,'\n');
		totalItem=num*cost;
	}

// -- Subtract the total cost from our balance and increase the 
//		quantity of the item:
	budget-=totalItem;
	quantity += num;
	cout << "\nYou have changed the quantity of " << name 
		<< " to " << quantity << "." << endl;
}




//************************************************
//			INCREASE INDIVIDUAL PRODUCT QUANTITIES
//
//	Gets the amount of quantity increase from the user
//		and changes the budget to reflect the purchase.

void node::fillOrder(float & budget)
{
	// 'num' stores the amount to increase the inventory by.
	int num=0;
	// 'totalItem' will track the item's value in order to change
	//		the budget accordingly.
	float totalItem=0.0;

// -- Display the item for the user:
	cout << "You have selected:\t" << name 
		<< "\nThere are currently " << quantity << " in stock."
		<< "\nHow many would you like to add to the inventory?\t";
	cin >> num;
	cin.ignore(100,'\n');

// -- If the user tries to send more than we have,
// 		we'll ask again:
	while (num>quantity)
	{
		cout << "That's too many! Please enter a smaller quantity:\t";			
		cin >> num;
		cin.ignore(100,'\n');
	}

// -- Calculate how much we make in the sale
//		add it to our balance, and 
// 		change the quantity:
	totalItem=num*msrp;
	budget+=totalItem;
	quantity-=num;
	cout << "\nYou have " << quantity 
		<< " of product " << name << " remaining." << endl;
}





//****************************************
//			READ EACH MEMBER ITEM FROM THE 
//				USER INPUT
//
//	Temporary values for data are initialized
//		and then

void node::createEach(float & budget)
{
// Initialize temporary variables:
	char tempN[100];
	int tempQ=0;
	float tempC=0;
	float tempM=0;
	char tempV[100];
	// The value for all items (quantity*cost):
	float totalItem=0.0;

// NAME
	cout << "\n\n[PRODUCT NAME]\t\t";
	cin.get(tempN,100,'\n');
	cin.ignore(100,'\n');
	upperCase(tempN);
	
// QUANTITY
	cout << "[STARTING QUANTITY]\t";
	cin >> tempQ;
	cin.ignore(100,'\n');

// COST
	cout << "[WHOLESALE COST]\t";
	cin >> tempC;
	cin.ignore(100,'\n');

// MSRP
	cout << "[MSRP]\t\t\t";
	cin >> tempM;
	cin.ignore(100,'\n');

// VENDOR
	cout << "[VENDOR]\t\t";	
	cin.get(tempV, 100, '\n');
	cin.ignore(100,'\n');
	upperCase(tempV);

// Copy temporaries over to the inventory:
	name=new char[strlen(tempN)+1];
	strcpy(name, tempN);
	quantity=tempQ;
	cost=tempC;
	msrp=tempM;
	vendor=new char[strlen(tempV)+1];
	strcpy(vendor, tempV);

// Change the balance to reflect the new entry:
	totalItem = quantity * cost;
	budget -= totalItem;
}



//****************************************
//			LOAD EACH MEMBER ITEM FROM THE 
//				EXTERNAL FILE
//
//	Sets up the initial NULL values for 
//		product class items

void node::saveEach(ofstream & write)
{
	write << name << '|'
		<< quantity << '|'
		<< cost << '|'
		<< msrp << '|'
		<< vendor << '|';
}



//***********************************
//			READ IN NEW ITEM DETAIL:
//
//	Makes the first character in a string of 
// 		characters pointed to by a pointer 
//		to upper case.

void node::upperCase(char *word)
{
	for (int i=0; word[i]!='\0' && i<strlen(word); ++i)
	{	if (i==0)
			word[i]=toupper(word[i]);
		else
		{
			if (word[i]!=' ' && word[i-1]==' ')	
				word[i]=toupper(word[i]);
		}	
	}
}



//**************
//			END.
//**************
