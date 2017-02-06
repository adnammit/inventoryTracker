
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
// 		CLASS INTERFACE AND NODE STRUCT DECLARATIONS
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


#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
using namespace std;



//******************
// NODE DECLARATION:
//******************

struct node
{
// -- VARIABLES:
	char*name;
	int quantity;
	float cost;
	float msrp;
	char*vendor;
	node*next;

// -- FUNCTION PROTOTYPES:
	node();
	~node();
	void loadEach(ifstream & read);
	void displayEach();
	void increaseItem(float & budget);
	void createEach(float & budget);
	void upperCase(char *word);
	void saveEach(ofstream & write);
	void fillOrder(float & budget);
};



//***************
// PRODUCT CLASS:
//***************

class product
{
public:
	product();
	~product();
	bool load(ifstream & read);
	void displayAll();
	void addInventory(float & budget);
	void fillOrder(float & budget);
	bool createNew(float & budget);
	bool more();
	bool save(ofstream & write);

private:
	node*head;		
};




//**************
//			END.
//**************
