
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
// 		ALGORITHM:
//
//	:: The product inventory for this program consists of a unified format for each item:
//		+ Name
//		+ Quantity
//		+ Wholesale cost
//		+ Price (MSRP)
//		+ Vendor name
// 	:: A small function welcomes the players to the program.
// 	:: A menu function loops, asking the user to make a selection until the user is done.
//		+ The menu function automatically loads two external files:
//			- One file called "inventory.txt" holds the contents of the inventory.
//			- Another file called "balancesheet.txt" holds the company's running budget.
// 		+ If there are no files, the company begins with a budget of $10,000 and an
//		  empty inventory.
//		+ The user may choose from several options: view inventory, view budget,
//		  add to existing inventory, fill a customer order, create a new item,
//		  and exit.
//			- "Display" will show each item in the inventory.
//			- "Budget" will display the balance that has been loaded or newly created.
//			- "Add Inventory" will add quantities of preexisting items and subtract
//			  the appropriate amount from the balance.
//			- "Fill Order" will subtract quantities of preexisting items and add the 
//			  appropriate amount to the balance.
//			- "Read Each" allows the user to create a new item in the inventory, up to 
//			  fifteen distinctive items.
//	:: When the user exits, the files are saved.
//	:: A farewell greeting is displayed.
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

void welcome();
bool load(char file[], product & inventory);
bool loadBudget(char file[], float & budget);
void manager(product item);
bool more();
int menu();
void goodbye();
bool save(char file[], product & inventory);
bool save(char file[], float & budget);




int main()
{
	welcome();

	// create a product item to start:
	product inventory;
	// and send it to the manager function:
	manager(inventory);

	goodbye();
	return 0;
}



//*************************************
//								MANAGER
//
//	Loads the external files, offers the
// 		user options and executes the 
//		appropriate action, and saves the
//		data upon exit.

void manager(product inventory)
{
// -- SETTING UP SOME VARIABLES:
	// 'whichMenu' returns the user's selection of menu items.
	int whichMenu=0;
	// The budget starts at $10,000 and changes over the course of the program.
	float budget=10000;
	// The file which contains all of the inventory data:
	char filename[]="inventory.txt";
	// The tiny file which contains the running budget for the company:
	char balancesheet[]="balancesheet.txt";

// -- LOAD THE FILES:
	// Load the inventory file. If it cannot be loaded, display a message.
	if (!load(filename, inventory))
	{
		cout << "\n\n[UH OH]"
			<< "\n\tThe inventory file could not be found -- starting a new one."
			<< "\n\tConsider creating some new items." 
			<< "\n\t(I hear ergonomic typing mats are really hot right now.)";
	}
	// Load the budget file. If it cannot be loaded, try to calculate it from 
	//		the inventory. If it cannot be calculated, budget remains $10,000.
	if (!loadBudget(balancesheet, budget))
	{
		cout << "\n\n[UH OH]"
			<< "\n\tNo prior balancesheet found, so you've got"
			<< "\n\ta new balance of $10,000!";
	}


// -- MENU:
//		Display and get a selection from the 
//		user until they are done.
	do
	{	
	// -- Display the menu and get a selection:
		whichMenu=menu();

	// -- DISPLAY ALL MEMBER ITEMS
		if (whichMenu==1)
			inventory.displayAll();

	// -- DISPLAY THE BUDGET
		if (whichMenu==2)
			cout << "The present budget is $" << budget << "." << endl;

	// -- ORDER STOCK
		if (whichMenu==3)
			inventory.addInventory(budget);

	// -- FILL A CUSTOMER ORDER
		if (whichMenu==4)
			inventory.fillOrder(budget);

	// -- CREATE A NEW ITEM:
		if (whichMenu==5)
			inventory.createNew(budget);

	}while (whichMenu);

	save(filename, inventory);
	save(balancesheet, budget);
}



//******************************
//			LOAD INVENTORY ITEMS
//
//	Reads in product data from the 
//		external file.

bool load(char file[], product & inventory)

{
	cout << "\n\n[--LOADING INVENTORY--]"; 

	ifstream read;
	read.open(file);
	if (!read)
		return false;

	inventory.load(read);

	read.close();
	cout << "\n\tInventory load was successful." << endl;	
	return true;
}



//***********************************
//			LOAD EXISTING $$$ BUDGET
//
//	Reads in the tiny budget file.

bool loadBudget(char file[], float & budget)
{
	ifstream read;
	read.open(file);

// check to ensure we can connect to the file:
	if (!read)
		return false;

	read >> budget;
	read.ignore();
	read.close();

	return true;
}



//*******************
//			WELCOME!

void welcome()
{
	cout << "\n[--INVENTORY MANAGER--]"
		<< "\n\n\tInventory management and budget tracking system:"
		<< "\n\tView budget, add new items, invoice fulfillment, reorder"
		<< "\n\tstock, and add new products to your system."
		<< "\n\tMake sure to save your changes by selecting 'EXIT' from the menu";

}



//**********************************
//								MENU
//
//	Displays program options to user 
// 	and returns a selection to main().

int menu()
{
	char reply='\0';
	do
	{
		cout << "\n\n[--MAIN MENU--]" 
			<< "\tPlease select from the following options:"
			<< "\n[1] DISPLAY\tview entire inventory"
			<< "\n[2] BUDGET\tview current budget"
			<< "\n[3] ADD\t\tincrease quantities of existing items"
			<< "\n[4] FILL\tfill a customer order from the inventory"
			<< "\n[5] CREATE\ta new product"
			<< "\n[X] EXIT\tto save your changes"
			<< endl;
		cin >> reply;
		cin.ignore(100,'\n');
		reply=tolower(reply);
		// DISPLAY
		if (reply=='1' || reply=='d')
			return 1;
		// BUDGET
		if (reply=='2' || reply=='b')
			return 2;
		// ADD
		if (reply=='3' || reply=='a')
			return 3; 
		// FILL
		if (reply=='4' || reply=='f')
			return 4;
		// CREATE
		if (reply=='5' || reply=='c')
			return 5;
		// EXIT
		if (reply=='6' || reply=='x' || reply=='e')	
			return 0;	
		else
			reply='r';
			// If the user does not make a valid menu selection,
			// 	'reply' is given the value 'r'.
			// 	'r' selected arbitrarily as a letter that
			// 	does not appear in any of the menu options
	}while (reply=='r');
}



//*****************************
//			SAVE INVENTORY FILE
//
//	Opens iostream; writes to file

bool save(char file[], product & inventory)
{
	ofstream write;
	write.open(file);

	if (!write)
	{	
		cout << "\t[UH OH]"
			<< "\n\tWe blew it -- the file could not be saved." << endl;
		return false;
	}
	else 
	{
		inventory.save(write);
		write.close();
		write.clear();
	}
	return true;
}



//**************************
//			SAVE BUDGET FILE
//
//	Opens iostream; writes to file

bool save(char file[], float & budget)
{
	ofstream write;
	write.open(file);

	if (!write)
		return false;
	else 
	{
		write << budget;
		write.close();
		write.clear();
	}
	return true;
}



//*************************************
//						ENTER MORE DATA
//							OR CONTINUE?
//
// 	More() returns true to continue the
// 		loop; returns false to quit

bool more()
{
	char reply='\0';
	cin >> reply;
	cin.ignore(100,'\n');
	if (tolower(reply)=='y')
		return true;
	return false;
}



//******************************
//						GOODBYE!
//
// A brief farewell, dear user.

void goodbye()
{
	cout << "\n[--SESSION COMPLETE--]";
	cin.get();
}




//*****************
// SMILE. YOU DONE!
//*****************
