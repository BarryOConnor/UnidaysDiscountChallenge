/*
Submission by : Barry O’Connor
Email : me@barryoconnor.co.uk
Mobile : 07860497508
*/

#pragma once
#include <vector>
#include <string>

// Enumerated type which is human readable, expandable and easy to code for when it comes to adding new deals
enum discountTypes : int { NONE, TWO_FOR, THREE_FOR, BOGOF, THREE_FOR_TWO, UNCODED };





struct basketItem {
	/*==================================
	basketItem is a structure which holds information relating to a type of item in the basket.

		intName = the name of the item
		count = how many of the item are in the basket
	==================================*/

	char itemName;
	int count;

	//constructor for the struct, requires an item name as parameter - should already know what you're putting in the basket
	basketItem(char _itemName) {
		itemName = _itemName;
		count = 1; //if you're putting an item in the basket, there must be at least 1 of it
	}

	//destructor. No specific action needed
	~basketItem() {};
};





struct CheckoutTotals {
	/*==================================
	structure for returning checkout information

		Total = calculated total price for items in the basket
		DeliveryCharge = delivery charge incurred for the current order
	==================================*/
	float Total;  //Order total
	float DeliveryCharge;  //Delivery charge for the order

	//constructor - no parameters needed
	CheckoutTotals() {
		//set values to 0.00 by default when the struct is created
		Total = 0.00;
		DeliveryCharge = 0.00;
	};

	//destructor. No specific action needed
	~CheckoutTotals() {};
};





struct pricingRule {
	/*==================================
	structure to hold pricing rules

		itemName = name of the item
		itemPrice = price of the item
		discountType = type of discount the item qualifies for (one from the discountTypes enumerated list
		discountPrice = price to apply for specific discount (2 for £XX.00, 3 for £XX.XX)
	==================================*/
	char itemName;
	float itemPrice;
	discountTypes discountType;
	float discountPrice;  

	//constructor for the struct, requires 4 parameters which match the above properties
	pricingRule(char _itemName, float _itemPrice, discountTypes _discountType, float _discountPrice = 0.00) {
		//do some sanity checks before doing anything with the data
		if (_itemPrice < 0.00) {
			//price is negative - store would owe money to customer as well as the item
			printf("Warning: itemPrice parameter should not be a negative number \n");
			exit(1);
		}
		if (_discountPrice < 0.00) {
			//discountPrice is negative - store would owe money to customer as well as the item
			printf("Warning: discountPrice parameter should not be a negative number \n");
			exit(1);
		}
		else if (_discountPrice == 0.00 && (_discountType == TWO_FOR || _discountType == THREE_FOR)) {
			//price is 0.00 when the discount is 2 for XX or 3 for XX - store would be giving items away for free
			printf("Error: this discount type requires a price in the fourth parameter \n");
			exit(1);
		};

		//checks passed, copy the parameters to the object properties
		itemName = _itemName;
		itemPrice = _itemPrice;
		discountType = _discountType;
		discountPrice = _discountPrice;  
		
	};

	
	~pricingRule() {}; // default destructor. No specific action needed
};





class UnidaysDiscountChallenge{
	/*==================================
	UnidaysDiscountChallenge class

		pricingRules = vector to contain all current Pricing Rules
		basket = vector to contain items the customer wants to buy
	==================================*/
	std::vector<pricingRule> pricingRules;
	std::vector<basketItem> basket;

	pricingRule* itemExists(std::vector<pricingRule>& _pricingRules, char _item); //function to check if a Pricing Rule exists for a specific item 
	basketItem* itemExists(std::vector<basketItem>& _basketItems, char _item); //function to check if a basket item already exists in the basket

public:
	bool AddToBasket(char _item); //function to add an item to the basket
	CheckoutTotals CalculateTotalPrice(); //function to calculate the total for the basket and the shipping due	
	
	UnidaysDiscountChallenge(const std::vector<pricingRule>& _pricingRules); //constructor for the class, requires a vector of pricingrules
	~UnidaysDiscountChallenge() {}; // default destructor. No specific action needed
};





/*==================================  TEST CLASS  ==================================*/
class testclass {
public:
	//test function, pass a string containing the test basket, expected Total and Delivery and the function prints a comparison and returns true or false 
	bool doTest(std::string _testBasket, float _expectedPrice, float _expectedDelivery); 
	
	testclass(); //constructor for the class, no requirements
	~testclass() {}; // default destructor. No specific action needed
};



