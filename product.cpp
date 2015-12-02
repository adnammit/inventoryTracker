
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
// 		PRODUCT FUNCTIONS:
//
//			The product constructor implements each product 
//	item with a head set to NULL. The destructor deletes 
// 	dynamically allocated data (the head).
//			
//			The remaining product functions perform subtasks 
//	for the main() function which involve loading and saving 
//	external files, and creating, adding to and traversing the 
//	linear linked list of inventory items. 
//
//		Manipulation of the actual data in the nodes is 
//	delegated to the node functions in ryman_node.cpp.
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

product::product()
{
	head=NULL;
}



//************
//	DESTRUCTOR

product::~product()
{
	if (head)
		delete head;
}



//******************************
//			LOAD INVENTORY ITEMS
//
//	Reads in product data from the 
//		external file.

bool product::load(ifstream & read)
{
	// If there's no head, make one:	
	if (!head)
	{
		head=new node;
	}
	// Set a current node to traverse as we read the file:
	node*current=head;
	// If there's no file to read, return false:
	read.peek();
	if (read.eof())
		return false;
	// Otherwise proceed to read as long as the next item is readable:
	else 
	{
		head->loadEach(read);
		read.peek();
		while (!read.eof())
		{
			current->next=new node;
			current->next->loadEach(read);
			current=current->next;
			current->next=NULL; // redundant?
			read.peek();
		}
	}
	return true;
}



//******************************
//			LOAD INVENTORY ITEMS
//
//	Reads in product data from the 
//		external file.

bool product::save(ofstream & write)
{
	if (!head)
		return false;
	// Set a current node to traverse as we read the file:
	node*current=head;

	// As long as there is something in the node, 
	//		we'll write it out:
	while (current)
	{
		current->saveEach(write);
		current=current->next;
	}
	return true;
}



//*********************************************
//			INCREASE QUANTITY OF EXISTING ITEMS
//
//	Allows user to select an item within the inventory
//		and increase it's quantity.
//	Also subtracts the cost of the item from the budget.

void product::addInventory(float & budget)
{
	cout << "\n[--ADD INVENTORY--]";
	cout << "\nSelect an item number to change:" << endl;
	do
	{
		// 'item' stores the item the user has selected to change.
		int item=0;
		// 'j' counts the number of items in the inventory so we can 
		//		return to the correct one after the user has chosen it.
		int j=0;

		node*current=head;
	// -- Display all the item names for the user:
		while (current)
		{
			cout << "\n[ITEM " << j+1 << "]  "
				<< current->name;
			++j;
			current=current->next;
		}
		cout << endl;	
		cin >> item;	
		cin.clear();								
		cin.ignore(100,'\n');

		// If item is not within the proper range, ask again:
		while (item>j || item<0)
		{
			cout << "That wasn't a valid item number. Try again!\t";
			cin >> item;
			cin.clear();
			cin.ignore(100,'\n');
		}

	// -- Go back through and find the correct item:
		// Change 'item' to be usable as an index:
		item -= 1;
		// Reset the variables 'current' and 'j' to go through the list:
		current=head;
		j=0;
		while (j<=item)
		{	
			if (j==item)
			{
				current->increaseItem(budget);
			}			
			current=current->next;
			++j;
		}
	// -- Do it again?
		cout << "\nWould you like to change another item? [Y/N]\t";
	}while (more());
}





//***************************************************
//								FILL A CUSTOMER ORDER
//
//	Allows user to select an item within the inventory
//		to be shipped to a customer.
//	Subtracts quantity from inventory and adds profit to 
//		the budget.

void product::fillOrder(float & budget)
{
	cout << "\n[--FILL ORDER--]";
	cout << "\nSelect an item to ship to a customer:\t" << endl;
	do
	{
		// 'item' stores the item the user has selected to change.
		int item=0;
		// 'j' counts the number of items in the inventory so we can 
		//		return to the correct one after the user has chosen it.
		int j=0;

		node*current=head;
	// -- Display all the item names for the user:
		while (current)
		{
			cout << "\n[ITEM " << j+1 << "]  "
				<< current->name;
			++j;
			current=current->next;
		}
		cout << endl;	
		cin >> item;	
		cin.clear();								
		cin.ignore(100,'\n');

		// If item is not within the proper range, ask again:
		while (item>j || item<0)
		{
			cout << "That wasn't a valid item number. Try again!\t";
			cin >> item;
			cin.clear();
			cin.ignore(100,'\n');
		}

	// -- Go back through and find the correct item:
		// Change 'item' to be usable as an index:
		item -= 1;
		// Reset the variables 'current' and 'j' to go through the list:
		current=head;
		j=0;
		while (j<=item)
		{	
			if (j==item)
			{
				current->fillOrder(budget);
			}			
			current=current->next;
			++j;
		}
		cout << "\n\nWould you like to fill another customer order? [Y/N]\t";
	}while (more());
}



bool product::createNew(float & budget)
{
	cout << "\n[--CREATE A NEW ITEM--]";

	// If there is no head, create a new node and enter an item into it:
	if (!head)
	{	head=new node;
		head->createEach(budget);
		return true;
	}

	// Otherwise look for a NULL node and enter an item into it:
	else
	{		
		// Set a current node to traverse as we read the file:
		node*current=head;
		
		// Start looking for an empty spot in the inventory. 
		while (current->next)
		{
			current=current->next;
		}
		current->next=new node;
		(current->next)->createEach(budget);
	}
	return true;
}



void product::displayAll()
{
	cout << "\n[--INVENTORY CONTENTS--]" << endl;

	node*current=head;

	while (current)
	{
		current->displayEach();
		current=current->next;
	}

	cout << "\n[--END INVENTORY--]" << endl;
}



//*************************
//			ENTER MORE DATA
//				OR CONTINUE?
//
// 	More() returns true to continue the
// 		loop; returns false to quit

bool product::more()
{
	char reply='\0';
	cin >> reply;
	cin.ignore(100,'\n');
	if (tolower(reply)=='y')
		return true;
	return false;
}



//**************
//			END.
//**************
