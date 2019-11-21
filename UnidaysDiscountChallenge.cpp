/*
Submission by : Barry O’Connor
Email : me@barryoconnor.co.uk
Mobile : 07860497508
*/

#include <cstdio>
#include <cctype>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>

#include "UnidaysDiscountChallenge.h"


pricingRule* UnidaysDiscountChallenge::itemExists(std::vector<pricingRule>& _pricingRules, char _itemName) {
	/*==================================
	Overloaded function to check if a rule exists for the itemName passed as a parameter
	parameters:
		_pricingRules = a vector of pricingRules
		_itemName = the itemName you want to check for existance
	returns:
		either return the matching rule or a NULL when no rule matches
	==================================*/


	//STL iterator using a predicate function to find the item in the vector
	std::vector<pricingRule>::iterator ruleResult = std::find_if(_pricingRules.begin(), _pricingRules.end(), [_itemName](pricingRule const& currRule) { return currRule.itemName == _itemName; });

	if (ruleResult == _pricingRules.end()) {
		//iterator has reached the end of the vector and not found a match so return a null
		return NULL;
	}
	else {
		//return the item the iterator is pointing to (address of pointer)
		return &(*ruleResult);
	}
}





basketItem* UnidaysDiscountChallenge::itemExists(std::vector<basketItem>& _basketItems, char _item) {
	/*==================================
	Overloaded function to check if a basketItem exists for the itemName passed as a parameter
	parameters:
		_basketItems = a vector of pricingRules
		_itemName = the itemName you want to check for existance
	returns:
		either return the matching rule or a NULL when no rule matches
	==================================*/

	//STL iterator using a predicate function to find the item in the vector
	std::vector<basketItem>::iterator basketResult = std::find_if(_basketItems.begin(), _basketItems.end(), [_item](basketItem const& currItem) { return currItem.itemName == _item; });

	if (basketResult == _basketItems.end()) {
		//iterator has reached the end of the vector and not found a match so return a null
		return NULL;
	}
	else {
		//return the item the iterator is pointing to (address of pointer)
		return &(*basketResult);
	}
}




bool UnidaysDiscountChallenge::AddToBasket(char _itemName) {
	/*==================================
	method to add an item to the basket
	parameters:
		_itemName = name of the item to add to the basket
	==================================*/

	bool errorEncountered = false;  //bool to hold the error status

	//capitalise the letter for ease of comparison and use and check entered item is a letter
	_itemName = toupper(_itemName);
	if (_itemName < 'A' && _itemName > 'Z') {
		printf("Error: Item %c should be a character between A and Z\n", _itemName);
		errorEncountered = true;
	}
	
	//sanity check to see if the item has a corresponding priceRule
	pricingRule* ruleResult = itemExists(pricingRules, _itemName);
	if (!ruleResult) {
		//no pricing rule found, create error message
		printf("Error: Item %c does not have a pricing rule assigned to it, unable to add it to the basket\n",_itemName);
		errorEncountered = true;
	}
	
	if (!errorEncountered) {
		//check for the existance of the item in the basket
		basketItem* basketResult = itemExists(basket, _itemName);
		if (basketResult) {
			//item exists so just increase the counter
			basketResult->count++;
			return true;
		}
		else {
			//item does not yet exist, so create it
			basket.push_back({ _itemName });
			return true;
		}
	}
	else {
		//error was encountered, don't add and return false
		return false;
	}	
}





CheckoutTotals UnidaysDiscountChallenge::CalculateTotalPrice() {
	/*==================================
	method to calculate price and delivery for the current basket contents
	
	==================================*/
	CheckoutTotals checkoutResult; //CheckoutTotals struct to hold the results
	
	// the constructor for the CheckoutTotoals struct defaults values to 0.00 so we don't need to check for an empty basket, the values will be correct for that by default

	//if the basket contains something
	if (basket.size() > 0) {
		/*-----
		Iterate through the basket and check each basket item against the corresponding rule.
		We already checked there IS a matching rule so no need to repeat that process
		Also  unless the customer puts one of each item in their basket, this will likely
		be quicker than checking if an item exists for every rule
		-----*/

		for (std::vector<basketItem>::iterator currItem = basket.begin(); currItem != basket.end(); ++currItem) {
			
			//get the pricing rule that applies to the current item
			pricingRule* ruleResult = itemExists(pricingRules, currItem->itemName);

			if (ruleResult) {
				//apply the correct price per item depending on the discount type
				switch (ruleResult->discountType) {
					case NONE:
						//NONE = multiply the number of items by the price per item
						checkoutResult.Total += currItem->count * ruleResult->itemPrice;
						break;
					case TWO_FOR:
						//TWO_FOR = for every 2, cost is equal to the discounted price. Add to that any remainder at the unit price
						checkoutResult.Total += (((currItem->count / 2) * ruleResult->discountPrice) + ((currItem->count % 2) * ruleResult->itemPrice));
						break;
					case THREE_FOR:
						//THREE_FOR = for every 3, cost is equal to the discounted price. Add to that any remainder at the unit price
						checkoutResult.Total += (((currItem->count / 3) * ruleResult->discountPrice) + ((currItem->count % 3) * ruleResult->itemPrice)) ;
						break;
					case BOGOF:
						//BOGOF = for every 2, cost is equal to 1. Add to that any remainder
						checkoutResult.Total += ((currItem->count / 2) + (currItem->count % 2)) * ruleResult->itemPrice;
						break;
					case THREE_FOR_TWO:
						//THREE_FOR_TWO = for every 3, cost is equal to 2 times the unit price. Add to that any remainder at the unit price
						checkoutResult.Total += (((currItem->count / 3) * (ruleResult->itemPrice * 2)) + ((currItem->count % 3) * ruleResult->itemPrice));
						break;
					default:
						//sanity check if none of the above match, assume price is no discount
						checkoutResult.Total += currItem->count * ruleResult->itemPrice;
						break;
				}
			}
		}

		/* ----- Delivery charge  ----- */
		
		//set the value to 7.00 as default
		checkoutResult.DeliveryCharge = 7.00;
		if (checkoutResult.Total >= 50.00) {
			//delivery is free so for over 50 so set the delivery charge to 0.00
			checkoutResult.DeliveryCharge = 0.00;
		}

	}

	return checkoutResult;
}




UnidaysDiscountChallenge::UnidaysDiscountChallenge(const std::vector<pricingRule>& _pricingRules) {
	/*==================================
	allows for the initialisation of the class object with a pre-defined set of price rules in a vector
	this can be created in any way the programmer wants before passing to this function

	_pricingRules = vector containing the Pricing Rules to be applied - passed by reference to save memory
	==================================*/

	pricingRules = _pricingRules;
}





/*==================================  TEST CLASS  ==================================*/

bool testclass::doTest(std::string _testBasket, float _expectedPrice, float _expectedDelivery) {
	/*==================================
	Method to test if a given basket produces an expected Total and Delivery result
	parameters:
		_testBasket = a string representing the contents of the basket
		_expectedPrice = the Total Price the basket is expected to cost
		_expectedDelivery = the Delivery Price the basket is expected to incur
	returns:
		true if the prices match actual results, false if the results differ from the expected
	==================================*/

	//barebones implementation of the UnidaysDiscountChallenge class for testing purposes - see main() for full breakdown
	CheckoutTotals result;
	UnidaysDiscountChallenge example({ { 'A', 8.00, NONE },{ 'B', 12.00, TWO_FOR, 20.00 },{ 'C', 4.00, THREE_FOR, 10.00 },{ 'D', 7.00, BOGOF },{ 'E', 5.00, THREE_FOR_TWO } });

	//split the sting into individual items and add to the class's built in basket
	for (int i = 0; i < _testBasket.size(); i++) {
		example.AddToBasket(_testBasket[i]);
	}

	//return the results of the price calculation
	result = example.CalculateTotalPrice();
	//print out the figures side by side for verification
	printf("basket:%s\n", _testBasket.c_str());
	printf("Total: Expected= %4.2f  Actual= %4.2f\n", _expectedPrice, result.Total);
	printf("Delivery: Expected= %4.2f  Actual= %4.2f\n", _expectedDelivery, result.DeliveryCharge);

	//check values and return result
	if (result.Total == _expectedPrice && result.DeliveryCharge == _expectedDelivery) {
		printf("--- Values Match ---\n\n");
		return true;
	}
	else {
		printf("--- Values Do Not Match ---\n\n");
		return false;
	}

}




testclass::testclass() {}